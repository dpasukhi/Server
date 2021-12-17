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

#endif // TST_SERVERTEST_H
