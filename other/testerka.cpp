/*
 * Testerka w kodzie - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#include "common.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

// Przykładowe zadanie: Rozłóż każdą liczbę z ciągu na liczby pierwsze.

#include "math/sieve.hpp"

vector<vector<int>> opt(vector<int> nums) {
  // Rozwiązanie wzorcowe
  int n = nums.size();

  auto smallest_factor = sieve_euler(r::max(nums)).smallest_factor;

  vector<vector<int>> result(n);
  for(auto i: v::iota(0, n)) {
    while(nums[i] > 1) {
      auto prime = smallest_factor[nums[i]];
      result[i].push_back(prime);
      nums[i] /= prime;
    }
  }
  return result;
}

vector<vector<int>> brute(vector<int> nums) {
  // Rozwiązanie brutalne
  int n = nums.size();

  vector<vector<int>> result(n);
  for(auto i: v::iota(0, n)) {
    for(auto prime: v::iota(2) | v::take_while(λ(nums[i] > 1))) {
      while(nums[i] % prime == 0) {
        result[i].push_back(prime);
        nums[i] /= prime;
      }
    }
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifdef TESTERKA
  // Dane testu
  int n;
  vector<int> nums;

  srand(time(nullptr));
  auto gen_test = [&]() {
    // Generowanie testu
    n = rand() % 10 + 1;
    nums.resize(n);
    for(auto &i: nums) {
      i = rand() % 200'000 + 1;
    }
  };

  for(auto test: v::iota(0)) {
    cout << "test " << test;
    cout.flush();
    gen_test();

    auto start = chrono::steady_clock::now();
    auto opt_ans = opt(nums);
    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0;
    auto brute_ans = brute(nums);

    // Porównanie wyników wzorcówki i bruta
    auto is_ok = opt_ans == brute_ans;
    /*
     * Więcej opcji formatowania tekstu w terminalu na Linuxie
     * można znaleźć przy pomocy komendy "man console_codes(4)"
     * w sekcji "ECMA-48 Select Graphic Rendition".
     */
    if(is_ok) {
      cout << " \e[32mOK\e[0m ";
    } else {
      cout << " \e[31mFAIL\e[0m ";
    }
    cout << fixed << setprecision(2) << elapsed << "s" << endl;

    if(!is_ok) {
      // Wypisanie testu z wcięciem dwóch spacji
      cout << "  " << n << "\n";
      cout << "  ";
      for(auto i: nums) {
        cout << i << " ";
      }
      cout << "\n";

      cout << "opt ans:\n";
      // Wypisanie wyniku algorytmu wzorcowego
      for(auto &primes: opt_ans) {
        cout << "  ";
        for(auto i: primes) {
          cout << i << " ";
        }
        cout << "\n";
      }

      cout << "brute ans:\n";
      // Wypisanie wyniku algorytmu brutalnego
      for(auto &primes: brute_ans) {
        cout << "  ";
        for(auto i: primes) {
          cout << i << " ";
        }
        cout << "\n";
      }

      cout << endl;
      exit(EXIT_FAILURE);
    }
  }

#else
  // Wczytanie danych wejściowych
  int n;
  cin >> n;
  vector<int> nums(n);
  for(auto &i: nums) {
    cin >> i;
  }

#ifdef BRUTE
  auto ans = brute(nums);
#else
  auto ans = opt(nums);
#endif

  // Wypisanie wyniku wzorcówki
  for(auto &primes: ans) {
    for(auto i: primes) {
      cout << i << " ";
    }
    cout << "\n";
  }
#endif
}
