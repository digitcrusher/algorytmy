/*
 * Testerka w kodzie - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
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

vector<vector<int>> opt(vector<int> nums) {
  // Rozwiązanie wzorcowe
  int const n = nums.size();

  int max_num = nums[0];
  for(int num: nums) {
    max_num = max(max_num, num);
  }

  auto smallest_factor = sieve_euler(max_num).smallest_factor;

  vector<vector<int>> result(n);
  for(int i = 0; i < n; i++) {
    while(nums[i] > 1) {
      int prime = smallest_factor[nums[i]];
      result[i].push_back(prime);
      nums[i] /= prime;
    }
  }
  return result;
}

vector<vector<int>> brute(vector<int> nums) {
  // Rozwiązanie brutalne
  int const n = nums.size();

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
    for(int &num: nums) {
      num = rand() % 200000 + 1;
    }
  };

  for(int test = 0; ; test++) {
    cout << "test " << test;
    cout.flush();
    gen_test();

    auto start = chrono::steady_clock::now();
    auto opt_ans = opt(nums);
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0;
    auto brute_ans = brute(nums);

    // Porównanie wyników wzorcówki i bruta
    bool is_ok = opt_ans == brute_ans;
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
      for(int num: nums) {
        cout << num << " ";
      }
      cout << "\n";

      cout << "opt ans:\n";
      // Wypisanie wyniku algorytmu wzorcowego
      for(auto const& primes: opt_ans) {
        cout << "  ";
        for(int prime: primes) {
          cout << prime << " ";
        }
        cout << "\n";
      }

      cout << "brute ans:\n";
      // Wypisanie wyniku algorytmu brutalnego
      for(auto const& primes: brute_ans) {
        cout << "  ";
        for(int prime: primes) {
          cout << prime << " ";
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
  for(int &num: nums) {
    cin >> num;
  }

#ifdef BRUTE
  auto ans = brute(nums);
#else
  auto ans = opt(nums);
#endif

  // Wypisanie wyniku wzorcówki
  for(auto const& primes: ans) {
    for(int prime: primes) {
      cout << prime << " ";
    }
    cout << "\n";
  }
#endif
}
