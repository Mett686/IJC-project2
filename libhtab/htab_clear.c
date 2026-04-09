// htab_clear.c
// Řešení IJC-DU2, příklad a), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "libhtab/htab_private.h"
#include <stdlib.h>
#include <stdio.h>

// Smaze cely obsah tabulky
void htab_clear(htab_t * t) {
  for( unsigned i = 0; i < t->arr_size; i++) {
    htab_item_t* item = t->arr[i];
    while(item) {
      htab_item_t* next = item->next;
      free(item);
      t->size--;
      item = next;
    }
    if(t->size) fprintf(stderr, "Error: htab_clear: htab_size is non 0 after clear!\n");
    t->arr[i] = NULL;
  }
}