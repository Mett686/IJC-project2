// htab_bucket_count.c
// Řešení IJC-DU2, příklad a), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "libhtab/htab_private.h"

// Vraci arr_size (pocet bucketu)
size_t htab_bucket_count(const htab_t * t) {
  return t->arr_size;
}