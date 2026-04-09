// htab_erase.c
// Řešení IJC-DU2, příklad a), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "libhtab/htab_private.h"

// Smaze dany zaznam z tabulky
bool htab_erase(htab_t * t, htab_key_t key) {
  size_t h = htab_hash_function(key) % t->arr_size;
  htab_item_t* item = t->arr[h];
  htab_item_t* previos_item = item;
  while(item) {
    if(strcmp(key, item->data.key) == 0) {
      previos_item->next = item->next;
      free(item);
      t->size--;
      return true;
    }
    previos_item = item;
    item = item->next;
  }
  return false;
}