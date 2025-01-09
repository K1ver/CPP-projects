#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(S21VectorTest, DefaultConstructor) {
  s21::vector<int> vec;
  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(S21VectorTest, ConstructorWithSize) {
  s21::vector<int> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], 0);
  }
}

TEST(S21VectorTest, InitializerListConstructor) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], i + 1);
  }
}

TEST(S21VectorTest, CopyConstructor) {
  s21::vector<int> vec1{1, 2, 3, 4, 5};
  s21::vector<int> vec2 = vec1;

  EXPECT_EQ(vec2.size(), vec1.size());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], vec1[i]);
  }
}

TEST(S21VectorTest, MoveConstructor) {
  s21::vector<int> vec1{1, 2, 3, 4, 5};
  s21::vector<int> vec2 = std::move(vec1);

  EXPECT_EQ(vec2.size(), 5);
  EXPECT_EQ(vec1.size(), 0);
}

TEST(S21VectorTest, PushBack) {
  s21::vector<int> vec;

  vec.push_back(10);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 10);

  vec.push_back(20);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[1], 20);
}

TEST(S21VectorTest, At) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(4), 5);
  EXPECT_THROW(vec.at(5), std::out_of_range);
}

TEST(S21VectorTest, Insert) {
  s21::vector<int> vec{1, 2, 4, 5};
  vec.insert(vec.begin() + 2, 3);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[2], 3);

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(vec[i], i + 1);
  }
}

TEST(S21VectorTest, PopBack) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  vec.pop_back();
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[3], 4);

  vec.pop_back();
  EXPECT_EQ(vec.size(), 3);
}

TEST(S21VectorTest, Reserve) {
  s21::vector<int> vec(5);

  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
  EXPECT_EQ(vec.size(), 5);

  EXPECT_THROW(vec.reserve(3), std::out_of_range);
}

TEST(S21VectorTest, ShrinkToFit) {
  s21::vector<int> vec(10);

  vec.reserve(20);
  EXPECT_GE(vec.capacity(), 20);

  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

TEST(S21VectorTest, Clear) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(S21VectorTest, Swap) {
  s21::vector<int> vec1{1, 2, 3};
  s21::vector<int> vec2{4, 5};

  vec1.swap(vec2);

  EXPECT_EQ(vec1.size(), 2);
  EXPECT_EQ(vec2.size(), 3);

  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec2[0], 1);
}

TEST(S21VectorTest, Erase) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  vec.erase(vec.begin() + 1);

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[1], 3);

  vec.erase(vec.begin() + 2);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[2], 5);
}

TEST(S21VectorTest, EraseOutOfRange) {
  s21::vector<int> vec{1, 2, 3};

  EXPECT_THROW(vec.erase(vec.begin() + 5), std::out_of_range);
}

TEST(S21VectorTest, OperatorAssign) {
  s21::vector<int> vec1{1, 2, 3};
  s21::vector<int> vec2{4, 5};

  vec2 = vec1;

  EXPECT_EQ(vec2.size(), vec1.size());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], vec1[i]);
  }
}

TEST(S21VectorTest, OperatorAssignSelf) {
  s21::vector<int> vec1{1, 2, 3};
  vec1 = vec1;

  EXPECT_EQ(vec1.size(), 3);
}

TEST(S21VectorTest, Empty) {
  s21::vector<int> vec;

  EXPECT_TRUE(vec.empty());

  vec.push_back(1);
  EXPECT_FALSE(vec.empty());
}

TEST(S21VectorTest, Front) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  EXPECT_EQ(vec.front(), 1);
}

TEST(S21VectorTest, Back) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  EXPECT_EQ(vec.back(), 5);
}

TEST(S21VectorTest, Data) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  EXPECT_EQ(*vec.data(), 1);
}

TEST(S21VectorTest, Begin) {
  s21::vector<int> vec{1, 2, 3};

  EXPECT_EQ(*vec.begin(), 1);
}

TEST(S21VectorTest, End) {
  s21::vector<int> vec{1, 2, 3};

  EXPECT_EQ(*(vec.end() - 1), 3);
}

TEST(S21VectorTest, Size) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  EXPECT_EQ(vec.size(), 5);
}

TEST(S21VectorTest, MaxSize) {
  s21::vector<int> vec;

  EXPECT_EQ(vec.max_size(), std::numeric_limits<size_t>::max() / sizeof(int));
}

TEST(S21VectorTest, InsertMany) {
  s21::vector<int> vec{1, 2, 5};
  vec.insert_many(vec.begin() + 2, 3, 4);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(S21VectorTest, InsertManyBack) {
  s21::vector<int> vec{1, 2};
  vec.insert_many_back(3, 4, 5);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(S21VectorTest, InsertAtBeginning) {
  s21::vector<int> vec{2, 3, 4};
  vec.insert(vec.begin(), 1);

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 1);
}

TEST(S21VectorTest, InsertAtEnd) {
  s21::vector<int> vec{1, 2, 3};
  vec.insert(vec.end(), 4);

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[3], 4);
}

TEST(S21VectorTest, CapacityGrowth) {
  s21::vector<int> vec;
  size_t initial_capacity = vec.capacity();

  vec.push_back(1);
  size_t new_capacity = vec.capacity();

  EXPECT_GE(new_capacity, 1);
  EXPECT_NE(initial_capacity, new_capacity);
}

TEST(S21VectorTest, CapacityDoubling) {
  s21::vector<int> vec;
  vec.reserve(2);

  vec.push_back(1);
  vec.push_back(2);
  size_t old_capacity = vec.capacity();

  vec.push_back(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_GT(vec.capacity(), old_capacity);
}

TEST(S21VectorTest, EraseSingleElement) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  vec.erase(vec.begin() + 2);

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[2], 4);
}

TEST(S21VectorTest, IteratorValidityAfterPushBack) {
  s21::vector<int> vec{1, 2, 3};
  auto it = vec.begin();

  vec.push_back(4);

  EXPECT_EQ(*it, 1);
}

TEST(S21VectorTest, IteratorValidityAfterInsert) {
  s21::vector<int> vec{1, 3, 4};
  auto it = vec.begin();

  vec.insert(vec.begin() + 1, 2);

  EXPECT_EQ(*it, 1);
  EXPECT_EQ(vec[1], 2);
}

TEST(S21VectorTest, ConstIteratorAccess) {
  const s21::vector<int> vec{1, 2, 3};
  auto it = vec.begin();

  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(S21VectorTest, AssignmentToEmptyVector) {
  s21::vector<int> vec1{1, 2, 3};
  s21::vector<int> vec2;

  vec2 = vec1;

  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}
