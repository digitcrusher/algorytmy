#include "ds/pbds.hpp"
#include "iostream.hpp"

int main() {
  pbds_set<ll> set;

  while(cin) {
    string op;
    cin >> op;

    if(op == "insert") {
      ll num;
      cin >> num;

      set.insert(num);

    } else if(op == "erase") {
      ll num;
      cin >> num;

      set.erase(num);

    } else if(op == "has") {
      ll num;
      cin >> num;

      cout << boolalpha << (set.find(num) != set.end()) << endl;

    } else if(op == "find_by_order") {
      int idx;
      cin >> idx;

      auto it = set.find_by_order(idx);
      if(it == set.end()) {
        cout << "nullopt" << endl;
      } else {
        cout << *it << endl;
      }

    } else if(op == "order_of_key") {
      ll num;
      cin >> num;

      cout << set.order_of_key(num) << endl;

    } else if(op == "print") {
      for(auto i: set) {
        cout << i << " ";
      }
      cout << endl;
    }
  }
}
