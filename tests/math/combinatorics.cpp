#include "math/combinatorics.hpp"
#include "iostream.hpp"
#include <sstream>

int main() {
  while(cin) {
    string op;
    cin >> op;

    if(op == "fac") {
      ll x, mod;
      cin >> x >> mod;

      cout << fac(x, mod) << endl;

    } else if(op == "fac_mem") {
      cout << "unordered_map<ll, vector<ll>> fac_mem = {" << endl;

      for(auto &[mod, vals]: fac_mem) {
        int line_width = printf("  {%lli, {", mod);
        for(auto val: vals) {
          auto str = to_string(val);

          stringstream alt;
          alt << "0x" << hex << val;
          if(alt.tellp() < str.size()) {
            str = alt.str();
          }

          str += ",";
          if(line_width + str.size() > 80) {
            cout << endl;
            line_width = printf("  ");
          }
          line_width += printf("%s", str.c_str());
        }
        cout << "}}," << endl;
      }

      cout << "};" << endl;
      cout << "ll const fac_skip = " << fac_skip << ";" << endl;

    } else if(op == "choose") {
      int n, k;
      ll mod;
      cin >> n >> k >> mod;

      cout << choose(n, k, mod) << endl;
      assert(choose_fac(n, k, mod) == choose_mul(n, k, mod));

    } else if(op == "any_in_uniq") {
      int n, k;
      ll mod;
      cin >> n >> k >> mod;

      cout << any_in_uniq(n, k, mod) << endl;

    } else if(op == "uniq_in_uniq") {
      int n, k;
      ll mod;
      cin >> n >> k >> mod;

      cout << uniq_in_uniq(n, k, mod) << endl;

    } else if(op == "subfac") {
      int n;
      ll mod;
      cin >> n >> mod;

      cout << subfac(n, mod) << endl;

    } else if(op == "burnside") {
      int n, k;
      ll mod;
      cin >> n >> k >> mod;

      cout << burnside(n, k, mod) << endl;

    } else if(op == "catalan") {
      int n;
      ll mod;
      cin >> n >> mod;

      cout << catalan(n, mod) << endl;
    }
  }
}
