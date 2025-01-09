#include "s21_vector.hpp"

namespace s21 {
// баZOVвый конструктор
template <typename T> vector<T>::vector() {
  size_ = 0;
  capacity_ = 0;
  elements_ = nullptr;
}

// почти баZOVый шаблонный конструктор
template <typename T> vector<T>::vector(size_type n) {
  if (n == 0) {
    size_ = 0;
    capacity_ = 0;
    elements_ = nullptr;
  } else {
    size_ = n;
    capacity_ = n;
    elements_ = new value_type[capacity_];

    for (size_type i = 0; i < size_; ++i) {
      elements_[i] = value_type();
    }
  }
}

// инициализированный констрктор
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  if (items.size() == 0) {
    size_ = 0;
    capacity_ = 0;
    elements_ = nullptr;
  } else {
    size_ = items.size();
    capacity_ = size_;
    elements_ = new value_type[capacity_];
  }
  size_type index = 0;
  for (const auto &item : items) {
    elements_[index++] = item;
  }
}

// конструктор копирования
template <typename T> vector<T>::vector(const vector &v) {
  if (v.size_ == 0) {
    size_ = 0;
    capacity_ = 0;
    elements_ = nullptr;
  } else {
    size_ = v.size_;
    capacity_ = v.capacity_;
    elements_ = new value_type[capacity_];

    for (size_type i = 0; i < size_; ++i) {
      elements_[i] = v.elements_[i];
    }
  }
}

// конструктор переноса
template <typename T> vector<T>::vector(vector &&v) noexcept {
  if (v.size_ == 0) {
    size_ = 0;
    capacity_ = 0;
    elements_ = nullptr;
  } else {
    size_ = v.size_;
    capacity_ = v.capacity_;
    elements_ = v.elements_;

    v.size_ = 0;
    v.capacity_ = 0;
    v.elements_ = nullptr;
  }
}

// деустрктор
template <typename T> vector<T>::~vector() { delete[] elements_; }

// опреатор присваиваня для конст
template <typename T> vector<T> &vector<T>::operator=(const vector &v) {
  if (this == &v) {
    return *this;
  }

  delete[] elements_;

  size_ = v.size_;
  capacity_ = v.capacity_;
  elements_ = new value_type[capacity_];
  for (size_type i = 0; i < size_; ++i) {
    elements_[i] = v.elements_[i];
  }
  return *this;
}

// доступ к  индексация
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[pos];
}

// доступ к  конст индексация
template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos > size_) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[pos];
}

// доступ к элементам
template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return elements_[pos];
}

// доступ к конст элементам
template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return elements_[pos];
}

// итератор начала перебора
template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return elements_[0];
}

// итератор конца перебора
template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return elements_[size_ - 1];
}

// итератор возвращения первого жлемента
template <typename T> typename vector<T>::iterator vector<T>::data() {
  return &elements_[0];
}

// итератор начала перебора
template <typename T> typename vector<T>::iterator vector<T>::begin() {
  return &elements_[0];
}

// итератор конца перебора
template <typename T> typename vector<T>::iterator vector<T>::end() {
  return &elements_[size_];
}

// конст итератор начала перебора
template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return &elements_[0];
}

// конст итератор конца перебора
template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return &elements_[size_];
}

// пустой ли контейнер
template <typename T> bool vector<T>::empty() const noexcept {
  return begin() == end();
}

// возвраащает рамзер контйнера
template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

// возвращает максимальный размер конйтенера
template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

//  подгоняет лишнию память под нужную емкость
template <typename T> void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    capacity_ = size_;
  }
}

// выделяет хранилище для всех жлементов и пермещивает их в новый массив
template <typename T> void vector<T>::reserve(size_type size) {
  if (size < capacity_) {
    throw std::out_of_range("Index out of range");
  }

  T *new_elements_ = new T[size];

  for (size_type i = 0; i < size_; ++i) {
    new_elements_[i] = std::move(elements_[i]);
  }
  delete[] elements_;

  elements_ = new_elements_;
  capacity_ = size;
}

// возвращает ёмкость контейнера
template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

// чистит размер контейнера но не трогет емкость
template <typename T> void vector<T>::clear() {
  while (begin() != end())
    pop_back();
}

// перенос из 1 в другой
template <typename T> void vector<T>::swap(vector &other) {
  std::swap(other.size_, this->size_);
  std::swap(other.capacity_, this->capacity_);
  std::swap(other.elements_, this->elements_);
}

// убирает последний элемент
template <typename T> void vector<T>::pop_back() {
  if (size_ > 0) {
    size_--;
  } else {
    throw std::out_of_range("Index out of range");
  }
}

// стираем какое то значение в векторе
template <typename T> void vector<T>::erase(iterator pos) {
  size_type elementpos = std::distance(elements_, pos);
  if (elementpos > size_) {
    throw std::out_of_range("Index out of range");
  }
  for (size_type i = elementpos + 1; i < size_; ++i) {
    elements_[i - 1] = elements_[i];
  }
  size_--;
}

// добавляет элемент и увеличвает массив крг
template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = std::distance(elements_, pos);

  if (size_ == capacity_) {
    if (capacity_ == 0) {
      reserve(1);
    } else {
      reserve(capacity_ * 2);
    }
  }

  if (index < size_) {
    for (size_type i = size_; i > index; --i) {
      elements_[i] = std::move(elements_[i - 1]);
    }
  }

  elements_[index] = value;
  ++size_;

  return elements_ + index;
}

// добавляет элемент в конец масива
template <typename T> void vector<T>::push_back(const_reference value) {
  this->insert(this->end(), value);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  size_type index = std::distance(const_cast<const_iterator>(begin()), pos);
  size_type count = sizeof...(args);

  if (size_ + count > capacity_) {
    reserve(std::max(capacity_ * 2, size_ + count));
  }

  for (size_type i = size_; i > index; --i) {
    elements_[i + count - 1] = std::move(elements_[i - 1]);
  }

  T temp[] = {std::forward<Args>(args)...};
  for (size_type i = 0; i < count; ++i) {
    elements_[index + i] = std::move(temp[i]);
  }

  size_ += count;
  return begin() + index;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

} // namespace s21
