// htab_free.c
// Řešení IJC-DU2, příklad 2), 14.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "htab_private.h"

// Smaze pomoci htab_clear a uvolni
void htab_free(htab_t * t) {
  htab_clear(t);
  free(t);
}