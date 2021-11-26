#include "include/handlerbd.h"

HandlerBD::HandlerBD(QObject *parent) : QObject(parent)
{

}

HandlerBD::~HandlerBD()
{

}

bool HandlerBD::checkTable(const QString nameTable) {
  static QStringList List;
  if (List.isEmpty())
    List = db->tables();
  return List.contains(nameTable);
}

bool HandlerBD::checkUser(const QString nameTable, const QString login, const QString password) {
  if (!checkTable("deliveryman_table"))
    return false;

  QSqlQuery query;
  QString str = "SELECT * FROM %1 WHERE email=%2;";
  QString newStr = str.arg(nameTable, login);
  if (!query.exec(newStr)) {
    qDebug() << "Failed to get data!";
  }

  if (query.next()) {
    QString pass = query.value(8).toString();
    return pass == password;
  }

  return false;
}

//********** Table for linking an order to products **********//
void HandlerBD::orderProductsTable_create() {
  QSqlQuery query;
  QString str = "CREATE TABLE orderProducts_table ("
                "id integer PRIMARY KEY NOT NULL, "
                "id_order integer NOT NULL, "
                "id_product integer NOT NULL"
                ");";

  if (!query.exec(str)) {
    qDebug() << "Failed to create a table!";
  }
}

void HandlerBD::orderProductsTable_insert(const orderProductsTable& orderProductsTable) {
  if (!checkTable("orderProducts_table"))
    orderProductsTable_create();

  QSqlQuery a_query;
  QString str_insert = "INSERT INTO orderProducts_table(id, id_order, id_product) VALUES (%1, %2, %3);";
  QString str = str_insert.arg(orderProductsTable.id).arg(orderProductsTable.id_order).arg(orderProductsTable.id_product);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to insert data!";
  }
}

void HandlerBD::orderProductsTable_update(const orderProductsTable& orderProductsTable) {
  orderProductsTable_insert(orderProductsTable);
}

QVector<HandlerBD::orderProductsTable> HandlerBD::orderProductsTable_getAll() {
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM orderProducts_table")) {
    qDebug() << "Failed to get data!";
  }

  QVector<orderProductsTable> result;
  while (a_query.next()) {
    orderProductsTable record;
    record.id = a_query.value(0).toInt();
    record.id_order = a_query.value(1).toInt();
    record.id_product = a_query.value(2).toInt();

    result.push_back(record);
  }

  return result;
}

void HandlerBD::orderProductsTable_delete(const orderProductsTable& orderProductsTable) {
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM orderProducts_table WHERE id=%1;";
  QString str = str_delete.arg(orderProductsTable.id);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to delete data!";
  }
}
//************************************************************//

//********** Table linking an order with a customer, a delivery person and an office **********//
void HandlerBD::clientDeliverymanTable_create() {
  QSqlQuery query;
  QString str = "CREATE TABLE clientDeliveryman_table ("
                "id_order integer PRIMARY KEY NOT NULL, "
                "id_client integer NOT NULL, "
                "id_deliver integer NOT NULL, "
                "id_office integer NOT NULL"
                ");";

  if (!query.exec(str)) {
    qDebug() << "Failed to create a table!";
  }
}

void HandlerBD::clientDeliverymanTable_insert(const clientDeliverymanTable& clientDeliverymanTable) {
  if (!checkTable("clientDeliveryman_table"))
    clientDeliverymanTable_create();

  QSqlQuery a_query;
  QString str_insert = "INSERT INTO clientDeliveryman_table(id_order, id_client, id_deliver, id_office) VALUES (%1, %2, %3, %4);";
  QString str = str_insert.arg(clientDeliverymanTable.id_order).arg(clientDeliverymanTable.id_client).arg(clientDeliverymanTable.id_deliver).arg(clientDeliverymanTable.id_office);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to insert data!";
  }
}

void HandlerBD::clientDeliverymanTable_update(const clientDeliverymanTable& clientDeliverymanTable) {
  clientDeliverymanTable_insert(clientDeliverymanTable);
}

QVector<HandlerBD::clientDeliverymanTable> HandlerBD::clientDeliverymanTable_getAll() {
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM clientDeliveryman_table")) {
    qDebug() << "Failed to get data!";
  }

  QVector<clientDeliverymanTable> result;
  while (a_query.next()) {
    clientDeliverymanTable record;
    record.id_order = a_query.value(0).toInt();
    record.id_client = a_query.value(1).toInt();
    record.id_deliver = a_query.value(2).toInt();
    record.id_office = a_query.value(3).toInt();

    result.push_back(record);
  }

  return result;
}

