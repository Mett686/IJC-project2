// htab_init.c
// Řešení IJC-DU2, příklad a), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "htab_private.h"

// Inicializuje tabulku o velikosti n bucketu
htab_t *htab_init(size_t n) {
  htab_t* t = malloc(sizeof(htab_t) + n * sizeof(htab_item_t*));
  if(t) {
    t->size = 0;
    t->arr_size = n;
    for(unsigned i = 0; i < n; i++) {
      t->arr[i] = NULL;
    }
  };
  return t;
}