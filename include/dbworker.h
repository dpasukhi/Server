#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QtSql>
#include "handlerbd.h"

class dbworker : public QObject
{
  Q_OBJECT
public:
  explicit dbworker(QObject *parent = nullptr);
  ~dbworker();
  void connect();
  void disconnect();

private:
  QSqlDatabase db;
  HandlerBD worker;
};

#endif // DBWORKER_H
