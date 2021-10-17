#ifndef HANDLERBD_H
#define HANDLERBD_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

class HandlerBD : public QObject
{
  Q_OBJECT
public:
  explicit HandlerBD(QObject *parent = nullptr);
  ~HandlerBD();

  void officeTable_insert(int id_office, QString office);
  void officeTable_update(int id_office, QString office);
  QVector<QMap<QString, QString>> officeTable_getAll();
  void officeTable_delete(int id_office);

  void productsTable_insert(int id, QString name, float cost);
  void productsTable_update(int id, QString new_name, float new_cost);
  QVector<QMap<QString, QString>> productsTable_getAll();
  void productsTable_delete(int id);
};

#endif // HANDLERBD_H
