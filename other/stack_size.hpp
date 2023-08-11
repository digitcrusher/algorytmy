#include <sys/resource.h>

/*
 * Może się przydać przy lokalnym testowaniu rozwiązania na dużych
 * danych. Na sprawdzaczkach jest niepotrzebne i najpewniej wywali błąd.
 */
void set_stack_size(int megabytes) {
  rlimit rl;
  rl.rlim_cur = (rlim_t) megabytes * 1'000'000;
  setrlimit(RLIMIT_STACK, &rl);
}
