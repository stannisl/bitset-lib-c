#include "../src/bitset/bitset.h"

/*
output:
  set: { 1 2 }
  set1: { 1 2 3 }
  set != set1
  set is a subset of set1
  set is a strict subset of set1
*/

int main() {
  bitSet set = bitset_create(123);
  bitSet set1 = bitset_create(123);

  bitset_add(&set, 1);
  bitset_add(&set, 2);

  bitset_add(&set1, 1);
  bitset_add(&set1, 2);
  bitset_add(&set1, 3);

  printf("set: ");
  bitset_print(&set, output_to_stdout);

  printf("set1: ");
  bitset_print(&set1, output_to_stdout);

  printf(bitset_is_equal(&set, &set1) ? "set1 == set\n" : "set != set1\n");

  printf(bitset_is_subset(&set, &set1) ? "set is a subset of set1\n"
                                       : "set is not a subset of set1\n");

  printf(bitset_is_strict_subset(&set, &set1)
             ? "set is a strict subset of set1\n"
             : "set is not a strict subset of set1\n");

  bitset_destroy(&set);
  bitset_destroy(&set1);

  return 0;
}