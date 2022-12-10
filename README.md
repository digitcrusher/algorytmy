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
  - [x] FFT
  - [x] modularne inty
  - [ ] NTT
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
  - [x] binary lifting
  - [x] najniższy wspólny przodek - z binary liftingu, z RMQ
  - [x] heavy-light decomposition
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
  - [ ] algorytm Rémy'ego
- [ ] struktury danych
  - [x] drzewo przedziałowe - rekurencyjne, iteratywne
  - [x] struktura zbiorów rozłącznych
  - [x] sparse table
  - [x] stos i kolejka minimum/monotoniczna
  - [x] sumy prefiksowe
  - [x] drzewo Fenwicka
  - [x] skompresowane drzewo trie
  - [x] sumy prefiksowe 2D
  - [x] drzewo Fenwicka 2D
  - [ ] big inty
  - [ ] ułamki
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
  - [ ] drzewo Li Chao
  - [ ] drzewo przedziałowe 2D
  - [ ] sparse table 2D
- [ ] algorytmy tekstowe i ciągi
  - [x] najdłuższy wspólny podciąg - z DP, z dziel i zwyciężaj
  - [x] haszowanie w okienku
  - [x] hasze prefiksowe
  - [ ] wyszukiwanie wzorca w tekście
    - [x] Rabin-Karp
    - [ ] KMP
  - [x] tablica sufiksowa
  - [ ] najdłuższy rosnący podciąg
  - [ ] funkcja prefiksowa - KMP
  - [ ] algorytm Manachera
  - [ ] KMR
- [ ] geometria
  - [x] convex hull trick
  - [ ] figury geometryczne
    - [x] punkt, odcinek
    - [ ] koło, trójkąt, wielokąt
  - [ ] triangulacja wielokątów
  - [ ] otoczka wypukła - Graham's scan
  - [ ] przecięcia i różnice prostokątów
  - [ ] euklidesowe minimalne drzewo spinające
- [ ] inne
  - [ ] algorytm Mo
  - [ ] liczba unikatowych elementów na przedziałach przy użyciu drzewa przedziałowego
  - [ ] znajdź jedną liczbe w ciągu par liczb i podobne problemy
  - [ ] Quickselect
  - [ ] algorytm magicznych piątek
  - [ ] Lazyselect
  - [ ] or/subset convolution
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
- [x] szybkie I/O

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
