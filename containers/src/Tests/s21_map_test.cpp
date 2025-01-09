#include "../s21_containers.h"
#include <gtest/gtest.h>

// Test for default constructor
TEST(MapTest, DefaultConstructor) {
  s21::map<int, std::string> map;
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

// Test for initializer list constructor
TEST(MapTest, InitializerListConstructor) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
}

// Test for copy constructor
TEST(MapTest, CopyConstructor) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> map2 = map1;
  EXPECT_EQ(map2.size(), map1.size());
  EXPECT_FALSE(map2.empty());
}

// Test for move constructor
TEST(MapTest, MoveConstructor) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> map2 = std::move(map1);
  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map1.empty());
}

// Test for insert method with value_type
TEST(MapTest, InsertValueType) {
  s21::map<int, std::string> map;
  auto result = map.insert({1, "one"});
  EXPECT_TRUE(result.second);
  auto hh = (*result.first).first;
  auto aa = (*result.first).second;
  EXPECT_EQ(hh, 1);
  EXPECT_EQ(aa, "one");
  result = map.insert({1, "one"});
  EXPECT_FALSE(result.second);
}

// Test for insert method with key and value
TEST(MapTest, InsertKeyValue) {
  s21::map<int, std::string> map;
  auto result = map.insert(1, "one");
  EXPECT_TRUE(result.second);
  auto hh = (*result.first).first;
  auto aa = (*result.first).second;
  EXPECT_EQ(hh, 1);
  EXPECT_EQ(aa, "one");
  result = map.insert(1, "one");
  EXPECT_FALSE(result.second);
}

// Test for insert_or_assign method
TEST(MapTest, InsertOrAssign) {
  s21::map<int, std::string> map;
  auto result = map.insert_or_assign(1, "one");
  EXPECT_TRUE(result.second);
  auto hh = (*result.first).first;
  auto aa = (*result.first).second;
  EXPECT_EQ(hh, 1);
  EXPECT_EQ(aa, "one");
  result = map.insert_or_assign(1, "two");
  auto zz = (*result.first).second;
  EXPECT_FALSE(result.second);
  EXPECT_EQ(zz, "two");
}

// Test for erase method
TEST(MapTest, Erase) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  map.erase(map.find(2));
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.find(2), map.end());
}

// Test for clear method
TEST(MapTest, Clear) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  map.clear();
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

// Test for swap method
TEST(MapTest, Swap) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> map2 = {{3, "three"}, {4, "four"}};
  map1.swap(map2);
  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ(map2.size(), 2);
}

// Test for merge method
TEST(MapTest, Merge) {
  s21::map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> map2 = {{3, "three"}, {4, "four"}};
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 4);
  EXPECT_TRUE(map2.empty());
}

// Test for contains method
TEST(MapTest, Contains) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}};
  EXPECT_TRUE(map.contains(1));
  EXPECT_FALSE(map.contains(3));
}

// Test for insert_many method
// TEST(MapTest, InsertMany) {
//   s21::map<int, std::string> map;
//   auto results = map.insert_many({1, "one"}, {2, "two"}, {3, "three"});
//   EXPECT_EQ(results.size(), 3);
//   for (const auto& result : results) {
//     EXPECT_TRUE(result.second);
//   }
//   EXPECT_EQ(map.size(), 3);
// }

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
