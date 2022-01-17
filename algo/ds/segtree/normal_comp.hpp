/*
 * Wyczerpująca implementacja drzewa przedziałowego przedział-przedział
 *                                               digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/int.hpp"
#include "misc.hpp"
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

// TODO: https://en.cppreference.com/w/cpp/container/node_handle

/*
 * Wyczerpująca implementacja drzewa przedziałowego przedział-przedział -
 *   Kontener wspierający operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i modyfikacji (modify) w czasie logarytmicznym.
 *
 * Ta implementacja jest zgodna z C++11 oraz spełnia Container, ReversibleContainer
 * i SequenceContainer.
 *
 * Iteratory nigdy nie są unieważnione, jeśli adres drzewa w pamięci się nie
 * zmieni. Referencja do drzewa w iteratorach pozostaje taka sama po swap'ie,
 * więc drzewa na które wskazują iteratory też są wymieniane podczas swap'u.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów. Sum musi być łączne, czyli
 *   sum(sum(a, b), c) = sum(a, sum(b, c)).
 * ApplyChange: (Value, Change, size_t) -> Value
 *   Aplikuje zmianę na wartość sumy spójnego przedziału elementów o rozmiarze
 *   będącym potęgą dwójki.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 */
template<class Value, class Change>
struct DefaultApplyChange {
  Value operator()(Value const& val,
                   Change const& change __attribute__((unused)),
                   size_t elemc __attribute__((unused))) const
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
  class Change = tuple<>,
  class ApplyChange = DefaultApplyChange<Value, Change>,
  class MergeChange = DefaultMergeChange<Change>
> struct SegTree {
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
    using tree_pointer = type_if_t<is_const, SegTree const*, SegTree*>;
    using const_iterator = Iterator<true>;

    Iterator(tree_pointer tree, size_t idx): tree(tree), idx(idx) {}

    reference operator*() const {
      return (*tree)[idx];
    }
    reference operator->() const {
      return **this;
    }
    reference operator[](ptrdiff_t offset) const {
      return (*tree)[idx + offset];
    }

    bool operator==(const_iterator const& other) const {
      return tree == other.tree && idx == other.idx;
    }
    bool operator!=(const_iterator const& other) const {
      return !(*this == other);
    }

    Iterator& operator++() {
      idx++;
      return *this;
    }
    Iterator& operator--() {
      idx--;
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
      idx += offset;
      return *this;
    }
    Iterator& operator-=(ptrdiff_t offset) {
      idx -= offset;
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
      assert(tree == other.tree);
      return idx - other.idx;
    }
    bool operator<(const_iterator const& other) const {
      assert(tree == other.tree);
      return idx < other.idx;
    }
    bool operator>(const_iterator const& other) const {
      assert(tree == other.tree);
      return idx > other.idx;
    }
    bool operator<=(const_iterator const& other) const {
      return !(*this > other);
    }
    bool operator>=(const_iterator const& other) const {
      return !(*this < other);
    }

    operator const_iterator() const {
      return const_iterator(tree, idx);
    }

  private:
    tree_pointer tree;
    size_t idx;

    friend SegTree;
  };

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;

  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  iterator begin() {
    return iterator(this, 0);
  }
  iterator end() {
    return iterator(this, elemc);
  }
  const_iterator begin() const {
    return const_iterator(this, 0);
  }
  const_iterator end() const {
    return const_iterator(this, elemc);
  }
  const_iterator cbegin() const {
    return const_iterator(this, 0);
  }
  const_iterator cend() const {
    return const_iterator(this, elemc);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }
  reverse_iterator rend() {
    return reverse_iterator(begin());
  }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(cend());
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(cbegin());
  }

  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;

  struct Node {
    Value val;
    Change latent_change;
    bool has_change = false;

    Node() {}
    Node(Value val): val(val) {}
  };
  struct NodeOps;

  // Metoda do inspekcji wewnętrznej struktury drzewa
  Node const& node_at(size_t num) const {
    assert(num != 0);
    assert(num - 1 < nodec());
    return nodes[num - 1];
  }

  SegTree(Sum const& sum = Sum(),
          ApplyChange const& apply_change = ApplyChange(),
          MergeChange const& merge_change = MergeChange()):
    sum(sum), apply_change(apply_change), merge_change(merge_change) {}

  SegTree(size_t cnt, Value const& val,
          Sum const& sum = Sum(),
          ApplyChange const& apply_change = ApplyChange(),
          MergeChange const& merge_change = MergeChange()):
    SegTree(sum, apply_change, merge_change)
  {
    assign(cnt, val);
  }

  template<class InputIt, class = require_input_iter<InputIt>>
  SegTree(InputIt first, InputIt end,
          Sum const& sum = Sum(),
          ApplyChange const& apply_change = ApplyChange(),
          MergeChange const& merge_change = MergeChange()):
    SegTree(sum, apply_change, merge_change)
  {
    assign(first, end);
  }

  SegTree(initializer_list<Value> elems,
          Sum const& sum = Sum(),
          ApplyChange const& apply_change = ApplyChange(),
          MergeChange const& merge_change = MergeChange()):
    SegTree(sum, apply_change, merge_change)
  {
    assign(elems);
  }

  Value& operator[](size_t idx) {
    assert(idx < elemc);
    require_up_to_date_base(idx, idx);
    invalidate_elem_parents(idx, idx);
    return nodes[nodec() - base_nodec() + idx].val;
  }
  Value const& operator[](size_t idx) const {
    assert(idx < elemc);
    require_up_to_date_base(idx, idx);
    return nodes[nodec() - base_nodec() + idx].val;
  }

  Value& at(size_t idx) {
    if(idx >= elemc) {
      throw std::out_of_range(
        "SegTree.at(idx): idx (równe " + to_string(idx) + ") >= "
        "elemc (równe " + to_string(elemc) + ")"
      );
    }
    return (*this)[idx];
  }
  Value const& at(size_t idx) const {
    if(idx >= elemc) {
      throw std::out_of_range(
        "SegTree.at(idx): idx (równe " + to_string(idx) + ") >= "
        "elemc (równe " + to_string(elemc) + ")"
      );
    }
    return (*this)[idx];
  }

  size_t size() const {
    return elemc;
  }
  size_t max_size() const {
    /*
     * Dodanie jeden do max_size wywołałoby overflow, gdy
     * max_size vector'a to maksymalna wartość size_t.
     */
    return 1ull << floor_log2((nodes.max_size() - 1) + 1) - 1;
  }
  bool empty() const {
    return elemc == 0;
  }

  template<class ...A>
  int compare(SegTree<A...> const& other) const {
    require_up_to_date_base(0, elemc - 1);
    other.require_up_to_date_base(0, elemc - 1);
    for(size_t i = 0; i < min(elemc, other.elemc); i++) {
      if(val_at(i) < other.val_at(i)) {
        return -1;
      } else if(val_at(i) > other.val_at(i)) {
        return 1;
      }
    }
    return elemc < other.elemc ? -1 : (elemc > other.elemc ? 1 : 0);
  }

  template<class ...A>
  bool operator==(SegTree<A...> const& other) const {
    return compare(other) == 0;
  }
  template<class ...A>
  bool operator!=(SegTree<A...> const& other) const {
    return compare(other) != 0;
  }
  template<class ...A>
  bool operator<(SegTree<A...> const& other) const {
    return compare(other) < 0;
  }
  template<class ...A>
  bool operator<=(SegTree<A...> const& other) const {
    return compare(other) <= 0;
  }
  template<class ...A>
  bool operator>(SegTree<A...> const& other) const {
    return compare(other) > 0;
  }
  template<class ...A>
  bool operator>=(SegTree<A...> const& other) const {
    return compare(other) >= 0;
  }

  void swap(SegTree &other) {
    swap(sum, other.sum);
    swap(apply_change, other.apply_change);
    swap(merge_change, other.merge_change);
    swap(elemc, other.elemc);
    swap(nodes, other.nodes);
    swap(has_latent_changes, other,has_latent_changes);
    swap(needs_resum, other.needs_resum);
    swap(to_resum_l, other.to_resum_l);
    swap(to_resum_r, other.to_resum_r);
  }

  void clear() {
    elemc = 0;
    nodes.clear();
    has_latent_changes = false;
    needs_resum = false;
  }

  // TODO: Leniwe zmniejszanie drzewa
  void resize(size_t new_size, Value const& val = Value()) {
    auto old_metrics = metrics();
    size_t old_elemc = elemc;
    size_t old_height = height();
    elemc = new_size;

    if((elemc < old_elemc || height() > old_height) &&
       old_elemc > 0) {
      elemc = old_elemc;
      /*
       * std::move nie zeruje wartości, które przesuwa, więc zaległe zmiany
       * zostaną w nieodpowiednich miejscach, jeśli nie zrobimy tego:
       */
      require_no_changes_above(0, elemc - 1);
      elemc = new_size;
    }

    if(height() != old_height) {
      // Zwiększanie
      if(height() > old_height) {
        size_t add_levelc = height() - old_height;
        nodes.resize(nodec());
        for(size_t level = old_height - 1; level != -1ull; level--) {
          auto it = nodes.begin() + old_metrics.level_offset(level);
          std::move(
            it,
            it + old_metrics.level_nodec(level),
            nodes.begin() + level_offset(level + add_levelc)
          );
        }

      // Zmniejszanie
      } else {
        size_t del_levelc = old_height - height();
        for(size_t level = 0; level < height(); level++) {
          auto it = nodes.begin() + old_metrics.level_offset(level + del_levelc);
          std::move(
            it,
            it + level_nodec(level),
            nodes.begin() + level_offset(level)
          );
        }
        nodes.resize(nodec());
      }
    }

    // Wypełniamy nowe elementy val'em
    if(elemc > old_elemc) {
      std::fill(node_at_base(old_elemc), node_at_base(elemc), Node(val));
      invalidate_elem_parents(old_elemc, elemc - 1);
    } else if(elemc < old_elemc && needs_resum) {
      if(to_resum_l >= elemc) {
        needs_resum = false;
      } else {
        to_resum_r = min(to_resum_r, elemc - 1);
      }
    }
  }

  void assign(size_t cnt, Value const& val) {
    clear();
    elemc = cnt;
    nodes.resize(nodec(), Node(val));
    if(elemc > 0) {
      root().resum();
    }
  }
  template<class InputIt, class = require_input_iter<InputIt>>
  void assign(InputIt first, InputIt end) {
    clear();
    elemc = std::distance(first, end);
    nodes.resize(nodec());
    std::copy(first, end, nodes.end() - base_nodec());
    if(elemc > 0) {
      root().resum();
    }
  }
  void assign(initializer_list<Value> elems) {
    assign(elems.begin(), elems.end());
  }
  SegTree& operator=(initializer_list<Value> elems) {
    assign(elems);
    return *this;
  }

  template<class ...Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    before_insert(pos, 1);
    val_at(pos.idx) = move(Value(forward(args)...));
    return after_insert(pos);
  }
  iterator insert(const_iterator pos, Value const& val) {
    before_insert(pos, 1);
    val_at(pos.idx) = val;
    return after_insert(pos);
  }
  iterator insert(const_iterator pos, Value &&val) {
    before_insert(pos, 1);
    val_at(pos.idx) = move(val);
    return after_insert(pos);
  }
  iterator insert(const_iterator pos, size_t cnt, Value const& val) {
    before_insert(pos, cnt);
    auto ptr = node_at_base(pos.idx);
    std::fill(ptr, ptr + cnt, Node(val));
    return after_insert(pos);
  }
  template<class InputIt, class = require_input_iter<InputIt>>
  iterator insert(const_iterator pos, InputIt first, InputIt end) {
    before_insert(pos, std::distance(first, end));
    std::copy(first, end, node_at_base(pos.idx));
    return after_insert(pos);
  }
  iterator insert(const_iterator pos, initializer_list<Value> elems) {
    return insert(pos, elems.begin(), elems.end());
  }

  iterator erase(const_iterator first_it, const_iterator end_it) {
    size_t first = first_it.idx, end = end_it.idx;
    if(first >= end) {
      return this->end();
    }
    assert(end <= elemc);

    if(end != elemc) {
      require_up_to_date_base(end, elemc - 1);
    }
    require_no_changes_above(first, end - 1);
    std::move(node_at_base(end), node_at_base(elemc), node_at_base(first));
    resize(elemc - (end - first));
    if(first != elemc) {
      invalidate_elem_parents(first, elemc - 1);
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
    return (*this)[elemc - 1];
  }
  Value const& back() const {
    return (*this)[elemc - 1];
  }

  template<class ...Args>
  void emplace_front(Args &&...args) {
    emplace(begin(), forward(args)...);
  }
  template<class ...Args>
  void emplace_back(Args &&...args) {
    emplace(end(), forward(args)...);
  }
  void push_front(Value const& val) {
    insert(begin(), val);
  }
  void push_front(Value &&val) {
    insert(begin(), move(val));
  }
  void push_back(Value const& val) {
    insert(end(), val);
  }
  void push_back(Value &&val) {
    insert(end(), move(val));
  }
  void pop_front() {
    erase(begin());
  }
  void pop_back() {
    erase(end() - 1);
  }

  Value get(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < elemc);
    assert(r < elemc);
    require_valid_subtree(l, r);
    return root().get(l, r);
  }
  void modify(size_t l, size_t r, Change const& change) {
    assert(l <= r);
    assert(l < elemc);
    assert(r < elemc);
    require_valid_subtree(l, r);
    if(l != r) {
      has_latent_changes = true;
    }
    root().modify(l, r, change);
  }

  // Stworzone aby uprościć implementację resize.
  struct Metrics {
    size_t elemc;

    Metrics(size_t elemc): elemc(elemc) {}

    size_t height() const {
      return elemc == 0 ? 0 : ceil_log2(elemc) + 1;
    }
    size_t level_nodec(size_t level) const {
      return 1ull << level;
    }
    size_t level_offset(size_t level) const {
      return (1ull << level) - 1;
    }

    size_t nodec() const {
      return level_offset(height());
    }
    size_t base_nodec() const {
      return level_nodec(height() - 1);
    }
    size_t base_offset() const {
      return level_offset(height() - 1);
    }
  };

  Metrics metrics() const {
    return Metrics(elemc);
  }

  size_t height() const {
    return metrics().height();
  }
  size_t level_nodec(size_t level) const {
    return metrics().level_nodec(level);
  }
  size_t level_offset(size_t level) const {
    return metrics().level_offset(level);
  }

  size_t nodec() const {
    return metrics().nodec();
  }
  size_t base_nodec() const {
    return metrics().base_nodec();
  }
  size_t base_offset() const {
    return metrics().base_offset();
  }

  /*
   * Node nie ma dostępu do drzewa z jego metod, a referencja do drzewa
   * w każdym wierzchołku byłaby za bardzo kosztowna pamięciowo.
   */
  struct NodeOps {
    size_t const num;
    SegTree const& tree;
    Node &node;

    size_t const level, elemc, l, r;
    bool const has_children;

    NodeOps(size_t num, SegTree const& tree):
      num(num), tree(tree), node(tree.nodes[num - 1]),
      level(floor_log2(num)),
      elemc(tree.base_nodec() >> level),
      l((num - 1 - tree.level_offset(level)) * elemc),
      r(l + elemc - 1),
      has_children(l != r) {}

    NodeOps parent() const {
      assert(level > 0);
      return NodeOps(num / 2, tree);
    }
    NodeOps left() const {
      assert(level < tree.height() - 1);
      return NodeOps(num * 2, tree);
    }
    NodeOps right() const {
      assert(level < tree.height() - 1);
      return NodeOps(num * 2 + 1, tree);
    }

    bool is_in(size_t l, size_t r) const {
      return l <= this->l && this->r <= r;
    }
    bool does_intersect(size_t l, size_t r) const {
      return !(l > this->r || r < this->l);
    }

    void receive_change(Change const& change) {
      /*
       * Nie powinny nas nigdy interesować wierzchołki
       * z przedziałem niezawierającym elementy z tablicy.
       */
      assert(l < tree.elemc);

      /*
       * Nie chcemy marnować czasu na aktualizowanie wartości wierzchołka
       * z przedziałem zawierającym elementy spoza tablicy.
       */
      if(r < tree.elemc) {
        node.val = tree.apply_change(node.val, change, elemc);
      }
      // SegTree.has_latent_changes zależy od poniższego zachowania.
      if(has_children) {
        node.latent_change = node.has_change ? tree.merge_change(node.latent_change, change) : change;
        node.has_change = true;
      }
    }
    void propagate_change(bool should_recurse = false) {
      assert(l < tree.elemc);

      if(node.has_change) {
        node.has_change = false;

        if(has_children) {
          left().receive_change(node.latent_change);
          /*
           * Nie chcemy marnować czasu na aktualizowanie prawego dziecka, jeśli
           * jego przedział nie zawiera żadnych elementów tablicy. Nie musimy
           * robić ifa dla lewego dziecka, bo na pewno zawiera jakieś elementy
           * z tablicy, jeśli obecny wierzchołek też zawiera jakieś, co na pewno
           * jest prawdą, skoro powyższy assert nie został naruszony.
           */
          if(right().l < tree.elemc) {
            right().receive_change(node.latent_change);
          }
        }
      }

      if(has_children && should_recurse) {
        left().propagate_change(true);
        if(right().l < tree.elemc) {
          right().propagate_change(true);
        }
      }
    }

    Value get(size_t l, size_t r) {
      assert(does_intersect(l, r));
      assert(this->l < tree.elemc);

      if(is_in(l, r)) {
        return node.val;
      } else {
        propagate_change();
        if(!right().does_intersect(l, r)) {
          return left().get(l, r);
        } else if(!left().does_intersect(l, r)) {
          /*
           * Poprawne zapytanie o modyfikacje nigdy nie zejdzie do prawego
           * dziecka, jeśli nie zawiera żadnych elementów tablicy. Poniższy
           * assert to sanity check.
           */
          assert(right().l < tree.elemc);
          return right().get(l, r);
        } else {
          assert(right().l < tree.elemc);
          return tree.sum(left().get(l, r), right().get(l, r));
        }
      }
    }

    void modify(size_t l, size_t r, Change const& change) {
      assert(does_intersect(l, r));
      assert(this->l < tree.elemc);

      if(is_in(l, r)) {
        receive_change(change);
      } else {
        propagate_change();
        if(left().does_intersect(l, r)) {
          left().modify(l, r, change);
        }
        if(right().does_intersect(l, r)) {
          assert(right().l < tree.elemc);
          right().modify(l, r, change);
        }
        /*
         * Poprawne zapytanie o sumę przedziału nigdy nie weźmie wartości
         * obecnego wierzchołka, jeśli jego przedział nie zawiera się w tablicy.
         */
        if(this->r < tree.elemc) {
          node.val = tree.sum(left().node.val, right().node.val);
        }
      }
    }

    void resum(size_t l, size_t r) {
      assert(does_intersect(l, r));
      assert(this->l < tree.elemc);

      if(has_children) {
        /*
         * Propagujemy zmiany tak, aby wierzchołki
         * w całości w [l, r] nie zostały zmienione.
         */
        if(node.has_change) {
          node.has_change = false;

          if(!left().is_in(l, r)) {
            left().receive_change(node.latent_change);
          }
          if(!right().is_in(l, r) && right().l < tree.elemc) {
            right().receive_change(node.latent_change);
          }
        }

        if(left().does_intersect(l, r)) {
          left().resum(l, r);
        }
        if(right().does_intersect(l, r)) {
          assert(right().l < tree.elemc);
          right().resum(l, r);
        }
        if(this->r < tree.elemc) {
          node.val = tree.sum(left().node.val, right().node.val);
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
  mutable vector<Node> nodes;
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
    assert(l < elemc);
    assert(r < elemc);

    // IDEA: Wymagaj brak zmian tylko nad [l, r]?
    require_no_changes_above(0, elemc - 1);
    if(needs_resum) {
      to_resum_l = min(to_resum_l, l);
      to_resum_r = max(to_resum_r, r);
    } else {
      needs_resum = true;
      to_resum_l = l;
      to_resum_r = r;
    }
  }
  void require_up_to_date_base(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < elemc);
    assert(r < elemc);

    require_no_changes_above(l, r);
  }
  void require_no_changes_above(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < elemc);
    assert(r < elemc);

    // IDEA: Propaguj zmiany tylko na ścieżkach z korzenia do [l, r]?
    if(has_latent_changes) {
      assert(!needs_resum);
      root().propagate_change(true);
      has_latent_changes = false;
    }
    assert(!has_latent_changes);
  }
  void require_valid_subtree(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < elemc);
    assert(r < elemc);

    if(needs_resum) {
      assert(!has_latent_changes);
      root().resum(to_resum_l, to_resum_r);
      needs_resum = false;
    }
  }

  // Skróty w implementacji

  NodeOps root() const {
    assert(elemc >= 1);
    return NodeOps(1, *this);
  }

  // operator[] bez kosztownych checków
  Node* node_at_base(size_t idx) const {
    return &nodes[nodec() - base_nodec() + idx];
  }
  Value& val_at(size_t idx) {
    return node_at_base(idx)->val;
  }
  Value const& val_at(size_t idx) const {
    return node_at_base(idx)->val;
  }

  void before_insert(const_iterator pos, size_t cnt) {
    assert(pos.idx <= elemc);
    if(pos.idx != elemc) {
      require_up_to_date_base(pos.idx, elemc - 1);
      require_no_changes_above(pos.idx, elemc - 1);
    }
    resize(elemc + cnt);
    std::move_backward(
      node_at_base(pos.idx), node_at_base(elemc - cnt), node_at_base(elemc)
    );
  }
  iterator after_insert(const_iterator pos) {
    invalidate_elem_parents(pos.idx, elemc - 1);
    return iterator(this, pos.idx);
  }
};
