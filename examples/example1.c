#include "../src/bitset.h"

int main() {
  bitSet set = bitset_create(100);

  printf("%d %d\n", set.capacity, set.size);

  for (int i = 0; i < 64; i++) printf("%d", (set.bits[0] >> i) & 1);

  //   bitset_destroy(&set);

  return 0;
}