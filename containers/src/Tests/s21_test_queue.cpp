#include "../s21_containers.h" // Подключаем заголовочный файл с вашей реализацией класса Queue
#include <gtest/gtest.h>

// Тесты конструктора по умолчанию
TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

// Тесты конструктора со списком инициализации
TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q({1, 2, 3});
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

// Тесты конструктора копирования
TEST(QueueTest, CopyConstructor) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

// Тесты конструктора перемещения
TEST(QueueTest, MoveConstructor) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
  EXPECT_TRUE(q1.empty());
}

// Тесты метода push
TEST(QueueTest, PushMethod) {
  s21::queue<int> q;
  q.push(10);
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 10);

  q.push(20);
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 20);
}

// Тесты метода pop
TEST(QueueTest, PopMethod) {
  s21::queue<int> q({1, 2, 3});
  q.pop();
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_TRUE(q.empty());
}

// Тесты метода swap
TEST(QueueTest, SwapMethod) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2({4, 5});
  q1.swap(q2);

  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 5);

  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

// Тесты методов front и back
TEST(QueueTest, FrontAndBackMethods) {
  s21::queue<int> q({1, 2, 3});
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);

  q.pop();
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.back(), 3);
}

// Тесты метода empty
TEST(QueueTest, EmptyMethod) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());

  q.push(1);
  EXPECT_FALSE(q.empty());
}

// Тесты метода size
TEST(QueueTest, SizeMethod) {
  s21::queue<int> q;
  EXPECT_EQ(q.size(), 0);

  q.push(1);
  q.push(2);
  EXPECT_EQ(q.size(), 2);

  q.pop();
  EXPECT_EQ(q.size(), 1);
}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
