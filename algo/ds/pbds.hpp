/*
 * GNU C++ PBDS - digitcrusher/algorytmy
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

/*
 * GNU C++ PBDS -
 *   Mapa i zbiór z dodatkowymi operacjami wzięcia n-tego klucza w porządku
 *   (find_by_order) i obliczenia pozycji potencjalnego klucza (order_of_key).
 *   Poniższe struktury zachowują się jak multimapa i multizbiór, jeśli Compare
 *   zwraca true dla równych kluczy. To jednak niesie za sobą pare haczyków.
 */
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template<class Key, class T, class Compare = less<Key>>
using pbds_map = tree<Key, T, Compare, rb_tree_tag, tree_order_statistics_node_update>;

template<class Key, class Compare = less<Key>>
using pbds_set = pbds_map<Key, null_type, Compare>;
