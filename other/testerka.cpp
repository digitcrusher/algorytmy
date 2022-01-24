/*
 * Testerka w kodzie - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#include "common.hpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

// Przykładowe zadanie: Rozłóż każdą liczbę z ciągu na liczby pierwsze.

#include "math/sieve.hpp"
#include <vector>

vector<vector<int>> opt(int n, vector<int> nums) {
  // Rozwiązanie wzorcowe
  auto max_num = nums[0];
  for(auto num: nums) {
    max_num = max(max_num, num);
  }

  auto smallest_factor = sieve_eratosthenes(max_num).smallest_factor;

  vector<vector<int>> result(n);
  for(int i = 0; i < n; i++) {
    while(nums[i] > 1) {
      auto prime = smallest_factor[nums[i]];
      if(prime == -1) {
        prime = nums[i];
      }
      result[i].push_back(prime);
      nums[i] /= prime;
    }
  }
  return result;
}

vector<vector<int>> brute(int n, vector<int> nums) {
  // Rozwiązanie brutalne
  vector<vector<int>> result(n);
  for(int i = 0; i < n; i++) {
    for(int prime = 2; nums[i] > 1; prime++) {
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
    for(auto &num: nums) {
      num = rand() % 200000 + 1;
    }
  };

  for(int test = 0; ; test++) {
    cout << "test " << test;
    cout.flush();
    gen_test();

    auto start = chrono::steady_clock::now();
    auto opt_ans = opt(n, nums);
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0;
    auto brute_ans = brute(n, nums);

    // Porównanie wyników wzorcówki i bruta
    bool has_failed = opt_ans != brute_ans;
    /*
     * Więcej opcji formatowania tekstu w terminalu na Linuxie
     * można znaleźć przy pomocy komendy "man console_codes(4)"
     * w sekcji "ECMA-48 Select Graphic Rendition".
     */
    if(!has_failed) {
      cout << " \e[32mOK\e[0m ";
    } else {
      cout << " \e[31mFAIL\e[0m ";
    }
    cout << fixed << setprecision(2) << elapsed << "s" << endl;

    if(has_failed) {
      // Wypisanie testu z wcięciem dwóch spacji
      cout << "  " << n << "\n";
      cout << "  ";
      for(auto num: nums) {
        cout << num << " ";
      }
      cout << "\n";

      cout << "opt ans:\n";
      // Wypisanie wyniku algorytmu wzorcowego
      for(auto const& primes: opt_ans) {
        cout << "  ";
        for(auto prime: primes) {
          cout << prime << " ";
        }
        cout << "\n";
      }

      cout << "brute ans:\n";
      // Wypisanie wyniku algorytmu brutalnego
      for(auto const& primes: brute_ans) {
        cout << "  ";
        for(auto prime: primes) {
          cout << prime << " ";
        }
        cout << "\n";
      }

      cout << endl;
    }
  }

#else
  // Wczytanie danych wejściowych
  int n;
  cin >> n;
  vector<int> nums(n);
  for(auto &num: nums) {
    cin >> num;
  }

#ifdef BRUTE
  auto ans = brute(n, nums);
#else
  auto ans = opt(n, nums);
#endif

  // Wypisanie wyniku wzorcówki
  for(auto const& primes: ans) {
    for(auto prime: primes) {
      cout << prime << " ";
    }
    cout << "\n";
  }
#endif
}
