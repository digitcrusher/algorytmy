#include "ds/min_stack.hpp"
#include <iomanip>
#include <iostream>

int main() {
  MinStack<int, less<int>> stack;

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;
    if(op == "top") {
      cout << stack.top() << endl;
    } else if(op == "min") {
      cout << stack.min() << endl;
    } else if(op == "pop") {
      stack.pop();
    } else if(op == "empty") {
      cout << boolalpha << stack.empty() << endl;
    } else if(op == "size") {
      cout << stack.size() << endl;
    } else if(op == "push") {
      int a;
      cin >> a;
      if(!cin) break;
      stack.push(a);
    }
  }
}
