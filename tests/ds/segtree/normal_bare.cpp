#include "ds/segtree/normal_bare.hpp"
#include "dummy_segtree.hpp"
#include <iostream>

int main() {
  struct ApplyChange {
    int operator()(int val, int change, int elemc) const {
      return val + change * elemc;
    }
  };
  using Tree = SegTree<int, plus<int>, int, ApplyChange, plus<int>>;
  using DummyTree = DummySegTree<int, plus<int>, int, ApplyChange, plus<int>>;

  Tree tree(10);
  DummyTree correct_tree(10, 0);

  constexpr int min_change = -10, max_change = 10;
  srand(time(nullptr));
  auto rand_range = [&]() {
    int i = rand() % tree.elemc;
    int j = rand() % (tree.elemc - i) + i;
    return make_pair(i, j);
  };
  auto rand_change = [&]() {
    return rand() % (max_change - min_change + 1) + min_change;
  };

  for(int iter = 1; ; iter++) {
    cerr << "iter = " << iter << endl;

    switch(rand() % 3) {
    case 0: {
      auto [i, j] = rand_range();
      cout << "tree.get(" << i << ", " << j << "); [iter = " << iter << "]" << endl;

      auto res = tree.get(i, j);
      auto correct_res = correct_tree.get(i, j);
      cout << "    " << res << " " << correct_res << endl;
      assert(res == correct_res);
    } break;

    case 1: {
      auto [i, j] = rand_range();
      int change = rand_change();
      cout << "tree.modify(" << i << ", " << j << ", " << change << "); [iter = " << iter << "]" << endl;

      tree.modify(i, j, change);
      correct_tree.modify(i, j, change);
    } break;
    }
  }
}
