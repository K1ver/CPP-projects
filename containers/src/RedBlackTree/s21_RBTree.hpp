#ifndef S21_RED_BLACK_TREE_HPP
#define S21_RED_BLACK_TREE_HPP

#include <initializer_list>
#include <limits>
#include <utility>

#include "../Vector/s21_vector.hpp"

namespace s21 {
template <typename K, typename V> class RBTree {
public:
  class Iterator;
  class ConstIterator;
  class PairIterator;
  class PairConstIterator;
  using key_type = K;
  using value_type = V;
  using reference = K &;
  using const_reference = const key_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = std::size_t;
  using pair_iterator = PairIterator;
  using pair_const_iterator = PairConstIterator;
  using pair_value_type = std::pair<const key_type, value_type>;
  using const_pair_value_type = const pair_value_type;

private:
  enum class Color { BLACK, RED };

  struct RBNode {
    key_type key_;
    value_type value_;
    RBNode *left_;
    RBNode *right_;
    RBNode *parent_;
    Color color_;

    RBNode(const K &key, const V &value, Color color = Color::RED)
        : key_(key), value_(value), left_(nullptr), right_(nullptr),
          parent_(nullptr), color_(color) {}
  };
  using NodePtr = RBNode *;

  NodePtr root_;
  NodePtr TNULL_;

public:
  class Iterator {
  public:
    Iterator();
    Iterator(NodePtr node);
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    reference operator*();
    bool operator==(const iterator &it) const;
    bool operator!=(const iterator &it) const;
    friend class RBTree<K, V>;
    value_type &GetValue();

  protected:
    NodePtr minimumIter(NodePtr node) const;
    NodePtr maximumIter(NodePtr node) const;
    NodePtr FindRoot(NodePtr node) const;
    NodePtr it_node_;
    NodePtr last_node_;
    NodePtr MoveForward(NodePtr it);
    NodePtr MoveBack(NodePtr it);
  };

  class ConstIterator : public Iterator {
  public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return Iterator::operator*(); };
  };

  class PairIterator : public Iterator {
  public:
    PairIterator() : Iterator(){};
    PairIterator(NodePtr node) : Iterator(node){};
    pair_value_type &operator*();
    value_type &GetValue() { return Iterator::GetValue(); };
  };

  class PairConstIterator : public PairIterator {
    PairConstIterator() : PairIterator(){};
    PairConstIterator(NodePtr node) : PairIterator(node){};
    const_pair_value_type operator*() const {
      return PairIterator::operator*();
    };
  };

private:
  size_type tree_size_;

  void LeftRotate(NodePtr &pt);
  void RightRotate(NodePtr &pt);
  void InsertFix(NodePtr &pt);
  void EraseFix(NodePtr &pt);

  void transplant(NodePtr u, NodePtr v);
  NodePtr minimum(NodePtr node) const;
  NodePtr maximum(NodePtr node) const;

  void destroyTree(NodePtr node);

public:
  RBTree();
  RBTree(RBTree &&ms);
  ~RBTree();
  RBTree &operator=(RBTree &&ms);
  void InsertNode(const K &key, const V &value);
  void InsertNodeWithDublicate(const K &key, const V &value);
  void EraseNode(const K &key);

  NodePtr FindNode(const K &key) const;

  void FixSize();
  size_type size() const;
  size_type max_size() const;
  bool empty() const;
  void clear();

  iterator begin() const;
  iterator end() const;
  pair_iterator pair_begin() const {
    iterator it = begin();
    return PairIterator(it.it_node_);
  }
  pair_iterator pair_end() const {
    iterator it = end();
    return PairIterator(it.it_node_);
  }

  NodePtr GetTNULL() { // Исправить
    return TNULL_;
  }
};
} // namespace s21

#include "s21_RBTree.tpp"

#endif
