#include <gtest/gtest.h>

#include "../s21_containersplus.h"

TEST(S21ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 0); // Проверяем, что все элементы равны 0
  }
}

TEST(S21ArrayTest, InitializerListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3};
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  for (size_t i = 3; i < 5; ++i) {
    EXPECT_EQ(arr[i], 0); // Остальные элементы должны быть равны 0
  }
}

TEST(S21ArrayTest, CopyConstructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2 = arr1; // Копирование
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(S21ArrayTest, CopyAssignmentOperator) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2;
  arr2 = arr1; // Копирование через оператор присваивания
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(S21ArrayTest, AtMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(4), 5);
  try {
    arr.at(5); // Должен выбросить исключение
    FAIL() << "Expected std::out_of_range exception";
  } catch (const std::out_of_range &e) {
    // Ожидаем ошибку
  }
}

TEST(S21ArrayTest, IndexOperator) {
  s21::array<int, 5> arr = {10, 20, 30, 40, 50};
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[4], 50);
  arr[2] = 100; // Изменим значение
  EXPECT_EQ(arr[2], 100);
}

TEST(S21ArrayTest, EmptyMethod) {
  s21::array<int, 5> arr;
  EXPECT_FALSE(arr.empty()); // Проверим, что контейнер не пустой
  s21::array<int, 0> empty_arr;
  EXPECT_TRUE(
      empty_arr.empty()); // Контейнер с нулевым размером должен быть пустым
}

TEST(S21ArrayTest, FrontBackMethods) {
  s21::array<int, 5> arr = {10, 20, 30, 40, 50};
  EXPECT_EQ(arr.front(), 10);
  EXPECT_EQ(arr.back(), 50);
}

TEST(S21ArrayTest, IteratorMethods) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  size_t index = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    EXPECT_EQ(*it, arr[index]);
    ++index;
  }
}

TEST(S21ArrayTest, ConstArrayAccess) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.front(), 1);
  EXPECT_EQ(arr.back(), 5);
}
