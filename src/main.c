#include <stdio.h>

#include "./bitset/bitset.h"

int main() {
  size_t capacity = 32;

  bitSet a = bitset_create(capacity);
  bitSet b = bitset_create(capacity);
  bitSet c = bitset_create(capacity);
  bitSet d = bitset_create(capacity);

  bitset_add(&a, 1);
  bitset_add(&a, 3);
  bitset_add(&b, 3);
  bitset_add(&b, 5);
  bitset_add(&c, 5);
  bitset_add(&c, 7);
  bitset_add(&d, 1);
  bitset_add(&d, 7);

  // Вычисляем A ∩ B
  bitSet intersection_ab = bitset_intersection(&a, &b);

  // Вычисляем C ∪ D
  bitSet union_cd = bitset_union(&c, &d);

  // Вычисляем (A ∩ B) △ (C ∪ D)
  bitSet sym_diff = bitset_symmetric_diff(&intersection_ab, &union_cd);

  // Вычисляем B'
  bitSet complement_b = bitset_complement(&b);

  // Вычисляем (A ∩ B')
  bitSet intersection_ABc = bitset_intersection(&a, &complement_b);

  // Вычисляем C − D
  bitSet difference_cd = bitset_sub(&c, &d);

  // Вычисляем (A ∩ B') ∪ (C − D)
  bitSet union_temp = bitset_union(&intersection_ABc, &difference_cd);

  // Финальный результат: (A ∩ B △ C ∪ D) − ((A ∩ B') ∪ (C − D))
  bitSet result = bitset_sub(&sym_diff, &union_temp);
  printf("Initial sets:\n");
  printf("A: ");
  bitset_print(&a, output_to_stdout);
  printf("B: ");
  bitset_print(&b, output_to_stdout);
  printf("C: ");
  bitset_print(&c, output_to_stdout);
  printf("D: ");
  bitset_print(&d, output_to_stdout);

  printf("Mid steps:\n");
  printf("A ∩ B: ");
  bitset_print(&intersection_ab, output_to_stdout);
  printf("C ∪ D: ");
  bitset_print(&union_cd, output_to_stdout);
  printf("(A ∩ B △ C ∪ D): ");
  bitset_print(&sym_diff, output_to_stdout);
  printf("B': ");
  bitset_print(&complement_b, output_to_stdout);
  printf("C − D: ");
  bitset_print(&difference_cd, output_to_stdout);
  printf("A ∩ B'");
  bitset_print(&intersection_ABc, output_to_stdout);
  printf("(A ∩ B') ∪ (C − D): ");
  bitset_print(&union_temp, output_to_stdout);

  printf(
      "\nFinal result for 17th task\n (A ∩ B △ C ∪ D) − ((A ∩ B') ∪ (C − "
      "D)): ");
  bitset_print(&result, output_to_stdout);

  bitset_destroy(&a);
  bitset_destroy(&b);
  bitset_destroy(&c);
  bitset_destroy(&d);
  bitset_destroy(&intersection_ab);
  bitset_destroy(&union_cd);
  bitset_destroy(&sym_diff);
  bitset_destroy(&complement_b);
  bitset_destroy(&intersection_ABc);
  bitset_destroy(&difference_cd);
  bitset_destroy(&union_temp);
  bitset_destroy(&result);

  return 0;
}