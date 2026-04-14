// htab_size.c
// Řešení IJC-DU2, příklad 2), 14.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "htab_private.h"

// Vraci pocet zaznamu v tabulce
size_t htab_size(const htab_t * t) {
  return t->size;
}