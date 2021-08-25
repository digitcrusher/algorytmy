#include "ds/segtree/normal/bare_bones.hpp"

#include "../dummy_segtree.hpp"
#include <cassert>
#include <cstdlib>
#include <functional>
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
  using Tree = SegTree<int, std::plus<int>, int, ApplyChange, MergeChange>;
  using DummyTree = DummySegTree<int, std::plus<int>, int, ApplyChange, MergeChange>;

  Tree tree(10);
  DummyTree correct_tree(10, 0);

  constexpr int min_change = -10, max_change = 10;

  srand(time(nullptr));
  auto rand_idx = [&]() {
    return rand() % tree.elemc;
  };
  auto rand_range = [&]() {
    size_t i = rand() % tree.elemc;
    size_t j = rand() % (tree.elemc - i) + i;
    return std::make_pair(i, j);
  };
  auto rand_change = [&]() {
    return rand() % (max_change - min_change + 1) + min_change;
  };

  for(int iter = 1;; iter++) {
    std::cerr << "iter = " << iter << std::endl;
    switch(rand() % 3) {
    case 0: {
      auto [i, j] = rand_range();
      std::cout << "tree.get(" << i << ", " << j << "); [iter = " << iter << "]" << std::endl;
      auto res = tree.get(i, j);
      auto correct_res = correct_tree.get(i, j);
      std::cout << "    " << res << " " << correct_res << std::endl;
      assert(res == correct_res);
    } break;

    case 1: {
      auto [i, j] = rand_range();
      int change = rand_change();
      std::cout << "tree.modify(" << i << ", " << j << ", " << change << "); [iter = " << iter << "]" << std::endl;
      tree.modify(i, j, change);
      correct_tree.modify(i, j, change);
    } break;
    }
  }
}
