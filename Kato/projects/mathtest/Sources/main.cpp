#include "Vector3.h"
#include "gtest\gtest.h"

TEST(Test1, Vec3Test)
{
  EXPECT_EQ(Vector3(), Vector3(0.f, 0.f, 0.f));
}