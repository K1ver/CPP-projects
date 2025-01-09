#ifndef CONTAINER_MAP_HPP
#define CONTAINER_MAP_HPP

#include "../RedBlackTree/s21_RBTree.hpp"

namespace s21 {
template <typename Key, typename T> class map {
public:
  class MapIterator;
  class ConstMapIterator;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<Key, T>::pair_iterator;
  using const_iterator = typename RBTree<Key, T>::pair_const_iterator;
  using size_type = std::size_t;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map &operator=(map &&m);

  T &at(const Key &key);
  T &operator[](const Key &key);

  iterator begin() const;
  iterator end() const;
  iterator find(const Key &key);

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  bool contains(const Key &key) const;

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

private:
  RBTree<Key, T> tree_;
};
} // namespace s21

#include "s21_map.tpp"

#endif
