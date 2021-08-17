/*
 * Wyczerpująca implementacja drzewa przedziałowego przedział-przedział
 *                                               digitcrusher/algorytmy
 *
 * Copyright (c) 2021 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "../../bit.hpp"
#include "../../common.hpp"
#include "../../misc.hpp"
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

/*
 * Wyczerpująca implementacja drzewa przedziałowego przedział-przedział -
 *   Kontener wspierający operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i modyfikacji (modify) w czasie logarytmicznym.
 *
 * Ta implementacja jest zgodna z C++11 i spełnia Container, ReversibleContainer
 * i SequenceContainer.
 *
 * Iteratory nigdy nie są unieważnione, jeśli adres drzewa w pamięci się nie
 * zmieni. Referencja do drzewa w iteratorach pozostaje taka sama po swap'ie,
 * więc drzewa na które wskazują iteratory też są wymieniane podczas swap'u.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów. Sum musi być łączne, czyli
 *   (a sum b) sum c = a sum (b sum c).
 * ApplyChange: (Value, Change, size_t) -> Value
 *   Aplikuje zmianę na wartość sumy spójnego przedziału elementów o rozmiarze
 *   będacym potęgą dwójki.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 */
template<class Value, class Change>
struct DefaultApplyChange {
  Value operator()(Value const& val,
                   Change const& change __attribute__((unused)),
                   size_t elem __attribute__((unused))) const
  {
    return val;
  };
};

template<class Change>
struct DefaultMergeChange {
  Change operator()(Change const& a,
                    Change const& b __attribute__((unused))) const
  {
    return b;
  }
};

template<
  class Value,
  class Sum,
  class Change = std::tuple<>,
  class ApplyChange = DefaultApplyChange<Value, Change>,
  class MergeChange = DefaultMergeChange<Change>
