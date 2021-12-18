#ifndef TST_SERVERTEST_H
#define TST_SERVERTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <dbworker.h>
#include <handlerbd.h>
#include <qsettings.h>
#include <string>
#include <QFile>
#include <QTextStream>

using namespace testing;

QSettings* crateLocalSettingWithPath(const QString& Path)
{
  return new QSettings(Path, QSettings::IniFormat, nullptr);
}

TEST(DatabaseTest, checkTable_Test)
{
  QString settingsfilename= "checkTableTest.ini";
  QString dbfilename = "checkTableTest.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliverymanTable_create();
  ASSERT_THAT(ahDB->checkTable("deliveryman_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, checkUser_Test)
{
  QString settingsfilename= "checkUser_Test.ini";
  QString dbfilename = "checkUser_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);;
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliverymanTable deliveryman_test_table;
  deliveryman_test_table.id_deliver = 0;
  deliveryman_test_table.last_name = "test_last_name";
  deliveryman_test_table.first_name = "test_first_name";
  deliveryman_test_table.middle_name = "test_middle_name";
  deliveryman_test_table.id_office = 0;
  deliveryman_test_table.phone = "test_phone";
  deliveryman_test_table.email = "test_email";
  deliveryman_test_table.pass = "test_pass";
  ahDB->deliverymanTable_insert(deliveryman_test_table);
  ASSERT_THAT(ahDB->checkUser("deliveryman_table", "test_email", "test_pass"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderProductsTable_create_Test)
{
  QString settingsfilename= "orderProductsTable_create_Test.ini";
  QString dbfilename = "orderProductsTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->orderProductsTable_create();
  ASSERT_THAT(ahDB->checkTable("orderProducts_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderProductsTable_Insert_Test)
{
  QString settingsfilename= "orderProductsTable_Insert_Test.ini";
  QString dbfilename = "orderProductsTable_Insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->orderProductsTable_create();
  HandlerBD::orderProductsTable orderProductsTable_test0;
  orderProductsTable_test0.id = 0;
  orderProductsTable_test0.id_order = 0;
  orderProductsTable_test0.id_product = 2;
  ahDB->orderProductsTable_insert(orderProductsTable_test0);
  QVector<HandlerBD::orderProductsTable> test = ahDB->orderProductsTable_getAll();
  ASSERT_THAT(test[0].id_product,Eq(2));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderProductsTable_Update_Test)
{
  QString settingsfilename= "orderProductsTable_Update_Test.ini";
  QString dbfilename = "orderProductsTable_Update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderProductsTable orderProductsTable_test1;
  orderProductsTable_test1.id = 0;
  orderProductsTable_test1.id_order = 0;
  orderProductsTable_test1.id_product = 2;
  ahDB->orderProductsTable_update({0,1,2});
  QVector<HandlerBD::orderProductsTable> test1 = ahDB->orderProductsTable_getAll();
  ASSERT_THAT(test1[0].id_order,Eq(1));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderProductsTable_GetAll_Test)
{
  QString settingsfilename= "orderProductsTable_GetAll_Test.ini";
  QString dbfilename = "orderProductsTable_GetAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderProductsTable orderProductsTable_test0;
  HandlerBD::orderProductsTable orderProductsTable_test1;
  orderProductsTable_test0.id = 0;
  orderProductsTable_test0.id_order = 0;
  orderProductsTable_test0.id_product = 0;
  orderProductsTable_test1.id = 1;
  orderProductsTable_test1.id_order = 1;
  orderProductsTable_test1.id_product = 1;
  ahDB->orderProductsTable_insert(orderProductsTable_test0);
  ahDB->orderProductsTable_insert(orderProductsTable_test1);
  QVector<HandlerBD::orderProductsTable> test1 = ahDB->orderProductsTable_getAll();
  ASSERT_THAT(test1[1].id,Eq(1));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderProductsTable_delete_Test)
{
  QString settingsfilename= "orderProductsTable_delete_Test.ini";
  QString dbfilename = "orderProductsTable_delete_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderProductsTable orderProductsTable_test0;
  HandlerBD::orderProductsTable orderProductsTable_test1;
  HandlerBD::orderProductsTable orderProductsTable_test2;
  orderProductsTable_test0.id = 0;
  orderProductsTable_test0.id_order = 0;
  orderProductsTable_test0.id_product = 0;
  orderProductsTable_test1.id = 1;
  orderProductsTable_test1.id_order = 1;
  orderProductsTable_test1.id_product = 1;
  orderProductsTable_test2.id = 2;
  orderProductsTable_test2.id_order = 2;
  orderProductsTable_test2.id_product = 2;
  ahDB->orderProductsTable_insert(orderProductsTable_test0);
  ahDB->orderProductsTable_insert(orderProductsTable_test1);
  ahDB->orderProductsTable_insert(orderProductsTable_test2);
  ahDB->orderProductsTable_delete(orderProductsTable_test1);
  QVector<HandlerBD::orderProductsTable> test1 = ahDB->orderProductsTable_getAll();
  ASSERT_THAT(test1[1].id_order,Eq(2));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientDeliverymanTable_create_Test)
{
  QString settingsfilename= "clientDeliverymanTable_create_Test.ini";
  QString dbfilename = "clientDeliverymanTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->clientDeliverymanTable_create();
  ASSERT_THAT(ahDB->checkTable("clientDeliveryman_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientDeliverymanTable_insert_Test)
{
  QString settingsfilename= "clientDeliverymanTable_insert_Test.ini";
  QString dbfilename = "clientDeliverymanTable_insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->clientDeliverymanTable_create();
  HandlerBD::clientDeliverymanTable clientDeliveryman_Test_Table;
  clientDeliveryman_Test_Table.id_order = 0;
  clientDeliveryman_Test_Table.id_client = 1;
  clientDeliveryman_Test_Table.id_deliver = 2;
  clientDeliveryman_Test_Table.id_office = 3;
  ahDB->clientDeliverymanTable_insert(clientDeliveryman_Test_Table);
  QVector<HandlerBD::clientDeliverymanTable> test1 = ahDB->clientDeliverymanTable_getAll();
  ASSERT_THAT(test1[0].id_deliver,Eq(2));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientDeliverymanTable_update_Test)
{
  QString settingsfilename= "clientDeliverymanTable_update_Test.ini";
  QString dbfilename = "clientDeliverymanTable_update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientDeliverymanTable clientDeliveryman_Test_Table;
  clientDeliveryman_Test_Table.id_order = 0;
  clientDeliveryman_Test_Table.id_client = 1;
  clientDeliveryman_Test_Table.id_deliver = 2;
  clientDeliveryman_Test_Table.id_office = 3;
  ahDB->clientDeliverymanTable_update(clientDeliveryman_Test_Table);
  QVector<HandlerBD::clientDeliverymanTable> test1 = ahDB->clientDeliverymanTable_getAll();
  ASSERT_THAT(test1[0].id_deliver,Eq(2));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientDeliverymanTable_getAll_Test)
{
  QString settingsfilename= "clientDeliverymanTable_getAll_Test.ini";
  QString dbfilename = "clientDeliverymanTable_getAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientDeliverymanTable clientDeliveryman_Test_Table0;
  clientDeliveryman_Test_Table0.id_order = 0;
  clientDeliveryman_Test_Table0.id_client = 0;
  clientDeliveryman_Test_Table0.id_deliver = 0;
  clientDeliveryman_Test_Table0.id_office = 0;
  HandlerBD::clientDeliverymanTable clientDeliveryman_Test_Table1;
  clientDeliveryman_Test_Table1.id_order = 1;
  clientDeliveryman_Test_Table1.id_client = 1;
  clientDeliveryman_Test_Table1.id_deliver = 1;
  clientDeliveryman_Test_Table1.id_office = 1;
  HandlerBD::clientDeliverymanTable clientDeliveryman_Test_Table2;
  clientDeliveryman_Test_Table2.id_order = 2;
  clientDeliveryman_Test_Table2.id_client = 2;
  clientDeliveryman_Test_Table2.id_deliver = 2;
  clientDeliveryman_Test_Table2.id_office = 2;
  ahDB->clientDeliverymanTable_create();
  ahDB->clientDeliverymanTable_insert(clientDeliveryman_Test_Table0);
  ahDB->clientDeliverymanTable_insert(clientDeliveryman_Test_Table1);
  ahDB->clientDeliverymanTable_insert(clientDeliveryman_Test_Table2);
  QVector<HandlerBD::clientDeliverymanTable> test1 = ahDB->clientDeliverymanTable_getAll();
  ASSERT_THAT(test1[2].id_deliver,Eq(2));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientDeliverymanTable_delete_Test)
{
  QString settingsfilename= "clientDeliverymanTable_delete_Test.ini";
  QString dbfilename = "clientDeliverymanTable_delete_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientDeliverymanTable clientDeliveryman_Test_Table0;
  clientDeliveryman_Test_Table0.id_order = 0;
  clientDeliveryman_Test_Table0.id_client = 0;
  clientDeliveryman_Test_Table0.id_deliver = 0;
  clientDeliveryman_Test_Table0.id_office = 0;
  HandlerBD::clientDeliverymanTable clientDeliveryman_Test_Table1;
  clientDeliveryman_Test_Table1.id_order = 1;
  clientDeliveryman_Test_Table1.id_client = 1;
  clientDeliveryman_Test_Table1.id_deliver = 1;
  clientDeliveryman_Test_Table1.id_office = 1;
  HandlerBD::clientDeliverymanTable clientDeliveryman_Test_Table2;
  clientDeliveryman_Test_Table2.id_order = 2;
  clientDeliveryman_Test_Table2.id_client = 2;
  clientDeliveryman_Test_Table2.id_deliver = 2;
  clientDeliveryman_Test_Table2.id_office = 2;
  ahDB->clientDeliverymanTable_create();
  ahDB->clientDeliverymanTable_insert(clientDeliveryman_Test_Table0);
  ahDB->clientDeliverymanTable_insert(clientDeliveryman_Test_Table1);
  ahDB->clientDeliverymanTable_insert(clientDeliveryman_Test_Table2);
  ahDB->clientDeliverymanTable_delete(clientDeliveryman_Test_Table1);
  QVector<HandlerBD::clientDeliverymanTable> test1 = ahDB->clientDeliverymanTable_getAll();
  ASSERT_THAT(test1[1].id_client,Eq(2));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliverymanTable_create_Test)
{
  QString settingsfilename= "deliverymanTable_create_Test.ini";
  QString dbfilename = "deliverymanTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliverymanTable_create();
  ASSERT_THAT(ahDB->checkTable("deliveryman_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliverymanTable_insert_Test)
{
  QString settingsfilename= "deliverymanTable_insert_Test.ini";
  QString dbfilename = "deliverymanTable_insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliverymanTable_create();
  HandlerBD::deliverymanTable deliveryman_test_table;
  deliveryman_test_table.id_deliver = 0;
  deliveryman_test_table.last_name = "test_last_name";
  deliveryman_test_table.first_name = "test_first_name";
  deliveryman_test_table.middle_name = "test_middle_name";
  deliveryman_test_table.id_office = 0;
  deliveryman_test_table.phone = "test_phone123";
  deliveryman_test_table.email = "test_email";
  deliveryman_test_table.pass = "test_pass";
  ahDB->deliverymanTable_insert(deliveryman_test_table);
  QVector<HandlerBD::deliverymanTable> test1 = ahDB->deliverymanTable_getAll();
  ASSERT_THAT(test1[0].first_name,Eq("test_first_name"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliverymanTable_update_Test)
{
  QString settingsfilename= "deliverymanTable_update_Test.ini";
  QString dbfilename = "deliverymanTable_update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliverymanTable_create();
  HandlerBD::deliverymanTable deliveryman_test_table;
  deliveryman_test_table.id_deliver = 0;
  deliveryman_test_table.last_name = "test_last_name";
  deliveryman_test_table.first_name = "test_first_name";
  deliveryman_test_table.middle_name = "test_middle_name";
  deliveryman_test_table.id_office = 0;
  deliveryman_test_table.phone = "test_phone321";
  deliveryman_test_table.email = "test_email23";
  deliveryman_test_table.pass = "test_pass222";
  ahDB->deliverymanTable_update(deliveryman_test_table);
  QVector<HandlerBD::deliverymanTable> test1 = ahDB->deliverymanTable_getAll();
  ASSERT_THAT(test1[0].middle_name,Eq("test_middle_name"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliverymanTable_getAll_Test)
{
  QString settingsfilename= "deliverymanTable_getAll_Test.ini";
  QString dbfilename = "deliverymanTable_getAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliverymanTable_create();
  HandlerBD::deliverymanTable deliveryman_test_table0;
  deliveryman_test_table0.id_deliver = 0;
  deliveryman_test_table0.last_name = "test_last_name1";
  deliveryman_test_table0.first_name = "test_first_name2";
  deliveryman_test_table0.middle_name = "test_middle_name3";
  deliveryman_test_table0.id_office = 5;
  deliveryman_test_table0.phone = "test_phone4";
  deliveryman_test_table0.email = "test_email5";
  deliveryman_test_table0.pass = "test_pass6";
  ahDB->deliverymanTable_insert(deliveryman_test_table0);
  HandlerBD::deliverymanTable deliveryman_test_table1;
  deliveryman_test_table1.id_deliver = 1;
  deliveryman_test_table1.last_name = "test_last_name";
  deliveryman_test_table1.first_name = "test_first_name";
  deliveryman_test_table1.middle_name = "test_middle_name";
  deliveryman_test_table1.id_office = 10;
  deliveryman_test_table1.phone = "test_phone8";
  deliveryman_test_table1.email = "test_email2";
  deliveryman_test_table1.pass = "test_pass";
  ahDB->deliverymanTable_insert(deliveryman_test_table1);
  QVector<HandlerBD::deliverymanTable> test1 = ahDB->deliverymanTable_getAll();
  ASSERT_THAT(test1[1].email,Eq("test_email2"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, checkDeliveryman_Test)
{
  QString settingsfilename= "checkDeliveryman_Test.ini";
  QString dbfilename = "checkDeliveryman_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliverymanTable deliveryman_test_table;
  deliveryman_test_table.id_deliver = 0;
  deliveryman_test_table.last_name = "test_last_name";
  deliveryman_test_table.first_name = "test_first_name";
  deliveryman_test_table.middle_name = "test_middle_name";
  deliveryman_test_table.id_office = 0;
  deliveryman_test_table.phone = "test_phone9";
  deliveryman_test_table.email = "test_email";
  deliveryman_test_table.pass = "test_pass";
  ahDB->deliverymanTable_insert(deliveryman_test_table);
  ASSERT_THAT(ahDB->checkDeliveryman("test_email", "test_pass"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliverymanTable_delete_Test)
{
  QString settingsfilename= "orderProductsTable_create_Test.ini";
  QString dbfilename = "orderProductsTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliverymanTable_create();
  HandlerBD::deliverymanTable deliveryman_test_table0;
  deliveryman_test_table0.id_deliver = 0;
  deliveryman_test_table0.last_name = "test_last_name1";
  deliveryman_test_table0.first_name = "test_first_name2";
  deliveryman_test_table0.middle_name = "test_middle_name3";
  deliveryman_test_table0.id_office = 5;
  deliveryman_test_table0.phone = "test_phone41";
  deliveryman_test_table0.email = "test_email51";
  deliveryman_test_table0.pass = "test_pass6";
  ahDB->deliverymanTable_insert(deliveryman_test_table0);
  HandlerBD::deliverymanTable deliveryman_test_table1;
  deliveryman_test_table1.id_deliver = 1;
  deliveryman_test_table1.last_name = "test_last_name";
  deliveryman_test_table1.first_name = "test_first_name";
  deliveryman_test_table1.middle_name = "test_middle_name";
  deliveryman_test_table1.id_office = 10;
  deliveryman_test_table1.phone = "test_phone";
  deliveryman_test_table1.email = "test_email24";
  deliveryman_test_table1.pass = "test_pass";
  ahDB->deliverymanTable_insert(deliveryman_test_table1);
  ahDB->deliverymanTable_delete(deliveryman_test_table0);
  QVector<HandlerBD::deliverymanTable> test1 = ahDB->deliverymanTable_getAll();
  ASSERT_THAT(test1[0].email,Eq("test_email24"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientTable_create_Test)
{
  QString settingsfilename= "clientTable_create_Test.ini";
  QString dbfilename = "clientTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->clientTable_create();
  ASSERT_THAT(ahDB->checkTable("client_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientTable_insert_Test)
{
  QString settingsfilename= "clientTable_insert_Test.ini";
  QString dbfilename = "clientTable_insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientTable clientTable_test;
  clientTable_test.id_client = 0;
  clientTable_test.email = "test_mail";
  clientTable_test.pass = "test_pass";
  clientTable_test.last_name = "test_lname";
  clientTable_test.first_name = "test_fname";
  clientTable_test.middle_name = "test_mname";
  clientTable_test.phone = "test_phone";
  ahDB->clientTable_create();
  ahDB->clientTable_insert(clientTable_test);
  QVector<HandlerBD::clientTable> test1 = ahDB->clientTable_getAll();
  ASSERT_THAT(test1[0].pass,Eq("test_pass"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientTable_update_Test)
{
  QString settingsfilename= "clientTable_update_Test.ini";
  QString dbfilename = "clientTable_update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientTable clientTable_test;
  clientTable_test.id_client = 0;
  clientTable_test.email = "test_mail";
  clientTable_test.pass = "test_pass";
  clientTable_test.last_name = "test_lname";
  clientTable_test.first_name = "test_fname";
  clientTable_test.middle_name = "test_mname";
  clientTable_test.phone = "test_phone";
  ahDB->clientTable_create();
  ahDB->clientTable_update(clientTable_test);
  QVector<HandlerBD::clientTable> test1 = ahDB->clientTable_getAll();
  ASSERT_THAT(test1[0].pass,Eq("test_pass"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientTable_getAll_Test)
{
  QString settingsfilename= "clientTable_getAll_Test.ini";
  QString dbfilename = "clientTable_getAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientTable clientTable_test0;
  clientTable_test0.id_client = 0;
  clientTable_test0.email = "test_mail0";
  clientTable_test0.pass = "test_pass0";
  clientTable_test0.last_name = "test_lname0";
  clientTable_test0.first_name = "test_fname0";
  clientTable_test0.middle_name = "test_mname0";
  clientTable_test0.phone = "test_phone0";
  HandlerBD::clientTable clientTable_test1;
  clientTable_test1.id_client = 1;
  clientTable_test1.email = "test_mail1";
  clientTable_test1.pass = "test_pass1";
  clientTable_test1.last_name = "test_lname1";
  clientTable_test1.first_name = "test_fname1";
  clientTable_test1.middle_name = "test_mname1";
  clientTable_test1.phone = "test_phone1";
  ahDB->clientTable_create();
  ahDB->clientTable_insert(clientTable_test0);
  ahDB->clientTable_insert(clientTable_test1);
  QVector<HandlerBD::clientTable> test1 = ahDB->clientTable_getAll();
  ASSERT_THAT(test1[1].email,Eq("test_mail1"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, checkClient_Test)
{
  QString settingsfilename= "checkClient_Test.ini";
  QString dbfilename = "checkClient_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientTable clientTable_test1;
  clientTable_test1.id_client = 1;
  clientTable_test1.email = "test_mail1";
  clientTable_test1.pass = "test_pass1";
  clientTable_test1.last_name = "test_lname1";
  clientTable_test1.first_name = "test_fname1";
  clientTable_test1.middle_name = "test_mname1";
  clientTable_test1.phone = "test_phone1";
  ahDB->clientTable_create();
  ahDB->clientTable_insert(clientTable_test1);
  ASSERT_THAT(ahDB->checkClient("test_mail1","test_pass1"),Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, clientTable_delete_Test)
{
  QString settingsfilename= "clientTable_delete_Test.ini";
  QString dbfilename = "clientTable_delete_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientTable clientTable_test0;
  clientTable_test0.id_client = 0;
  clientTable_test0.email = "test_mail0";
  clientTable_test0.pass = "test_pass0";
  clientTable_test0.last_name = "test_lname0";
  clientTable_test0.first_name = "test_fname0";
  clientTable_test0.middle_name = "test_mname0";
  clientTable_test0.phone = "test_phone0";
  HandlerBD::clientTable clientTable_test1;
  clientTable_test1.id_client = 1;
  clientTable_test1.email = "test_mail1";
  clientTable_test1.pass = "test_pass1";
  clientTable_test1.last_name = "test_lname1";
  clientTable_test1.first_name = "test_fname1";
  clientTable_test1.middle_name = "test_mname1";
  clientTable_test1.phone = "test_phone1";
  ahDB->clientTable_create();
  ahDB->clientTable_insert(clientTable_test0);
  ahDB->clientTable_insert(clientTable_test1);
  ahDB->clientTable_delete(clientTable_test0);
  QVector<HandlerBD::clientTable> test1 = ahDB->clientTable_getAll();
  ASSERT_THAT(test1[0].email,Eq("test_mail1"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliveryTable_create_Test)
{
  QString settingsfilename= "deliveryTable_create_Test.ini";
  QString dbfilename = "deliveryTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliveryTable_create();
  ASSERT_THAT(ahDB->checkTable("delivery_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliveryTable_insert_Test)
{
  QString settingsfilename= "deliveryTable_insert_Test.ini";
  QString dbfilename = "deliveryTable_insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliveryTable deliveryTable_test;
  deliveryTable_test.id = 0;
  deliveryTable_test.id_deliver = 0;
  deliveryTable_test.id_condition = 0;
  deliveryTable_test.id_office = 0;
  deliveryTable_test.time = "12:12";
  ahDB->deliveryTable_create();
  ahDB->deliveryTable_insert(deliveryTable_test);
  QVector<HandlerBD::deliveryTable> test1 = ahDB->deliveryTable_getAll();
  ASSERT_THAT(test1[0].time,Eq("12:12"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliveryTable_update_Test)
{
  QString settingsfilename= "deliveryTable_update_Test.ini";
  QString dbfilename = "deliveryTable_update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliveryTable deliveryTable_test;
  deliveryTable_test.id = 0;
  deliveryTable_test.id_deliver = 0;
  deliveryTable_test.id_condition = 0;
  deliveryTable_test.id_office = 0;
  deliveryTable_test.time = "21:21";
  ahDB->deliveryTable_create();
  ahDB->deliveryTable_update(deliveryTable_test);
  QVector<HandlerBD::deliveryTable> test1 = ahDB->deliveryTable_getAll();
  ASSERT_THAT(test1[0].time,Eq("21:21"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliveryTable_getAll_Test)
{
  QString settingsfilename= "deliveryTable_getAll_Test.ini";
  QString dbfilename = "deliveryTable_getAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliveryTable deliveryTable_test0;
  deliveryTable_test0.id = 0;
  deliveryTable_test0.id_deliver = 12;
  deliveryTable_test0.id_condition = 2;
  deliveryTable_test0.id_office = 5;
  deliveryTable_test0.time = "21:21";
  HandlerBD::deliveryTable deliveryTable_test1;
  deliveryTable_test1.id = 1;
  deliveryTable_test1.id_deliver = 13;
  deliveryTable_test1.id_condition = 1;
  deliveryTable_test1.id_office = 0;
  deliveryTable_test1.time = "11:41";
  ahDB->deliveryTable_create();
  ahDB->deliveryTable_insert(deliveryTable_test0);
  ahDB->deliveryTable_insert(deliveryTable_test1);
  QVector<HandlerBD::deliveryTable> test1 = ahDB->deliveryTable_getAll();
  ASSERT_THAT(test1[1].time,Eq("11:41"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, deliveryTable_delete_Test)
{
  QString settingsfilename= "deliveryTable_delete_Test.ini";
  QString dbfilename = "deliveryTable_delete_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliveryTable deliveryTable_test0;
  deliveryTable_test0.id = 0;
  deliveryTable_test0.id_deliver = 12;
  deliveryTable_test0.id_condition = 2;
  deliveryTable_test0.id_office = 5;
  deliveryTable_test0.time = "21:21";
  HandlerBD::deliveryTable deliveryTable_test1;
  deliveryTable_test1.id = 1;
  deliveryTable_test1.id_deliver = 13;
  deliveryTable_test1.id_condition = 1;
  deliveryTable_test1.id_office = 0;
  deliveryTable_test1.time = "11:41";
  ahDB->deliveryTable_create();
  ahDB->deliveryTable_insert(deliveryTable_test0);
  ahDB->deliveryTable_insert(deliveryTable_test1);
  ahDB->deliveryTable_delete(deliveryTable_test0);
  QVector<HandlerBD::deliveryTable> test1 = ahDB->deliveryTable_getAll();
  ASSERT_THAT(test1[0].id_deliver,Eq(13));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, stateTable_create_Test)
{
  QString settingsfilename= "stateTable_create_Test.ini";
  QString dbfilename = "stateTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->stateTable_create();
  ASSERT_THAT(ahDB->checkTable("state_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, stateTable_insert_Test)
{
  QString settingsfilename= "stateTable_insert_Test.ini";
  QString dbfilename = "stateTable_insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::stateTable stateTable_test;
  stateTable_test.id_condition = 0;
  stateTable_test.condition = "in progress";
  ahDB->stateTable_create();
  ahDB->stateTable_insert(stateTable_test);
  QVector<HandlerBD::stateTable> test1 = ahDB->stateTable_getAll();
  ASSERT_THAT(test1[0].condition,Eq("in progress"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, stateTable_update_Test)
{
  QString settingsfilename= "stateTable_update_Test.ini";
  QString dbfilename = "stateTable_update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::stateTable stateTable_test;
  stateTable_test.id_condition = 0;
  stateTable_test.condition = "in progress";
  ahDB->stateTable_create();
  ahDB->stateTable_update(stateTable_test);
  QVector<HandlerBD::stateTable> test1 = ahDB->stateTable_getAll();
  ASSERT_THAT(test1[0].condition,Eq("in progress"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, stateTable_getAll_Test)
{
  QString settingsfilename= "stateTable_getAll_Test.ini";
  QString dbfilename = "stateTable_getAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::stateTable stateTable_test0;
  stateTable_test0.id_condition = 0;
  stateTable_test0.condition = "in progress";
  HandlerBD::stateTable stateTable_test1;
  stateTable_test1.id_condition = 1;
  stateTable_test1.condition = "delivered";
  ahDB->stateTable_create();
  ahDB->stateTable_insert(stateTable_test0);
  ahDB->stateTable_insert(stateTable_test1);
  QVector<HandlerBD::stateTable> test1 = ahDB->stateTable_getAll();
  ASSERT_THAT(test1[1].condition,Eq("delivered"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, stateTable_delete_Test)
{
  QString settingsfilename= "stateTable_delete_Test.ini";
  QString dbfilename = "stateTable_delete_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::stateTable stateTable_test0;
  stateTable_test0.id_condition = 0;
  stateTable_test0.condition = "in progress";
  HandlerBD::stateTable stateTable_test1;
  stateTable_test1.id_condition = 1;
  stateTable_test1.condition = "delivered";
  ahDB->stateTable_create();
  ahDB->stateTable_insert(stateTable_test0);
  ahDB->stateTable_insert(stateTable_test1);
  ahDB->stateTable_delete(stateTable_test0);
  QVector<HandlerBD::stateTable> test1 = ahDB->stateTable_getAll();
  ASSERT_THAT(test1[0].condition,Eq("delivered"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, locationTable_create_Test)
{
  QString settingsfilename= "locationTable_create_Test.ini";
  QString dbfilename = "locationTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->locationTable_create();
  ASSERT_THAT(ahDB->checkTable("location_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, locationTable_insert_Test)
{
  QString settingsfilename= "locationTable_insert_Test.ini";
  QString dbfilename = "locationTable_insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::locationTable locationTable_test;
  locationTable_test.id_office = 0;
  locationTable_test.office = "office";
  ahDB->locationTable_create();
  ahDB->locationTable_insert(locationTable_test);
  QVector<HandlerBD::locationTable> test1 = ahDB->locationTable_getAll();
  ASSERT_THAT(test1[0].office,Eq("office"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, locationTable_update_Test)
{
  QString settingsfilename= "locationTable_update_Test.ini";
  QString dbfilename = "locationTable_update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::locationTable locationTable_test;
  locationTable_test.id_office = 0;
  locationTable_test.office = "office";
  ahDB->locationTable_create();
  ahDB->locationTable_update(locationTable_test);
  QVector<HandlerBD::locationTable> test1 = ahDB->locationTable_getAll();
  ASSERT_THAT(test1[0].office,Eq("office"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, locationTable_getAll_Test)
{
  QString settingsfilename= "locationTable_getAll_Test.ini";
  QString dbfilename = "locationTable_getAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::locationTable locationTable_test0;
  locationTable_test0.id_office = 0;
  locationTable_test0.office = "office";
  HandlerBD::locationTable locationTable_test1;
  locationTable_test1.id_office = 1;
  locationTable_test1.office = "Default";
  ahDB->locationTable_create();
  ahDB->locationTable_insert(locationTable_test0);
  ahDB->locationTable_insert(locationTable_test1);
  QVector<HandlerBD::locationTable> test1 = ahDB->locationTable_getAll();
  ASSERT_THAT(test1[1].office,Eq("Default"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, locationTable_delete_Test)
{
  QString settingsfilename= "locationTable_delete_Test.ini";
  QString dbfilename = "locationTable_delete_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::locationTable locationTable_test0;
  locationTable_test0.id_office = 0;
  locationTable_test0.office = "office";
  HandlerBD::locationTable locationTable_test1;
  locationTable_test1.id_office = 1;
  locationTable_test1.office = "Default";
  ahDB->locationTable_create();
  ahDB->locationTable_insert(locationTable_test0);
  ahDB->locationTable_insert(locationTable_test1);
  ahDB->locationTable_delete(locationTable_test0);
  QVector<HandlerBD::locationTable> test1 = ahDB->locationTable_getAll();
  ASSERT_THAT(test1[0].office,Eq("Default"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, productsTable_create_Test)
{
  QString settingsfilename= "productsTable_create_Test.ini";
  QString dbfilename = "productsTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->productsTable_create();
  ASSERT_THAT(ahDB->checkTable("products_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, productsTable_insert_Test)
{
  QString settingsfilename= "productsTable_insert_Test.ini";
  QString dbfilename = "productsTable_insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::productsTable productsTable_test;
  productsTable_test.id = 0;
  productsTable_test.pizza_name = "Itallian";
  productsTable_test.description = "Salami";
  productsTable_test.cost = 450.0f;
  ahDB->productsTable_create();
  ahDB->productsTable_insert(productsTable_test);
  QVector<HandlerBD::productsTable> test1 = ahDB->productsTable_getAll();
  ASSERT_THAT(test1[0].pizza_name,Eq("Itallian"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, productsTable_update_Test)
{
  QString settingsfilename= "productsTable_update_Test.ini";
  QString dbfilename = "productsTable_update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->productsTable_create();
  HandlerBD::productsTable productsTable_test;
  productsTable_test.id = 0;
  productsTable_test.pizza_name = "Pepperoni";
  productsTable_test.description = "Salami";
  productsTable_test.cost = 450.0f;
  ahDB->productsTable_update(productsTable_test);
  QVector<HandlerBD::productsTable> test1 = ahDB->productsTable_getAll();
  ASSERT_THAT(test1[0].description,Eq("Salami"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, productsTable_getAll_Test)
{
  QString settingsfilename= "productsTable_getAll_Test.ini";
  QString dbfilename = "productsTable_getAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->productsTable_create();
  HandlerBD::productsTable productsTable_test0;
  productsTable_test0.id = 0;
  productsTable_test0.pizza_name = "Sicilian";
  productsTable_test0.description = "Salami";
  productsTable_test0.cost = 550.0f;
  HandlerBD::productsTable productsTable_test1;
  productsTable_test1.id = 1;
  productsTable_test1.pizza_name = "Haw";
  productsTable_test1.description = "Pineapple";
  productsTable_test1.cost = 450.0f;
  ahDB->productsTable_insert(productsTable_test0);
  ahDB->productsTable_insert(productsTable_test1);
  QVector<HandlerBD::productsTable> test1 = ahDB->productsTable_getAll();
  ASSERT_THAT(test1[1].pizza_name,Eq("Haw"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, productsTable_delete_Test)
{
  QString settingsfilename= "productsTable_delete_Test.ini";
  QString dbfilename = "productsTable_delete_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->productsTable_create();
  HandlerBD::productsTable productsTable_test0;
  productsTable_test0.id = 0;
  productsTable_test0.pizza_name = "Pepperoni";
  productsTable_test0.description = "Salami";
  productsTable_test0.cost = 550.0f;
  HandlerBD::productsTable productsTable_test1;
  productsTable_test1.id = 1;
  productsTable_test1.pizza_name = "Haw";
  productsTable_test1.description = "Pineapple";
  productsTable_test1.cost = 450.0f;
  ahDB->productsTable_insert(productsTable_test0);
  ahDB->productsTable_insert(productsTable_test1);
  ahDB->productsTable_delete(productsTable_test0);
  QVector<HandlerBD::productsTable> test1 = ahDB->productsTable_getAll();
  ASSERT_THAT(test1[0].description,Eq("Pineapple"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderTable_create_Test)
{
  QString settingsfilename= "orderTable_create_Test.ini";
  QString dbfilename = "orderTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->orderTable_create();
  ASSERT_THAT(ahDB->checkTable("order_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderTable_insert_Test)
{
  QString settingsfilename= "orderTable_insert_Test.ini";
  QString dbfilename = "orderTable_insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderTable orderTable_test;
  orderTable_test.id = 0;
  orderTable_test.status = "working";
  orderTable_test.id_client = 0;
  orderTable_test.adress = "Russia";
  orderTable_test.id_office = 0;
  orderTable_test.timeStart = "12:12";
  orderTable_test.timeEnd = "13:02";
  ahDB->orderTable_create();
  ahDB->orderTable_insert(orderTable_test);
  QVector<HandlerBD::orderTable> test1 = ahDB->orderTable_getAll();
  ASSERT_THAT(test1[0].status,Eq("working"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderTable_update_Test)
{
  QString settingsfilename= "orderTable_update_Test.ini";
  QString dbfilename = "orderTable_update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderTable orderTable_test;
  orderTable_test.id = 0;
  orderTable_test.status = "working";
  orderTable_test.id_client = 0;
  orderTable_test.adress = "Russia";
  orderTable_test.id_office = 0;
  orderTable_test.timeStart = "12:12";
  orderTable_test.timeEnd = "13:02";
  ahDB->orderTable_create();
  ahDB->orderTable_update(orderTable_test);
  QVector<HandlerBD::orderTable> test1 = ahDB->orderTable_getAll();
  ASSERT_THAT(test1[0].id_office,Eq(0));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderTable_getAll_Test)
{
  QString settingsfilename= "orderTable_getAll_Test.ini";
  QString dbfilename = "orderTable_getAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderTable orderTable_test0;
  orderTable_test0.id = 0;
  orderTable_test0.status = "working";
  orderTable_test0.id_client = 0;
  orderTable_test0.adress = "Russia";
  orderTable_test0.id_office = 0;
  orderTable_test0.timeStart = "12:12";
  orderTable_test0.timeEnd = "13:02";
  HandlerBD::orderTable orderTable_test1;
  orderTable_test1.id = 1;
  orderTable_test1.status = "done";
  orderTable_test1.id_client = 0;
  orderTable_test1.adress = "Russia";
  orderTable_test1.id_office = 0;
  orderTable_test1.timeStart = "14:17";
  orderTable_test1.timeEnd = "15:02";
  ahDB->orderTable_create();
  ahDB->orderTable_insert(orderTable_test0);
  ahDB->orderTable_insert(orderTable_test1);
  QVector<HandlerBD::orderTable> test1 = ahDB->orderTable_getAll();
  ASSERT_THAT(test1[1].adress,Eq("Russia"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderTable_delete_Test)
{
  QString settingsfilename= "orderTable_delete_Test.ini";
  QString dbfilename = "orderTable_delete_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderTable orderTable_test0;
  orderTable_test0.id = 0;
  orderTable_test0.status = "working";
  orderTable_test0.id_client = 0;
  orderTable_test0.adress = "Russia";
  orderTable_test0.id_office = 0;
  orderTable_test0.timeStart = "12:12";
  orderTable_test0.timeEnd = "13:02";
  HandlerBD::orderTable orderTable_test1;
  orderTable_test1.id = 1;
  orderTable_test1.status = "done";
  orderTable_test1.id_client = 0;
  orderTable_test1.adress = "Russia";
  orderTable_test1.id_office = 0;
  orderTable_test1.timeStart = "14:17";
  orderTable_test1.timeEnd = "15:02";
  ahDB->orderTable_create();
  ahDB->orderTable_insert(orderTable_test0);
  ahDB->orderTable_insert(orderTable_test1);
  ahDB->orderTable_delete(orderTable_test0);
  QVector<HandlerBD::orderTable> test1 = ahDB->orderTable_getAll();
  ASSERT_THAT(test1[0].timeEnd,Eq("15:02"));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderCompilationTable_create_Test)
{
  QString settingsfilename= "orderCompilationTable_create_Test.ini";
  QString dbfilename = "orderCompilationTable_create_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->orderCompilationTable_create();
  ASSERT_THAT(ahDB->checkTable("orderCompilation_table"), Eq(true));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderCompilationTable_insert_Test)
{
  QString settingsfilename= "orderCompilationTable_insert_Test.ini";
  QString dbfilename = "orderCompilationTable_insert_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderCompilationTable orderCompilationTable_test;
  orderCompilationTable_test.id = 0;
  orderCompilationTable_test.id_order = 0;
  orderCompilationTable_test.id_pizza = 0;
  ahDB->orderCompilationTable_create();
  ahDB->orderCompilationTable_insert(orderCompilationTable_test);
  QVector<HandlerBD::orderCompilationTable> test1 = ahDB->orderCompilationTable_getAll();
  ASSERT_THAT(test1[0].id_order,Eq(0));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderCompilationTable_update_Test)
{
  QString settingsfilename= "orderCompilationTable_update_Test.ini";
  QString dbfilename = "orderCompilationTable_update_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderCompilationTable orderCompilationTable_test;
  orderCompilationTable_test.id = 0;
  orderCompilationTable_test.id_order = 0;
  orderCompilationTable_test.id_pizza = 0;
  ahDB->orderCompilationTable_create();
  ahDB->orderCompilationTable_update(orderCompilationTable_test);
  QVector<HandlerBD::orderCompilationTable> test1 = ahDB->orderCompilationTable_getAll();
  ASSERT_THAT(test1[0].id_order,Eq(0));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderCompilationTable_getAll_Test)
{
  QString settingsfilename= "orderCompilationTable_getAll_Test.ini";
  QString dbfilename = "orderCompilationTable_getAll_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderCompilationTable orderCompilationTable_test0;
  orderCompilationTable_test0.id = 0;
  orderCompilationTable_test0.id_order = 0;
  orderCompilationTable_test0.id_pizza = 0;
  HandlerBD::orderCompilationTable orderCompilationTable_test1;
  orderCompilationTable_test1.id = 1;
  orderCompilationTable_test1.id_order = 1;
  orderCompilationTable_test1.id_pizza = 1;
  ahDB->orderCompilationTable_create();
  ahDB->orderCompilationTable_insert(orderCompilationTable_test0);
  ahDB->orderCompilationTable_insert(orderCompilationTable_test1);
  QVector<HandlerBD::orderCompilationTable> test1 = ahDB->orderCompilationTable_getAll();
  ASSERT_THAT(test1[1].id_order,Eq(1));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

TEST(DatabaseTest, orderCompilationTable_delete_Test)
{
  QString settingsfilename= "orderCompilationTable_delete_Test.ini";
  QString dbfilename = "orderCompilationTable_delete_Test.sqlite";
  QFile dbfile( dbfilename );
  QFile file( settingsfilename );
  if ( file.open(QIODevice::ReadWrite) )
  {
      QTextStream stream( &file );
      stream << "[database]\n" <<  "path=\""<< dbfilename + '"' << '\n';
  }
  QSettings* aLocalSetting = crateLocalSettingWithPath(settingsfilename);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderCompilationTable orderCompilationTable_test0;
  orderCompilationTable_test0.id = 0;
  orderCompilationTable_test0.id_order = 0;
  orderCompilationTable_test0.id_pizza = 0;
  HandlerBD::orderCompilationTable orderCompilationTable_test1;
  orderCompilationTable_test1.id = 1;
  orderCompilationTable_test1.id_order = 1;
  orderCompilationTable_test1.id_pizza = 1;
  HandlerBD::orderCompilationTable orderCompilationTable_test2;
  orderCompilationTable_test2.id = 2;
  orderCompilationTable_test2.id_order = 2;
  orderCompilationTable_test2.id_pizza = 2;
  ahDB->orderCompilationTable_create();
  ahDB->orderCompilationTable_insert(orderCompilationTable_test0);
  ahDB->orderCompilationTable_insert(orderCompilationTable_test1);
  ahDB->orderCompilationTable_insert(orderCompilationTable_test2);
  ahDB->orderCompilationTable_delete(orderCompilationTable_test1);
  QVector<HandlerBD::orderCompilationTable> test1 = ahDB->orderCompilationTable_getAll();
  ASSERT_THAT(test1[1].id_order,Eq(2));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

#endif // TST_SERVERTEST_H
