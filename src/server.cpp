#include <server.h>

#include <QtSql>


Server::Server(QObject *parent) : QObject(parent)
{
  QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
  dbase.setDatabaseName("my_db.sqlite");
  if (!dbase.open())
  {
    qDebug() << "Error: creation of database crashed";
  }
}
