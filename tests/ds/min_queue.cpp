#include "ds/min_queue.hpp"
#include <iostream>

int main() {
  MinQueue<int, less<int>> queue;
  LazyMinQueue<int, less<int>> lazy;

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "front") {
      cout << queue.front() << endl;
    } else if(op == "min") {
      cout << queue.min() << endl;
      assert(queue.min() == lazy.min());
    } else if(op == "push") {
      int a;
      cin >> a;
      if(!cin) break;
      queue.push(a);
      lazy.push(a);
    } else if(op == "pop") {
      queue.pop();
      lazy.pop();
    } else if(op == "clear") {
      queue.clear();
      lazy.clear();
    } else if(op == "empty") {
      cout << boolalpha << queue.empty() << endl;
      assert(queue.empty() == lazy.empty());
    } else if(op == "size") {
      cout << queue.size() << endl;
      assert(queue.size() == lazy.size());
    }
  }
}
