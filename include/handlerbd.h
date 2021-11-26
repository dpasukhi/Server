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
private:
  QSqlDatabase* db;
public:
  explicit HandlerBD(QObject *parent = nullptr);
  void setWorker(QSqlDatabase* db) { this->db = db; };
  bool checkTable(const QString nameTable);
  bool checkUser(const QString nameTable, const QString login, const QString password);
  ~HandlerBD();

  //********** Table for linking an order to products **********//
  struct orderProductsTable {
    int id = -1;
    int id_order = -1;
    int id_product = -1;
  };
  void orderProductsTable_create();
  void orderProductsTable_insert(const orderProductsTable& orderProductsTable);
  void orderProductsTable_update(const orderProductsTable& orderProductsTable);
  QVector<orderProductsTable> orderProductsTable_getAll();
  void orderProductsTable_delete(const orderProductsTable& orderProductsTable);
  //************************************************************//

  //********** Table linking an order with a customer, a delivery person and an office **********//
  struct clientDeliverymanTable {
    int id_order = -1;
    int id_client = -1;
    int id_deliver = -1;
    int id_office = -1;
  };
  void clientDeliverymanTable_create();
  void clientDeliverymanTable_insert(const clientDeliverymanTable& clientDeliverymanTable);
  void clientDeliverymanTable_update(const clientDeliverymanTable& clientDeliverymanTable);
  QVector<clientDeliverymanTable> clientDeliverymanTable_getAll();
  void clientDeliverymanTable_delete(const clientDeliverymanTable& clientDeliverymanTable);
  //*********************************************************************************************//

  //********** Deliveryman information table **********//
  struct deliverymanTable {
    int id_deliver = -1;
    QString last_name = "";
    QString first_name = "";
    QString middle_name = "";
    int id_office = -1;
    QString phone = "";
    QString email = "";
    QString pass = "";
  };
  void deliverymanTable_create();
  void deliverymanTable_insert(const deliverymanTable& clientDeliverymanTable);
  void deliverymanTable_update(const deliverymanTable& clientDeliverymanTable);
  QVector<deliverymanTable> deliverymanTable_getAll();
  bool checkDeliveryman(const QString login, const QString password);
  void deliverymanTable_delete(const deliverymanTable& clientDeliverymanTable);
  //**********************************************//

  //********** Client information table **********//
  struct clientTable {
    int id_client = -1;
    QString email = "";
    QString pass = "";
    QString last_name = "";
    QString first_name = "";
    QString middle_name = "";
    QString phone = "";
  };
  void clientTable_create();
  void clientTable_insert(const clientTable& clientTable);
  void clientTable_update(const clientTable& clientTable);
  QVector<clientTable> clientTable_getAll();
  bool checkClient(const QString login, const QString password);
  void clientTable_delete(const clientTable& clientTable);
  //**********************************************//

  //********** Delivery table **********//
  struct deliveryTable {
    int id = -1;
    int id_deliver = -1;
    int id_condition = -1;
    int id_office = -1;
    QString time = "";
  };
  void deliveryTable_create();
  void deliveryTable_insert(const deliveryTable& deliveryTable);
  void deliveryTable_update(const deliveryTable& deliveryTable);
  QVector<deliveryTable> deliveryTable_getAll();
  void deliveryTable_delete(const deliveryTable& deliveryTable);
  //************************************//

  //********** Table for states **********//
  struct stateTable {
    int id_condition = -1;
    QString condition = "";
  };
  void stateTable_create();
  void stateTable_insert(const stateTable& stateTable);
  void stateTable_update(const stateTable& stateTable);
  QVector<stateTable> stateTable_getAll();
  void stateTable_delete(const stateTable& stateTable);
  //*************************************//

  //********** Location table **********//
  struct locationTable {
    int id_office = -1;
    QString office = "";
  };
  void locationTable_create();
  void locationTable_insert(const locationTable& locationTable);
  void locationTable_update(const locationTable& locationTable);
  QVector<locationTable> locationTable_getAll();
  void locationTable_delete(const locationTable& locationTable);
  //************************************//

  //********** Product table (pizzas) **********//
  struct productsTable {
    int id = -1;
    QString pizza_name = "";
    QString description = "";
    float cost = -1.f;
  };
  void productsTable_create();
  void productsTable_insert(const productsTable& productsTable);
  void productsTable_update(const productsTable& productsTable);
  QVector<productsTable> productsTable_getAll();
  void productsTable_delete(const productsTable& productsTable);
  //********************************************//


};

#endif // HANDLERBD_H
