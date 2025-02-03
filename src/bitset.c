#include "bitset.h"

bitSet bitset_create(size_t capacity) {
  bitSet set;

  set.capacity = capacity;
  set.size = (size_t)ceil(capacity / BIT_PER_BLOCK);
  set.bits = (uint64_t*)(malloc(sizeof(uint64_t) * set.size));

  return set;
}

void bitset_destroy(bitSet* set) {
  if (set->bits != NULL) free(set->bits);
}

void bitset_add(bitSet* set, int element) {
  if (set->capacity > element) {
    int block = element / BIT_PER_BLOCK;
    set->bits[block] |= (1ULL << (element & BIT_PER_BLOCK));
  }
}

bool bitset_contains(const bitSet* set, int element);
    
