# BitSet-lib

This lib were written on C programming language

## Compiling

Target to build static lib

```
make all
```

Compiled lib in `/build/bitset.a`

You can use it with linking using such template

```
gcc <flags> <objects with bitset.h header> <objects> bitset.a -o <outputname>
```

## Requirements for build

Linux \
**clang-format** 14.0.0 (or above if you dont care) \
**valgrind** ^3.18.1 \
**gcc** ^11.4.0

## Running the tests

This tests running with assert macros from assert.h

### Functionality tests

Run tests to check functionality

```
make test
```

### And coding style tests

Make target to get code to clang-14 Google CodeStyle

```
make clang-check
```

### Memory leaks test

Make target to get code to clang-14 Google CodeStyle

```
make valgrind
```

## Makefile targets

| Target name | Description                                              |
| ----------- | -------------------------------------------------------- |
| all         | compiles and run main.c (lab task)                       |
| rebuild     | recompiles static lib                                    |
| bitset.a    | links and build static lib                               |
| clean       | clean build dir and main executable for (lab task)       |
| test        | build lib and runs test.c                                |
| rebuild     | compiles and run main.c (lab task)                       |
| valgrind    | build lib and runs test.c with valgrind memoryleak check |

## Docs

### bitset.h Lib

bitSet это структура со след полями \

```
struct {
    uint64_t* bits;
  size_t size;
  size_t capacity;
}
```

Библиотека предоставляет функции для работы с битовыми множествами. Основные функции:

| Lib Function              | Description                                                          |
| ------------------------- | -------------------------------------------------------------------- |
| `bitset_create`           | Создает битовое множество с заданной емкостью.                       |
| `bitset_destroy`          | Освобождает память, выделенную для битового множества.               |
| `bitset_add`              | Добавляет элемент в битовое множество.                               |
| `bitset_remove`           | Удаляет элемент в битовом множестве.                                 |
| `bitset_add_many`         | Добавляет несколько элементов в битовое множество.                   |
| `bitset_contains`         | Проверяет, содержится ли элемент в битовом множестве.                |
| `bitset_print`            | Выводит битовое множество в указанную функцию вывода.                |
| `bitset_is_equal`         | Проверяет, равны ли два битовых множества.                           |
| `bitset_is_subset`        | Проверяет, является ли одно множество подмножеством другого.         |
| `bitset_is_strict_subset` | Проверяет, является ли одно множество строгим подмножеством другого. |
| `bitset_union`            | Возвращает объединение двух битовых множеств.                        |
| `bitset_intersection`     | Возвращает пересечение двух битовых множеств.                        |
| `bitset_sub`              | Возвращает разность двух битовых множеств.                           |
| `bitset_symmetric_diff`   | Возвращает симметрическую разность двух битовых множеств.            |
| `bitset_complement`       | Возвращает дополнение битового множества.                            |

Более подробно в bitset.h расписано все.
