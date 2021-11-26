#include "common.hpp"
#include "misc.hpp"
#include <vector>

template<
  class Value,
  class Sum,
  class Change,
  class ApplyChange,
  class MergeChange
> struct DummySegTree: vector<Value> {
  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;

  DummySegTree(): vector<Value>() {}
  DummySegTree(int cnt, Value const& val): vector<Value>(cnt, val) {}
  explicit DummySegTree(int cnt): vector<Value>(cnt) {}
  template<class InputIt, class = require_input_iter<InputIt>>
  DummySegTree(InputIt first, InputIt end): vector<Value>(first, end) {}
  DummySegTree(initializer_list<Value> elems): vector<Value>(elems) {}

  Value get(int l, int r) const {
    assert(l <= r);
    assert(l < this->size());
    assert(r < this->size());
    Value result = (*this)[l];
    for(int i = l + 1; i <= r; i++) {
      result = sum(result, (*this)[i]);
    }
    return result;
  }
  void modify(int l, int r, Change const& change) {
    assert(l <= r);
    assert(l < this->size());
    assert(r < this->size());
    for(int i = l; i <= r; i++) {
      (*this)[i] = apply_change((*this)[i], change, 1);
    }
  }
};
