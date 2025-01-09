#include "s21_array.hpp"

namespace s21 {
// базовичек контрсуктор заполненный нулми
template <typename T, std::size_t N> array<T, N>::array() {
  size_ = N;
  for (size_t i = 0; i < N; ++i) {
    elements_[i] = T();
  }
}

// инициализированный консутрктор для доступа к объектам const(которые ток для
// чтения)
template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("Wrong arr size");
  }
  size_type index = 0;
  for (const auto &item : items) {
    elements_[index++] = item;
  }
}

// конструктор копирования
template <typename T, std::size_t N> array<T, N>::array(const array &a) {
  for (size_type i = 0; i < N; ++i) {
    elements_[i] = a.elements_[i];
  }
}

// конструктор перемещения
template <typename T, std::size_t N> array<T, N>::array(array &&a) noexcept {
  for (size_type i = 0; i < N; ++i) {
    elements_[i] = std::move(a.elements_[i]);
    a.elements_[i] = T();
  }
}

// переобпределение оператора присваивания
template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array &a) {
  if (this != &a) {
    for (size_type i = 0; i < N; ++i) {
      elements_[i] = a.elements_[i];
    }
  }
  return *this;
}

// оператор присваивания с перемещением
template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) noexcept {
  if (this != &a) { // Защита от само-присваивания
    for (size_type i = 0; i < N; ++i) {
      elements_[i] = std::move(a.elements_[i]);
      a.elements_[i] = T();
    }
  }
  return *this;
}

// индексация для доступа к элемаентам массива
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return elements_[pos];
}

// коснтантная индексация для доступа к элемаентам массива
template <typename T, std::size_t N>
typename array<T, N>::const_reference
array<T, N>::operator[](size_type pos) const {
  return elements_[pos];
}

// доступ к элементам
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[pos];
}

// констуантный доступ к элементам
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[pos];
}

// ссылка на первый элемент контейнера
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return elements_[0];
}

// ссылка последний элемент контейнера
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return elements_[N - 1];
}

// итератор начала перебора
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return &elements_[0];
}

// итератор конца перебора
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return &elements_[N];
}

// итератор возвращает первый элемент контенерйа
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return &elements_[0];
}

// итератор начала перебора
template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const {
  return &elements_[0];
}

// итератор конца перебора
template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const {
  return &elements_[N];
}

// метож проверки контейнера на пустоту
template <typename T, std::size_t N> bool array<T, N>::empty() const noexcept {
  if (N == 0) {
    return true;
  } else {
    return false;
  }
}

// метож возвращает размер контейнера
template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return N;
}

// метод возвращает макс размер контейнера
template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return N;
}
} // namespace s21