> struct SegmentTree {
  using value_type = Value;
  using reference = Value&;
  using const_reference = Value const&;

  using difference_type = ptrdiff_t;
  using size_type = size_t;

  template<bool is_const>
  struct Iterator {
    using difference_type = ptrdiff_t;
    using value_type = Value;
    using pointer = type_if_t<is_const, Value const*, Value*>;
    using reference = type_if_t<is_const, Value const&, Value&>;
    using iterator_category = std::random_access_iterator_tag;

    /*
     * tree jest wskaźnikiem, żeby domyślny operator= działał; a other we
     * wszystkich metodach jest const_iterator'em żeby umożliwić operacje
     * iterator'a z const_iterator'em.
     */
    using tree_pointer = type_if_t<is_const, SegmentTree const*, SegmentTree*>;
    using const_iterator = Iterator<true>;

    Iterator(tree_pointer tree, size_t idx): tree(tree), idx(idx) {}

    reference operator*() const {
      return (*this->tree)[this->idx];
    }
    reference operator->() const {
      return **this;
    }
    reference operator[](ptrdiff_t offset) const {
      return (*this->tree)[this->idx + offset];
    }

    bool operator==(const_iterator const& other) const {
      return this->tree == other.tree && this->idx == other.idx;
    }
    bool operator!=(const_iterator const& other) const {
      return !(*this == other);
    }

    Iterator& operator++() {
      this->idx++;
      return *this;
    }
    Iterator& operator--() {
      this->idx--;
      return *this;
    }

    Iterator operator++(int) {
      Iterator result = *this;
      ++*this;
      return result;
    }
    Iterator operator--(int) {
      auto result = *this;
      --*this;
      return result;
    }

    Iterator& operator+=(ptrdiff_t offset) {
      this->idx += offset;
      return *this;
    }
    Iterator& operator-=(ptrdiff_t offset) {
      this->idx -= offset;
      return *this;
    }

    Iterator operator+(ptrdiff_t offset) const {
      auto result = *this;
      result += offset;
      return result;
    }
    Iterator operator-(ptrdiff_t offset) const {
      auto result = *this;
      result -= offset;
      return result;
    }

    ptrdiff_t operator-(const_iterator const& other) const {
      assert(this->tree == other.tree);
      return this->idx - other.idx;
    }
    bool operator<(const_iterator const& other) const {
      assert(this->tree == other.tree);
      return this->idx < other.idx;
    }
    bool operator>(const_iterator const& other) const {
      assert(this->tree == other.tree);
      return this->idx > other.idx;
    }
    bool operator<=(const_iterator const& other) const {
      return !(*this > other);
    }
    bool operator>=(const_iterator const& other) const {
      return !(*this < other);
    }

    operator const_iterator() const {
      return const_iterator(this->tree, this->idx);
    }

  private:
    tree_pointer tree;
    size_t idx;

    friend SegmentTree;
  };

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;

  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  iterator begin() {
    return iterator(this, 0);
  }
  iterator end() {
    return iterator(this, this->elemc);
  }
  const_iterator begin() const {
    return const_iterator(this, 0);
  }
  const_iterator end() const {
    return const_iterator(this, this->elemc);
  }
  const_iterator cbegin() const {
    return const_iterator(this, 0);
  }
  const_iterator cend() const {
    return const_iterator(this, this->elemc);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(this->end());
  }
  reverse_iterator rend() {
    return reverse_iterator(this->begin());
  }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(this->end());
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(this->begin());
  }
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(this->cend());
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(this->cbegin());
  }

  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;

  struct Node {
    Value val;
    bool has_change = false;
    Change latent_change;

    Node() {}
    Node(Value val): val(val) {}
  };
  struct NodeOps;

  // Metoda do inspekcji wewnetrznej struktury drzewa.
  Node const& node_at(size_t num) const {
    assert(num != 0);
    assert(num - 1 < this->nodec());
    return this->nodes[num - 1];
  }

  SegmentTree(Sum const& sum = Sum(),
              ApplyChange const& apply_change = ApplyChange(),
              MergeChange const& merge_change = MergeChange()):
    sum(sum), apply_change(apply_change), merge_change(merge_change) {}

  SegmentTree(size_t cnt, Value const& val,
              Sum const& sum = Sum(),
              ApplyChange const& apply_change = ApplyChange(),
              MergeChange const& merge_change = MergeChange()):
    SegmentTree(sum, apply_change, merge_change)
  {
    assign(cnt, val);
  }

  template<class InputIt, class = require_input_iter<InputIt>>
  SegmentTree(InputIt first, InputIt end,
              Sum const& sum = Sum(),
              ApplyChange const& apply_change = ApplyChange(),
              MergeChange const& merge_change = MergeChange()):
    SegmentTree(sum, apply_change, merge_change)
  {
    assign(first, end);
  }

  SegmentTree(std::initializer_list<Value> elems,
              Sum const& sum = Sum(),
              ApplyChange const& apply_change = ApplyChange(),
              MergeChange const& merge_change = MergeChange()):
    SegmentTree(sum, apply_change, merge_change)
  {
    assign(elems);
  }

  Value& operator[](size_t idx) {
    assert(idx < this->elemc);
    require_up_to_date_base(idx, idx);
    invalidate_elem_parents(idx, idx);
    return this->nodes[this->nodec() - this->basec() + idx].val;
  }
  Value const& operator[](size_t idx) const {
    assert(idx < this->elemc);
    require_up_to_date_base(idx, idx);
    return this->nodes[this->nodec() - this->basec() + idx].val;
  }

  Value& at(size_t idx) {
    if(idx >= this->elemc) {
      throw std::out_of_range(
        "SegmentTree.at(idx): idx (równe " + std::to_string(idx) + ") >= "
        "this->elemc (równe " + std::to_string(this->elemc) + ")"
      );
    }
    return (*this)[idx];
  }
  Value const& at(size_t idx) const {
    if(idx >= this->elemc) {
      throw std::out_of_range(
        "SegmentTree.at(idx): idx (równe " + std::to_string(idx) + ") >= "
        "this->elemc (równe " + std::to_string(this->elemc) + ")"
      );
    }
    return (*this)[idx];
  }

  size_t size() const {
    return this->elemc;
  }
  size_t max_size() const {
    /*
     * Dodanie jeden do max_size wywołałoby overflow, jeśli
     * max_size vector'a to maksymalna wartość size_t.
     */
    return 1ull << floor_log2((this->nodes.max_size() - 1) + 1) - 1;
  }
  bool empty() const {
    return this->elemc == 0;
  }

  template<class ...A>
  int compare(SegmentTree<A...> const& other) const {
    require_up_to_date_base(0, this->elemc - 1);
    other.require_up_to_date_base(0, this->elemc - 1);
    for(size_t i = 0; i < std::min(this->elemc, other.elemc); i++) {
      if(val_at(i) < other.val_at(i)) {
        return -1;
      } else if(val_at(i) > other.val_at(i)) {
        return 1;
      }
    }
    return this->elemc < other.elemc ? -1 : (this->elemc > other.elemc ? 1 : 0);
  }

  template<class ...A>
  bool operator==(SegmentTree<A...> const& other) const {
    return this->compare(other) == 0;
  }
  template<class ...A>
  bool operator!=(SegmentTree<A...> const& other) const {
    return this->compare(other) != 0;
  }
  template<class ...A>
  bool operator<(SegmentTree<A...> const& other) const {
    return this->compare(other) < 0;
  }
  template<class ...A>
  bool operator<=(SegmentTree<A...> const& other) const {
    return this->compare(other) <= 0;
  }
  template<class ...A>
  bool operator>(SegmentTree<A...> const& other) const {
    return this->compare(other) > 0;
  }
  template<class ...A>
  bool operator>=(SegmentTree<A...> const& other) const {
    return this->compare(other) >= 0;
  }

  void swap(SegmentTree &other) {
    std::swap(this->sum, other.sum);
    std::swap(this->apply_change, other.apply_change);
    std::swap(this->merge_change, other.merge_change);
    std::swap(this->elemc, other.elemc);
    std::swap(this->nodes, other.nodes);
    std::swap(this->has_latent_changes, other,has_latent_changes);
    std::swap(this->needs_resum, other.needs_resum);
    std::swap(this->to_resum_l, other.to_resum_l);
    std::swap(this->to_resum_r, other.to_resum_r);
  }

  void clear() {
    this->elemc = 0;
    this->nodes.clear();
    this->has_latent_changes = false;
    this->needs_resum = false;
  }

  // TODO: Leniwe zmniejszanie drzewa
  void resize(size_t new_size, Value const& val = Value()) {
    auto old_metrics = this->metrics();
    size_t old_elemc = this->elemc;
    size_t old_height = this->height();
    this->elemc = new_size;

    if((this->elemc < old_elemc || this->height() > old_height) &&
       old_elemc > 0) {
      this->elemc = old_elemc;
      /*
       * std::move nie zeruje wartości, które przesuwa, więc zaległe zmiany
       * zostaną w nieodpowiednich miejscach, jeśli nie zrobimy tego:
       */
      require_no_changes_above(0, this->elemc - 1);
      this->elemc = new_size;
    }

    if(this->height() != old_height) {
      // Zwiększanie
      if(this->height() > old_height) {
        size_t add_levelc = this->height() - old_height;
        this->nodes.resize(this->nodec());
        for(size_t level = old_height - 1; level != -1ull; level--) {
          auto it = this->nodes.begin() + old_metrics.level_offset(level);
          std::move(
            it,
            it + old_metrics.level_nodec(level),
            this->nodes.begin() + this->level_offset(level + add_levelc)
          );
        }

      // Zmniejszanie
      } else {
        size_t del_levelc = old_height - this->height();
        for(size_t level = 0; level < this->height(); level++) {
          auto it = this->nodes.begin() + old_metrics.level_offset(level + del_levelc);
          std::move(
            it,
            it + this->level_nodec(level),
            this->nodes.begin() + this->level_offset(level)
          );
        }
        this->nodes.resize(this->nodec());
      }
    }

    // Wypełniamy nowe elementy val'em
    if(this->elemc > old_elemc) {
      std::fill(node_at2(old_elemc), node_at2(this->elemc), Node(val));
      invalidate_elem_parents(old_elemc, this->elemc - 1);
    } else if(this->elemc < old_elemc && this->needs_resum) {
      if(this->to_resum_l >= this->elemc) {
        this->needs_resum = false;
      } else {
        this->to_resum_r = std::min(this->to_resum_r, this->elemc - 1);
      }
    }
  }

  void assign(size_t cnt, Value const& val) {
    clear();
    this->elemc = cnt;
    this->nodes.resize(this->nodec(), Node(val));
    if(this->elemc > 0) {
      this->root_ops().resum();
    }
  }
  template<class InputIt, class = require_input_iter<InputIt>>
  void assign(InputIt first, InputIt end) {
    clear();
    this->elemc = std::distance(first, end);
    this->nodes.resize(this->nodec());
    std::copy(first, end, this->nodes.end() - this->basec());
    if(this->elemc > 0) {
      this->root_ops().resum();
    }
  }
  void assign(std::initializer_list<Value> elems) {
    assign(elems.begin(), elems.end());
  }
  SegmentTree& operator=(std::initializer_list<Value> elems) {
    assign(elems);
    return *this;
  }

  template<class ...Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    before_insert(pos, 1);
    val_at(pos.idx) = std::move(Value(std::forward(args)...));
    return after_insert(pos);
  }
  iterator insert(const_iterator pos, Value const& val) {
    before_insert(pos, 1);
    val_at(pos.idx) = val;
    return after_insert(pos);
  }
  iterator insert(const_iterator pos, Value &&val) {
    before_insert(pos, 1);
    val_at(pos.idx) = std::move(val);
    return after_insert(pos);
  }
  iterator insert(const_iterator pos, size_t cnt, Value const& val) {
    before_insert(pos, cnt);
    auto ptr = node_at2(pos.idx);
    std::fill(ptr, ptr + cnt, Node(val));
    return after_insert(pos);
  }
  template<class InputIt, class = require_input_iter<InputIt>>
  iterator insert(const_iterator pos, InputIt first, InputIt end) {
    before_insert(pos, std::distance(first, end));
    std::copy(first, end, node_at2(pos.idx));
    return after_insert(pos);
  }
  iterator insert(const_iterator pos, std::initializer_list<Value> elems) {
    return insert(pos, elems.begin(), elems.end());
  }

  iterator erase(const_iterator first_it, const_iterator end_it) {
    size_t first = first_it.idx, end = end_it.idx;
    if(first >= end) {
      return this->end();
    }
    assert(end <= this->elemc);

    if(end != this->elemc) {
      require_up_to_date_base(end, this->elemc - 1);
    }
    require_no_changes_above(first, end - 1);
    std::move(node_at2(end), node_at2(this->elemc), node_at2(first));
    resize(this->elemc - (end - first));
    if(first != this->elemc) {
      invalidate_elem_parents(first, this->elemc - 1);
    }

    return iterator(this, first);
  }
  iterator erase(const_iterator pos) {
    return erase(pos, pos + 1);
  }

  Value& front() {
    return (*this)[0];
  }
  Value const& front() const {
    return (*this)[0];
  }
  Value& back() {
    return (*this)[this->elemc - 1];
  }
  Value const& back() const {
    return (*this)[this->elemc - 1];
  }

  template<class ...Args>
  void emplace_front(Args &&...args) {
    emplace(this->begin(), std::forward(args)...);
  }
  template<class ...Args>
  void emplace_back(Args &&...args) {
    emplace(this->end(), std::forward(args)...);
  }
  void push_front(Value const& val) {
    insert(this->begin(), val);
  }
  void push_front(Value &&val) {
    insert(this->begin(), std::move(val));
  }
  void push_back(Value const& val) {
    insert(this->end(), val);
  }
  void push_back(Value &&val) {
    insert(this->end(), std::move(val));
  }
  void pop_front() {
    erase(this->begin());
  }
  void pop_back() {
    erase(this->end() - 1);
  }

  Value get(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < this->elemc);
    assert(r < this->elemc);
    require_valid_subtree(l, r);
    return this->root_ops().get(l, r);
  }
  void modify(size_t l, size_t r, Change const& change) {
    assert(l <= r);
    assert(l < this->elemc);
    assert(r < this->elemc);
    require_valid_subtree(l, r);
    if(l != r) {
      this->has_latent_changes = true;
    }
    this->root_ops().modify(l, r, change);
  }

  // Stworzone aby uprościć implementację resize.
  struct Metrics {
    size_t elemc;

    Metrics(size_t elemc): elemc(elemc) {}

    size_t height() const {
      return this->elemc == 0 ? 0 : ceil_log2(this->elemc) + 1;
    }
    size_t nodec() const {
      return (1ull << this->height()) - 1;
    }
    size_t basec() const {
      return this->elemc == 0 ? 0 : 1ull << (this->height() - 1);
    }
    size_t base_offset() const {
      return (1ull << (this->height() - 1)) - 1;
    }
    size_t level_nodec(size_t level) const {
      return 1ull << level;
    }
    size_t level_offset(size_t level) const {
      return (1ull << level) - 1;
    }
  };

  Metrics metrics() const {
    return Metrics(this->elemc);
  }
  size_t height() const {
    return this->metrics().height();
  }
  size_t nodec() const {
    return this->metrics().nodec();
  }
  size_t basec() const {
    return this->metrics().basec();
  }
  size_t base_offset() const {
    return this->metrics().base_offset();
  }
  size_t level_nodec(size_t level) const {
    return this->metrics().level_nodec(level);
  }
  size_t level_offset(size_t level) const {
    return this->metrics().level_offset(level);
  }

  /*
   * Node nie ma dostępu do drzewa z jego metod, a referencja do drzewa
   * w każdym wierzchołku byłaby za bardzo kosztowna pamięciowo.
   */
  struct NodeOps {
    Node &node;
    SegmentTree const& tree;

    NodeOps(Node &node, SegmentTree const& tree): node(node), tree(tree) {}

    size_t num() const {
      return &node - &tree.nodes.front() + 1;
    }
    NodeOps parent() const {
      assert(this->level() > 0);
      return NodeOps(tree.nodes[this->num() / 2 - 1], tree);
    }
    NodeOps left() const {
      assert(this->level() < tree.height() - 1);
      return NodeOps(tree.nodes[this->num() * 2 - 1], tree);
    }
    NodeOps right() const {
      assert(this->level() < tree.height() - 1);
      return NodeOps(tree.nodes[this->num() * 2 + 1 - 1], tree);
    }
    size_t level() const {
      return floor_log2(this->num());
    }
    size_t elemc() const {
      return tree.basec() >> this->level();
    }
    size_t l() const {
      return (this->num() - (1ull << this->level())) * this->elemc();
    }
    size_t r() const {
      return this->l() + this->elemc() - 1;
    }
    bool has_children() const {
      return this->l() != this->r();
    }

    void receive_change(Change const& change) {
      /*
       * Nie powinny nas nigdy interesować wierzchołki
       * z przedziałem niezawierającym elementy z tablicy.
       */
      assert(this->l() < tree.elemc);

      /*
       * Nie chcemy marnować czasu na aktualizowanie wartości wierzchołka
       * z przedziałem zawierającym elementy spoza tablicy.
       */
      if(this->r() < tree.elemc) {
        node.val = tree.apply_change(node.val, change, this->elemc());
      }
      // SegmentTree.has_latent_changes zależy od poniższego zachowania.
      if(this->has_children()) {
        node.latent_change = node.has_change ? tree.merge_change(node.latent_change, change) : change;
        node.has_change = true;
      }
    }
    void propagate_change(bool should_recurse = false) {
      assert(this->l() < tree.elemc);

      if(node.has_change) {
        node.has_change = false;

        if(this->has_children()) {
          this->left().receive_change(node.latent_change);
          /*
           * Nie chcemy marnować czasu na aktualizowanie prawego dziecka, jeśli
           * jego przedział nie zawiera żadnych elementów tablicy. Nie musimy
           * robić ifa dla lewego dziecka, bo na pewno zawiera jakieś elementy
           * z tablicy, jeśli obecny wierzchołek też zawiera jakieś, co na pewno
           * jest prawdą, skoro powyższy assert nie został naruszony.
           */
          if(this->right().l() < tree.elemc) {
            this->right().receive_change(node.latent_change);
          }
        }
      }

      if(this->has_children() && should_recurse) {
        this->left().propagate_change(true);
        if(this->right().l() < tree.elemc) {
          this->right().propagate_change(true);
        }
      }
    }

    Value get(size_t l, size_t r) {
      assert(!(l > this->r()));
      assert(!(r < this->l()));
      assert(this->l() < tree.elemc);

      if(l <= this->l() && this->r() <= r) {
        return node.val;
      } else {
        propagate_change();
        if(r < this->right().l()) {
          return this->left().get(l, r);
        } else if(l > this->left().r()) {
          /*
           * Poprawne zapytanie o modyfikacje nigdy nie zejdzie do prawego
           * dziecka, jeśli nie zawiera żadnych elementów tablicy. Poniższy
           * assert to sanity check.
           */
          assert(this->right().l() < tree.elemc);
          return this->right().get(l, r);
        } else {
          assert(this->right().l() < tree.elemc);
          return tree.sum(this->left().get(l, r), this->right().get(l, r));
        }
      }
    }

    void modify(size_t l, size_t r, Change const& change) {
      assert(!(l > this->r()));
      assert(!(r < this->l()));
      assert(this->l() < tree.elemc);

      if(l <= this->l() && this->r() <= r) {
        receive_change(change);
      } else {
        propagate_change();
        if(!(l > this->left().r())) {
          this->left().modify(l, r, change);
        }
        if(!(r < this->right().l())) {
          assert(this->right().l() < tree.elemc);
          this->right().modify(l, r, change);
        }
        /*
         * Poprawne zapytanie o sumę przedziału nigdy nie weźmie wartości
         * obecnego wierzchołka, jeśli jego przedział nie zawiera się w tablicy.
         */
        if(this->r() < tree.elemc) {
          node.val = tree.sum(this->left().node.val, this->right().node.val);
        }
      }
    }

    void resum(size_t l, size_t r) {
      assert(!(l > this->r()));
      assert(!(r < this->l()));
      assert(this->l() < tree.elemc);

      if(this->has_children()) {
        /*
         * Propagujemy zmiany tak, aby wierzchołki
         * w całości w [l, r] nie zostały zmienione.
         */
        if(node.has_change) {
          node.has_change = false;

          if(!(l <= this->left().l() && this->left().r() <= r)) {
            this->left().receive_change(node.latent_change);
          }
          if(!(l <= this->right().l() && this->right().r() <= r) &&
             this->right().l() < tree.elemc) {
            this->right().receive_change(node.latent_change);
          }
        }

        if(!(l > this->left().r())) {
          this->left().resum(l, r);
        }
        if(!(r < this->right().l())) {
          assert(this->right().l() < tree.elemc);
          this->right().resum(l, r);
        }
        if(this->r() < tree.elemc) {
          node.val = tree.sum(this->left().node.val, this->right().node.val);
        }
      }
    }
    void resum(size_t idx) {
      resum(idx, idx);
    }
    void resum() {
      resum(0, tree.elemc - 1);
    }
  };

