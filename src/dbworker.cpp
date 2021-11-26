#include "./include/dbworker.h"

dbworker::dbworker(QObject *parent)
  : QObject{parent}
{ }

dbworker::~dbworker()
{ }

void dbworker::connect() {
  if (db.open()) {
    qDebug() << "The connection to the database has already been established!";
    return;
  }

  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("my_db.sqlite");

  if (!db.open()) {
    qDebug() << "Failed to establish a connection to the database!";
  }

  worker.setWorker(&db);
}

void dbworker::disconnect() {
  if (!db.open()) {
    return;
  }

  db.close();
}
