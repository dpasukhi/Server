#include <QCoreApplication>
#include <QDir>
#include "global.h"
#include <httplistener.h>
#include "requestmapper.h"
#include "dbworker.h"

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

//  HandlerBD* myWorker = db->GetWorker();

//  // Offices
//  HandlerBD::locationTable aLoc1 { 1, "ул. Литвинова, 74, корп. 30, Нижний Новгород"};
//  HandlerBD::locationTable aLoc2 { 2, "ул. Звездинка, 11, корп. 1, Нижний Новгород"};
//  HandlerBD::locationTable aLoc3 { 3, "Керченская ул., 26, Нижний Новгород"};
//  HandlerBD::locationTable aLoc4 { 4, "ул. Чаадаева, 1АЧ, Нижний Новгород"};
//  myWorker->locationTable_insert(aLoc1);
//  myWorker->locationTable_insert(aLoc2);
//  myWorker->locationTable_insert(aLoc3);
//  myWorker->locationTable_insert(aLoc4);

//  //********** Deliveryman information table **********//
//  HandlerBD::deliverymanTable aDel1 {1, "Name 1", "Name 1", "Name 1", 1, "8878888888", "admin1", "admin1" };
//  HandlerBD::deliverymanTable aDel2 {2, "Name 2", "Name 2", "Name 2", 1, "88888088888", "admin2", "admin2" };
//  HandlerBD::deliverymanTable aDel3 {3, "Name 3", "Name 3", "Name 3", 1, "88888088888", "admin3", "admin3" };
//  HandlerBD::deliverymanTable aDel4 {4, "Name 4", "Name 4", "Name 4", 1, "88088888888", "admin4", "admin4" };
//  myWorker->deliverymanTable_insert(aDel1);
//  myWorker->deliverymanTable_insert(aDel2);
//  myWorker->deliverymanTable_insert(aDel3);
//  myWorker->deliverymanTable_insert(aDel4);

//  //********** Product table (pizzas) **********//
//  HandlerBD::productsTable aPizza1 {1, "Деревенское Барбекю", "Сезон барбекю! Ароматная свинина, пикантная пепперони, шампиньоны, лук, зеленый перец с сыром Моцарелла и соусом барбекю", 499};
//  HandlerBD::productsTable aPizza2 {2, "Чикен Пармеджано", "Нежный вкус: сочное куриное филе, шампиньоны, сыр Чеддер и сыр Моцарелла, орегано, соус Пармеджано", 499};
//  HandlerBD::productsTable aPizza3 {3, "Пепперони с медом и халапеньо", "The Bee Sting - пицца с пепперони, цветочным медом, острым халапеньо, сыром Моцарелла и фирменным томатным соусом", 499};
//  HandlerBD::productsTable aPizza4 {4, "Хот Пепперони", "Еще горячее! Американская классика с пикантной пепперони, Моцареллой и фирменным томатным соусом с острым халапеньо", 499};
//  HandlerBD::productsTable aPizza5 {5, "Ветчина и бекон", "Соус 1000 островов, ароматная ветчина, хрустящий бекон, зеленый перец, шампиньоны, сыр Моцарелла и смесь итальянских трав", 499};
//  HandlerBD::productsTable aPizza6 {6, "Деревенское Барбекю", "Сезон барбекю! Ароматная свинина, пикантная пепперони, шампиньоны, лук, зеленый перец с сыром Моцарелла и соусом барбекю", 499};
//  HandlerBD::productsTable aPizza7 {7, "Чикен Пармеджано", "Нежный вкус: сочное куриное филе, шампиньоны, сыр Чеддер и сыр Моцарелла, орегано, соус Пармеджано", 499};
//  HandlerBD::productsTable aPizza8 {8, "Пепперони с медом и халапеньо", "The Bee Sting - пицца с пепперони, цветочным медом, острым халапеньо, сыром Моцарелла и фирменным томатным соусом", 499};
//  HandlerBD::productsTable aPizza9 {9, "Хот Пепперони", "Еще горячее! Американская классика с пикантной пепперони, Моцареллой и фирменным томатным соусом с острым халапеньо", 499};
//  HandlerBD::productsTable aPizza10 {10, "Ветчина и бекон", "Соус 1000 островов, ароматная ветчина, хрустящий бекон, зеленый перец, шампиньоны, сыр Моцарелла и смесь итальянских трав", 499};
//  myWorker->productsTable_insert(aPizza1);
//  myWorker->productsTable_insert(aPizza2);
//  myWorker->productsTable_insert(aPizza3);
//  myWorker->productsTable_insert(aPizza4);
//  myWorker->productsTable_insert(aPizza5);
//  myWorker->productsTable_insert(aPizza6);
//  myWorker->productsTable_insert(aPizza7);
//  myWorker->productsTable_insert(aPizza8);
//  myWorker->productsTable_insert(aPizza9);
//  myWorker->productsTable_insert(aPizza10);

//  //********** Table for states **********//
//  HandlerBD::stateTable aStat1 {1, "0"};
//  HandlerBD::stateTable aStat2 {2, "1"};
//  HandlerBD::stateTable aStat3 {3, "2"};
//  myWorker->stateTable_insert(aStat1);
//  myWorker->stateTable_insert(aStat2);
//  myWorker->stateTable_insert(aStat3);



  qWarning("Application has started");
  app.exec();
  qWarning("Application has stopped");
}
