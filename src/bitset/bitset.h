#ifndef BITSET_H
#define BITSET_H

#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../output/output.h"

#define INITIAL_BUFFER_SIZE 1024
#define BIT_PER_BLOCK 64

typedef void (*outputFunc)(const char*);

typedef struct bitSet {
  uint64_t* bits;
  size_t size;
  size_t capacity;
} bitSet;

/**
 * @brief создает структуру битового множества
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param size_t capacity, мощность битового множества
 *
 * @return bitSet
 */
bitSet bitset_create(size_t capacity);

/**
 * @brief Очищает память объекта стуктуры bitSet
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* set, указатель на битовое множество
 *
 * @return Nothing
 */
void bitset_destroy(bitSet* set);

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
void bitset_add(bitSet* set, int element);

/**
 * @brief Добавляет n бит в битовое множество
 *
 * @author Mike Ostanin (github.com/stannisl)
 *
 * @param bitSet* set, указатель на битовое множество
 * @param int n, кол-во элементов
 * @param int ..., n битов для добавления.
 *
 * @return Nothing
 */
void bitset_add_many(bitSet* set, int n, ...);

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
bool bitset_contains(const bitSet* set, int element);

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
void bitset_print(const bitSet* set, outputFunc func_output);

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
extern bool bitset_is_equal(const bitSet*, const bitSet*);

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
extern bool bitset_is_subset(const bitSet*, const bitSet*);

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
extern bool bitset_is_strict_subset(const bitSet*, const bitSet*);

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
bitSet bitset_union(const bitSet*, const bitSet*);

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
bitSet bitset_intersection(const bitSet*, const bitSet*);

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
bitSet bitset_sub(const bitSet*, const bitSet*);

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
bitSet bitset_symmetric_diff(const bitSet*, const bitSet*);

//  7) дополнение А.
bitSet bitset_complement(const bitSet* set);

#endif