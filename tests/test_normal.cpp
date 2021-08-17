#include "../ds/segtree/normal.hpp"
#include "dummy_segtree.hpp"
#include <iostream>

int main() {
  struct ApplyChange {
    int operator()(int val, int change, size_t elemc) const {
      return val + change * elemc;
    }
  };
  struct MergeChange {
    int operator()(int a, int b) const {
      return a + b;
    }
  };
  using Tree = SegmentTree<int, std::plus<int>, int, ApplyChange, MergeChange>;
  using DummyTree = DummySegmentTree<int, std::plus<int>, int, ApplyChange, MergeChange>;

  Tree tree(10, 0);
  DummyTree correct_tree(10, 0);

  constexpr int min_change = -10, max_change = 10;

  auto print_both = [&]() {
    tree.root_ops().propagate_change(true);
    std::cout << "    tree: ";
    for(size_t i = 0; i < tree.size(); i++) {
      std::cout << tree.nodes[tree.base_offset() + i].val << " ";
    }
    std::cout << std::endl;

    std::cout << "    correct_tree: ";
    for(size_t i = 0; i < correct_tree.size(); i++) {
      std::cout << correct_tree[i] << " ";
    }
    std::cout << std::endl;
  };

  srand(time(nullptr));
  auto rand_idx = [&]() {
    return rand() % tree.size();
  };
  auto rand_range = [&]() {
    size_t i = rand() % tree.size();
    size_t j = rand() % (tree.size() - i) + i;
    return std::make_pair(i, j);
  };
  auto rand_change = [&]() {
    return rand() % (max_change - min_change + 1) + min_change;
  };

  for(int iter = 1;; iter++) {
    std::cerr << "iter = " << iter << std::endl;
    switch(rand() % 3) {
    case 0: {
      if(tree.empty()) {
        break;
      }
      auto [i, j] = rand_range();
      std::cout << "tree.get(" << i << ", " << j << "); [iter = " << iter << "]" << std::endl;
      auto res = tree.get(i, j);
      auto correct_res = correct_tree.get(i, j);
      std::cout << "    " << res << " " << correct_res << std::endl;
      assert(res == correct_res);
    } break;

    case 1: {
      if(tree.empty()) {
        break;
      }
      auto [i, j] = rand_range();
      int change = rand_change();
      std::cout << "tree.modify(" << i << ", " << j << ", " << change << "); [iter = " << iter << "]" << std::endl;
      tree.modify(i, j, change);
      correct_tree.modify(i, j, change);
    } break;

    case 2:
      std::cout << "equals [iter = " << iter << "]"<< std::endl;
      print_both();
      for(size_t i = 0; i < tree.size(); i++) {
        assert(tree.nodes[tree.base_offset() + i].val == correct_tree[i]);
      }
      break;
    }
  }
}
