#include "../s21_containersplus.h"
#include <gtest/gtest.h>

// Test for default constructor
TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

// Test for initializer list constructor
TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5};
  EXPECT_FALSE(ms.empty());
  EXPECT_EQ(ms.size(), 5);
}

// Test for copy constructor
TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = ms1;
  EXPECT_EQ(ms2.size(), ms1.size());
  EXPECT_FALSE(ms2.empty());
}

// Test for move constructor
TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = std::move(ms1);
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms1.empty());
}

// Test for insert method
TEST(MultisetTest, Insert) {
  s21::multiset<int> ms;
  auto it = ms.insert(1);
  EXPECT_EQ(*it, 1);
  it = ms.insert(1);
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(ms.size(), 2);
}

// Test for erase method
TEST(MultisetTest, Erase) {
  s21::multiset<int> ms = {1, 2, 3, 3, 4};
  ms.erase(ms.find(3));
  EXPECT_EQ(ms.size(), 4);
  EXPECT_EQ(ms.count(3), 1);
}

// Test for clear method
TEST(MultisetTest, Clear) {
  s21::multiset<int> ms = {1, 2, 3};
  ms.clear();
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

// Test for swap method
TEST(MultisetTest, Swap) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {4, 5, 6};
  ms1.swap(&ms2);
  EXPECT_EQ(ms1.size(), 3);
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_EQ(ms1.find(1), ms1.end());
  EXPECT_EQ(ms2.find(4), ms2.end());
}

// Test for merge method
TEST(MultisetTest, Merge) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {3, 4, 5};
  ms1.merge(ms2);
  EXPECT_EQ(ms1.size(), 6);
  EXPECT_TRUE(ms2.empty());
}

// Test for count method
TEST(MultisetTest, Count) {
  s21::multiset<int> ms = {1, 2, 2, 3, 3, 3};
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 3);
  EXPECT_EQ(ms.count(4), 0);
}

// Test for find method
TEST(MultisetTest, Find) {
  s21::multiset<int> ms = {1, 2, 3};
  auto it = ms.find(2);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 2);
}

// Test for contains method
TEST(MultisetTest, Contains) {
  s21::multiset<int> ms = {1, 2, 3};
  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(4));
}

// Test for lower_bound method
TEST(MultisetTest, LowerBound) {
  s21::multiset<int> ms = {1, 2, 2, 3, 3, 3, 4};
  auto it = ms.lower_bound(2);
  EXPECT_EQ(*it, 2);
}

// Test for upper_bound method
TEST(MultisetTest, UpperBound) {
  s21::multiset<int> ms = {1, 2, 2, 3, 3, 3, 4};
  auto it = ms.upper_bound(2);
  EXPECT_EQ(*it, 3);
}

// Test for equal_range method
TEST(MultisetTest, EqualRange) {
  s21::multiset<int> ms = {1, 2, 2, 3, 3, 3, 4};
  auto range = ms.equal_range(2);
  EXPECT_EQ(*range.first, 2);
  EXPECT_EQ(*range.second, 3);
}

// Test for insert_many method
TEST(MultisetTest, InsertMany) {
  s21::multiset<int> ms;
  auto results = ms.insert_many(1, 2, 3, 4, 5);
  EXPECT_EQ(results.size(), 5);
  for (const auto &result : results) {
    EXPECT_TRUE(result.second);
  }
  EXPECT_EQ(ms.size(), 5);
}