void HandlerBD::clientDeliverymanTable_delete(const clientDeliverymanTable& clientDeliverymanTable) {
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM clientDeliveryman_table WHERE id_order=%1;";
  QString str = str_delete.arg(clientDeliverymanTable.id_order);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to delete data!";
  }
}
//*********************************************************************************************//

//********** Deliveryman information table **********//
void HandlerBD::deliverymanTable_create() {
  QSqlQuery query;
  QString str = "CREATE TABLE deliveryman_table ("
                "id_order integer PRIMARY KEY NOT NULL, "
                "last_name VARCHAR(255) NOT NULL, "
                "first_name VARCHAR(255) NOT NULL, "
                "middle_name VARCHAR(255), "
                "id_office integer NOT NULL, "
                "phone VARCHAR(255) NOT NULL, "
                "email VARCHAR(255) NOT NULL, "
                "pass VARCHAR(255) NOT NULL "
                ");";

  if (!query.exec(str)) {
    qDebug() << "Failed to create a table!";
  }
}

void HandlerBD::deliverymanTable_insert(const deliverymanTable& clientDeliverymanTable) {
  if (!checkTable("deliveryman_table"))
    deliverymanTable_create();

  QSqlQuery a_query;
  QString str_delete = "SELECT * FROM deliveryman_table WHERE email=%1;";
  QString strd = str_delete.arg(clientDeliverymanTable.email);
  if (!a_query.exec(strd)) {
    qDebug() << "Failed to get data!";
  }
  if (a_query.next()) {
    QString email = a_query.value(6).toString();
    qDebug() << "Delivery man with mail " + email + " already exists";
    return;
  }

  str_delete = "SELECT * FROM deliveryman_table WHERE email=%1;";
  strd = str_delete.arg(clientDeliverymanTable.phone);
  if (!a_query.exec(strd)) {
    qDebug() << "Failed to get data!";
  }
  if (a_query.next()) {
    QString phone = a_query.value(5).toString();
    qDebug() << "Delivery man with phone " + phone + " already exists";
    return;
  }

  QString str_insert = "INSERT INTO deliveryman_table(id_client, last_name, first_name, middle_name, id_office, phone, email, pass) VALUES (%1, '%2', '%3', '%4', %5, '%6', '%7', '%8');";
  QString str = str_insert.arg(clientDeliverymanTable.id_deliver).arg(clientDeliverymanTable.last_name).arg(clientDeliverymanTable.first_name).arg(clientDeliverymanTable.middle_name).arg(clientDeliverymanTable.id_office).arg(clientDeliverymanTable.phone).arg(clientDeliverymanTable.email).arg(clientDeliverymanTable.pass);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to insert data!";
  }
}

void HandlerBD::deliverymanTable_update(const deliverymanTable& clientDeliverymanTable) {
  deliverymanTable_insert(clientDeliverymanTable);
}

QVector<HandlerBD::deliverymanTable> HandlerBD::deliverymanTable_getAll() {
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM deliveryman_table")) {
    qDebug() << "Failed to get data!";
  }

  QVector<deliverymanTable> result;
  while (a_query.next()) {
    deliverymanTable record;
    record.id_deliver = a_query.value(0).toInt();
    record.last_name = a_query.value(1).toString();
    record.first_name = a_query.value(2).toString();
    record.middle_name = a_query.value(3).toString();
    record.id_office = a_query.value(4).toInt();
    record.phone = a_query.value(5).toString();
    record.email = a_query.value(6).toString();
    record.pass = a_query.value(7).toString();

    result.push_back(record);
  }

  return result;
}

bool HandlerBD::checkDeliveryman(const QString login, const QString password) {
  return checkUser("deliveryman_table", login, password);
}

void HandlerBD::deliverymanTable_delete(const deliverymanTable& clientDeliverymanTable) {
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM deliveryman_table WHERE id_deliver=%1;";
  QString str = str_delete.arg(clientDeliverymanTable.id_deliver);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to delete data!";
  }
}
//**********************************************//

//********** Client information table **********//
void HandlerBD::clientTable_create() {
  QSqlQuery query;
  QString str = "CREATE TABLE client_table ("
                "id_order integer PRIMARY KEY NOT NULL, "
                "email VARCHAR(255) NOT NULL, "
                "pass VARCHAR(255) NOT NULL, "
                "last_name VARCHAR(255) NOT NULL, "
                "first_name VARCHAR(255) NOT NULL, "
                "middle_name VARCHAR(255), "
                "phone VARCHAR(255) NOT NULL "
                ");";

  if (!query.exec(str)) {
    qDebug() << "Failed to create a table!";
  }
}

