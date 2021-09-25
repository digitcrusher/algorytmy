/*
 * Wyczerpująca implementacja leniwego drzewa przedziałowego przedział-przedział
 *                                                        digitcrusher/algorytmy
 *
 * Copyright (c) 2021 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/int.hpp"
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

// TODO: niedokończone

// Op has to be associative
// recurses around log2(b) times
template<typename Value, typename Op>
Value pow(Value base, unsigned int exp, Op const& op = Op()) { // TODO: iterative version
  assert(exp >= 1);
  if(exp == 1) return base;
  Value x = pow(base, exp / 2, op);
  return exp % 2 == 0 ? op(x, x) : op(op(x, x), base);
}

template<typename Value, typename Change>
struct DefaultApplyChange {
  Value operator ()(
    Value const& val,
    __attribute__((unused)) Change const& change,
    __attribute__((unused)) size_t elem
  ) const {
    return val;
  };
};

template<typename Change>
struct DefaultMergeChange {
  Change operator()(
    Change const& a,
    __attribute__((unused)) Change const& b
  ) const {
    return b;
  }
};

/*
 * Sum:         (Value, Value) -> Value          - Łaczy dwa sąsiednie przedziały elementów. Sum musi być łączne.
 * ApplyChange: (Value, Change, size_t) -> Value - Aplikuje modyfikacje na cały przedział.
 * MergeChange: (Change, Change) -> Change       - Kumuluje dwie zmiany do jednej.
 */

template<
  typename Value,
  typename Sum,

  typename Change = tuple<>,
  typename ApplyChange = DefaultApplyChange<Value, Change>,
  typename MergeChange = DefaultMergeChange<Change>
