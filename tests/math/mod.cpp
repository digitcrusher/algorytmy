#include "math/mod.hpp"
#include <iostream>
#include <sstream>

int main() {
  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "norm_mod") {
      ll a, mod;
      cin >> a >> mod;
      if(!cin) break;
      cout << norm_mod(a, mod) << endl;

    } else if(op == "mod_mul") {
      ll a, b, mod;
      cin >> a >> b >> mod;
      if(!cin) break;
      cout << mod_mul(a, b, mod) << endl;

    } else if(op == "mod_pow") {
      ll a, b, mod;
      cin >> a >> b >> mod;
      if(!cin) break;
      cout << mod_pow(a, b, mod) << endl;

    } else if(op == "mod_inv") {
      ll a, mod;
      cin >> a >> mod;
      if(!cin) break;
      auto result = mod_inv(a, mod);
      if(result == nullopt) {
        cout << "nullopt" << endl;
      } else {
        cout << *result << endl;
        assert(norm_mod(a * *result, mod) == 1);
      }

    } else if(op == "mod_inv_prime") {
      ll a, mod;
      cin >> a >> mod;
      if(!cin) break;
      auto result = mod_inv_prime(a, mod);
      if(result == nullopt) {
        cout << "nullopt" << endl;
      } else {
        cout << *result << endl;
        assert(norm_mod(a * *result, mod) == 1);
      }

    } else if(op == "fac") {
      ll a, mod;
      cin >> a >> mod;
      if(!cin) break;
      cout << fac(a, mod) << endl;

    } else if(op == "fac_mem") {
      cout << "unordered_map<ll, vector<ll>> fac_mem = {" << endl;

      for(auto &[mod, vals]: fac_mem) {
        int line_width = printf("  {%lli, {", mod);
        for(ll val: vals) {
          string val_str = to_string(val);

          stringstream alt;
          alt << "0x" << hex << val;
          if(val_str.size() > alt.tellp()) {
            val_str = alt.str();
          }

          val_str += ",";
          if(line_width + val_str.size() > 80) {
            cout << endl;
            line_width = printf("  ");
          }
          line_width += printf("%s", val_str.c_str());
        }
        cout << "}}," << endl;
      }

      cout << "};" << endl;
      cout << "int const fac_skip = " << fac_skip << ";" << endl;
    }
  }
}
