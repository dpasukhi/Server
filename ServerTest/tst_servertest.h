#ifndef TST_SERVERTEST_H
#define TST_SERVERTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <dbworker.h>
#include <handlerbd.h>
#include <qsettings.h>

using namespace testing;

QSettings* crateLocalSettingWithPath(const QString& Path)
{
  return new QSettings;
}

TEST(ServerTest, ServerTest)
{
  QSettings* aLocalSetting = crateLocalSettingWithPath("ThePath");
  HandlerBD hd;
  dbworker dbW(aLocalSetting);
  EXPECT_EQ(1, 1);
  ASSERT_THAT(0, Eq(0));
}

#endif // TST_SERVERTEST_H
