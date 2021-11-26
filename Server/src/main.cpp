/**
  @file

*/

#include <QCoreApplication>
#include <QDir>
#include "./include/global.h"
#include <httplistener.h>
#include "./include/requestmapper.h"
#include "./include/dbworker.h"

using namespace stefanfrings;

/** Search the configuration file */
QString searchConfigFile()
{
    QString binDir=QCoreApplication::applicationDirPath();
    QString fileName("Server.ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"Server/etc");
    searchList.append(binDir+"/../Server/etc");
    searchList.append(binDir+"/../Server/etc"); // for development with shadow build (Linux)
    searchList.append(binDir+"/../../Server/etc"); // for development with shadow build (Windows)
    searchList.append(binDir+"/../../Server/Server/etc"); // for development with shadow build (Linux)
    searchList.append(binDir+"/../../../Server/Server/etc"); // for development with shadow build (Windows)
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");
    searchList.append(QDir::rootPath()+"Server/etc/opt");
    searchList.append(QDir::rootPath()+"Server/etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Cannot find config file %s",qPrintable(fileName));
    return nullptr;
}


/**
  Entry point of the program.
*/
int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);
    app.setApplicationName("Server");

    // Find the configuration file
    QString configFileName=searchConfigFile();

    // Configure logging into a file
    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    logSettings->beginGroup("logging");
    FileLogger* logger=new FileLogger(logSettings,10000,&app);
    logger->installMsgHandler();

    // Configure template loader and cache
    QSettings* templateSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    templateSettings->beginGroup("templates");
    templateCache=new TemplateCache(templateSettings,&app);

    // Configure session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    sessionSettings->beginGroup("sessions");
    sessionStore=new HttpSessionStore(sessionSettings,&app);

    // Configure static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    fileSettings->beginGroup("docroot");
    staticFileController=new StaticFileController(fileSettings,&app);

    // Configure and start the TCP listener
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings,new RequestMapper(&app),&app);


    // Configure static Database connection
    QSettings* databaseSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    databaseSettings->beginGroup("database");
    db=new dbworker(databaseSettings,&app);
    db->connect();
    db->disconnect();

    qWarning("Application has started");
    app.exec();
    qWarning("Application has stopped");
}
