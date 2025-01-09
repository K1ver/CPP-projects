#ifndef CONTAINER_SET_HPP
#define CONTAINER_SET_HPP

#include "../RedBlackTree/s21_RBTree.hpp"

namespace s21 {
template <typename T> class set {
public:
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename RBTree<T, T>::iterator;
  using const_iterator = typename RBTree<T, T>::const_iterator;
  using size_type = std::size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s) noexcept;
  ~set();

  set &operator=(set &&s) noexcept;

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const key_type &key);
  bool contains(const key_type &key) const;

  // допы
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

private:
  RBTree<T, T> tree_;
};
} // namespace s21

#include "s21_set.tpp"

#endif
