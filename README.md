# BitSet-lib

This lib were written on C programming language

## Compiling

Target to build static lib

```
make all
```

Compiled lib in /build/bitset.a

You can use it with linking using such template

```
gcc <flags> <objects with bitset.h header> <objects> bitset.a -o <outputname>
```

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

| Target name | Description                                                         |
| ----------- | ------------------------------------------------------------------- |
| example     | example bla bla bla example bla bla bla example bla bla bla \n dsda |

## Docs

### bitset.h funcs

### output.h funcs
