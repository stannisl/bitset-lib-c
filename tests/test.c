#include "../src/bitset.h"

int main() {
  bitSet set = bitset_create(63);

  printf("%ld %ld\n", set.capacity, set.size);

  bitset_add(&set, 5);

  bitset_print(&set, output_to_stdout);

  bitset_destroy(&set);

  return 0;
}