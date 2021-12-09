#ifndef TST_SERVERTEST_H
#define TST_SERVERTEST_H

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <dbworker.h>
#include <handlerbd.h>
#include <qsettings.h>
#include <fstream>
#include <experimental/filesystem>
#include <fstream>
#include <string>
using namespace testing;

QString getFilePath(const QString& theFileName)
{
  namespace fs = std::experimental::filesystem;
  QString aPath = fs::current_path().string().c_str();
  aPath = aPath.toCaseFolded();
  aPath += "\\";
  aPath+= theFileName;
  aPath.replace("\\","\\\\");
  return aPath;
}

QSettings* crateLocalSettingWithPath(const QString& theName)
{
  return new QSettings(theName, QSettings::IniFormat, nullptr);
}

TEST(DatabaseTest, checkTable_Test)
{
  QString aSetPath = getFilePath("checkTableTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("checkTableTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliverymanTable_create();
  ASSERT_THAT(ahDB->checkTable("deliveryman_table"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("checkTableTest.ini");
  std::remove("checkTableTest.sqlite");
}
/*
TEST(DatabaseTest, checkUser_Test)
{
  QString aSetPath = getFilePath("checkUserTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("checkUserTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliverymanTable test {0,"test_last_name","test_first_name","test_middle_name",0,"test_phone","test_email","test_pass"};
  ahDB->deliverymanTable_create();
  ahDB->deliverymanTable_insert(test);
  ASSERT_THAT(ahDB->checkUser("deliveryman_table", "test_email", "test_pass"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("checkUserTest.ini");
  std::remove("checkUserTest.sqlite");
}
*/
TEST(DatabaseTest, orderProductsTable_create_Test)
{
  QString aSetPath = getFilePath("orderProductsTable_create_Test.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("orderProductsTable_create_Test.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->orderProductsTable_create();
  ASSERT_THAT(ahDB->checkTable("orderProducts_table"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("orderProductsTable_create_Test.ini");
  std::remove("orderProductsTable_create_Test.sqlite");
}

TEST(DatabaseTest, orderProductsTable_Insert_Test)
{
  QString aSetPath = getFilePath("orderProductsTable_Insert_Test.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("orderProductsTable_Insert_Test.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderProductsTable orderProductsTable_test = {0,1,2};
  ahDB->orderProductsTable_create();
  ahDB->orderProductsTable_insert(orderProductsTable_test);
  QVector<HandlerBD::orderProductsTable> test = ahDB->orderProductsTable_getAll();
  ASSERT_THAT(test[0].id_product,Eq(2));
  dbW.disconnect();
  outfile.close();
  std::remove("orderProductsTable_Insert_Test.ini");
  std::remove("orderProductsTable_Insert_Test.sqlite");
}

TEST(DatabaseTest, orderProductsTable_Update_Test)
{
  QString aSetPath = getFilePath("orderProductsTable_UpdateTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("orderProductsTable_UpdateTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderProductsTable orderProductsTable_test = {0,1,2};
  ahDB->orderProductsTable_update(orderProductsTable_test);
  QVector<HandlerBD::orderProductsTable> test1 = ahDB->orderProductsTable_getAll();
  ASSERT_THAT(test1[0].id_order,Eq(1));
  dbW.disconnect();
  outfile.close();
  std::remove("orderProductsTable_UpdateTest.ini");
  std::remove("orderProductsTable_UpdateTest.sqlite");
}

TEST(DatabaseTest, orderProductsTable_GetAll_Test)
{
  QString aSetPath = getFilePath("orderProductsTable_GetAllTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("orderProductsTable_GetAllTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderProductsTable orderProductsTable_test0 = {0,0,0};
  HandlerBD::orderProductsTable orderProductsTable_test1 = {1,1,1};
  HandlerBD::orderProductsTable orderProductsTable_test2 = {2,2,2};
  ahDB->orderProductsTable_insert(orderProductsTable_test0);
  ahDB->orderProductsTable_insert(orderProductsTable_test1);
  ahDB->orderProductsTable_insert(orderProductsTable_test2);
  QVector<HandlerBD::orderProductsTable> test1 = ahDB->orderProductsTable_getAll();
  ASSERT_THAT(test1[0].id,Eq(0));
  dbW.disconnect();
  outfile.close();
  std::remove("orderProductsTable_GetAllTest.ini");
  std::remove("orderProductsTable_GetAllTest.sqlite");
}

TEST(DatabaseTest, orderProductsTable_delete_Test)
{
  QString aSetPath = getFilePath("orderProductsTable_deleteTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("orderProductsTable_deleteTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::orderProductsTable orderProductsTable_test0 = {0,0,0};
  HandlerBD::orderProductsTable orderProductsTable_test1 = {1,1,1};
  HandlerBD::orderProductsTable orderProductsTable_test2 = {2,2,2};
  ahDB->orderProductsTable_insert(orderProductsTable_test0);
  ahDB->orderProductsTable_insert(orderProductsTable_test1);
  ahDB->orderProductsTable_insert(orderProductsTable_test2);
  ahDB->orderProductsTable_delete(orderProductsTable_test1);
  QVector<HandlerBD::orderProductsTable> test1 = ahDB->orderProductsTable_getAll();
  ASSERT_THAT(test1[1].id_order,Eq(2));
  dbW.disconnect();
  outfile.close();
  std::remove("orderProductsTable_deleteTest.ini");
  std::remove("orderProductsTable_deleteTest.sqlite");
}

TEST(DatabaseTest, clientDeliverymanTable_create_Test)
{
  QString aSetPath = getFilePath("clientDeliverymanTable_createTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientDeliverymanTable_createTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->clientDeliverymanTable_create();
  ASSERT_THAT(ahDB->checkTable("clientDeliveryman_table"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("clientDeliverymanTable_createTest.ini");
  std::remove("clientDeliverymanTable_createTest.sqlite");
}

TEST(DatabaseTest, clientDeliverymanTable_insert_Test)
{
  QString aSetPath = getFilePath("clientDeliverymanTable_insertTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientDeliverymanTable_insertTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  const HandlerBD::clientDeliverymanTable clientDeliverymanTable_test = {0,1,2,3};
  ahDB->clientDeliverymanTable_create();
  ahDB->clientDeliverymanTable_insert(clientDeliverymanTable_test);
  QVector<HandlerBD::clientDeliverymanTable> test1 = ahDB->clientDeliverymanTable_getAll();
  ASSERT_THAT(test1[0].id_order,Eq(0));
  dbW.disconnect();
  outfile.close();
  std::remove("clientDeliverymanTable_insertTest.ini");
  std::remove("clientDeliverymanTable_insertTest.sqlite");
}

TEST(DatabaseTest, clientDeliverymanTable_update_Test)
{
  QString aSetPath = getFilePath("clientDeliverymanTable_update.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientDeliverymanTable_update.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientDeliverymanTable orderProductsTable_test = {0,1,2,3};
  ahDB->clientDeliverymanTable_create();
  ahDB->clientDeliverymanTable_update(orderProductsTable_test);
  QVector<HandlerBD::clientDeliverymanTable> test1 = ahDB->clientDeliverymanTable_getAll();
  ASSERT_THAT(test1[0].id_deliver,Eq(2));
  dbW.disconnect();
  outfile.close();
  std::remove("clientDeliverymanTable_update.ini");
  std::remove("clientDeliverymanTable_update.sqlite");
}

TEST(DatabaseTest, clientDeliverymanTable_getAll_Test)
{
  QString aSetPath = getFilePath("clientDeliverymanTablegetAll.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientDeliverymanTablegetAll.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientDeliverymanTable clientDeliverymanTable_test0 = {0,0,0,0};
  HandlerBD::clientDeliverymanTable clientDeliverymanTable_test1 = {1,1,1,1};
  HandlerBD::clientDeliverymanTable clientDeliverymanTable_test2 = {2,2,2,2};
  ahDB->clientDeliverymanTable_create();
  ahDB->clientDeliverymanTable_insert(clientDeliverymanTable_test0);
  ahDB->clientDeliverymanTable_insert(clientDeliverymanTable_test1);
  ahDB->clientDeliverymanTable_insert(clientDeliverymanTable_test2);
  QVector<HandlerBD::clientDeliverymanTable> test1 = ahDB->clientDeliverymanTable_getAll();
  ASSERT_THAT(test1[2].id_deliver,Eq(2));
  dbW.disconnect();
  outfile.close();
  std::remove("clientDeliverymanTablegetAll.ini");
  std::remove("clientDeliverymanTablegetAll.sqlite");
}

TEST(DatabaseTest, clientDeliverymanTable_delete_Test)
{
  QString aSetPath = getFilePath("clientDeliverymanTable_delete.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientDeliverymanTable_delete.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientDeliverymanTable orderProductsTable_test0 = {0,0,0,0};
  HandlerBD::clientDeliverymanTable orderProductsTable_test1 = {1,1,1,1};
  HandlerBD::clientDeliverymanTable orderProductsTable_test2 = {2,2,2,2};
  ahDB->clientDeliverymanTable_create();
  ahDB->clientDeliverymanTable_insert(orderProductsTable_test0);
  ahDB->clientDeliverymanTable_insert(orderProductsTable_test1);
  ahDB->clientDeliverymanTable_insert(orderProductsTable_test2);
  ahDB->clientDeliverymanTable_delete(orderProductsTable_test1);
  QVector<HandlerBD::clientDeliverymanTable> test1 = ahDB->clientDeliverymanTable_getAll();
  ASSERT_THAT(test1[1].id_client,Eq(2));
  dbW.disconnect();
  outfile.close();
  std::remove("clientDeliverymanTable_delete.ini");
  std::remove("clientDeliverymanTable_delete.sqlite");
}

TEST(DatabaseTest, deliverymanTable_create_Test)
{
  QString aSetPath = getFilePath("deliverymanTable_createTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("deliverymanTable_createTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliverymanTable_create();
  ASSERT_THAT(ahDB->checkTable("deliveryman_table"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("deliverymanTable_createTest.ini");
  std::remove("deliverymanTable_createTest.sqlite");
}

TEST(DatabaseTest, deliverymanTable_insert_Test)
{
  QString aSetPath =getFilePath("deliverymanTableinsertTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("deliverymanTableinsertTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliverymanTable deliverymanTable_test = {0,"Test_lname","Test_fname","Test_mname",2,"test_phone","test_email", "test_pass"};
  ahDB->deliverymanTable_create();
  ahDB->deliverymanTable_insert(deliverymanTable_test);
  QVector<HandlerBD::deliverymanTable> test1 = ahDB->deliverymanTable_getAll();
  ASSERT_THAT(1,Eq(1));
  dbW.disconnect();
  outfile.close();
  std::remove("deliverymanTableinsertTest.ini");
  std::remove("deliverymanTableinsertTest.sqlite");
}

TEST(DatabaseTest, deliverymanTable_update_Test)
{
  QString aSetPath = getFilePath("DeliverymanTableupdate.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("DeliverymanTableupdate.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  const HandlerBD::deliverymanTable deliverymanTable_test = {0,"Test_lname","Test_fname","Test_mname",2,"test_phone","test_email", "test_pass"};
  ahDB->deliverymanTable_create();
  ahDB->deliverymanTable_update(deliverymanTable_test);
  QVector<HandlerBD::deliverymanTable> test1 = ahDB->deliverymanTable_getAll();
  ASSERT_THAT(1,Eq(1));
  dbW.disconnect();
  outfile.close();
  std::remove("DeliverymanTableupdate.ini");
  std::remove("DeliverymanTableupdate.sqlite");
}

TEST(DatabaseTest, deliverymanTable_getAll_Test)
{
  QString aSetPath = getFilePath("deliverymanTable_getAllTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("deliverymanTable_getAllTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliverymanTable deliverymanTable_test0 = {0,"last_name0","first_name0","middle_name0",0,"phone0","email0","pass0"};
  HandlerBD::deliverymanTable deliverymanTable_test1 = {1,"last_name1","first_name1","middle_name1",5,"phone1","email1","pass1"};
  HandlerBD::deliverymanTable deliverymanTable_test2 = {2,"last_name2","first_name2","middle_name2",1,"phone2","email2","pass2"};
  ahDB->deliverymanTable_create();
  ahDB->deliverymanTable_insert(deliverymanTable_test0);
  ahDB->deliverymanTable_insert(deliverymanTable_test1);
  ahDB->deliverymanTable_insert(deliverymanTable_test2);
  QVector<HandlerBD::deliverymanTable> test1 = ahDB->deliverymanTable_getAll();
  ASSERT_THAT(1,Eq(1));
  dbW.disconnect();
  outfile.close();
  std::remove("deliverymanTable_getAllTest.ini");
  std::remove("deliverymanTable_getAllTest.sqlite");
}

TEST(DatabaseTest, checkDeliveryman_Test)
{
  QString aSetPath = getFilePath("checkDeliverymanTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("checkDeliverymanTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliverymanTable deliverymanTable_test0 = {0,"Test_lname","Test_fname","Test_mname",2,"test_phone","test_email", "test_pass"};
  ahDB->deliverymanTable_create();
  ahDB->deliverymanTable_insert(deliverymanTable_test0);
  ASSERT_THAT(1,Eq(1));
  dbW.disconnect();
  outfile.close();
  std::remove("checkDeliverymanTest.ini");
  std::remove("checkDeliverymanTest.sqlite");
}

TEST(DatabaseTest, deliverymanTable_delete_Test)
{
  QString aSetPath = getFilePath("deliverymanTable_deleteTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("deliverymanTable_deleteTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliverymanTable deliverymanTable_test0 = {0,"Test_lname0","Test_fname0","Test_mname0",0,"test_phone0","test_email0", "test_pass0"};
  HandlerBD::deliverymanTable deliverymanTable_test1 = {1,"Test_lname1","Test_fname1","Test_mname1",1,"test_phone1","test_email1", "test_pass1"};
  HandlerBD::deliverymanTable deliverymanTable_test2 = {2,"Test_lname2","Test_fname2","Test_mname2",2,"test_phone2","test_email2", "test_pass2"};
  ahDB->deliverymanTable_create();
  ahDB->deliverymanTable_insert(deliverymanTable_test0);
  ahDB->deliverymanTable_insert(deliverymanTable_test1);
  ahDB->deliverymanTable_insert(deliverymanTable_test2);
  ahDB->deliverymanTable_delete(deliverymanTable_test1);
  QVector<HandlerBD::deliverymanTable> test1 = ahDB->deliverymanTable_getAll();
  ASSERT_THAT(1,Eq(1));
  dbW.disconnect();
  outfile.close();
  std::remove("deliverymanTable_deleteTest.ini");
  std::remove("deliverymanTable_deleteTest.sqlite");
}

TEST(DatabaseTest, clientTable_create_Test)
{
  QString aSetPath = getFilePath("clientTable_createTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientTable_createTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->clientTable_create();
  ASSERT_THAT(ahDB->checkTable("client_table"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("clientTable_createTest.ini");
  std::remove("clientTable_createTest.sqlite");
}

TEST(DatabaseTest, clientTable_insert_Test)
{
  QString aSetPath = getFilePath("clientTable_insertTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientTable_insertTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  const HandlerBD::clientTable clientTable_test = {0,"test_mail","test_password","test_lname","test_fname","test_mname","test_phone"};
  ahDB->clientTable_create();
  ahDB->clientTable_insert(clientTable_test);
  QVector<HandlerBD::clientTable> test1 = ahDB->clientTable_getAll();
  ASSERT_THAT(test1[0].pass,Eq("test_password"));
  dbW.disconnect();
  outfile.close();
  std::remove("clientTable_insertTest.ini");
  std::remove("clientTable_insertTest.sqlite");
}

TEST(DatabaseTest, clientTable_update_Test)
{
  QString aSetPath = getFilePath("clientTable_updateTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientTable_updateTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientTable clientTable_test = {0,"test_mail","test_password","test_lname","test_fname","test_mname","test_phone"};
  ahDB->clientTable_create();
  ahDB->clientTable_update(clientTable_test);
  QVector<HandlerBD::clientTable> test1 = ahDB->clientTable_getAll();
  ASSERT_THAT(test1[0].pass,Eq("test_password"));
  dbW.disconnect();
  outfile.close();
  std::remove("clientTable_updateTest.ini");
  std::remove("clientTable_updateTest.sqlite");
}

TEST(DatabaseTest, clientTable_getAll_Test)
{
  QString aSetPath = getFilePath("clientTable_getAllTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientTable_getAllTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientTable clientTable_test0 = {0,"test_mail0","test_password0","test_lname0","test_fname0","test_mname0","test_phone0"};
  HandlerBD::clientTable clientTable_test1 = {1,"test_mail1","test_password1","test_lname1","test_fname1","test_mname1","test_phone1"};
  HandlerBD::clientTable clientTable_test2 = {2,"test_mail2","test_password2","test_lname2","test_fname2","test_mname2","test_phone2"};
  ahDB->clientTable_create();
  ahDB->clientTable_insert(clientTable_test0);
  ahDB->clientTable_insert(clientTable_test1);
  ahDB->clientTable_insert(clientTable_test2);
  QVector<HandlerBD::clientTable> test1 = ahDB->clientTable_getAll();
  ASSERT_THAT(test1[2].email,Eq("test_mail2"));
  dbW.disconnect();
  outfile.close();
  std::remove("clientTable_getAllTest.ini");
  std::remove("clientTable_getAllTest.sqlite");
}

TEST(DatabaseTest, checkClient_Test)
{
  QString aSetPath = getFilePath("checkClientTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("checkClientTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientTable clientTable_test0 = {0,"test_mail","test_password","test_lname","test_fname","test_mname","test_phone"};
  ahDB->clientTable_create();
  ahDB->clientTable_insert(clientTable_test0);
  ASSERT_THAT(1,Eq(1));
  dbW.disconnect();
  outfile.close();
  std::remove("checkClientTest.ini");
  std::remove("checkClientTest.sqlite");
}

TEST(DatabaseTest, clientTable_delete_Test)
{
  QString aSetPath = getFilePath("clientTable_deleteTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("clientTable_deleteTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::clientTable clientTable_test0 = {0,"test_mail0","test_password0","test_lname0","test_fname0","test_mname0","test_phone0"};
  HandlerBD::clientTable clientTable_test1 = {1,"test_mail1","test_password1","test_lname1","test_fname1","test_mname1","test_phone1"};
  HandlerBD::clientTable clientTable_test2 = {2,"test_mail2","test_password2","test_lname2","test_fname2","test_mname2","test_phone2"};
  ahDB->clientTable_create();
  ahDB->clientTable_insert(clientTable_test0);
  ahDB->clientTable_insert(clientTable_test1);
  ahDB->clientTable_insert(clientTable_test2);
  ahDB->clientTable_delete(clientTable_test1);
  QVector<HandlerBD::clientTable> test1 = ahDB->clientTable_getAll();
  ASSERT_THAT(test1[1].email,Eq("test_mail2"));
  dbW.disconnect();
  outfile.close();
  std::remove("clientTable_deleteTest.ini");
  std::remove("clientTable_deleteTest.sqlite");
}

TEST(DatabaseTest, deliveryTable_create_Test)
{
  QString aSetPath = getFilePath("deliveryTable_createTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("deliveryTable_createTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->deliveryTable_create();
  ASSERT_THAT(ahDB->checkTable("delivery_table"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("deliveryTable_createTest.ini");
  std::remove("deliveryTable_createTest.sqlite");
}

TEST(DatabaseTest, deliveryTable_insert_Test)
{
  QString aSetPath = getFilePath("deliveryTable_insertTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("deliveryTable_insertTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  const HandlerBD::deliveryTable deliveryTable_test = {0,0,0,0,"12:12"};
  ahDB->deliveryTable_create();
  ahDB->deliveryTable_insert(deliveryTable_test);
  QVector<HandlerBD::deliveryTable> test1 = ahDB->deliveryTable_getAll();
  ASSERT_THAT(test1[0].time,Eq("12:12"));
  dbW.disconnect();
  outfile.close();
  std::remove("deliveryTable_insertTest.ini");
  std::remove("deliveryTable_insertTest.sqlite");
}

TEST(DatabaseTest, deliveryTable_update_Test)
{
  QString aSetPath = getFilePath("deliveryTable_updateTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("deliveryTable_updateTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliveryTable deliveryTable_test = {0,0,0,0,"21:21"};
  ahDB->deliveryTable_create();
  ahDB->deliveryTable_update(deliveryTable_test);
  QVector<HandlerBD::deliveryTable> test1 = ahDB->deliveryTable_getAll();
  ASSERT_THAT(test1[0].time,Eq("21:21"));
  dbW.disconnect();
  outfile.close();
  std::remove("deliveryTable_updateTest.ini");
  std::remove("deliveryTable_updateTest.sqlite");
}

TEST(DatabaseTest, deliveryTable_getAll_Test)
{
  QString aSetPath = getFilePath("deliveryTable_getAllTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("deliveryTable_getAllTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliveryTable deliveryTable_test0 = {0,0,0,0,"15:12"};
  HandlerBD::deliveryTable deliveryTable_test1 = {1,1,1,1,"16:22"};
  HandlerBD::deliveryTable deliveryTable_test2 = {2,2,2,2,"17:40"};
  ahDB->deliveryTable_create();
  ahDB->deliveryTable_insert(deliveryTable_test0);
  ahDB->deliveryTable_insert(deliveryTable_test1);
  ahDB->deliveryTable_insert(deliveryTable_test2);
  QVector<HandlerBD::deliveryTable> test1 = ahDB->deliveryTable_getAll();
  ASSERT_THAT(test1[2].time,Eq("17:40"));
  dbW.disconnect();
  outfile.close();
  std::remove("deliveryTable_getAllTest.ini");
  std::remove("deliveryTable_getAllTest.sqlite");
}

TEST(DatabaseTest, deliveryTable_delete_Test)
{
  QString aSetPath = getFilePath("deliveryTable_deleteTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("deliveryTable_deleteTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::deliveryTable deliveryTable_test0 = {0,0,0,0,"15:40"};
  HandlerBD::deliveryTable deliveryTable_test1 = {1,1,1,1,"14:40"};
  HandlerBD::deliveryTable deliveryTable_test2 = {2,2,2,2,"18:10"};
  ahDB->deliveryTable_insert(deliveryTable_test0);
  ahDB->deliveryTable_insert(deliveryTable_test1);
  ahDB->deliveryTable_insert(deliveryTable_test2);
  ahDB->deliveryTable_delete(deliveryTable_test1);
  QVector<HandlerBD::deliveryTable> test1 = ahDB->deliveryTable_getAll();
  ASSERT_THAT(test1[1].time,Eq("18:10"));
  dbW.disconnect();
  outfile.close();
  std::remove("deliveryTable_deleteTest.ini");
  std::remove("deliveryTable_deleteTest.sqlite");
}

TEST(DatabaseTest, stateTable_create_Test)
{
  QString aSetPath =getFilePath("stateTable_createTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("stateTable_createTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->stateTable_create();
  ASSERT_THAT(ahDB->checkTable("state_table"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("stateTable_createTest.ini");
  std::remove("stateTable_createTest.sqlite");
}

TEST(DatabaseTest, stateTable_insert_Test)
{
  QString aSetPath = getFilePath("stateTable_insertTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("stateTable_insertTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  const HandlerBD::stateTable stateTable_test = {0, "in progress"};
  ahDB->stateTable_create();
  ahDB->stateTable_insert(stateTable_test);
  QVector<HandlerBD::stateTable> test1 = ahDB->stateTable_getAll();
  ASSERT_THAT(test1[0].condition,Eq("in progress"));
  dbW.disconnect();
  outfile.close();
  std::remove("stateTable_insertTest.ini");
  std::remove("stateTable_insertTest.sqlite");
}

TEST(DatabaseTest, stateTable_update_Test)
{
  QString aSetPath = getFilePath("stateTable_updateTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("stateTable_updateTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::stateTable stateTable_test = {0,"in progress"};
  ahDB->stateTable_create();
  ahDB->stateTable_update(stateTable_test);
  QVector<HandlerBD::stateTable> test1 = ahDB->stateTable_getAll();
  ASSERT_THAT(test1[0].condition,Eq("in progress"));
  dbW.disconnect();
  outfile.close();
  std::remove("stateTable_updateTest.ini");
  std::remove("stateTable_updateTest.sqlite");
}

TEST(DatabaseTest, stateTable_getAll_Test)
{
  QString aSetPath = getFilePath("stateTable_getAllTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("stateTable_getAllTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::stateTable stateTable_test0 = {0,"in progress"};
  HandlerBD::stateTable stateTable_test1 = {1,"starting"};
  HandlerBD::stateTable stateTable_test2 = {2,"delivered"};
  ahDB->stateTable_create();
  ahDB->stateTable_insert(stateTable_test0);
  ahDB->stateTable_insert(stateTable_test1);
  ahDB->stateTable_insert(stateTable_test2);
  QVector<HandlerBD::stateTable> test1 = ahDB->stateTable_getAll();
  ASSERT_THAT(test1[2].condition,Eq("delivered"));
  dbW.disconnect();
  outfile.close();
  std::remove("stateTable_getAllTest.ini");
  std::remove("stateTable_getAllTest.sqlite");
}

TEST(DatabaseTest, stateTable_delete_Test)
{
  QString aSetPath = getFilePath("stateTable_deleteTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("stateTable_deleteTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::stateTable stateTable_test0 = {0,"in progress"};
  HandlerBD::stateTable stateTable_test1 = {1,"starting"};
  HandlerBD::stateTable stateTable_test2 = {2,"delivered"};
  ahDB->stateTable_create();
  ahDB->stateTable_insert(stateTable_test0);
  ahDB->stateTable_insert(stateTable_test1);
  ahDB->stateTable_insert(stateTable_test2);
  ahDB->stateTable_delete(stateTable_test1);
  QVector<HandlerBD::stateTable> test1 = ahDB->stateTable_getAll();
  ASSERT_THAT(test1[1].condition,Eq("delivered"));
  dbW.disconnect();
  outfile.close();
  std::remove("stateTable_deleteTest.ini");
  std::remove("stateTable_deleteTest.sqlite");
}

TEST(DatabaseTest, locationTable_create_Test)
{
  QString aSetPath = getFilePath("locationTable_createTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("locationTable_createTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->locationTable_create();
  ASSERT_THAT(ahDB->checkTable("location_table"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("locationTable_createTest.ini");
  std::remove("locationTable_createTest.sqlite");
}

TEST(DatabaseTest, locationTable_insert_Test)
{
  QString aSetPath = getFilePath("locationTable_insertTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("locationTable_insertTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  const HandlerBD::locationTable locationTable_test = {0,"office"};
  ahDB->locationTable_create();
  ahDB->locationTable_insert(locationTable_test);
  QVector<HandlerBD::locationTable> test1 = ahDB->locationTable_getAll();
  ASSERT_THAT(test1[0].office,Eq("office"));
  dbW.disconnect();
  outfile.close();
  std::remove("locationTable_insertTest.ini");
  std::remove("locationTable_insertTest.sqlite");
}

TEST(DatabaseTest, locationTable_update_Test)
{
  QString aSetPath = getFilePath("locationTable_updateTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("locationTable_updateTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::locationTable locationTable_test = {0,"Default"};
  ahDB->locationTable_create();
  ahDB->locationTable_update(locationTable_test);
  QVector<HandlerBD::locationTable> test1 = ahDB->locationTable_getAll();
  ASSERT_THAT(test1[0].office,Eq("Default"));
  dbW.disconnect();
  outfile.close();
  std::remove("locationTable_updateTest.ini");
  std::remove("locationTable_updateTest.sqlite");
}

TEST(DatabaseTest, locationTable_getAll_Test)
{
  QString aSetPath = getFilePath("locationTable_getAllTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("locationTable_getAllTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::locationTable locationTable_test0 = {0,"Home"};
  HandlerBD::locationTable locationTable_test1 = {1,"Office"};
  HandlerBD::locationTable locationTable_test2 = {2,"Default"};
  ahDB->locationTable_create();
  ahDB->locationTable_insert(locationTable_test0);
  ahDB->locationTable_insert(locationTable_test1);
  ahDB->locationTable_insert(locationTable_test2);
  QVector<HandlerBD::locationTable> test1 = ahDB->locationTable_getAll();
  ASSERT_THAT(test1[2].office,Eq("Default"));
  dbW.disconnect();
  outfile.close();
  std::remove("locationTable_getAllTest.ini");
  std::remove("locationTable_getAllTest.sqlite");
}

TEST(DatabaseTest, locationTable_delete_Test)
{
  QString aSetPath = getFilePath("locationTable_deleteTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("locationTable_deleteTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::locationTable locationTable_test0 = {0,"Home"};
  HandlerBD::locationTable locationTable_test1 = {1,"Office"};
  HandlerBD::locationTable locationTable_test2 = {2,"Metro"};
  ahDB->locationTable_create();
  ahDB->locationTable_insert(locationTable_test0);
  ahDB->locationTable_insert(locationTable_test1);
  ahDB->locationTable_insert(locationTable_test2);
  ahDB->locationTable_delete(locationTable_test1);
  QVector<HandlerBD::locationTable> test1 = ahDB->locationTable_getAll();
  ASSERT_THAT(test1[1].office,Eq("Metro"));
  dbW.disconnect();
  outfile.close();
  std::remove("locationTable_deleteTest.ini");
  std::remove("locationTable_deleteTest.sqlite");
}

TEST(DatabaseTest, productsTable_create_Test)
{
  QString aSetPath = getFilePath("productsTable_createTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("productsTable_createTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  ahDB->productsTable_create();
  ASSERT_THAT(ahDB->checkTable("products_table"), Eq(true));
  dbW.disconnect();
  outfile.close();
  std::remove("productsTable_createTest.ini");
  std::remove("productsTable_createTest.sqlite");
}

TEST(DatabaseTest, productsTable_insert_Test)
{
  QString aSetPath = getFilePath("productsTable_insertTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("productsTable_insertTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  const HandlerBD::productsTable productsTable_test = {0,"pizza_name","desc", 350.00};
  ahDB->productsTable_create();
  ahDB->productsTable_insert(productsTable_test);
  QVector<HandlerBD::productsTable> test1 = ahDB->productsTable_getAll();
  ASSERT_THAT(test1[0].pizza_name,Eq("pizza_name"));
  dbW.disconnect();
  outfile.close();
  std::remove("productsTable_insertTest.ini");
  std::remove("productsTable_insertTest.sqlite");
}

TEST(DatabaseTest, productsTable_update_Test)
{
  QString aSetPath = getFilePath("productsTable_updateTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("productsTable_updateTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::productsTable productsTable_test = {0,"Cheese","desc",450.00};
  ahDB->productsTable_create();
  ahDB->productsTable_update(productsTable_test);
  QVector<HandlerBD::productsTable> test1 = ahDB->productsTable_getAll();
  ASSERT_THAT(test1[0].pizza_name,Eq("Cheese"));
  dbW.disconnect();
  outfile.close();
  std::remove("productsTable_updateTest.ini");
  std::remove("productsTable_updateTest.sqlite");
}

TEST(DatabaseTest, productsTable_getAll_Test)
{
  QString aSetPath = getFilePath("productsTable_getAll_Test.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("productsTable_getAll_Test.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::productsTable productsTable_test0 = {0,"Cheeze","", 450.00};
  HandlerBD::productsTable productsTable_test1 = {1,"Salami","", 400.00};
  HandlerBD::productsTable productsTable_test2 = {2,"Pepper","", 420.00};
  ahDB->productsTable_create();
  ahDB->productsTable_insert(productsTable_test0);
  ahDB->productsTable_insert(productsTable_test1);
  ahDB->productsTable_insert(productsTable_test2);
  QVector<HandlerBD::productsTable> test1 = ahDB->productsTable_getAll();
  ASSERT_THAT(test1[1].pizza_name,Eq("Salami"));
  dbW.disconnect();
  outfile.close();
  std::remove("productsTable_getAll_Test.ini");
  std::remove("productsTable_getAll_Test.sqlite");
}

TEST(DatabaseTest, productsTable_delete_Test)
{
  QString aSetPath = getFilePath("productsTable_deleteTest.ini");
  std::ofstream outfile(aSetPath.toStdString());
  QString abIniFile = getFilePath("productsTable_deleteTest.sqlite");
  outfile<< "[database]\n" <<  "path=\""<< abIniFile.toStdString() + '"' << '\n' << std::endl;
  QSettings* aLocalSetting = crateLocalSettingWithPath(aSetPath);
  aLocalSetting->beginGroup("database");
  dbworker dbW(aLocalSetting);
  dbW.connect();
  HandlerBD* ahDB = dbW.GetWorker();
  HandlerBD::productsTable productsTable_test0 = {0,"Cheeze","desc", 420.00};
  HandlerBD::productsTable productsTable_test1 = {1,"Salami","desc", 400.00};
  HandlerBD::productsTable productsTable_test2 = {2,"Pepper","desc", 420.00};
  ahDB->productsTable_create();
  ahDB->productsTable_insert(productsTable_test0);
  ahDB->productsTable_insert(productsTable_test1);
  ahDB->productsTable_insert(productsTable_test2);
  ahDB->productsTable_delete(productsTable_test1);
  QVector<HandlerBD::productsTable> test1 = ahDB->productsTable_getAll();
  ASSERT_THAT(test1[1].pizza_name,Eq("Pepper"));
  dbW.disconnect();
  outfile.close();
  std::remove("productsTable_deleteTest.ini");
  std::remove("productsTable_deleteTest.sqlite");
}

#endif // TST_SERVERTEST_H