> struct SegmentTree {
  using value_type = Value;
  using reference = Value&;
  using const_reference = Value const&;

  /* TODO
  using iterator = ;
  using const_iterator = ;
  */

  using difference_type = ptrdiff_t;
  using size_type = size_t;



  using sum_type = Sum;
  using apply_change_type = ApplyChange;
  using merge_change_type = MergeChange;

  Value default_val;
  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;

  /*
   * - Rozmiar przedziału każdego wierzchołka w poddrzewie
   *   lewego dziecka każdego wierzchołka jest potęgą dwójki.
   * - Rozmiar przedziału lewego dziecka jest zawsze
   *   większy równy rozmiarowi prawego dziecka.
   */
  struct Node {
    /*
     * This is a double pointer to SegmentTree so that the
     * reference to this SegmentTree in every node doesn't
     * have to be changed in every node during a swap.
     */
    SegmentTree *&tree;

    size_t l, r;
    Node *parent = nullptr;

    bool has_children = false;
    bool has_val = false;
    Node *left = nullptr, *right = nullptr;
    Value val;

    bool has_change = false;
    Change latent_change;

    Node(SegmentTree *&tree, size_t l, size_t r, Node *parent = nullptr):
      tree(tree), l(l), r(r), parent(parent) {}

    Node(Node const& other, SegmentTree *&tree, Node *parent = nullptr):
      tree(tree),
      l(other.l), r(other.r),
      parent(parent),
      has_children(other.has_children),
      has_val(other.has_val),
      left(other.left == nullptr ? nullptr : new Node(*other.left, tree, this)),
      right(other.right == nullptr ? nullptr : new Node(*other.right, tree, this)),
      val(other.val),
      has_change(other.has_change),
      latent_change(other.latent_change) {}

    Node(Node const& other): Node(other, other.tree, other.parent) {}

    Node(Node &&other):
      tree(other.tree),
      l(other.l), r(other.r),
      parent(other.parent),
      has_children(other.has_children),
      has_val(other.has_val),
      left(other.left), right(other.right),
      val(other.val),
      has_change(other.has_change),
      latent_change(other.latent_change) {}

    ~Node() {
      if(this->left != nullptr) {
        delete this->left;
      }
      if(this->right != nullptr) {
        delete this->right;
      }
    }

    size_t elemc() const {
      return this->r - this->l + 1;
    }
    bool can_have_children() const {
      return this->l != this->r;
    }

    size_t left_elemc() const {
      // Największa potęga dwójki mniejsza niż liczba elementów przedziału obecnego wierzchołka
      return 1ull << floor_log2(this->elemc() - 1);
    }
    size_t right_elemc() const {
      return this->elemc() - this->left_elemc();
    }

    void need_children(bool should_recurse = false) {
      if(!this->can_have_children()) return;

      if(!this->has_children) {
        this->has_children = true;
        this->left = new Node(tree, this->l, this->left_elemc() - 1, this);
        this->right = new Node(tree, this->left_elemc(), this->r, this);
      }

      assert(left != nullptr);
      assert(right != nullptr);

      if(should_recurse) {
        left->need_children(true);
        right->need_children(true);
      }
    }
    void need_val() {
      if(this->has_val) return;
      this->has_val = true;

      if(this->has_children) {
        assert(this->left != nullptr);
        assert(this->right != nullptr);

        this->val = tree->sum(this->left->val, this->right->val);
      } else {
        this->val = pow(tree->default_val, this->elemc(), tree->sum);
      }
    }

    void receive_change(Change const& change) {
      need_val();
      this->val = tree->apply_change(this->val, change, this->elemc());
      this->latent_change = this->has_change ? tree->merge_change(this->latent_change, change) : change;
      this->has_change = true;
    }
    void propagate_change(bool should_recurse = false) {
      if(!this->has_change) return;
      this->has_change = false;

      need_children();
      if(this->has_children) {
        this->left->receive_change(this->latent_change);
        this->right->receive_change(this->latent_change);

        if(should_recurse) {
          this->left->propagate_change(true);
          this->right->propagate_change(true);
        }
      }
    }

    Value get(size_t l, size_t r) {
      assert(!(l > this->r));
      assert(!(r < this->l));

      if(l <= this->l && this->r <= r) {
        need_val();
        return this->val;
      } else {
        need_children();
        assert(this->has_children);

        propagate_change();
        if(r < this->right->l) {
          return this->left->get(l, r);
        } else if(l > this->left->r) {
          return this->right->get(l, r);
        } else {
          return tree->sum(this->left->get(l, r), this->right->get(l, r));
        }
      }
    }

    void modify(size_t l, size_t r, Change const& change) {
      assert(!(l > this->r));
      assert(!(r < this->l));

      if(l <= this->l && this->r <= r) {
        receive_change(change);
      } else {
        need_children();
        assert(this->has_children);

        if(!(l > this->left->r)) {
          this->left->modify(l, r, change);
        }
        if(!(r < this->right->l)) {
          this->right->modify(l, r, change);
        }
      }
    }
  };

  SegmentTree **node_middleman = new SegmentTree*(this);
  Node *root = nullptr;
  size_t len = 0;

  SegmentTree(Value const& default_val = Value()): default_val(default_val) {}

  SegmentTree(Value const& default_val,
              Sum const& sum,
              ApplyChange const& apply_change,
              MergeChange const& merge_change):
    default_val(default_val),
    sum(sum),
    apply_change(apply_change),
    merge_change(merge_change) {}

  SegmentTree(SegmentTree const& other):
    default_val(other.default_val),
    sum(other.sum),
    apply_change(other.apply_change),
    merge_change(other.merge_change),
    root(other.root == nullptr ? nullptr : new Node(*other.root, *this->node_middleman)),
    len(other.len) {}

  SegmentTree(SegmentTree &&other):
    default_val(move(other.default_val)),
    sum(move(other.sum)),
    apply_change(move(other.apply_change)),
    merge_change(move(other.merge_change)),
    root(move(other.root)),
    len(move(other.len))
  {
    swap(this->node_middleman, other.node_middleman);
    swap(*this->node_middleman, *other.node_middleman);
    other.root = nullptr;
  }

  ~SegmentTree() {
    if(this->root != nullptr) {
      delete this->root;
    }
    delete this->node_middleman;
  }

  SegmentTree& operator=(SegmentTree const& other) {
    this->default_val = other.default_val;
    this->sum = other.sum;
    this->apply_change = other.apply_change;
    this->merge_change = other.merge_change;
    this->root = other.root == nullptr ? nullptr : new Node(*other.root, *this->node_middleman);
    this->len = other.len;
    return *this;
  }

  SegmentTree& operator=(SegmentTree &&other) {
    this->default_val = move(other.default_val);
    this->sum = move(other.sum);
    this->apply_change = move(other.apply_change);
    this->merge_change = move(other.merge_change);
    this->root = move(other.root);
    this->len = move(other.len);

    swap(this->node_middleman, other.node_middleman);
    swap(*this->node_middleman, *other.node_middleman);
    other.root = nullptr;

    return *this;
  }

  Value get(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < this->len);
    assert(r < this->len);
    assert(this->root != nullptr);
    return this->root->get(l, r);
  }

  void modify(size_t l, size_t r, Change const& change) {
    assert(l <= r);
    assert(l < this->len);
    assert(r < this->len);
    assert(this->root != nullptr);
    this->root->modify(l, r, change);
  }

  void swap(SegmentTree &other) {
    swap(this->sum, other.sum);
    swap(this->apply_change, other.apply_change);
    swap(this->merge_change, other.merge_change);
    swap(this->node_middleman, other.node_middleman);
    swap(*this->node_middleman, *other.node_middleman);
    swap(this->root, other.root);
    swap(this->len, other.len);
  }

  size_t size() const {
    return this->len;
  }

  size_t max_size() const {
    return numeric_limits<difference_type>::max();
  }

  bool empty() const {
    return this->len == 0;
  }



  void clear() {
    delete this->root;
    this->root = nullptr;
    this->len = 0;
  }


/*
  void update_one(Node *node) {
    assert(node != nullptr);

    if(node->right != nullptr) {
      assert(node->left != nullptr);

      node->val = this->sum(node->left->val, node->right->val);
    } else if(node->left != nullptr) {
      node->val = node->left->val;
    }
  }
  void update_upward(Node *node) {
    assert(node != nullptr);

    Node *curr = node;
    while(curr != nullptr) {
      update_one(curr);
      curr = curr->parent;
    }
  }
  void update_upward(size_t idx) {
    assert(0 <= idx);
    assert(idx < this->size);

    update_upward(&this->nodes[idx]);
  }
  void update_downward(Node *node) {
    assert(node != nullptr);

    if(node->left != nullptr) {
      update_downward(node->left);

      if(node->right != nullptr) {
        update_downward(node->right);

        node->val = this->sum(node->left->val, node->right->val);
      } else {
        node->val = node->left->val;
      }
    } else {
      assert(node->right == nullptr);
    }
  }
  void update() {
    assert(this->root != nullptr);
    update_downward(this->root);
  }
*/
};
