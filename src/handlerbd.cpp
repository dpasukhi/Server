#include "include/handlerbd.h"

HandlerBD::HandlerBD(QObject *parent) : QObject(parent)
{

}

HandlerBD::~HandlerBD()
{

}

void HandlerBD::officeTable_insert(int id_office, QString office){
  QSqlQuery a_query;
  QString str_insert = "INSERT INTO office_table(id_office, office) VALUES (%1, '%2');";
  QString str = str_insert.arg(id_office).arg(office);

  if (!a_query.exec(str)) {
    qDebug() << "Кажется данные не вставляются, ты - олень!";
  }
}

void HandlerBD::officeTable_update(int id_office, QString office){
  officeTable_delete(id_office);
  officeTable_insert(id_office, office);
}

QVector<QMap<QString, QString> > HandlerBD::officeTable_getAll(){
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM office_table")) {
    qDebug() << "Даже селект не получается, я пас.";
  }

  QVector<QMap<QString, QString>> result;
  while (a_query.next()) {
    QMap<QString, QString> map;
    map.insert("id_office", a_query.value(0).toString());
    map.insert("office", a_query.value(1).toString());

    result.push_back(map);
  }

  return result;
}

void HandlerBD::officeTable_delete(int id_office){
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM office_table WHERE id_office=%1;";
  QString str = str_delete.arg(id_office);

  if (!a_query.exec(str)) {
    qDebug() << "Кажется данные не удаляются, ты - олень!";
  }
}

void HandlerBD::productsTable_insert(int id, QString name, float cost)
{
  QSqlQuery a_query;
  QString str_insert = "INSERT INTO products_table(id_product, pizza_name, cost) VALUES (%1, '%2', %3);";
  QString str = str_insert.arg(id).arg(name).arg(cost);

  if (!a_query.exec(str)) {
    qDebug() << "Кажется данные не вставляются, ты - олень!";
  }
}

void HandlerBD::productsTable_update(int id, QString new_name, float new_cost)
{
  productsTable_delete(id);
  productsTable_insert(id, new_name, new_cost);
}

QVector<QMap<QString, QString>> HandlerBD::productsTable_getAll()
{
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM products_table")) {
    qDebug() << "Даже селект не получается, я пас.";
  }

  QVector<QMap<QString, QString>> result;
  while (a_query.next()) {
    QMap<QString, QString> map;
    map.insert("id_product", a_query.value(0).toString());
    map.insert("pizza_name", a_query.value(1).toString());
    map.insert("cost", a_query.value(2).toString());

    result.push_back(map);
  }

  return result;
}

void HandlerBD::productsTable_delete(int id)
{
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM products_table WHERE id_product=%1;";
  QString str = str_delete.arg(id);

  if (!a_query.exec(str)) {
    qDebug() << "Кажется данные не удаляются, ты - олень!";
  }
}
