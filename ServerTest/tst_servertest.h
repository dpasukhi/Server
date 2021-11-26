#ifndef TST_SERVERTEST_H
#define TST_SERVERTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(ServerTest, ServerTest)
{
  EXPECT_EQ(1, 1);
  ASSERT_THAT(0, Eq(0));
}

#endif // TST_SERVERTEST_H
