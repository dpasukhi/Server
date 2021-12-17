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
  ahDB->deliverymanTable_insert({0,"test_last_name","test_first_name","test_middle_name",0,"test_phone","test_email","test_pass"});
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
  ahDB->orderProductsTable_insert({0,1,2});
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
  ahDB->orderProductsTable_insert({0,0,0});
  ahDB->orderProductsTable_insert({1,1,1});
  ahDB->orderProductsTable_insert({2,2,2});
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
  ahDB->orderProductsTable_insert({0,0,0});
  ahDB->orderProductsTable_insert({1,1,1});
  ahDB->orderProductsTable_insert({2,2,2});
  ahDB->orderProductsTable_delete({1,1,1});
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
  ahDB->clientDeliverymanTable_insert({0,1,2,3});
  QVector<HandlerBD::clientDeliverymanTable> test1 = ahDB->clientDeliverymanTable_getAll();
  ASSERT_THAT(test1[0].id_order,Eq(0));
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

#endif // TST_SERVERTEST_H
