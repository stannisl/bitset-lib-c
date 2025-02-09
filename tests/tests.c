#include <assert.h>
#include <stdio.h>

#include "../src/bitset/bitset.h"

void test_create_destroy() {
  bitSet set = bitset_create(128);
  assert(set.capacity == 128);
  assert(set.size == 2);
  bitset_destroy(&set);
}

void test_remove() {
  bitSet set = bitset_create(64);

  bitset_add(&set, 1);
  bitset_add(&set, 2);
  bitset_add(&set, 3);

  assert(bitset_contains(&set, 1));
  assert(bitset_contains(&set, 2));
  assert(bitset_contains(&set, 3));

  bitset_remove(&set, 2);

  assert(bitset_contains(&set, 1));
  assert(!bitset_contains(&set, 2));
  assert(bitset_contains(&set, 3));

  bitset_remove(&set, 5);
  assert(!bitset_contains(&set, 5));

  bitset_destroy(&set);
}

void test_add_contains() {
  bitSet set = bitset_create(64);
  bitset_add(&set, 0);
  bitset_add(&set, 63);
  assert(bitset_contains(&set, 0));
  assert(bitset_contains(&set, 63));
  assert(!bitset_contains(&set, 1));
  bitset_destroy(&set);
}

void test_union() {
  bitSet a = bitset_create(64);
  bitSet b = bitset_create(64);
  bitset_add(&a, 1);
  bitset_add(&b, 2);
  bitSet u = bitset_union(&a, &b);
  assert(bitset_contains(&u, 1));
  assert(bitset_contains(&u, 2));
  bitset_destroy(&a);
  bitset_destroy(&b);
  bitset_destroy(&u);
}

void test_intersection() {
  bitSet a = bitset_create(64);
  bitSet b = bitset_create(64);
  bitset_add(&a, 1);
  bitset_add(&b, 1);
  bitSet i = bitset_intersection(&a, &b);
  assert(bitset_contains(&i, 1));
  assert(!bitset_contains(&i, 2));
  bitset_destroy(&a);
  bitset_destroy(&b);
  bitset_destroy(&i);
}

void test_complement() {
  bitSet a = bitset_create(3);
  bitset_add(&a, 0);
  bitSet c = bitset_complement(&a);
  assert(!bitset_contains(&c, 0));
  assert(bitset_contains(&c, 1));
  assert(bitset_contains(&c, 2));
  bitset_destroy(&a);
  bitset_destroy(&c);
}

void test_sub() {
  bitSet a = bitset_create(64);
  bitSet b = bitset_create(64);
  bitset_add(&a, 1);
  bitset_add(&a, 2);
  bitset_add(&b, 2);

  bitSet res = bitset_sub(&a, &b);
  assert(bitset_contains(&res, 1));
  assert(!bitset_contains(&res, 2));

  bitset_destroy(&a);
  bitset_destroy(&b);
  bitset_destroy(&res);
}

void test_symmetric_diff() {
  bitSet a = bitset_create(64);
  bitSet b = bitset_create(64);
  bitset_add(&a, 1);
  bitset_add(&a, 2);
  bitset_add(&b, 2);
  bitset_add(&b, 3);

  bitSet res = bitset_symmetric_diff(&a, &b);
  assert(bitset_contains(&res, 1));
  assert(bitset_contains(&res, 3));
  assert(!bitset_contains(&res, 2));

  bitset_destroy(&a);
  bitset_destroy(&b);
  bitset_destroy(&res);
}

void test_is_subset() {
  bitSet a = bitset_create(64);
  bitSet b = bitset_create(64);
  bitset_add(&a, 1);
  bitset_add(&b, 1);
  bitset_add(&b, 2);

  assert(bitset_is_subset(&a, &b));
  assert(!bitset_is_subset(&b, &a));

  bitset_destroy(&a);
  bitset_destroy(&b);
}

void test_is_strict_subset() {
  bitSet a = bitset_create(64);
  bitSet b = bitset_create(64);
  bitset_add(&a, 1);
  bitset_add(&b, 1);

  assert(!bitset_is_strict_subset(&a, &b));
  bitset_add(&b, 2);
  assert(bitset_is_strict_subset(&a, &b));

  bitset_destroy(&a);
  bitset_destroy(&b);
}

void test_is_equal() {
  bitSet a = bitset_create(64);
  bitSet b = bitset_create(64);
  bitset_add(&a, 1);
  bitset_add(&b, 1);

  assert(bitset_is_equal(&a, &b));
  bitset_add(&b, 2);
  assert(!bitset_is_equal(&a, &b));

  bitset_destroy(&a);
  bitset_destroy(&b);
}

void test_add_many() {
  bitSet set = bitset_create(128);
  bitset_add_many(&set, 3, 5, 10, 15);

  assert(bitset_contains(&set, 5));
  assert(bitset_contains(&set, 10));
  assert(bitset_contains(&set, 15));
  assert(!bitset_contains(&set, 1));

  bitset_destroy(&set);
}

void test_edge_cases() {
  bitSet set = bitset_create(64);
  bitset_add(&set, 0);
  bitset_add(&set, 63);
  assert(bitset_contains(&set, 0));
  assert(bitset_contains(&set, 63));

  bitset_destroy(&set);
}

int main() {
  test_create_destroy();
  test_add_contains();
  test_union();
  test_intersection();
  test_complement();
  test_sub();
  test_symmetric_diff();
  test_is_subset();
  test_is_strict_subset();
  test_is_equal();
  test_add_many();
  test_edge_cases();
  test_remove();

  printf("All tests passed!\n");
  return 0;
}