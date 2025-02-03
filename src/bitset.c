#include "bitset.h"

/**
 * @brief создает структуру битового множества
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param size_t capacity, мощность битового множества
 *
 * @return bitSet
 */
bitSet bitset_create(size_t capacity) {
  bitSet set;

  set.capacity = capacity;
  set.size = (size_t)((capacity + 63) / 64);
  set.bits = (uint64_t*)(calloc(sizeof(uint64_t), set.size));

  assert(set.bits != NULL);

  return set;
}

/**
 * @brief Очищает память объекта bitSet
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* set, указатель на битовое множество
 *
 * @return Nothing
 */
void bitset_destroy(bitSet* set) {
  free(set->bits);
  set->bits = NULL;
  set->size = 0;
  set->capacity = 0;
}

/**
 * @brief Добавляет бит в битовое множество
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* set, указатель на битовое множество
 * @param int element, номер элемента
 *
 * @return Nothing
 */
void bitset_add(bitSet* set, int element) {
  if (element > 0 && set->capacity > (size_t)element) {
    int block = element / BIT_PER_BLOCK;
    set->bits[block] |= (1ULL << (element % BIT_PER_BLOCK));
  }
}

/**
 * @brief Проверяет есть ли n-ый бит в битовом множестве
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* set, указатель на битовое множество
 * @param int element, номер элемента
 *
 * @return true, если есть, иначе false
 */
bool bitset_contains(const bitSet* set, int element) {
  bool isContain = true;

  if (element < 0 || (size_t)element >= set->capacity)
    isContain = false;
  else {
    size_t block = element / BIT_PER_BLOCK;
    size_t bit = element % BIT_PER_BLOCK;
    isContain = (set->bits[block] >> bit) & 1;
  }

  return isContain;
}

/**
 * @brief Выводит битовое множество в функцию outputFunc
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param outputFunc* func_output, callback на функцию вывода
 * @param bitSet* set, указатель на битовове множество
 *
 * @return Nothing
 */
void bitset_print(const bitSet* set, outputFunc func_output) {
  int max_buffer_size = 1024;
  int curr_buffer_size = 0;
  char* buffer = (char*)malloc(max_buffer_size);

  curr_buffer_size += snprintf(buffer, max_buffer_size, "{ ");

  for (int i = 0; i < (int)set->capacity; i++) {
    if (bitset_contains(set, i)) {
      int needed_size = snprintf(NULL, 0, "%d ", i);

      if (curr_buffer_size + needed_size >= max_buffer_size) {
        max_buffer_size = curr_buffer_size + needed_size + 1;
        buffer = (char*)realloc(buffer, max_buffer_size);
      }

      curr_buffer_size +=
          snprintf(buffer + curr_buffer_size,
                   max_buffer_size - curr_buffer_size, "%d ", i);
    }
  }

  if (curr_buffer_size + 2 >= max_buffer_size) {
    max_buffer_size = curr_buffer_size + 3;
    buffer = (char*)realloc(buffer, max_buffer_size);
  }

  curr_buffer_size += snprintf(buffer + curr_buffer_size,
                               max_buffer_size - curr_buffer_size, "}");

  func_output(buffer);
  free(buffer);
}