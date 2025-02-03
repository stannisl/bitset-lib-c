#ifndef BITSET_H
#define BITSET_H

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "output.h"

// #define GET_BLOCK(element) (element / BIT_PER_BLOCK)
// #define GET_BIT(element) (element % BIT_PER_BLOCK)

#define INITIAL_BUFFER_SIZE 1024
#define BIT_PER_BLOCK 64

typedef void (*outputFunc)(const char*);

typedef struct {
  uint64_t* bits;
  size_t size;
  size_t capacity;
} bitSet;

bitSet bitset_create(size_t capacity);
void bitset_destroy(bitSet* set);

void bitset_add(bitSet* set, int element);
bool bitset_contains(const bitSet* set, int element);

void bitset_print(const bitSet* set, outputFunc func_output);

#endif