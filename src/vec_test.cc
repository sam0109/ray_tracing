#include "src/vec.h"

#include "gtest/gtest.h"

// Demonstrate some basic assertions.
TEST(VecTest, BasicStorageAndRetrieval) {
  Vec<double, 3> v0;
  EXPECT_EQ(v0[0], 0.0);
  EXPECT_EQ(v0[1], 0.0);
  EXPECT_EQ(v0[2], 0.0);

  Vec<double, 3> v1{1.0, 2.0, 3.0};
  EXPECT_EQ(v1[0], 1.0);
  EXPECT_EQ(v1[1], 2.0);
  EXPECT_EQ(v1[2], 3.0);

  Vec<double, 1> v2{1.0};
  EXPECT_EQ(v2.X(), 1.0);
}

TEST(VecTest, Addition) {
  Vec<double, 3> v1{1.0, 2.0, 3.0};
  Vec<double, 3> v2{3.0, 2.0, 1.0};
  v1 += v2;
  EXPECT_EQ(v1.Y(), 4.0);
}

TEST(VecTest, Multiplication) {
  Vec<double, 3> v1{1.0, 2.0, 3.0};
  v1 *= 5;
  EXPECT_EQ(v1.Y(), 10.0);
}

TEST(VecTest, Negation) {
  Vec<double, 3> v1{1.0, 2.0, 3.0};
  EXPECT_EQ((-v1).Y(), -2.0);
}

TEST(VecTest, Division) {
  Vec<double, 3> v1{1.0, 2.0, 3.0};
  v1 /= 2;
  EXPECT_EQ(v1.Y(), 1.0);
}

TEST(VecTest, Length) {
  Vec<double, 3> v1{2.0, 3.0, 6.0};
  EXPECT_EQ(v1.length_squared(), 49.0);
  EXPECT_EQ(v1.length(), 7.0);
}