#include "s21_queue.hpp"

namespace s21 {

template <typename T> queue<T>::queue() : container_() {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : container_(items) {}

template <typename T>
queue<T>::queue(const queue &q) : container_(q.container_) {}

template <typename T>
queue<T>::queue(queue &&q) : container_(std::move(q.container_)) {}

template <typename T> queue<T>::~queue() {}

template <typename T> queue<T> &queue<T>::operator=(queue &&q) {
  if (this != &q) {
    this->container_ = std::move(q.container_);
  }
  return *this;
}

template <typename T> typename queue<T>::const_reference queue<T>::front() {
  return container_.front();
}

template <typename T> typename queue<T>::const_reference queue<T>::back() {
  return container_.back();
}

template <typename T> bool queue<T>::empty() { return container_.empty(); }

template <typename T> typename queue<T>::size_type queue<T>::size() {
  return container_.size();
}

template <typename T> void queue<T>::push(const_reference value) {
  this->container_.push_back(value);
}

template <typename T> void queue<T>::pop() { this->container_.pop_front(); }

template <typename T> void queue<T>::swap(queue &other) {
  this->container_.swap(other.container_);
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  (container_.push(std::forward<Args>(args)), ...);
}

} // namespace s21