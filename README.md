# digitcrusher/algorytmy

## Metodologia

- Nie ma jednej implementacji algorytmu zaspokojającej wszystkie przypadki użycia, więc algorytmy powinny być proste do skopiowania, wklejenia do własnego kodu i zmodyfikowania w ważnych punktach ich działania.

- Wszystkie algorytmy w tej bibliotece powinny być możliwie niezależnymi od siebie kawałkami kodu, wymagać jak najmniej kodu do samodzielnego funkcjonowania i mieć jak najprostszy interfejs.

- Kod ma być czytelny, krótki, bez mikrooptymalizacji.

- Asserty powinny sprawdzać warunki dotyczące wejścia, które nie mogą być wykryte na inne sposoby (np. przez sygnał naruszenia ochrony pamięci lub tryb debugowania w glibc++).

## Lista zadań

### Algorytmy

- [ ] matematyka
  - [x] NWD, NWW
  - [x] mnożenie i potęgowanie modularne
  - [x] rozszerzony algorytm Euklidesa
  - [x] odwrotność modularna
  - [x] liniowe równania diofantyczne
  - [x] chińskie twierdzenie o resztach
  - [x] logarytm dyskretny
  - [x] sito liczb pierwszych - Eratostenes, Euler
  - [x] test pierwszości - z sita, Miller-Rabin
  - [x] rozkład na czynniki pierwsze - z sita, rho Pollarda
  - [x] funkcja φ Eulera
  - [x] liczba i suma dzielników
  - [x] spamiętywana silnia
  - [x] symbol Newtona
  - [x] różne wzorki kombinatoryczne
  - [ ] FFT/NTT
  - [ ] rozszerzony binarny algorytm Euklidesa
  - [ ] funkcje tworzące
- [ ] grafy
  - [x] skojarzenia w grafie dwudzielnym - Hopcroft-Karp
  - [x] przeszukiwanie grafu - BFS, DFS (w tym funkcja low)
  - [x] sortowanie topologiczne - Kahn, z DFS
  - [x] silnie spójne składowe - Kosaraju
  - [x] dwu-kolorowanie grafu
  - [x] mosty i punkty artykulacji
  - [x] generator grafów losowych
  - [x] minimalne drzewo rozpinające - Kruskal, Prim
  - [x] najkrótsze ścieżki
    - [x] dla DAGów, Dijkstra, Dial, Bellman-Ford, SPFA, Floyd-Warshall
    - [ ] A*, Johnson
  - [ ] jump pointery/binary lifting
  - [ ] lowest common ancestor
  - [ ] heavy-light decomposition
  - [ ] chain decomposition
  - [ ] centroid decomposition
  - [ ] 2-SAT
  - [ ] transformacje drzew binarnych
  - [ ] znajdywanie cykli w grafie
  - [ ] skojarzenia
  - [ ] problem komiwojażera - z DP, z branch-and-bound
  - [ ] problem skoczka szachowego
  - [ ] liczba ścieżek prostych w grafie
  - [ ] dwuspójne składowe
  - [ ] ścieżka i cykl Eulera
- [ ] struktury danych
  - [x] drzewo przedziałowe
  - [x] struktura zbiorów rozłącznych
  - [x] sparse table
  - [x] stos i kolejka minimum/monotoniczna
  - [x] sumy prefiksowe
  - [x] drzewo Fenwicka
  - [x] skompresowane drzewo trie
  - [ ] big inty
  - [ ] ułamki
  - [ ] modularne inty
  - [ ] modularne ułamki
  - [ ] treap (drzewiec)
  - [ ] ciągi
  - [ ] dynamiczne drzewo AABB
  - [ ] leniwe drzewo przedziałowe
  - [ ] maski bitowe
  - [ ] glibc pbds
  - [ ] permutacje
  - [ ] fibonacci heap
  - [ ] disjoint sparse table
- [ ] algorytmy tekstowe i ciągi
  - [x] najdłuższy wspólny podciąg - z DP, z dziel i zwyciężaj
  - [ ] haszowanie
  - [ ] wyszukiwanie ciągow - KMP, Rabin-Karp
  - [ ] najdłuższy rosnący podciąg
  - [ ] funkcja prefiksowa - KMP
  - [ ] algorytm Manachera
- [ ] geometria
  - [ ] podstawowe konstrukcje - punkt, linia, koło, trójkąt, wielokąt
  - [ ] triangulacja wielokątów
  - [ ] convex hull trick
  - [ ] otoczka wypukła - Graham's scan
  - [ ] operacje na wektorach - iloczyn wektorowy, skalarny, współliniowość
  - [ ] sortowanie kątowe
  - [ ] przecięcia i różnice prostokątów
  - [ ] euklidesowe minimalne drzewo spinające
- [ ] inne
  - [ ] algorytm Mo
  - [ ] liczba unikatowych elementów na przedziałach przy użyciu drzewa przedziałowego
  - [ ] znajdź jedną liczbe w ciągu par liczb i podobne problemy
- [ ] reszta algorytmów

### Notatki i materiały

- [ ] kwadraty łacińskie
- [ ] sztuczki i triki
  - [ ] kompresja wartości i współrzędnych
- [ ] digit dp
- [ ] meet in the middle
- [ ] wszystko

### Inne

- [x] moja templatka do rozwiązań
- [x] pragmy
- [x] testerka w kodzie
- [ ] szybkie i/o

### Przykładowe zadania

- [x] "Kajaki" z IV OI
- [x] "Małpki" z Solve
- [ ] zadania z przedziałami
  - [ ] "Dyżury" z Solve
  - [ ] "Szpilki i zdjęcia" z Solve
  - [ ] "Too Many Segments" z Codeforces
- [ ] reszta zadań

## Podziękowania

- https://cp-algorithms.com/
