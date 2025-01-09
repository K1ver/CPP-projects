#include "../s21_containers.h" // Подключаем заголовочный файл с вашей реализацией класса Stack
#include <gtest/gtest.h>

// Тесты конструктора по умолчанию
TEST(StackTest, DefaultConstructor) {
  s21::stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

// Тесты конструктора со списком инициализации
TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> s({1, 2, 3});
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 3);
}

// Тесты конструктора копированияy
TEST(StackTest, CopyConstructor) {
  s21::stack<int> s1({1, 2, 3});
  s21::stack<int> s2(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

// Тесты конструктора перемещения
TEST(StackTest, MoveConstructor) {
  s21::stack<int> s1({1, 2, 3});
  s21::stack<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
  EXPECT_TRUE(s1.empty());
}

// Тесты метода push
TEST(StackTest, PushMethod) {
  s21::stack<int> s;
  s.push(10);
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 10);

  s.push(20);
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), 20);
}

// Тесты метода pop
TEST(StackTest, PopMethod) {
  s21::stack<int> s({1, 2, 3});
  s.pop();
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 1);
  s.pop();
  EXPECT_TRUE(s.empty());
}

// Тесты метода swap
TEST(StackTest, SwapMethod) {
  s21::stack<int> s1({1, 2, 3});
  s21::stack<int> s2({4, 5});
  s1.swap(s2);

  EXPECT_EQ(s1.size(), 2);
  EXPECT_EQ(s1.top(), 5);

  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

// Тесты метода top
TEST(StackTest, TopMethod) {
  s21::stack<int> s({1, 2, 3});
  EXPECT_EQ(s.top(), 3);

  s.pop();
  EXPECT_EQ(s.top(), 2);
}

// Тесты метода empty
TEST(StackTest, EmptyMethod) {
  s21::stack<int> s;
  EXPECT_TRUE(s.empty());

  s.push(1);
  EXPECT_FALSE(s.empty());
}

// Тесты метода size
TEST(StackTest, SizeMethod) {
  s21::stack<int> s;
  EXPECT_EQ(s.size(), 0);

  s.push(1);
  s.push(2);
  EXPECT_EQ(s.size(), 2);

  s.pop();
  EXPECT_EQ(s.size(), 1);
}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
