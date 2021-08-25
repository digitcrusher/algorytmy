#include "misc.hpp"
#include <cassert>
#include <vector>

template<
  class Value,
  class Sum,
  class Change,
  class ApplyChange,
  class MergeChange
> struct DummySegTree: std::vector<Value> {
  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;

  DummySegTree(): std::vector<Value>() {}
  DummySegTree(size_t cnt, Value const& val): std::vector<Value>(cnt, val) {}
  explicit DummySegTree(size_t cnt): std::vector<Value>(cnt) {}
  template<typename InputIt, typename = require_input_iter<InputIt>>
  DummySegTree(InputIt first, InputIt end): std::vector<Value>(first, end) {}
  DummySegTree(std::initializer_list<Value> elems): std::vector<Value>(elems) {}

  Value get(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < this->size());
    assert(r < this->size());
    Value result = (*this)[l];
    for(size_t i = l + 1; i <= r; i++) {
      result = this->sum(result, (*this)[i]);
    }
    return result;
  }
  void modify(size_t l, size_t r, Change const& change) {
    assert(l <= r);
    assert(l < this->size());
    assert(r < this->size());
    for(size_t i = l; i <= r; i++) {
      (*this)[i] = this->apply_change((*this)[i], change, 1);
    }
  }
};
