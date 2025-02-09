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
 * @brief Очищает память объекта стуктуры bitSet
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
 * @brief Добавляет бит в битовое множество, если размер меньше чем бит, ничего
 * не произойдет и бит не будет добавлен.
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* set, указатель на битовое множество
 * @param int element, номер элемента
 *
 * @return Nothing
 */
void bitset_add(bitSet* set, int element) {
  assert("Adding a bit that bigger than capacity" &&
         set->capacity > (size_t)element);
  assert("Adding a negative place bit in the set" && element >= 0);

  int block = element / BIT_PER_BLOCK;
  set->bits[block] |= (1ULL << (element % BIT_PER_BLOCK));
}

/**
 * @brief Добавляет n бит в битовое множество
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param int n, кол-во элементов
 * @param bitSet* set, указатель на битовое множество
 * @param int ..., n битов для добавления.
 *
 * @return Nothing
 */
void bitset_add_many(bitSet* set, int n, ...) {
  assert("Amount of args should be positive integer" && (n > 0));

  va_list args;
  va_start(args, n);

  for (int i = 0; i < n; ++i) {
    int element = va_arg(args, int);
    assert("Element should meet boundaries of set" && element >= 0 &&
           (size_t)element < set->capacity);
    bitset_add(set, element);
  }

  va_end(args);
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
  int max_buffer_size = INITIAL_BUFFER_SIZE;
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

  snprintf(buffer + curr_buffer_size, max_buffer_size - curr_buffer_size, "}");

  func_output(buffer);
  free(buffer);
}

/**
 * @brief Сравнивает равны ли битовые множества.
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* A, указатель на битовове множество
 * @param bitSet* B, указатель на битовове множество
 *
 * @return true (1), A == B или же false (0), A != B
 */
bool bitset_is_equal(const bitSet* A, const bitSet* B) {
  bool isEqual = true;
  bool aSetIsBigger = false;

  size_t biggerSize = (A->size > B->size) ? A->size : B->size;
  size_t lessSize = (A->size < B->size) ? A->size : B->size;
  if (biggerSize == A->size) aSetIsBigger = true;

  for (int i = 0; (i < (int)lessSize) && isEqual; i++)
    if (A->bits[i] != B->bits[i]) isEqual = false;

  for (int i = lessSize; (i < (int)biggerSize) && isEqual; i++)
    if (aSetIsBigger)
      isEqual = (A->bits[i] == 0);
    else
      isEqual = (B->bits[i] == 0);

  return isEqual;
}

/**
 * @brief Проверяет, является ли A ⊆ В
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* A, указатель на битовове множество
 * @param bitSet* B, указатель на битовове множество
 *
 * @return true (1), A ⊆ B или же false (0), !(A ⊆ B)
 */
bool bitset_is_subset(const bitSet* A, const bitSet* B) {
  bool isSubset = true;
  size_t maxSize = A->size > B->size ? A->size : B->size;

  for (size_t i = 0; i < maxSize && isSubset; ++i) {
    uint64_t a_block = (i < A->size) ? A->bits[i] : 0;
    uint64_t b_block = (i < B->size) ? B->bits[i] : 0;
    if ((a_block & b_block) != a_block) isSubset = false;
  }
  return isSubset;
}

/**
 * @brief Проверяет, является ли A ⊂ В
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* A, указатель на битовове множество
 * @param bitSet* B, указатель на битовове множество
 *
 * @return true (1), A ⊂ B или же false (0), !(A ⊂ B)
 */
bool bitset_is_strict_subset(const bitSet* A, const bitSet* B) {
  return bitset_is_subset(A, B) && !bitset_is_equal(A, B);
}

/**
 * @brief Создает битовое множество, значение которого будет А ∪ В
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* A, указатель на битовове множество
 * @param bitSet* B, указатель на битовове множество
 *
 * @return bitSet, результат объединения двух множеств
 */
bitSet bitset_union(const bitSet* A, const bitSet* B) {
  bitSet result =
      bitset_create(A->capacity > B->capacity ? A->capacity : B->capacity);

  for (size_t i = 0; i < result.size; i++) {
    uint64_t a_block = (i < A->size) ? A->bits[i] : 0;
    uint64_t b_block = (i < B->size) ? B->bits[i] : 0;
    result.bits[i] = a_block | b_block;
  }

  return result;
}

/**
 * @brief Создает битовое множество, значение которого будет А ∩ В
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* A, указатель на битовове множество
 * @param bitSet* B, указатель на битовове множество
 *
 * @return bitSet, результат пересечения двух множеств
 */
bitSet bitset_intersection(const bitSet* A, const bitSet* B) {
  bitSet result =
      bitset_create(A->capacity > B->capacity ? A->capacity : B->capacity);

  for (size_t i = 0; i < result.size; i++) {
    uint64_t a_block = (i < A->size) ? A->bits[i] : 0;
    uint64_t b_block = (i < B->size) ? B->bits[i] : 0;
    result.bits[i] = a_block & b_block;
  }

  return result;
}

/**
 * @brief Создает битовое множество, значение которого будет А - В
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* A, указатель на битовове множество
 * @param bitSet* B, указатель на битовове множество
 *
 * @return bitSet, результат разности двух множеств
 */
bitSet bitset_sub(const bitSet* A, const bitSet* B) {
  bitSet result =
      bitset_create(A->capacity > B->capacity ? A->capacity : B->capacity);

  for (size_t i = 0; i < result.size; i++) {
    uint64_t a_block = (i < A->size) ? A->bits[i] : 0;
    uint64_t b_block = (i < B->size) ? B->bits[i] : 0;
    result.bits[i] = a_block & ~b_block;
  }

  return result;
}

/**
 * @brief Создает битовое множество, значение которого будет А △ В
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* A, указатель на битовове множество
 * @param bitSet* B, указатель на битовове множество
 *
 * @return bitSet, результат симметрической разности двух множеств
 */
bitSet bitset_symmetric_diff(const bitSet* A, const bitSet* B) {
  bitSet result =
      bitset_create(A->capacity > B->capacity ? A->capacity : B->capacity);

  for (size_t i = 0; i < result.size; i++) {
    uint64_t a_block = (i < A->size) ? A->bits[i] : 0;
    uint64_t b_block = (i < B->size) ? B->bits[i] : 0;
    result.bits[i] = a_block ^ b_block;
  }
  return result;
}

/**
 * @brief Считает битовое множество, которое дополнения множества A (разница
 * универсального и A)
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* A, указатель на битовове множество
 *
 * @return bitSet, результат расчета дополнения
 */
bitSet bitset_complement(const bitSet* set) {
  bitSet result = bitset_create(set->capacity);
  for (size_t i = 0; i < result.size; ++i) {
    result.bits[i] = ~set->bits[i];
  }
  size_t excess_bits = result.size * 64 - result.capacity;
  if (excess_bits > 0) {
    result.bits[result.size - 1] &= (1ULL << (64 - excess_bits)) - 1;
  }
  return result;
}