void HandlerBD::clientTable_insert(const clientTable& clientTable) {
  if (!checkTable("client_table"))
    clientTable_create();

  QSqlQuery a_query;
  QString str_insert = "INSERT INTO client_table(id_client, last_name, first_name, middle_name, phone, email) VALUES (%1, '%2', '%3', '%4', '%5', '%6', '%7');";
  QString str = str_insert.arg(clientTable.id_client).arg(clientTable.email).arg(clientTable.pass).arg(clientTable.last_name).arg(clientTable.first_name).arg(clientTable.middle_name).arg(clientTable.phone);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to insert data!";
  }
}

void HandlerBD::clientTable_update(const clientTable& clientTable) {
  clientTable_insert(clientTable);
}

QVector<HandlerBD::clientTable> HandlerBD::clientTable_getAll() {
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM client_table")) {
    qDebug() << "Failed to get data!";
  }

  QVector<clientTable> result;
  while (a_query.next()) {
    clientTable record;
    record.id_client = a_query.value(0).toInt();
    record.email = a_query.value(1).toString();
    record.pass = a_query.value(2).toString();
    record.last_name = a_query.value(3).toString();
    record.first_name = a_query.value(4).toString();
    record.middle_name = a_query.value(5).toString();
    record.phone = a_query.value(6).toString();

    result.push_back(record);
  }

  return result;
}

bool HandlerBD::checkClient(const QString login, const QString password) {
  return checkUser("client_table", login, password);
}

void HandlerBD::clientTable_delete(const clientTable& clientTable) {
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM client_table WHERE id_client=%1;";
  QString str = str_delete.arg(clientTable.id_client);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to delete data!";
  }
}
//**********************************************//

//********** Delivery table **********//
void HandlerBD::deliveryTable_create() {
  QSqlQuery query;
  QString str = "CREATE TABLE delivery_table ("
                "id integer PRIMARY KEY NOT NULL, "
                "id_deliver integer NOT NULL, "
                "id_condition integer NOT NULL, "
                "id_office integer NOT NULL, "
                "time VARCHAR(255) NOT NULL "
                ");";

  if (!query.exec(str)) {
    qDebug() << "Failed to create a table!";
  }
}

void HandlerBD::deliveryTable_insert(const deliveryTable& deliveryTable) {
  if (!checkTable("delivery_table"))
    deliveryTable_create();

  QSqlQuery a_query;
  QString str_insert = "INSERT INTO delivery_table(id, id_deliver, id_condition, id_office, time) VALUES (%1, %2, %3, %4, '%5');";
  QString str = str_insert.arg(deliveryTable.id).arg(deliveryTable.id_deliver).arg(deliveryTable.id_condition).arg(deliveryTable.id_office).arg(deliveryTable.time);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to insert data!";
  }
}

void HandlerBD::deliveryTable_update(const deliveryTable& deliveryTable) {
  deliveryTable_insert(deliveryTable);
}

QVector<HandlerBD::deliveryTable> HandlerBD::deliveryTable_getAll() {
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM delivery_table")) {
    qDebug() << "Failed to get data!";
  }

  QVector<deliveryTable> result;
  while (a_query.next()) {
    deliveryTable record;
    record.id = a_query.value(0).toInt();
    record.id_deliver = a_query.value(1).toInt();
    record.id_condition = a_query.value(2).toInt();
    record.id_office = a_query.value(3).toInt();
    record.time = a_query.value(4).toString();

    result.push_back(record);
  }

  return result;
}

void HandlerBD::deliveryTable_delete(const deliveryTable& deliveryTable) {
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM delivery_table WHERE id=%1;";
  QString str = str_delete.arg(deliveryTable.id);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to delete data!";
  }
}
//************************************//

//********** Table for states **********//
void HandlerBD::stateTable_create() {
  QSqlQuery query;
  QString str = "CREATE TABLE state_table ("
                "id_condition integer PRIMARY KEY NOT NULL, "
                "condition VARCHAR(255) NOT NULL "
                ");";

  if (!query.exec(str)) {
    qDebug() << "Failed to create a table!";
  }
}

