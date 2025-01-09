#include "s21_list.hpp"

namespace s21 {

template <typename T>
list<T>::Node::Node(const T &value)
    : data_(value), next_(nullptr), prev_(nullptr) {}

// ListIterator

template <typename T>
list<T>::ListIterator::ListIterator(Node *node, Node *last)
    : current_(node), last_(last) {}

template <typename T>
typename list<T>::ListIterator::reference
list<T>::ListIterator::operator*() const {
  return current_->data_;
}

template <typename T>
typename list<T>::ListIterator::pointer list<T>::ListIterator::operator->() {
  return &current_->data_;
}

template <typename T>
typename list<T>::iterator &list<T>::ListIterator::operator++() {
  if (current_)
    current_ = current_->next_;
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator++(int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename T>
typename list<T>::iterator &list<T>::ListIterator::operator--() {
  if (current_)
    current_ = current_->prev_;
  else
    current_ = last_;
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator--(int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T>
bool list<T>::ListIterator::operator==(
    const typename list<T>::iterator &it) const {
  return this->current_ == it.current_;
}

template <typename T>
bool list<T>::ListIterator::operator!=(
    const typename list<T>::iterator &it) const {
  return this->current_ != it.current_;
}

// ListConstIterator

template <typename T>
list<T>::ListConstIterator::ListConstIterator(const ListIterator &node,
                                              ListIterator &last)
    : ListIterator(node, last) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(const ListIterator &other)
    : ListIterator(other.current_, other.last_) {}

// Constructors and Destructors
template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), list_size_(0) {}

template <typename T>
list<T>::list(typename list<T>::size_type n)
    : head_(nullptr), tail_(nullptr), list_size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<T> const &items)
    : head_(nullptr), tail_(nullptr), list_size_(0) {
  for (const auto &item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list &l) : head_(nullptr), tail_(nullptr), list_size_(0) {
  for (auto it = l.begin(); it != l.end(); it++) {
    push_back(*it);
  }
}

template <typename T>
list<T>::list(list &&l)
    : head_(l.head_), tail_(l.tail_), list_size_(l.list_size_) {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.list_size_ = 0;
}

template <typename T> list<T>::~list() {
  if (!empty())
    clear();
}

template <typename T> list<T> &list<T>::operator=(list &&l) {
  if (this != &l) {
    clear();
    this->head_ = l.head_;
    this->tail_ = l.tail_;
    this->list_size_ = l.list_size_;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.list_size_ = 0;
  }
  return *this;
}

// Element access

template <typename T> typename list<T>::reference list<T>::front() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  return head_->data_;
}

template <typename T> typename list<T>::reference list<T>::back() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  return tail_->data_;
}

// Iterators

template <typename T> typename list<T>::iterator list<T>::begin() const {
  return iterator(head_, tail_);
}

template <typename T> typename list<T>::iterator list<T>::end() const {
  return iterator(nullptr, tail_);
}

// Capacity

template <typename T> bool list<T>::empty() const { return list_size_ == 0; }

template <typename T> typename list<T>::size_type list<T>::size() const {
  return list_size_;
}

template <typename T> typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename T> void list<T>::clear() {
  while (head_) {
    Node *tmp = head_;
    head_ = head_->next_;
    delete tmp;
  }
  tail_ = nullptr;
  list_size_ = 0;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *new_node = new Node(value);
  if (pos == begin()) {
    new_node->next_ = head_;
    if (head_)
      head_->prev_ = new_node;
    head_ = new_node;
    if (tail_ == nullptr)
      tail_ = new_node;
  } else {
    Node *prev_node = pos.current_->prev_;
    new_node->next_ = pos.current_;
    new_node->prev_ = prev_node;
    if (prev_node)
      prev_node->next_ = new_node;
    pos.current_->prev_ = new_node;
    if (pos.current_ == head_)
      head_ = new_node;
  }
  ++list_size_;
  return iterator(new_node, tail_);
}

template <typename T> void list<T>::erase(iterator pos) {
  if (pos == begin()) {
    head_ = head_->next_;
    if (head_) {
      head_->prev_ = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete pos.current_;
  } else if (pos == end()) {
    if (tail_ == head_) {
      delete tail_;
    } else {
      tail_ = tail_->prev_;
      delete tail_->next_;
      if (tail_) {
        tail_->next_ = nullptr;
      } else {
        head_ = nullptr;
      }
    }
  } else {
    Node *prev_node = pos.current_->prev_;
    Node *next_node = pos.current_->next_;
    prev_node->next_ = next_node;
    next_node->prev_ = prev_node;
    delete pos.current_;
  }
  --list_size_;
}

template <typename T> void list<T>::push_back(const_reference value) {
  Node *new_node = new Node(value);
  if (tail_) {
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    tail_ = new_node;
  } else {
    head_ = tail_ = new_node;
  }
  ++list_size_;
}

template <typename T> void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  erase(end());
}

template <typename T> void list<T>::push_front(const_reference value) {
  Node *new_node = new Node(value);
  if (head_) {
    head_->prev_ = new_node;
    new_node->next_ = head_;
    head_ = new_node;
  } else {
    head_ = tail_ = new_node;
  }
  ++list_size_;
}

template <typename T> void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  erase(begin());
}

template <typename T> void list<T>::swap(list &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(list_size_, other.list_size_);
}

template <typename T> void list<T>::merge(list &other) {
  for (auto it = other.begin(); it != other.end(); it++) {
    push_back(*it);
  }
  other.clear();
}

template <typename T> void list<T>::splice(iterator pos, list &other) {
  if (this != &other && !other.empty()) {
    if (pos == end()) {
      // Splice at the end
      other.tail_->next_ = nullptr;
      if (tail_) {
        tail_->next_ = other.head_;
        other.head_->prev_ = tail_;
        tail_ = other.tail_;
      } else {
        head_ = other.head_;
        tail_ = other.tail_;
      }
    } else {
      // Splice at the given position
      Node *prev_node = pos.current_->prev_;
      other.tail_->next_ = pos.current_;
      pos.current_->prev_ = other.tail_;
      if (prev_node) {
        prev_node->next_ = other.head_;
        other.head_->prev_ = prev_node;
      } else {
        head_ = other.head_;
      }
    }
    other.head_ = other.tail_ = nullptr;
    list_size_ += other.list_size_;
    other.list_size_ = 0;
  }
}

template <typename T> void list<T>::reverse() {
  if (empty())
    return;

  Node *current = head_;
  Node *temp = nullptr;
  tail_ = head_;

  while (current != nullptr) {
    temp = current->prev_;
    current->prev_ = current->next_;
    current->next_ = temp;
    current = current->prev_;
  }

  if (temp != nullptr) {
    head_ = temp->prev_;
  }
}

template <typename T> void list<T>::unique() {
  if (head_ == nullptr)
    return;
  Node *current_ = head_;
  while (current_->next_ != nullptr) {
    if (current_->data_ == current_->next_->data_) {
      Node *temp = current_->next_;
      current_->next_ = temp->next_;
      if (temp->next_)
        temp->next_->prev_ = current_;
      delete temp;
      --list_size_;
    } else {
      current_ = current_->next_;
    }
  }
  tail_ = current_;
}

template <typename T> void list<T>::sort() {
  if (head_ == nullptr)
    return;
  bool swapped;
  Node *ptr1;
  Node *lptr = nullptr;
  do {
    swapped = false;
    ptr1 = head_;
    while (ptr1->next_ != lptr) {
      if (ptr1->data_ > ptr1->next_->data_) {
        std::swap(ptr1->data_, ptr1->next_->data_);
        swapped = true;
      }
      ptr1 = ptr1->next_;
    }
    lptr = ptr1;
  } while (swapped);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_front(arg);
  }
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  iterator it = end();
  for (const auto &arg : {args...}) {
    if (it == end())
      it = insert(pos, arg);
    else
      insert(pos, arg);
  }
  return it;
}

} // namespace s21
