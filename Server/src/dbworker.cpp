#include <dbworker.h>

dbworker::dbworker(const QSettings* settings, QObject *parent)
  : QObject{parent}
{
  Q_ASSERT(settings!=nullptr);
  this->settings=settings;
  qDebug("dbworker: created");
}

dbworker::~dbworker()
{
  qDebug("dbworker: destroyed");
}

void dbworker::connect() {
  if (db.open()) {
    qDebug() << "The connection to the database has already been established!";
    return;
  }

  db = QSqlDatabase::addDatabase("QSQLITE");

  QString path = settings->value("path").toString();
  db.setDatabaseName(path);
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