void HandlerBD::stateTable_insert(const stateTable& stateTable){
  if (!checkTable("state_table"))
    stateTable_create();

  QSqlQuery a_query;
  QString str_insert = "INSERT INTO state_table(id_condition, condition) VALUES (%1, '%2');";
  QString str = str_insert.arg(stateTable.id_condition).arg(stateTable.condition);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to insert data!";
  }
}

void HandlerBD::stateTable_update(const stateTable& stateTable){
  stateTable_insert(stateTable);
}

QVector<HandlerBD::stateTable> HandlerBD::stateTable_getAll(){
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM state_table")) {
    qDebug() << "Failed to get data!";
  }

  QVector<stateTable> result;
  while (a_query.next()) {
    stateTable record;
    record.id_condition = a_query.value(0).toInt();
    record.condition = a_query.value(1).toString();

    result.push_back(record);
  }

  return result;
}

void HandlerBD::stateTable_delete(const stateTable& stateTable){
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM state_table WHERE id_condition=%1;";
  QString str = str_delete.arg(stateTable.id_condition);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to delete data!";
  }
}
//*************************************//

//********** Location table **********//
void HandlerBD::locationTable_create() {
  QSqlQuery query;
  QString str = "CREATE TABLE state_table ("
                "id_office integer PRIMARY KEY NOT NULL, "
                "office VARCHAR(255) NOT NULL "
                ");";

  if (!query.exec(str)) {
    qDebug() << "Failed to create a table!";
  }
}

void HandlerBD::locationTable_insert(const locationTable& locationTable){
  if (!checkTable("location_table"))
    locationTable_create();

  QSqlQuery a_query;
  QString str_insert = "INSERT INTO location_table(id_office, office) VALUES (%1, '%2');";
  QString str = str_insert.arg(locationTable.id_office).arg(locationTable.office);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to insert data!";
  }
}

void HandlerBD::locationTable_update(const locationTable& locationTable){
  locationTable_insert(locationTable);
}

QVector<HandlerBD::locationTable> HandlerBD::locationTable_getAll(){
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM location_table")) {
    qDebug() << "Failed to get data!";
  }

  QVector<locationTable> result;
  while (a_query.next()) {
    locationTable record;
    record.id_office = a_query.value(0).toInt();
    record.office = a_query.value(1).toString();

    result.push_back(record);
  }

  return result;
}

void HandlerBD::locationTable_delete(const locationTable& locationTable){
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM location_table WHERE id_office=%1;";
  QString str = str_delete.arg(locationTable.id_office);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to delete data!";
  }
}
//************************************//

//********** Product table (pizzas) **********//
void HandlerBD::productsTable_create() {
  QSqlQuery query;
  QString str = "CREATE TABLE products_table ("
                "id integer PRIMARY KEY NOT NULL, "
                "pizza_name VARCHAR(255) NOT NULL, "
                "description VARCHAR(255) NOT NULL, "
                "cost FLOAT NOT NULL, "
                ");";

  if (!query.exec(str)) {
    qDebug() << "Failed to create a table!";
  }
}

void HandlerBD::productsTable_insert(const productsTable& productsTable) {
  if (!checkTable("products_table"))
    productsTable_create();

  QSqlQuery a_query;
  QString str_insert = "INSERT INTO products_table(id_product, pizza_name, cost) VALUES (%1, '%2', '%3', %4);";
  QString str = str_insert.arg(productsTable.id).arg(productsTable.pizza_name).arg(productsTable.description).arg(productsTable.cost);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to insert data!";
  }
}

void HandlerBD::productsTable_update(const productsTable& productsTable)
{
  productsTable_insert(productsTable);
}

QVector<HandlerBD::productsTable> HandlerBD::productsTable_getAll()
{
  QSqlQuery a_query;
  if (!a_query.exec("SELECT * FROM products_table")) {
    qDebug() << "Failed to get data!";
  }

  QVector<productsTable> result;
  while (a_query.next()) {
    productsTable record;
    record.id = a_query.value(0).toInt();
    record.pizza_name = a_query.value(1).toString();
    record.description = a_query.value(2).toString();
    record.cost = a_query.value(3).toFloat();

    result.push_back(record);
  }

  return result;
}

void HandlerBD::productsTable_delete(const productsTable& productsTable)
{
  QSqlQuery a_query;
  QString str_delete = "DELETE FROM products_table WHERE id_product=%1;";
  QString str = str_delete.arg(productsTable.id);

  if (!a_query.exec(str)) {
    qDebug() << "Failed to delete data!";
  }
}
//********************************************//
