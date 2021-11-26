#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QtSql>
#include "handlerbd.h"
#include <QSettings>

class dbworker : public QObject
{
  Q_OBJECT
public:
  explicit dbworker(const QSettings* settings, QObject *parent = nullptr);
  ~dbworker();
  void connect();
  void disconnect();

private:
  QSqlDatabase db;
  HandlerBD worker;
  const QSettings* settings;
};

#endif // DBWORKER_H
