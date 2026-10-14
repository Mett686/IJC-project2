# IJC Project 2 – Hash Table & Tail Utility

Second project for the **IJC (The C Programming Language)** course, written in C (ISO C11).

## Overview
1. **`tail`**: A C implementation of the POSIX `tail` utility using a circular buffer to print the last N lines of a file or `stdin`.
2. **`wordcount`**: A word frequency counter backed by a custom-built hash table library (`htab`), compiled as both a static (`libhtab.a`) and dynamic (`libhtab.so`) library.

## Build & Usage
```bash
make
./tail -n 10 <file>
./wordcount < <file>
```