private:
  size_t elemc = 0;
  mutable std::vector<Node> nodes;
  mutable bool has_latent_changes = false;
  mutable bool needs_resum = false;
  size_t to_resum_l, to_resum_r;

  /*
   * Z powodu rosnącej zawiłości implementacji metod zależących od pewnych
   * niezmienników stanu drzewa, zdecydowałem sie stworzyć poniższy subinterfejs
   * składający się z poniższych czterech semantycznie nazwanych metod.
   * Zaprojektowanie tego subinterfejsu wymagało spisania, jakie niezmienniki są
   * wymagane (przez metody używające poniższe metody) oraz subsekwentne
   * napisanie metod zapewniające te niezmienniki.
   */

  // Wierzchołki nie są nigdy resumowane przed wywołaniem require_valid_subtree.
  void invalidate_elem_parents(size_t l, size_t r) {
    assert(l <= r);
    assert(l < this->elemc);
    assert(r < this->elemc);

    // IDEA: Wymagaj brak zmian tylko nad [l, r]?
    require_no_changes_above(0, this->elemc - 1);
    if(this->needs_resum) {
      this->to_resum_l = std::min(this->to_resum_l, l);
      this->to_resum_r = std::max(this->to_resum_r, r);
    } else {
      this->needs_resum = true;
      this->to_resum_l = l;
      this->to_resum_r = r;
    }
  }
  void require_up_to_date_base(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < this->elemc);
    assert(r < this->elemc);

    require_no_changes_above(l, r);
  }
  void require_no_changes_above(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < this->elemc);
    assert(r < this->elemc);

    // IDEA: Propaguj zmiany tylko na ścieżkach z korzenia do [l, r]?
    if(this->has_latent_changes) {
      assert(!this->needs_resum);
      this->root_ops().propagate_change(true);
      this->has_latent_changes = false;
    }
    assert(!this->has_latent_changes);
  }
  void require_valid_subtree(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < this->elemc);
    assert(r < this->elemc);

    if(this->needs_resum) {
      assert(!this->has_latent_changes);
      this->root_ops().resum(this->to_resum_l, this->to_resum_r);
      this->needs_resum = false;
    }
  }

  // Skróty w implementacji

  NodeOps root_ops() const {
    assert(this->nodes.size() >= 1);
    return NodeOps(this->nodes[0], *this);
  }

  // operator[] bez kosztownych checków
  Node* node_at2(size_t idx) const {
    return &this->nodes[this->nodec() - this->basec() + idx];
  }
  Value& val_at(size_t idx) {
    return node_at2(idx)->val;
  }
  Value const& val_at(size_t idx) const {
    return node_at2(idx)->val;
  }

  void before_insert(const_iterator pos, size_t cnt) {
    assert(pos.idx <= this->elemc);
    if(pos.idx != this->elemc) {
      require_up_to_date_base(pos.idx, this->elemc - 1);
      require_no_changes_above(pos.idx, this->elemc - 1);
    }
    resize(this->elemc + cnt);
    std::move_backward(
      node_at2(pos.idx), node_at2(this->elemc - cnt), node_at2(this->elemc)
    );
  }
  iterator after_insert(const_iterator pos) {
    invalidate_elem_parents(pos.idx, this->elemc - 1);
    return iterator(this, pos.idx);
  }
};
