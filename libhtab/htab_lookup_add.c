// htab_lookup_add.c
// Řešení IJC-DU2, příklad a), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "libhtab/htab_private.h"
#include <stdlib.h>
#include <stdio.h>

// Najde, popripade prida zaznam s danum klicem
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
  size_t h = htab_hash_function(key) % t->arr_size;
  htab_item_t* item = t->arr[h];
  do {
    if(strcmp(key, item->data.key) == 0) {
      return &item->data;
    }
    item = item->next;
  } while(item && item->next);

  htab_item_t* new_item = malloc(sizeof(htab_item_t));
  if(new_item) {
    fprintf(stderr, "Error: htab_lookup_add: malloc failed!\n");
  } else {
    t->size++;
    item->next = new_item;
    strcpy(key, new_item->data.key);
    new_item->data.value = 0;
    new_item->next = NULL;
  }
  return new_item;
}