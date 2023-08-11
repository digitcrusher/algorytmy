#include "graph/two_sat.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m;
    cin >> n >> m;
    vector<Clause> formula(m);
    for(auto &[a, not_a, b, not_b]: formula) {
      string a_str, b_str;
      cin >> a_str >> b_str;
      not_a = a_str[0] == '!';
      not_b = b_str[0] == '!';
      a = stoi(not_a ? a_str.substr(1) : a_str) - 1;
      b = stoi(not_b ? b_str.substr(1) : b_str) - 1;
    }

    auto result = two_sat(n, formula);
    if(result) {
      cout << boolalpha << *result << endl;
    } else {
      cout << "nullopt" << endl;
    }
  }
}
