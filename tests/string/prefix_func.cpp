#include "string/prefix_func.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string s;
    cin >> s;

    cout << prefix_func(s) << endl;
  }
}
