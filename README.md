# digitcrusher/algorytmy

## Metodologia

- Biblioteczka powinna być stworzona z myślą o 90% przypadków użycia - algorytmy powinny być w nich szybkie do skopiowania, nie wymagać żadnych wewnętrznych modyfikacji i być wygodne w użyciu.

- Dla zaspokojenia tych pozostałych 10% kod powinien być czytelny, krótki i bez mikrooptymalizacji - tak, żeby można było go łatwo zmodyfikować w ważnych punktach jego działania.

- Asserty powinny sprawdzać warunki dotyczące wejścia, które nie mogą być wykryte na inne sposoby (np. przez sygnał naruszenia ochrony pamięci lub tryb debugowania w glibc++).

## Zawartość

### Algorytmy

- [ ] matematyka
  - [x] mnożenie i potęgowanie modularne
  - [x] rozszerzony algorytm Euklidesa
  - [x] odwrotność modularna
  - [x] liniowe równania diofantyczne
  - [x] chińskie twierdzenie o resztach
  - [x] logarytm dyskretny
  - [x] sito liczb pierwszych - Eratostenes, Euler
  - [x] test pierwszości - z sita, Miller-Rabin
  - [x] rozkład na czynniki pierwsze - z sita, rho Pollarda
  - [x] funkcja φ Eulera
  - [x] liczba, suma i iloczyn dzielników
  - [x] spamiętywana silnia - zwykła, z przeskokami
  - [x] symbol Newtona
  - [x] liczba podziałów elementów do kilku zbiorów
  - [x] FFT
  - [x] modularny int
  - [x] NTT
  - [x] pierwiastek pierwotny
  - [x] podsilnia
  - [x] lemat Burnside'a
  - [x] liczby Catalana
  - [x] FWHT o podstawie 3
  - [ ] rozszerzony binarny algorytm Euklidesa
  - [ ] eliminacja Gaussa - rzeczywista, modularna, bitowa
- [ ] grafy
  - [x] skojarzenie w grafie dwudzielnym - Hopcroft-Karp
  - [x] przeszukiwanie grafu - BFS, DFS (w tym funkcja low)
  - [x] sortowanie topologiczne - Kahn, z DFS
  - [x] silnie spójne składowe - Kosaraju
  - [x] dwukolorowanie grafu
  - [x] mosty, punkty artykulacji i dwuspójne składowe
  - [x] generator grafów losowych
  - [x] minimalne drzewo rozpinające - Kruskal, Prim
  - [x] najkrótsze ścieżki
    - [x] dla DAGów, Dijkstra, Dial, Bellman-Ford, SPFA, Floyd-Warshall
    - [ ] A*, Johnson
  - [x] binary lifting
  - [x] najniższy wspólny przodek - z binary liftingu, z RMQ
  - [x] heavy-light decomposition
  - [x] centroid decomposition
  - [x] 2-SAT
  - [x] graf funkcyjny
  - [x] problem skoczka szachowego - Warnsdorff i Pohl
  - [x] maksymalny przepływ - Edmonds-Karp
  - [x] ścieżka Eulera (lub cykl)
  - [x] liczba ścieżek i najdłuższa ścieżka w DAGu
  - [x] znajdywanie cykli
  - [x] najbardziej oddalony wierzchołek i średnica w drzewie
  - [x] offline dynamic connectivity
  - [x] przepływ minimalnego kosztu - Ford-Fulkerson i SPFA
  - [ ] chain decomposition
  - [ ] skojarzenie w ogólnym grafie
  - [ ] problem komiwojażera - z DP, z branch-and-bound
  - [ ] algorytm Rémy'ego
- [ ] struktury danych
  - [x] drzewo przedziałowe
    - [x] przedział-przedział, przedział-przedział bez propagacji, przedział-przedział 2D, punkt-przedział, punkt-przedział 2D, przedział-punkt, przedział-punkt 2D
    - [ ] leniwe przedział-przedział
  - [x] struktura zbiorów rozłącznych - las zbiorów rozłącznych, z trzymaniem elementów, z cofaniem
  - [x] sparse table
  - [x] stos i kolejka minimum/monotoniczna
  - [x] sumy prefiksowe - 1D, 2D
  - [x] drzewo Fenwicka - punkt-przedział, punkt-przedział 2D, przedział-punkt, przedział-punkt 2D, przedział-przedział, przedział-przedział 2D
  - [x] skompresowane drzewo trie
  - [x] GNU C++ PBDS
  - [x] implicit treap
  - [x] drzewo Li Chao
  - [x] sumy pierwiastkowe
  - [ ] big int
  - [ ] ułamek
  - [ ] treap
  - [ ] wielomian
  - [ ] dynamiczne drzewo AABB
  - [ ] fibonacci heap
  - [ ] disjoint sparse table
  - [ ] sparse table 2D
  - [ ] macierz i wektor
- [ ] tekstówki
  - [x] najdłuższy wspólny podciąg - z DP, z dziel i zwyciężaj
  - [x] haszowanie w okienku
  - [x] hasze prefiksowe
  - [x] wyszukiwanie wzorca w tekście - Rabin-Karp, KMP
  - [x] tablica sufiksowa - w O(n log n), z haszy
  - [x] funkcja prefiksowa
  - [x] najmniejsze przesunięcie cykliczne - Booth
  - [x] algorytm Manachera
  - [x] algorytm Aho-Corasick
  - [x] tablica LCP - Kasai
  - [x] funkcja Z
  - [ ] KMR
- [ ] geometria
  - [x] convex hull trick
  - [x] figury geometryczne - punkt, odcinek, wielokąt, koło
  - [x] twierdzenie Picka
  - [x] najbliższa para punktów - z zamiatania, z dziel i zwyciężaj
  - [x] otoczka wypukła - Graham
  - [ ] triangulacja wielokątów
  - [ ] przecięcie i różnica prostokątów
  - [ ] euklidesowe minimalne drzewo spinające
- [ ] inne
  - [x] najdłuższy rosnący podciąg
  - [x] algorytm Mo
  - [x] meet in the middle
  - [ ] Quickselect
  - [ ] algorytm magicznych piątek
  - [ ] Lazyselect
  - [ ] or/subset convolution
  - [ ] algorytm sympleksowy
- [ ] reszta algorytmów

### Inne

- [x] templatka do rozwiązań
- [x] pragmy
- [x] testerka w kodzie
- [x] szybkie I/O
- [x] rozmiar stosu

### Przykładowe zadania

- [x] "Kajaki" z IV OI
- [x] "Małpki" z Solve

## Podziękowania

- https://cp-algorithms.com/
- https://cses.fi/problemset/
