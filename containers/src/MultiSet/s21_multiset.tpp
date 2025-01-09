#include "s21_multiset.hpp"

namespace s21 {

// constructor and destructor

template <typename Key> multiset<Key>::multiset() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const &items) {
  for (const auto &item : items) {
    tree_.InsertNode(item, item);
  }
}

template <typename Key> multiset<Key>::multiset(const multiset &ms) {
  for (const auto &item : ms) {
    tree_.InsertNode(item, item);
  }
}

template <typename Key>
multiset<Key>::multiset(multiset &&ms) : tree_(std::move(ms.tree_)) {
  tree_.FixSize();
  ms.tree_.FixSize();
}

template <typename Key> multiset<Key>::~multiset() {}

template <typename Key> multiset<Key> &multiset<Key>::operator=(multiset &&ms) {
  if (this != &ms) {
    tree_ = std::move(ms.tree_);
    tree_.FixSize();
    ms.tree_.FixSize();
  }
  return *this;
}

// iterators

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() const {
  return tree_.begin();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() const {
  return tree_.end();
}

// capacity

template <typename Key> bool multiset<Key>::empty() { return tree_.empty(); }

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() {
  return tree_.size();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  return tree_.max_size();
}

// modifiers
template <typename Key> void multiset<Key>::clear() { tree_.clear(); }

template <typename Key>
typename multiset<Key>::iterator
multiset<Key>::insert(const value_type &value) {
  tree_.InsertNodeWithDublicate(value, value);
  return tree_.FindNode(value);
}

template <typename Key> void multiset<Key>::erase(iterator pos) {
  tree_.EraseNode(*pos);
}

template <typename Key> void multiset<Key>::swap(multiset *other) {
  if (this != other) {
    multiset<Key> temp = std::move(*this);
    *this = std::move(*other);
    *other = std::move(temp);
  }
}

template <typename Key> void multiset<Key>::merge(multiset &other) {
  for (auto it = other.begin(); it != other.end(); it++) {
    this->insert(*it);
  }
  other.clear();
}

// lookup
template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  typename multiset<Key>::size_type size = 0;
  auto it = this->find(key);
  auto it_end = this->end();
  if (it != it_end) {
    while (*it++ == *it) {
      ++size;
    }
    ++size;
  }
  return size;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key &key) {
  return tree_.FindNode(key);
}

template <typename Key> bool multiset<Key>::contains(const Key &key) {
  return this->find(key) != this->end() ? 1 : 0;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) {
  auto it = this->begin();
  while (*it != key && it != this->end())
    it++;
  if (it != this->end())
    it++;
  return it;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) {
  auto it = this->begin();
  while (*it != key && it != this->end())
    it++;
  if (it != this->end()) {
    while (*it++ == *it)
      ;
  }
  return it;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  return {this->lower_bound(key), this->upper_bound(key)};
}

template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args &&...args) {
  s21::vector<std::pair<typename multiset<Key>::iterator, bool>> res;
  for (const auto &arg : {args...}) {
    auto it = this->insert(arg);
    res.push_back({it, 1});
  }

  return res;
}

} // namespace s21