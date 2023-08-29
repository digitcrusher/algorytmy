#include "ds/min_stack.hpp"
#include "iostream.hpp"

int main() {
  MinStack<ll, less<>> stack;

  while(cin) {
    string op;
    cin >> op;

    if(op == "top") {
      cout << stack.top() << endl;

    } else if(op == "min") {
      cout << stack.min() << endl;

    } else if(op == "push") {
      ll num;
      cin >> num;

      stack.push(num);

    } else if(op == "pop") {
      stack.pop();

    } else if(op == "clear") {
      stack.clear();

    } else if(op == "empty") {
      cout << boolalpha << stack.empty() << endl;

    } else if(op == "size") {
      cout << stack.size() << endl;
    }
  }
}
