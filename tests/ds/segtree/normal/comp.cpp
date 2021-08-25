#include "ds/segtree/normal/comp.hpp"

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
  using Tree = SegmentTree<int, std::plus<int>, int, ApplyChange, MergeChange>;
  using DummyTree = DummySegTree<int, std::plus<int>, int, ApplyChange, MergeChange>;

  auto print_nodes = [&](Tree const& tree) {
    for(size_t i = 1; i <= tree.nodec(); i++) {
      std::cout << i << " has val " << tree.node_at(i).val;
      if(tree.node_at(i).has_change) {
        std::cout << " and change " << tree.node_at(i).latent_change;
      }
      std::cout << std::endl;
    }
  };

  std::cout << "\ntest #1" << std::endl;

  {
    struct Test1ApplyChange {
      Test1ApplyChange() {std::cout<<"Test1ApplyChange: default ctor"<<std::endl;}
      Test1ApplyChange(Test1ApplyChange const&) {std::cout<<"Test1ApplyChange: copy ctor"<<std::endl;}
      Test1ApplyChange(Test1ApplyChange &&) {std::cout<<"Test1ApplyChange: move ctor"<<std::endl;}
      Test1ApplyChange& operator=(Test1ApplyChange const&) {std::cout<<"Test1ApplyChange: copy assign"<<std::endl;return*this;}
      Test1ApplyChange& operator=(Test1ApplyChange &&) {std::cout<<"Test1ApplyChange: move assign"<<std::endl;return*this;}
      int operator()(int val, int change, size_t elemc) const {
        return val + change * elemc;
      }
    };
    using Tree = SegmentTree<int, std::plus<int>, int, Test1ApplyChange, MergeChange>;

    std::cout << "default ctor tree" << std::endl;
    Tree tree1;
    tree1.assign(7, 1);
    std::cout << tree1.get(1, 6) << std::endl;
    tree1.modify(1, 3, 2);
    std::cout << tree1.get(1, 6) << std::endl;


    std::cout << "copy ctor tree" << std::endl;
    Tree tree2 = tree1;

    std::cout << (tree2 == tree1) << std::endl;

    std::cout << "copy assign tree" << std::endl;
    Tree tree3;
    tree3 = tree1;

    std::cout << (tree3 == tree1) << std::endl;

    std::cout << "move ctor tree" << std::endl;
    Tree tree4 = std::move(tree1);

    std::cout << (tree4 == tree2) << std::endl;

    std::cout << "move assign tree" << std::endl;
    Tree tree5;
    tree5 = std::move(tree4);

    std::cout << (tree5 == tree2) << std::endl;

    tree1 = std::move(tree5);
    std::cout << (tree1 == tree2) << std::endl;
    tree2.modify(4, 5, -1);
    std::cout << (tree1 == tree2) << std::endl;
  }

  std::cout << "\ntest #2" << std::endl;

  {
    Tree tree, tree2;
    tree.assign({1, 2, 3, 4, 5, 6, 7, 8, 9});
    tree2.assign({0, 1, 2, 3, 4, 5, 6, 7, 8});
    std::cout << (tree == tree2) << std::endl;
    tree2.modify(0, 8, 1);
    std::cout << (tree == tree2) << std::endl;
    tree2.assign({0, 2, 3, 4, 5, 6, 7, 8, 9});
    tree2.modify(0, 0, 1);
    std::cout << (tree == tree2) << std::endl;
  }

  std::cout << "\ntest #3" << std::endl;

  {
    Tree tree;
    tree.assign({1, 2, 3, 4, 5});

    print_nodes(tree);

    tree.modify(0, 4, 1);

    print_nodes(tree);
  }

  std::cout << "\ntest #4" << std::endl;

  {
    Tree tree;
    tree.assign({1, 2, 3, 4, 5});

    std::cout << "iterator ";
    for(auto it = tree.begin(); it != tree.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "const_iterator ";
    for(auto it = tree.cbegin(); it != tree.cend(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;

    tree.assign(6, -1);

    std::cout << "iterator ";
    for(auto it = tree.begin(); it != tree.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "const_iterator ";
    for(auto it = tree.cbegin(); it != tree.cend(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;

    *tree.begin() = 123;
    //*tree.cbegin() = 123; // error: assignment of read-only location

    auto test = tree.cbegin();
    test = tree.end();
    std::cout << (tree.begin() - tree.cbegin()) << std::endl;
    std::cout << (tree.begin() - tree.end()) << std::endl;
    std::cout << (tree.cbegin() == tree.begin()) << std::endl;
    std::cout << (tree.begin() == tree.cbegin()) << std::endl;

    int test2[5] = {1, 2, 3, 4, 5};
    tree.insert(tree.begin() + 2, test2, test2 + 5);

    for(auto i: tree) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "\ntest #5" << std::endl;

  {
    Tree const tree({1, 2, 3, 4, 5});

    //tree.at(5); // Powinno wywalić błąd std::out_of_range

    std::cout << tree[2] << std::endl;

    for(auto it = tree.begin(); it != tree.end(); it++) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }

#if 0
  std::cout << "\ntemp test" << std::endl;

  {
    Tree tree(1, 0);
    auto print = [&]() {
      std::cout << "    tree: ";
      for(size_t i = 0; i < tree.size(); i++) {
        std::cout << tree[i] << " ";
      }
      std::cout << std::endl;
    };
    print();
    tree.resize(4);
    //print_nodes(tree);
    std::cout << tree.get(0, tree.size() - 1) << std::endl;


    for(auto i: tree) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
  return 0;
#endif

  std::cout << "\nrandom testing" << std::endl;

  {
    Tree tree(1, 0);
    DummyTree correct_tree(1, 0);

    constexpr size_t max_size = 10;
    constexpr int min_val = -50, max_val = 50;
    constexpr int min_change = -10, max_change = 10;

    auto print_both = [&]() {
      std::cout << "    tree: ";
      for(size_t i = 0; i < tree.size(); i++) {
        std::cout << tree[i] << " ";
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
    auto rand_val = [&]() {
      return rand() % (max_val - min_val + 1) + min_val;
    };
    auto rand_change = [&]() {
      return rand() % (max_change - min_change + 1) + min_change;
    };

    for(int iter = 1;; iter++) {
      std::cerr << "iter = " << iter << std::endl;
      switch(rand() % 7) {
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
          assert(tree[i] == correct_tree[i]);
        }
        break;

      case 3: {
        size_t new_size = rand() % max_size + 1;
        std::cout << "tree.resize(" << new_size << "); [iter = " << iter << "]" << std::endl;
        tree.resize(new_size);
        correct_tree.resize(new_size);
      } break;

      case 4: {
        auto i = rand() % (tree.size() + 1);
        int val = rand_val();
        std::cout << "tree.insert(tree.begin() + " << i << ", " << val << "); [iter = " << iter << "]" << std::endl;
        tree.insert(tree.begin() + i, val);
        correct_tree.insert(correct_tree.begin() + i, val);
      } break;

      case 5: {
        if(tree.empty()) {
          break;
        }
        auto [i, j] = rand_range();
        j++;
        std::cout << "tree.erase(tree.begin() + " << i << ", tree.begin() + " << j << "); [iter = " << iter << "]" << std::endl;
        tree.erase(tree.begin() + i, tree.begin() + j);
        correct_tree.erase(correct_tree.begin() + i, correct_tree.begin() + j);
      } break;

      case 6: {
        if(tree.empty()) {
          break;
        }
        auto i = rand_idx();
        auto val = rand_val();
        std::cout << "tree[" << i << "] = " << val << ";" << std::endl;
        tree[i] = val;
        correct_tree[i] = val;
      } break;

      }
    }
  }
}
