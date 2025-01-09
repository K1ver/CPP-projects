#include "s21_RBTree.hpp"

namespace s21 {
template <typename K, typename V> RBTree<K, V>::RBTree() {
  TNULL_ = new RBNode(K(), V(), Color::BLACK);
  TNULL_->left_ = nullptr;
  TNULL_->right_ = nullptr;
  TNULL_->parent_ = nullptr;
  root_ = TNULL_;
  tree_size_ = 0;
}

template <typename K, typename V> RBTree<K, V>::~RBTree() {
  destroyTree(root_);
  delete TNULL_;
}

template <typename K, typename V> RBTree<K, V>::RBTree(RBTree &&ms) {
  this->root_ = ms.root_;
  this->TNULL_ = ms.TNULL_;
  ms.TNULL_ = nullptr;
  ms.root_ = nullptr;
}

template <typename K, typename V>
RBTree<K, V> &RBTree<K, V>::operator=(RBTree<K, V> &&ms) {
  if (this != &ms) {
    this->root_ = ms.root_;
    this->TNULL_ = ms.TNULL_;
    ms.TNULL_ = nullptr;
    ms.root_ = nullptr;
  }
  return *this;
}

template <typename K, typename V> void RBTree<K, V>::destroyTree(NodePtr node) {
  if (node != TNULL_) {
    destroyTree(node->left_);
    destroyTree(node->right_);
    delete node;
  }
}

template <typename K, typename V> void RBTree<K, V>::LeftRotate(NodePtr &pt) {
  NodePtr pt_right = pt->right_;

  pt->right_ = pt_right->left_;

  if (pt_right->left_ != TNULL_) {
    pt_right->left_->parent_ = pt;
  }

  pt_right->parent_ = pt->parent_;

  if (pt->parent_ == nullptr) {
    root_ = pt_right;
  } else if (pt == pt->parent_->left_) {
    pt->parent_->left_ = pt_right;
  } else {
    pt->parent_->right_ = pt_right;
  }

  pt_right->left_ = pt;
  pt->parent_ = pt_right;
}

template <typename K, typename V> void RBTree<K, V>::RightRotate(NodePtr &pt) {
  NodePtr pt_left = pt->left_;

  pt->left_ = pt_left->right_;

  if (pt_left->right_ != TNULL_) {
    pt_left->right_->parent_ = pt;
  }

  pt_left->parent_ = pt->parent_;

  if (pt->parent_ == nullptr) {
    root_ = pt_left;
  } else if (pt == pt->parent_->right_) {
    pt->parent_->right_ = pt_left;
  } else {
    pt->parent_->left_ = pt_left;
  }

  pt_left->right_ = pt;
  pt->parent_ = pt_left;
}

template <typename K, typename V> void RBTree<K, V>::InsertFix(NodePtr &pt) {
  NodePtr parent_pt = nullptr;
  NodePtr grand_parent_pt = nullptr;

  while ((pt != root_) && (pt->color_ != Color::BLACK) &&
         (pt->parent_->color_ == Color::RED)) {
    parent_pt = pt->parent_;
    grand_parent_pt = pt->parent_->parent_;

    if (parent_pt == grand_parent_pt->left_) {
      NodePtr uncle_pt = grand_parent_pt->right_;

      if (uncle_pt != TNULL_ && uncle_pt->color_ == Color::RED) {
        grand_parent_pt->color_ = Color::RED;
        parent_pt->color_ = Color::BLACK;
        uncle_pt->color_ = Color::BLACK;
        pt = grand_parent_pt;
      } else {
        if (pt == parent_pt->right_) {
          LeftRotate(parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent_;
        }

        RightRotate(grand_parent_pt);
        std::swap(parent_pt->color_, grand_parent_pt->color_);
        pt = parent_pt;
      }
    } else {
      NodePtr uncle_pt = grand_parent_pt->left_;

      if ((uncle_pt != TNULL_) && (uncle_pt->color_ == Color::RED)) {
        grand_parent_pt->color_ = Color::RED;
        parent_pt->color_ = Color::BLACK;
        uncle_pt->color_ = Color::BLACK;
        pt = grand_parent_pt;
      } else {
        if (pt == parent_pt->left_) {
          RightRotate(parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent_;
        }

        LeftRotate(grand_parent_pt);
        std::swap(parent_pt->color_, grand_parent_pt->color_);
        pt = parent_pt;
      }
    }
  }

  root_->color_ = Color::BLACK;
}

template <typename K, typename V>
void RBTree<K, V>::InsertNodeWithDublicate(const K &key, const V &value) {
  NodePtr pt = new RBNode(key, value);
  pt->parent_ = nullptr;
  pt->left_ = TNULL_;
  pt->right_ = TNULL_;
  pt->color_ = Color::RED;

  NodePtr y = nullptr;
  NodePtr x = root_;

  while (x != TNULL_) {
    y = x;
    if (pt->key_ == x->key_) {
      x = x->right_;
    } else if (pt->key_ < x->key_) {
      x = x->left_;
    } else {
      x = x->right_;
    }
  }

  pt->parent_ = y;
  if (y == nullptr) {
    root_ = pt;
  } else if (pt->key_ < y->key_) {
    y->left_ = pt;
  } else {
    y->right_ = pt;
  }

  tree_size_++;

  if (pt->parent_ == nullptr) {
    pt->color_ = Color::BLACK;
    return;
  }

  if (pt->parent_->parent_ == nullptr) {
    return;
  }

  InsertFix(pt);
}

template <typename K, typename V>
void RBTree<K, V>::InsertNode(const K &key, const V &value) {
  NodePtr pt = new RBNode(key, value);
  pt->parent_ = nullptr;
  pt->left_ = TNULL_;
  pt->right_ = TNULL_;
  pt->color_ = Color::RED;

  NodePtr y = nullptr;
  NodePtr x = root_;

  while (x != TNULL_) {
    y = x;
    if (pt->key_ < x->key_) {
      x = x->left_;
    } else {
      x = x->right_;
    }
  }

  pt->parent_ = y;
  if (y == nullptr) {
    root_ = pt;
  } else if (pt->key_ < y->key_) {
    y->left_ = pt;
  } else {
    y->right_ = pt;
  }

  tree_size_++;

  if (pt->parent_ == nullptr) {
    pt->color_ = Color::BLACK;
    return;
  }

  if (pt->parent_->parent_ == nullptr) {
    return;
  }

  InsertFix(pt);
}

template <typename K, typename V>
void RBTree<K, V>::transplant(NodePtr u, NodePtr v) {
  if (u->parent_ == nullptr) {
    root_ = v;
  } else if (u == u->parent_->left_) {
    u->parent_->left_ = v;
  } else {
    u->parent_->right_ = v;
  }
  v->parent_ = u->parent_;
}

template <typename K, typename V> void RBTree<K, V>::EraseFix(NodePtr &x) {
  NodePtr s;
  while (x != root_ && x->color_ == Color::BLACK) {
    if (x == x->parent_->left_) {
      s = x->parent_->right_;
      if (s->color_ == Color::RED) {
        s->color_ = Color::BLACK;
        x->parent_->color_ = Color::RED;
        LeftRotate(x->parent_);
        s = x->parent_->right_;
      }

      if (s->left_->color_ == Color::BLACK &&
          s->right_->color_ == Color::BLACK) {
        s->color_ = Color::RED;
        x = x->parent_;
      } else {
        if (s->right_->color_ == Color::BLACK) {
          s->left_->color_ = Color::BLACK;
          s->color_ = Color::RED;
          RightRotate(s);
          s = x->parent_->right_;
        }

        s->color_ = x->parent_->color_;
        x->parent_->color_ = Color::BLACK;
        s->right_->color_ = Color::BLACK;
        LeftRotate(x->parent_);
        x = root_;
      }
    } else {
      s = x->parent_->left_;
      if (s->color_ == Color::RED) {
        s->color_ = Color::BLACK;
        x->parent_->color_ = Color::RED;
        RightRotate(x->parent_);
        s = x->parent_->left_;
      }

      if (s->right_->color_ == Color::BLACK &&
          s->left_->color_ == Color::BLACK) {
        s->color_ = Color::RED;
        x = x->parent_;
      } else {
        if (s->left_->color_ == Color::BLACK) {
          s->right_->color_ = Color::BLACK;
          s->color_ = Color::RED;
          LeftRotate(s);
          s = x->parent_->left_;
        }

        s->color_ = x->parent_->color_;
        x->parent_->color_ = Color::BLACK;
        s->left_->color_ = Color::BLACK;
        RightRotate(x->parent_);
        x = root_;
      }
    }
  }
  x->color_ = Color::BLACK;
}

template <typename K, typename V> void RBTree<K, V>::EraseNode(const K &key) {
  NodePtr z = TNULL_;
  NodePtr x, y;
  NodePtr node = FindNode(key);

  if (node == TNULL_) {
    return;
  }

  z = node;
  y = z;
  Color y_original_color = y->color_;

  if (z->left_ == TNULL_) {
    x = z->right_;
    transplant(z, z->right_);
  } else if (z->right_ == TNULL_) {
    x = z->left_;
    transplant(z, z->left_);
  } else {
    y = minimum(z->right_);
    y_original_color = y->color_;
    x = y->right_;
    if (y->parent_ == z) {
      x->parent_ = y;
    } else {
      transplant(y, y->right_);
      y->right_ = z->right_;
      y->right_->parent_ = y;
    }

    transplant(z, y);
    y->left_ = z->left_;
    y->left_->parent_ = y;
    y->color_ = z->color_;
  }
  delete z;
  if (y_original_color == Color::BLACK) {
    EraseFix(x);
  }
  tree_size_--;
}

template <typename K, typename V>
typename RBTree<K, V>::NodePtr RBTree<K, V>::FindNode(const K &key) const {
  NodePtr node = root_;
  while (node != TNULL_) {
    if (key == node->key_) {
      return node;
    } else if (key < node->key_) {
      node = node->left_;
    } else {
      node = node->right_;
    }
  }
  return TNULL_;
}

template <typename K, typename V> void RBTree<K, V>::FixSize() {
  std::size_t temp = 0;
  if (begin() != end()) {
    for (auto it = begin(); it != end(); it++)
      ++temp;
  }
  tree_size_ = temp;
}

template <typename K, typename V>
typename RBTree<K, V>::size_type RBTree<K, V>::size() const {
  return tree_size_;
}

template <typename K, typename V>
typename RBTree<K, V>::size_type RBTree<K, V>::max_size() const {
  return std::numeric_limits<typename RBTree<K, V>::size_type>::max();
}

template <typename K, typename V> bool RBTree<K, V>::empty() const {
  return tree_size_ == 0;
}

template <typename K, typename V> void RBTree<K, V>::clear() {
  destroyTree(root_);
  root_ = TNULL_;
  tree_size_ = 0;
}

template <typename K, typename V>
typename RBTree<K, V>::NodePtr RBTree<K, V>::minimum(NodePtr node) const {
  while (node->left_ != TNULL_) {
    node = node->left_;
  }
  return node;
}

template <typename K, typename V>
typename RBTree<K, V>::NodePtr RBTree<K, V>::maximum(NodePtr node) const {
  while (node->right_ != TNULL_) {
    node = node->right_;
  }
  return node;
}

// ---------------------------------------- ITERATOR
template <typename K, typename V>
RBTree<K, V>::Iterator::Iterator() : it_node_(nullptr) {}

template <typename K, typename V>
RBTree<K, V>::Iterator::Iterator(NodePtr node) : it_node_(node) {
  if (!node) {
    last_node_ = node;
  } else {
    if (node->right_ != nullptr) {
      last_node_ = node;
      while (last_node_->parent_ != nullptr) {
        last_node_ = last_node_->parent_;
      }
      while (last_node_->right_->right_ != nullptr) {
        last_node_ = last_node_->right_;
      }
    } else {
      last_node_ = node;
    }
  }
}

template <typename K, typename V>
typename RBTree<K, V>::NodePtr
RBTree<K, V>::Iterator::FindRoot(NodePtr node) const {
  while (node->parent_ != nullptr) {
    node = node->parent_;
  }
  return node;
}

template <typename K, typename V>
typename RBTree<K, V>::NodePtr
RBTree<K, V>::Iterator::minimumIter(NodePtr node) const {
  if (node->left_ == nullptr) {
    return node;
  }

  while (node->left_->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}

template <typename K, typename V>
typename RBTree<K, V>::NodePtr
RBTree<K, V>::Iterator::maximumIter(NodePtr node) const {
  if (node->right_ == nullptr) {
    return node;
  }

  while (node->right_->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

template <typename K, typename V>
typename RBTree<K, V>::iterator RBTree<K, V>::begin() const {
  if (root_ == TNULL_) {
    return RBTree<K, V>::Iterator(root_);
  }
  iterator min = minimum(root_);
  min.last_node_ = maximum(root_);
  return min;
}

template <typename K, typename V>
typename RBTree<K, V>::iterator RBTree<K, V>::end() const {
  if (root_ == TNULL_) {
    return RBTree<K, V>::Iterator(root_);
  }
  iterator max = maximum(root_);
  max.last_node_ = max.it_node_;
  max.it_node_ = max.it_node_->right_;
  return max;
}

template <typename K, typename V>
typename RBTree<K, V>::iterator &RBTree<K, V>::Iterator::operator++() {
  NodePtr max;
  if (it_node_ != nullptr) {
    max = maximumIter(FindRoot(last_node_));
  }
  if (max->right_ == nullptr) {
    it_node_ = max;
  } else if (it_node_ == max) {
    it_node_ = it_node_->right_;
  } else if (it_node_ != max && it_node_ != max->right_) {
    it_node_ = MoveForward(it_node_);
  }

  return *this;
}

template <typename K, typename V>
typename RBTree<K, V>::iterator RBTree<K, V>::Iterator::operator++(int) {
  Iterator temp = *this;
  operator++();
  return temp;
}

template <typename K, typename V>
typename RBTree<K, V>::iterator &RBTree<K, V>::Iterator::operator--() {
  NodePtr min;
  NodePtr max = maximumIter(FindRoot(last_node_));
  if (it_node_ != nullptr) {
    min = minimumIter(FindRoot(last_node_));
  }

  if (max->right_ == nullptr) {
    it_node_ = max;
  } else if (it_node_ == max->right_) {
    it_node_ = max;
  } else if (it_node_ != min) {
    it_node_ = MoveBack(it_node_);
  }

  return *this;
}

template <typename K, typename V>
typename RBTree<K, V>::iterator RBTree<K, V>::Iterator::operator--(int) {
  Iterator temp = *this;
  operator--();
  return temp;
}

template <typename K, typename V> K &RBTree<K, V>::Iterator::operator*() {
  return it_node_->key_;
}

template <typename K, typename V>
bool RBTree<K, V>::Iterator::operator==(const iterator &it) const {
  return this->it_node_ == it.it_node_;
}

template <typename K, typename V>
bool RBTree<K, V>::Iterator::operator!=(const iterator &it) const {
  return this->it_node_ != it.it_node_;
}

template <typename K, typename V>
typename RBTree<K, V>::NodePtr RBTree<K, V>::Iterator::MoveForward(NodePtr it) {
  if (it == nullptr)
    return nullptr;
  if (it->right_->right_ != nullptr) {
    return minimumIter(it->right_);
  }
  NodePtr parent_ = it->parent_;
  while (parent_ != nullptr && it == parent_->right_) {
    it = parent_;
    parent_ = parent_->parent_;
  }
  return parent_;
}

template <typename K, typename V>
typename RBTree<K, V>::NodePtr RBTree<K, V>::Iterator::MoveBack(NodePtr it) {
  if (it == nullptr)
    return nullptr;
  if (it->left_->left_ != nullptr) {
    return maximumIter(it->left_);
  }
  NodePtr parent_ = it->parent_;
  while (parent_ != nullptr && it == parent_->left_) {
    it = parent_;
    parent_ = parent_->parent_;
  }
  return parent_;
}

template <typename K, typename V>
typename RBTree<K, V>::value_type &RBTree<K, V>::Iterator::GetValue() {
  return it_node_->value_;
}

template <typename K, typename V>
typename RBTree<K, V>::pair_value_type &
RBTree<K, V>::PairIterator::operator*() {
  if (RBTree<K, V>::Iterator::it_node_ == nullptr) {
    static std::pair<const K, V> fake{};
    return fake;
  }
  std::pair<const K, V> pr =
      std::make_pair(RBTree<K, V>::Iterator::it_node_->key_,
                     RBTree<K, V>::Iterator::it_node_->value_);
  std::pair<const K, V> &refer = pr;
  return refer;
}
} // namespace s21
