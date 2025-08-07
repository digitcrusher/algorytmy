/*
 * Problem skoczka szachowego - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"

/*
 * Heurystyka Warnsdorffa z modyfikacją Pohla -
 *   Znajduje ścieżkę skoczka szachowego przechodzącą po każdym polu planszy
 *   w prawie zawsze O(w * h). Tę heurystykę można też zastosować do
 *   ogólniejszego problemu ścieżki Hamiltona.
 */
optional<vector<vector<int>>> knights_tour(int w, int h, int x, int y) {
  if(w % 2 != 0 && h % 2 != 0 && (x + y) % 2 != 0) {
    return nullopt;
  }

  constexpr pair<int, int> moves[] = {
    {2, 1},
    {1, 2},
    {-1, 2},
    {-2, 1},
    {-2, -1},
    {-1, -2},
    {1, -2},
    {2, -1},
  };

  vector result(h, vector(w, -1));

  auto backtrack = Y([&](auto &self, int x, int y, int visc) -> bool {
    result[y][x] = visc;
    visc++;
    if(visc == w * h) {
      return true;
    }

    struct Next {
      int furtherc, beyondc, x, y;
    };
    vector<Next> nexts;
    nexts.reserve(size(moves));
    for(auto [dx, dy]: moves) {
      auto nx = x + dx, ny = y + dy;
      if(nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
      if(result[ny][nx] != -1) continue;

      int furtherc = 0, beyondc = size(moves);
      for(auto [dx, dy]: moves) {
        auto mx = nx + dx, my = ny + dy;
        if(mx < 0 || my < 0 || mx >= w || my >= h) continue;
        if(result[my][mx] != -1) continue;
        furtherc++;

        auto my_furtherc = -1;
        for(auto [dx, dy]: moves) {
          auto ox = mx + dx, oy = my + dy;
          if(ox < 0 || oy < 0 || ox >= w || oy >= h) continue;
          if(result[oy][ox] != -1) continue;
          my_furtherc++;
        }
        beyondc = min(beyondc, my_furtherc);
      }

      nexts.emplace_back(furtherc, beyondc, nx, ny);
    }
    r::sort(nexts, {}, λ(tie(_.furtherc, _.beyondc)));

    for(auto [_1, _2, x, y]: nexts) {
      if(self(x, y, visc)) {
        return true;
      }
    }

    result[y][x] = -1;
    return false;
  });

  return backtrack(x, y, 0) ? optional(result) : nullopt;
}
