#include "string/lcs.hpp"
#include <iostream>

int main() {
  while(true) {
    string op, a, b;
    cin >> op >> a >> b;
    if(!cin) break;
    if(op == "len") {
      cout << lcs_len(a, b) << endl;
    } else if(op == "dp") {
      auto result = lcs_dp(a, b);
      for(auto &row: result) {
        for(int cell: row) {
          cout << cell << " ";
        }
        cout << endl;
      }
    } else if(op == "str") {
      string result = lcs_str(a, b);
      cout << result << endl;
      assert(result == lcs_str(a, b, lcs_dp(a, b)));
    }
  }
}
