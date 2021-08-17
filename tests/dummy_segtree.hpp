#include "../misc.hpp"
#include <tuple>
#include <vector>

template<
  typename Value,
  typename Sum,
  typename Change = std::tuple<>,
  typename ApplyChange = DefaultApplyChange<Value, Change>,
  typename MergeChange = DefaultMergeChange<Change>
> struct DummySegmentTree: std::vector<Value> {
  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;

  DummySegmentTree(): std::vector<Value>() {}
  DummySegmentTree(size_t cnt, Value const& val): std::vector<Value>(cnt, val) {}
  explicit DummySegmentTree(size_t cnt): std::vector<Value>(cnt) {}
  template<typename InputIt, typename = require_input_iter<InputIt>>
  DummySegmentTree(InputIt first, InputIt end): std::vector<Value>(first, end) {}
  DummySegmentTree(std::initializer_list<Value> elems): std::vector<Value>(elems) {}

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
