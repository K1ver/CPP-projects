#include "s21_map.hpp"

namespace s21 {

template <typename Key, typename T> map<Key, T>::map() {} // tree_

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : tree_() {
  for (const auto &item : items) {
    tree_.InsertNode(item.first, item.second);
  }
}

template <typename Key, typename T> map<Key, T>::map(const map &m) {
  for (const auto &item : m) {
    tree_.InsertNode(item.first, item.second);
  }
}

template <typename Key, typename T>
map<Key, T>::map(map &&m) : tree_(std::move(m.tree_)) {
  tree_.FixSize();
  m.tree_.FixSize();
}

template <typename Key, typename T> map<Key, T>::~map() {}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&m) {
  if (this != &m) {
    tree_ = std::move(m.tree_);
    tree_.FixSize();
    m.tree_.FixSize();
  }
  return *this;
}

template <typename Key, typename T> T &map<Key, T>::at(const Key &key) {
  iterator it = tree_.FindNode(key);
  return it.GetValue();
}

template <typename Key, typename T> T &map<Key, T>::operator[](const Key &key) {
  iterator it = tree_.FindNode(key);
  return it.GetValue();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() const {
  return tree_.pair_begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() const {
  return tree_.pair_end();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key &key) {
  return (tree_.FindNode(key));
}

template <typename Key, typename T> bool map<Key, T>::empty() const {
  return tree_.empty();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() const {
  return tree_.size();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename Key, typename T> void map<Key, T>::clear() { tree_.clear(); }

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert(const value_type &value) {
  return insert(value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert(const Key &key, const T &obj) {
  if (iterator(tree_.FindNode(key)) != end()) {
    return {end(), 0};
  }
  tree_.InsertNode(key, obj);
  iterator result(tree_.FindNode(key));
  if (result == end()) {
    return {result, 0};
  }
  return {result, 1};
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  iterator result(tree_.FindNode(key));
  if (result != tree_.end()) {
    erase(result);
    auto res = insert(key, obj);
    return {res.first, 0};
  }
  return insert(key, obj);
}

template <typename Key, typename T> void map<Key, T>::erase(iterator pos) {
  tree_.EraseNode((*pos).first);
}

template <typename Key, typename T> void map<Key, T>::swap(map &other) {
  if (this != &other) {
    map<Key, T> temp = std::move(*this);
    *this = std::move(other);
    other = std::move(temp);
  }
}

template <typename Key, typename T> void map<Key, T>::merge(map &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    tree_.InsertNode((*it).first, (*it).second);
  }
  other.clear();
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key &key) const {
  return iterator(tree_.FindNode(key)) != tree_.end();
}

template <typename Key, typename T>
template <typename... Args>
s21::vector<std::pair<typename map<Key, T>::iterator, bool>>
s21::map<Key, T>::insert_many(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> result;
  for (const auto &arg : {args...}) {
    result.push_back(insert(arg));
  }
  return result;
}
} // namespace s21
