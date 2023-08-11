#include "ds/min_queue.hpp"
#include "iostream.hpp"

int main() {
  MinQueue<ll, less<ll>> queue;
  LazyMinQueue<ll, less<ll>> lazy;

  while(cin) {
    string op;
    cin >> op;

    if(op == "front") {
      cout << queue.front() << endl;

    } else if(op == "min") {
      cout << queue.min() << endl;
      assert(queue.min() == lazy.min());

    } else if(op == "push") {
      ll num;
      cin >> num;

      queue.push(num);
      lazy.push(num);

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
