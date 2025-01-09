#ifndef S21_LIST_HPP
#define S21_LIST_HPP

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T> class list {
public:
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  class Node {
  public:
    Node(const T &value);
    T data_;
    Node *next_;
    Node *prev_;
  };

  class ListIterator {
  public:
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    ListIterator() : current_(nullptr){};
    ListIterator(Node *node, Node *last);
    reference operator*() const;
    pointer operator->();
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    bool operator==(const iterator &it) const;
    bool operator!=(const iterator &it) const;

    friend class list;

  private:
    Node *current_;
    Node *last_;
  };

  class ListConstIterator : public ListIterator {
  public:
    ListConstIterator() : ListIterator(){};
    ListConstIterator(const ListIterator &node, ListIterator &last);
    ListConstIterator(const ListIterator &other);

    friend class list;
  };

  list();
  list(size_type n);
  list(std::initializer_list<T> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(list &&l);

  reference front();
  reference back();

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void clear();

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  // Insert Many
  template <typename... Args> void insert_many_back(Args &&...args);

  template <typename... Args> void insert_many_front(Args &&...args);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

private:
  Node *head_;
  Node *tail_;
  size_type list_size_;
};

} // namespace s21

#include "s21_list.tpp"

#endif // S21_LIST_HPP
