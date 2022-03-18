#include "math/fft.hpp"
#include <iostream>

int main() {
  while(true) {
    string op;
    int n;
    cin >> op >> n;
    vector<cld> a(n);
    for(cld &num: a) {
      cin >> num;
    }
    if(!cin) break;

    vector<cld> result;

    if(op == "dft") {
      fft(a);
    } else if(op == "idft") {
      fft(a, true);
    } else if(op.substr(0, 3) == "mul") {
      int m;
      cin >> m;
      vector<cld> b(m);
      for(cld &num: b) {
        cin >> num;
      }
      if(!cin) break;
      mul(a, b);
      if(op.substr(3) == "_real") {
        for(cld &num: a) {
          num = num.real();
        }
      } else if(op.substr(3) == "_int") {
        for(cld &num: a) {
          num = round(num.real());
        }
      }
    }

    for(cld num: a) {
      cout << num << " ";
    }
    cout << endl;
  }
}
