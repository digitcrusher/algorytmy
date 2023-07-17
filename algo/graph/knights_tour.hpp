/*
 * Problem skoczka szachowego - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <functional>
#include <optional>
#include <vector>

/*
 * Znajduje ścieżkę skoczka szachowego przechodzącą po każdym polu planszy przy
 * pomocy heurystyki Warnsdorffa z modyfikacją Pohla w prawie zawsze O(w * h).
 * Tę heurystykę można też zastosować do ogólniejszego problemu ścieżki
 * Hamiltona.
 */
optional<vector<vector<int>>> knights_tour(int w, int h, int x, int y) {
  if(w % 2 == 1 && h % 2 == 1 && (x + y) % 2 == 1) {
    return nullopt;
  }

  array<pair<int, int>, 8> const moves = {{
    {2, 1},
    {1, 2},
    {-1, 2},
    {-2, 1},
    {-2, -1},
    {-1, -2},
    {1, -2},
    {2, -1},
  }};

  vector result(h, vector<int>(w, -1));

  function<bool(int, int, int)> backtrack = [&](int x, int y, int visc) {
    result[y][x] = visc;
    visc++;
    if(visc == w * h) {
      return true;
    }

    struct Next {
      int furtherc, beyondc, x, y;
    };
    vector<Next> nexts;
    nexts.reserve(moves.size());
    for(auto [dx, dy]: moves) {
      auto nx = x + dx, ny = y + dy;
      if(nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
      if(result[ny][nx] != -1) continue;

      int furtherc = 0, beyondc = moves.size();
      for(auto [dx, dy]: moves) {
        auto mx = nx + dx, my = ny + dy;
        if(mx < 0 || my < 0 || mx >= w || my >= h) continue;
        furtherc += result[my][mx] == -1 ? 1 : 0;

        int my_furtherc = 0;
        for(auto [dx, dy]: moves) {
          auto ox = mx + dx, oy = my + dy;
          if(ox < 0 || oy < 0 || ox >= w || oy >= h) continue;
          my_furtherc += result[oy][ox] == -1 ? 1 : 0;
        }
        beyondc = min(beyondc, my_furtherc);
      }

      nexts.push_back({furtherc, beyondc, nx, ny});
    }
    sort(nexts.begin(), nexts.end(), [](Next const& a, Next const& b) {
      return a.furtherc != b.furtherc ? a.furtherc < b.furtherc : a.beyondc < b.beyondc;
    });

    for(auto [_1, _2, x, y]: nexts) {
      if(backtrack(x, y, visc)) {
        return true;
      }
    }

    result[y][x] = -1;
    return false;
  };

  if(backtrack(x, y, 0)) {
    return result;
  } else {
    return nullopt;
  }
}
