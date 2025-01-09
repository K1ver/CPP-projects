#ifndef S21_MULTISET_HPP
#define S21_MULTISET_HPP

#include "../RedBlackTree/s21_RBTree.hpp"

namespace s21 {
template <typename Key> class multiset {
public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<key_type, value_type>::iterator;
  using const_iterator = typename RBTree<key_type, value_type>::const_iterator;
  using size_type = size_t;

private:
  RBTree<key_type, value_type> tree_;

public:
  // constructor and destructor
  multiset(); // default
  multiset(std::initializer_list<value_type> const
               &items);         // initializer list constructor
  multiset(const multiset &ms); // copy constructor
  multiset(multiset &&ms);      // move constructor
  ~multiset();                  // destructor

  multiset &
  operator=(multiset &&ms); // assignment operator overload for moving object

  // iterators
  iterator begin() const;
  iterator end() const;

  // capacity

  bool empty();
  size_type size();
  size_type max_size();

  // modifiers
  void clear();
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(multiset *other);
  void merge(multiset &other);

  // lookup
  size_type count(const Key &key);
  iterator find(const Key &key);
  bool contains(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};
} // namespace s21

#include "s21_multiset.tpp"

#endif