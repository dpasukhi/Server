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

TEST(DatabaseTest, deliverymanTable_insert_test)
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
  HandlerBD ahDB;
  //ahDB.deliverymanTable_create(); //DB file and table created
  HandlerBD::deliverymanTable deliverymanTable_test = {0,"Test_lname","Test_fname","Test_mname",2,"test_phone","test_email", "test_pass"};
  ahDB.deliverymanTable_insert(deliverymanTable_test);
  QVector<HandlerBD::deliverymanTable> test1 = ahDB.deliverymanTable_getAll();
  ASSERT_THAT(test1[0].id_office, Eq(2));
  //ASSERT_THAT(ahDB.checkTable("deliveryman_table"), Eq(true)); //ERROR
  dbW.disconnect();
  file.remove();
  dbfile.remove();
}

#endif // TST_SERVERTEST_H
