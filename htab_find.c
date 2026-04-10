// htab_find.c
// Řešení IJC-DU2, příklad a), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "htab_private.h"

// Vraci ukazatel na zaznam s danym klicem v tabulce
htab_pair_t * htab_find(const htab_t * t, htab_key_t key) {
  size_t h = htab_hash_function(key) % t->arr_size;
  htab_item_t* item = t->arr[h];
  while(item) {
    if(strcmp(key, item->data.key) == 0) {
      return &item->data;
    }
    item = item->next;
  }
  return NULL;
}