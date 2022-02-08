#include "ds/seg_tree_extra.hpp"
#include <iostream>

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

int main() {
  struct ApplyChange {
    int operator()(int val, int change, size_t elemc) const {
      return val + change * elemc;
    }
  };
  using Tree = SegTree<int, plus<int>, int, ApplyChange, plus<int>>;
  using DummyTree = DummySegTree<int, plus<int>, int, ApplyChange, plus<int>>;

  auto print_nodes = [&](Tree const& tree) {
    for(int i = 1; i <= tree.nodec(); i++) {
      cout << i << " has val " << tree.node_at(i).val;
      if(tree.node_at(i).has_change) {
        cout << " and change " << tree.node_at(i).latent_change;
      }
      cout << endl;
    }
  };

  cout << "\ntest #1" << endl;

  {
    struct Test1ApplyChange {
      Test1ApplyChange() {cout<<"Test1ApplyChange: default ctor"<<endl;}
      Test1ApplyChange(Test1ApplyChange const&) {cout<<"Test1ApplyChange: copy ctor"<<endl;}
      Test1ApplyChange(Test1ApplyChange &&) {cout<<"Test1ApplyChange: move ctor"<<endl;}
      Test1ApplyChange& operator=(Test1ApplyChange const&) {cout<<"Test1ApplyChange: copy assign"<<endl;return*this;}
      Test1ApplyChange& operator=(Test1ApplyChange &&) {cout<<"Test1ApplyChange: move assign"<<endl;return*this;}
      int operator()(int val, int change, size_t elemc) const {
        return val + change * elemc;
      }
    };
    using Tree = SegTree<int, plus<int>, int, Test1ApplyChange, plus<int>>;

    cout << "default ctor tree" << endl;
    Tree tree1;
    tree1.assign(7, 1);
    cout << tree1.get(1, 6) << endl;
    tree1.modify(1, 3, 2);
    cout << tree1.get(1, 6) << endl;


    cout << "copy ctor tree" << endl;
    Tree tree2 = tree1;

    cout << (tree2 == tree1) << endl;

    cout << "copy assign tree" << endl;
    Tree tree3;
    tree3 = tree1;

    cout << (tree3 == tree1) << endl;

    cout << "move ctor tree" << endl;
    Tree tree4 = move(tree1);

    cout << (tree4 == tree2) << endl;

    cout << "move assign tree" << endl;
    Tree tree5;
    tree5 = move(tree4);

    cout << (tree5 == tree2) << endl;

    tree1 = move(tree5);
    cout << (tree1 == tree2) << endl;
    tree2.modify(4, 5, -1);
    cout << (tree1 == tree2) << endl;
  }

  cout << "\ntest #2" << endl;

  {
    Tree tree, tree2;
    tree.assign({1, 2, 3, 4, 5, 6, 7, 8, 9});
    tree2.assign({0, 1, 2, 3, 4, 5, 6, 7, 8});
    cout << (tree == tree2) << endl;
    tree2.modify(0, 8, 1);
    cout << (tree == tree2) << endl;
    tree2.assign({0, 2, 3, 4, 5, 6, 7, 8, 9});
    tree2.modify(0, 0, 1);
    cout << (tree == tree2) << endl;
  }

  cout << "\ntest #3" << endl;

  {
    Tree tree;
    tree.assign({1, 2, 3, 4, 5});

    print_nodes(tree);

    tree.modify(0, 4, 1);

    print_nodes(tree);
  }

  cout << "\ntest #4" << endl;

  {
    Tree tree;
    tree.assign({1, 2, 3, 4, 5});

    cout << "iterator ";
    for(auto it = tree.begin(); it != tree.end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
    cout << "const_iterator ";
    for(auto it = tree.cbegin(); it != tree.cend(); ++it) {
      cout << *it << " ";
    }
    cout << endl;

    tree.assign(6, -1);

    cout << "iterator ";
    for(auto it = tree.begin(); it != tree.end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
    cout << "const_iterator ";
    for(auto it = tree.cbegin(); it != tree.cend(); ++it) {
      cout << *it << " ";
    }
    cout << endl;

    *tree.begin() = 123;
    //*tree.cbegin() = 123; // error: assignment of read-only location

    auto test = tree.cbegin();
    test = tree.end();
    cout << (tree.begin() - tree.cbegin()) << endl;
    cout << (tree.begin() - tree.end()) << endl;
    cout << (tree.cbegin() == tree.begin()) << endl;
    cout << (tree.begin() == tree.cbegin()) << endl;

    int test2[5] = {1, 2, 3, 4, 5};
    tree.insert(tree.begin() + 2, test2, test2 + 5);

    for(auto i: tree) {
      cout << i << " ";
    }
    cout << endl;
  }

  cout << "\ntest #5" << endl;

  {
    Tree const tree({1, 2, 3, 4, 5});

    //tree.at(5); // Powinno wywalić błąd out_of_range

    cout << tree[2] << endl;

    for(auto it = tree.begin(); it != tree.end(); it++) {
      cout << *it << " ";
    }
    cout << endl;
  }

#if 0
  cout << "\ntemp test" << endl;

  {
    Tree tree(1, 0);
    auto print = [&]() {
      cout << "    tree: ";
      for(int i = 0; i < tree.size(); i++) {
        cout << tree[i] << " ";
      }
      cout << endl;
    };
    print();
    tree.resize(4);
    //print_nodes(tree);
    cout << tree.get(0, tree.size() - 1) << endl;


    for(auto i: tree) {
      cout << i << " ";
    }
    cout << endl;
  }
  return 0;
#endif

  cout << "\nrandom testing" << endl;

  {
    Tree tree(1, 0);
    DummyTree correct_tree(1, 0);

    constexpr int max_size = 10;
    constexpr int min_val = -50, max_val = 50;
    constexpr int min_change = -10, max_change = 10;

    auto print_both = [&]() {
      cout << "    tree: ";
      for(int i = 0; i < tree.size(); i++) {
        cout << tree[i] << " ";
      }
      cout << endl;

      cout << "    correct_tree: ";
      for(int i = 0; i < correct_tree.size(); i++) {
        cout << correct_tree[i] << " ";
      }
      cout << endl;
    };

    srand(time(nullptr));
    auto rand_idx = [&]() {
      return rand() % tree.size();
    };
    auto rand_range = [&]() {
      int i = rand() % tree.size();
      int j = rand() % (tree.size() - i) + i;
      return make_pair(i, j);
    };
    auto rand_val = [&]() {
      return rand() % (max_val - min_val + 1) + min_val;
    };
    auto rand_change = [&]() {
      return rand() % (max_change - min_change + 1) + min_change;
    };

    for(int iter = 1;; iter++) {
      cerr << "iter = " << iter << endl;
      switch(rand() % 7) {
      case 0: {
        if(tree.empty()) {
          break;
        }
        auto [i, j] = rand_range();
        cout << "tree.get(" << i << ", " << j << "); [iter = " << iter << "]" << endl;
        auto res = tree.get(i, j);
        auto correct_res = correct_tree.get(i, j);
        cout << "    " << res << " " << correct_res << endl;
        assert(res == correct_res);
      } break;

      case 1: {
        if(tree.empty()) {
          break;
        }
        auto [i, j] = rand_range();
        int change = rand_change();
        cout << "tree.modify(" << i << ", " << j << ", " << change << "); [iter = " << iter << "]" << endl;
        tree.modify(i, j, change);
        correct_tree.modify(i, j, change);
      } break;

      case 2:
        cout << "equals [iter = " << iter << "]"<< endl;
        print_both();
        for(int i = 0; i < tree.size(); i++) {
          assert(tree[i] == correct_tree[i]);
        }
        break;

      case 3: {
        int new_size = rand() % max_size + 1;
        cout << "tree.resize(" << new_size << "); [iter = " << iter << "]" << endl;
        tree.resize(new_size);
        correct_tree.resize(new_size);
      } break;

      case 4: {
        auto i = rand() % (tree.size() + 1);
        int val = rand_val();
        cout << "tree.insert(tree.begin() + " << i << ", " << val << "); [iter = " << iter << "]" << endl;
        tree.insert(tree.begin() + i, val);
        correct_tree.insert(correct_tree.begin() + i, val);
      } break;

      case 5: {
        if(tree.empty()) {
          break;
        }
        auto [i, j] = rand_range();
        j++;
        cout << "tree.erase(tree.begin() + " << i << ", tree.begin() + " << j << "); [iter = " << iter << "]" << endl;
        tree.erase(tree.begin() + i, tree.begin() + j);
        correct_tree.erase(correct_tree.begin() + i, correct_tree.begin() + j);
      } break;

      case 6: {
        if(tree.empty()) {
          break;
        }
        auto i = rand_idx();
        auto val = rand_val();
        cout << "tree[" << i << "] = " << val << ";" << endl;
        tree[i] = val;
        correct_tree[i] = val;
      } break;

      }
    }
  }
}
