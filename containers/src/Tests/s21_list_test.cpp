#include "../s21_containers.h"
#include <gtest/gtest.h>

// Test for default constructor
TEST(ListTest, DefaultConstructor) {
  s21::list<int> lst;
  EXPECT_TRUE(lst.empty());
  EXPECT_EQ(lst.size(), 0);
}

// Test for constructor with size
TEST(ListTest, SizeConstructor) {
  s21::list<int> lst(5);
  EXPECT_FALSE(lst.empty());
  EXPECT_EQ(lst.size(), 5);
}

// Test for initializer list constructor
TEST(ListTest, InitializerListConstructor) {
  s21::list<int> lst = {1, 2, 3, 4, 5};
  EXPECT_FALSE(lst.empty());
  EXPECT_EQ(lst.size(), 5);
}

// Test for copy constructor
TEST(ListTest, CopyConstructor) {
  s21::list<int> lst1 = {1, 2, 3};
  s21::list<int> lst2 = lst1;
  EXPECT_EQ(lst2.size(), lst1.size());
  EXPECT_FALSE(lst2.empty());
}

// Test for move constructor
TEST(ListTest, MoveConstructor) {
  s21::list<int> lst1 = {1, 2, 3};
  s21::list<int> lst2 = std::move(lst1);
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_TRUE(lst1.empty());
}

// Test for front method
TEST(ListTest, Front) {
  s21::list<int> lst = {1, 2, 3};
  EXPECT_EQ(lst.front(), 1);
}

// Test for back method
TEST(ListTest, Back) {
  s21::list<int> lst = {1, 2, 3};
  EXPECT_EQ(lst.back(), 3);
}

// Test for insert method
TEST(ListTest, Insert) {
  s21::list<int> lst = {1, 2, 3};
  auto it = lst.insert(lst.begin(), 0);
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(lst.size(), 4);
}

// Test for erase method
TEST(ListTest, Erase) {
  s21::list<int> lst = {1, 2, 3};
  lst.erase(lst.begin());
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), 2);
}

// Test for push_back method
TEST(ListTest, PushBack) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.back(), 2);
}

// Test for pop_back method
TEST(ListTest, PopBack) {
  s21::list<int> lst = {1, 2, 3};
  lst.pop_back();
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.back(), 2);
}

// Test for push_front method
TEST(ListTest, PushFront) {
  s21::list<int> lst;
  lst.push_front(1);
  lst.push_front(2);
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), 2);
}

// Test for pop_front method
TEST(ListTest, PopFront) {
  s21::list<int> lst = {1, 2, 3};
  lst.pop_front();
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), 2);
}

// Test for swap method
TEST(ListTest, Swap) {
  s21::list<int> lst1 = {1, 2, 3};
  s21::list<int> lst2 = {4, 5, 6};
  lst1.swap(lst2);
  EXPECT_EQ(lst1.size(), 3);
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_EQ(lst1.front(), 4);
  EXPECT_EQ(lst2.front(), 1);
}

// Test for merge method
TEST(ListTest, Merge) {
  s21::list<int> lst1 = {1, 2, 3};
  s21::list<int> lst2 = {4, 5, 6};
  lst1.merge(lst2);
  EXPECT_EQ(lst1.size(), 6);
  EXPECT_TRUE(lst2.empty());
}

// Test for splice method
TEST(ListTest, Splice) {
  s21::list<int> lst1 = {1, 2, 3};
  s21::list<int> lst2 = {4, 5, 6};
  lst1.splice(lst1.end(), lst2);
  EXPECT_EQ(lst1.size(), 6);
  EXPECT_TRUE(lst2.empty());
}

// Test for reverse method
TEST(ListTest, Reverse) {
  s21::list<int> lst = {1, 2, 3};
  lst.reverse();
  EXPECT_EQ(lst.front(), 3);
  EXPECT_EQ(lst.back(), 1);
}

// Test for unique method
TEST(ListTest, Unique) {
  s21::list<int> lst = {1, 1, 2, 2, 3, 3};
  lst.unique();
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);
}

// Test for sort method
TEST(ListTest, Sort) {
  s21::list<int> lst = {3, 1, 2};
  lst.sort();
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);
}

// Test for insert_many_back method
TEST(ListTest, InsertManyBack) {
  s21::list<int> lst;
  lst.insert_many_back(1, 2, 3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.back(), 3);
}

// Test for insert_many_front method
TEST(ListTest, InsertManyFront) {
  s21::list<int> lst;
  lst.insert_many_front(1, 2, 3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 3);
}

// Test for insert_many method
TEST(ListTest, InsertMany) {
  s21::list<int> lst = {1, 2, 3};
  auto it = lst.insert_many(lst.begin(), 4, 5, 6);
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(lst.size(), 6);
}
