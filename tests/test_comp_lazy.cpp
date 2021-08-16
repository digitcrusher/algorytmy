#include "../ds/segtree/comp_lazy.hpp"
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
  Tree const tree;
  const_cast<Tree&>(tree).default_val = 1;
  const_cast<Tree&>(tree).len = 10;
  const_cast<Tree&>(tree).root = new decltype(tree)::Node(*tree.node_middleman, 0, tree.len - 1);

  Tree const tree2(tree);
  //std::cout << "tree2 " << std::is_const<typename std::remove_pointer<decltype(tree2)>::type>::value << std::endl;

  std::cout << tree.get(1, 3) << " " << tree2.get(1, 3) << std::endl;
  //tree.modify(1, 3, 2);
  std::cout << tree.get(1, 3) << " " << tree2.get(1, 3) << std::endl;
  //tree.swap(tree2);
  std::cout << tree.get(1, 3) << " " << tree2.get(1, 3) << std::endl;

  Tree const tree3 = std::move(tree2);

  std::cout << "ready" << std::endl;

  std::cout << tree3.get(1, 3) << std::endl;
}
