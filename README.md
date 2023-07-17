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
  - [x] NTT
  - [x] pierwiastek pierwotny
  - [ ] rozszerzony binarny algorytm Euklidesa
  - [ ] funkcje tworzące
  - [ ] eliminacja Gaussa - rzeczywista, modularna, bitowa
- [ ] grafy
  - [x] skojarzenia w grafie dwudzielnym - Hopcroft-Karp
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
  - [x] grafy funkcyjne
  - [x] problem skoczka szachowego - Warnsdorff i Pohl
  - [ ] chain decomposition
  - [ ] transformacje drzew binarnych
  - [ ] znajdywanie cykli w grafie
  - [ ] skojarzenia
  - [ ] problem komiwojażera - z DP, z branch-and-bound
  - [ ] liczba ścieżek prostych w grafie
  - [ ] ścieżka i cykl Eulera
  - [ ] algorytm Rémy'ego
  - [ ] maksymalny przepływ - Edmonds-Karp
- [ ] struktury danych
  - [x] drzewo przedziałowe
    - [x] przedział-przedział, przedział-przedział bez propagacji, przedział-przedział 2D, punkt-przedział, punkt-przedział 2D, przedział-punkt, przedział-punkt 2D
    - [ ] leniwe przedział-przedział
  - [x] struktura zbiorów rozłącznych - las zbiorów rozłącznych, z trzymaniem elementów
  - [x] sparse table
  - [x] stos i kolejka minimum/monotoniczna
  - [x] sumy prefiksowe - 1D, 2D
  - [x] drzewo Fenwicka - punkt-przedział, punkt-przedział 2D, przedział-punkt, przedział-punkt 2D, przedział-przedział, przedział-przedział 2D
  - [x] skompresowane drzewo trie
  - [x] GNU C++ PBDS
  - [ ] big inty
  - [ ] ułamki
  - [ ] modularne ułamki
  - [ ] treap (drzewiec)
  - [ ] ciągi
  - [ ] dynamiczne drzewo AABB
  - [ ] maski bitowe
  - [ ] permutacje
  - [ ] fibonacci heap
  - [ ] disjoint sparse table
  - [ ] drzewo Li Chao
  - [ ] sparse table 2D
  - [ ] quadtree
- [ ] algorytmy tekstowe i ciągi
  - [x] najdłuższy wspólny podciąg - z DP, z dziel i zwyciężaj
  - [x] haszowanie w okienku
  - [x] hasze prefiksowe
  - [x] wyszukiwanie wzorca w tekście - Rabin-Karp, KMP
  - [x] tablica sufiksowa
  - [x] funkcja prefiksowa
  - [x] najdłuższy rosnący podciąg
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

- [x] templatka do rozwiązań
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
