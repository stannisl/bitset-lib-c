#include "../src/bitset/bitset.h"

/*
output:
{ 1 2 4 5 }
{ 4 }
{ 1 2 5 }
{ 1 5 }
*/

int main() {
  bitSet set = bitset_create(64);
  bitSet set1 = bitset_create(64);

  bitset_add_many(&set, 3, 1, 4, 5);
  bitset_add_many(&set1, 3, 2, 4, 6);

  bitSet un_set = bitset_union(&set1, &set);
  bitSet in_set = bitset_intersection(&set1, &set);

  bitSet sym_diff_set = bitset_symmetric_diff(&set, &set1);
  bitSet diff_set = bitset_sub(&set, &set1);

  bitset_print(&un_set, output_to_stdout);
  bitset_print(&in_set, output_to_stdout);
  bitset_print(&sym_diff_set, output_to_stdout);
  bitset_print(&diff_set, output_to_stdout);

  bitset_destroy(&set1);
  bitset_destroy(&set);
  bitset_destroy(&un_set);
  bitset_destroy(&in_set);
  bitset_destroy(&diff_set);
  bitset_destroy(&sym_diff_set);

  return 0;
}