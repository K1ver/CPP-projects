#include "s21_set.hpp"

namespace s21 {

template <typename T> set<T>::set() {} // tree_

template <typename T>
set<T>::set(std::initializer_list<value_type> const &items) : tree_() {
  for (const auto &item : items) {
    tree_.InsertNode(item, item);
  }
}

template <typename T> // copy
set<T>::set(const set &s) {
  for (const auto &item : s) {
    tree_.InsertNode(item, item);
  }
}

template <typename T> // move
set<T>::set(set &&s) noexcept : tree_(std::move(s.tree_)) {
  tree_.FixSize();
  s.tree_.FixSize();
}

template <typename T> set<T>::~set() {}

template <typename T> set<T> &set<T>::operator=(set &&s) noexcept {
  if (this != &s) {
    tree_ = std::move(s.tree_);
    tree_.FixSize();
    s.tree_.FixSize();
  }
  return *this;
}

template <typename T> typename set<T>::iterator set<T>::begin() const {
  return tree_.begin();
}

template <typename T> typename set<T>::iterator set<T>::end() const {
  return tree_.end();
}

template <typename T> bool set<T>::empty() const { return tree_.empty(); }

template <typename T> typename set<T>::size_type set<T>::size() const {
  return tree_.size();
}

template <typename T> typename set<T>::size_type set<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T> void set<T>::clear() { tree_.clear(); }

template <typename T>
std::pair<typename set<T>::iterator, bool>
set<T>::insert(const value_type &value) {
  if (iterator(tree_.FindNode(value)) != tree_.end()) {
    return {tree_.end(), 0};
  }
  tree_.InsertNode(value, value);
  iterator result(tree_.FindNode(value));
  if (result == tree_.end()) {
    return {result, 0};
  }
  return {result, 1};
}

template <typename T> void set<T>::erase(iterator pos) {
  tree_.EraseNode(*pos);
}

template <typename T> void set<T>::swap(set &other) {
  if (this != &other) {
    set<T> temp = std::move(*this);
    *this = std::move(other);
    other = std::move(temp);
  }
}

template <typename T> void set<T>::merge(set &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}

template <typename T>
typename set<T>::iterator set<T>::find(const key_type &key) {
  return tree_.FindNode(key);
}

template <typename T> bool set<T>::contains(const key_type &key) const {
  return iterator(tree_.FindNode(key)) != tree_.end();
}

template <typename T>
template <typename... Args>
vector<std::pair<typename set<T>::iterator, bool>>
set<T>::insert_many(Args &&...args) {
  vector<std::pair<iterator, bool>> result;
  for (const auto &arg : {args...}) {
    result.push_back(insert(arg));
  }
  return result;
}
} // namespace s21
