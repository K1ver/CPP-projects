#include "../s21_containers.h"
#include <gtest/gtest.h>

// Test for default constructor
TEST(SetTest, DefaultConstructor) {
  s21::set<int> set;
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

// Test for initializer list constructor
TEST(SetTest, InitializerListConstructor) {
  s21::set<int> set = {1, 2, 3, 4, 5};
  EXPECT_FALSE(set.empty());
  EXPECT_EQ(set.size(), 5);
}

// Test for copy constructor
TEST(SetTest, CopyConstructor) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = set1;
  EXPECT_EQ(set2.size(), set1.size());
  EXPECT_FALSE(set2.empty());
}

// Test for move constructor
TEST(SetTest, MoveConstructor) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = std::move(set1);
  EXPECT_EQ(set2.size(), 3);
  EXPECT_TRUE(set1.empty());
}

// Test for insert method
TEST(SetTest, Insert) {
  s21::set<int> set;
  auto result = set.insert(1);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(*result.first, 1);
  result = set.insert(1);
  EXPECT_FALSE(result.second);
}

// Test for erase method
TEST(SetTest, Erase) {
  s21::set<int> set = {1, 2, 3};
  set.erase(set.find(2));
  EXPECT_EQ(set.size(), 2);
  EXPECT_EQ(set.find(2), set.end());
}

// Test for clear method
TEST(SetTest, Clear) {
  s21::set<int> set = {1, 2, 3};
  set.clear();
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

// Test for swap method
TEST(SetTest, Swap) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};
  set1.swap(set2);
  EXPECT_EQ(set1.size(), 3);
  EXPECT_EQ(set2.size(), 3);
  EXPECT_EQ(set1.find(1), set1.end());
  EXPECT_EQ(set2.find(4), set2.end());
}

// Test for merge method
TEST(SetTest, Merge) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {3, 4, 5};
  set1.merge(set2);
  EXPECT_EQ(set1.size(), 5);
  EXPECT_TRUE(set2.empty());
}

// Test for find method
TEST(SetTest, Find) {
  s21::set<int> set = {1, 2, 3};
  auto it = set.find(2);
  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 2);
}

// Test for contains method
TEST(SetTest, Contains) {
  s21::set<int> set = {1, 2, 3};
  EXPECT_TRUE(set.contains(2));
  EXPECT_FALSE(set.contains(4));
}

// Test for insert_many method
TEST(SetTest, InsertMany) {
  s21::set<int> set;
  auto results = set.insert_many(1, 2, 3, 4, 5);
  EXPECT_EQ(results.size(), 5);
  for (const auto &result : results) {
    EXPECT_TRUE(result.second);
  }
  EXPECT_EQ(set.size(), 5);
}

TEST(SetTest, operators) {
  s21::set<int> set;
  set.insert_many(1, 2, 3, 4, 5);
  auto it = set.end();
  EXPECT_EQ(*--it, 5);
  EXPECT_EQ(*--it, 4);
  EXPECT_EQ(*it--, 4);
  EXPECT_EQ(*it, 3);
  set.erase(it);
  it = set.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it, 2);
  EXPECT_NE(*++it, 3);
  set.insert_many(8, 16, 5, 11, 18, 35, 100, 15, 28);
  it = set.begin();
  set.erase(++it);
  it = set.begin();
  EXPECT_NE(*++it, 2);
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
