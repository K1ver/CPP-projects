#include "s21_stack.hpp"

namespace s21 {

template <class T> stack<T>::stack() : container_() {}

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : container_(items) {}

template <class T> stack<T>::stack(const stack &s) : container_(s.container_) {}

template <class T>
stack<T>::stack(stack &&s) : container_(std::move(s.container_)) {}

template <class T> stack<T>::~stack() {}

template <class T> stack<T> &stack<T>::operator=(stack &&s) {
  this->container_ = std::move(s.container_);
  return *this;
}

template <class T> typename stack<T>::const_reference stack<T>::top() {
  return container_.back();
}

template <class T> bool stack<T>::empty() { return container_.empty(); }

template <class T> typename stack<T>::size_type stack<T>::size() {
  return container_.size();
}

template <class T> void stack<T>::push(const_reference value) {
  this->container_.push_back(value);
}

template <class T> void stack<T>::pop() { this->container_.pop_back(); }

template <class T> void stack<T>::swap(stack &other) {
  this->container_.swap(other.container_);
}

template <class T>
template <class... Args>
void stack<T>::insert_many_back(Args &&...args) {
  (container_.push_back(std::forward<Args>(args)), ...);
}

} // namespace s21
