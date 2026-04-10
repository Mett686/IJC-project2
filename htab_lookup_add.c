// htab_lookup_add.c
// Řešení IJC-DU2, příklad a), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "htab_private.h"
#include <stdio.h>

htab_item_t* htab_item_create(htab_key_t key, htab_value_t value) {
  htab_item_t* item = malloc(sizeof(htab_item_t));
  if(item) {
    char* key_str = malloc(sizeof(char)*(strlen(key)+1));
    if(key_str) {
      strcpy(key_str, key);
      item->data.key = key_str;
      item->data.value = value;
      item->next = NULL;
    } else {
      free(item);
      fprintf(stderr, "Error: htab_lookup_add: malloc failed!\n");
      return NULL;
    }
  } else {
    fprintf(stderr, "Error: htab_lookup_add: malloc failed!\n");
    return NULL;
  }
  return item;
}

// Najde, popripade prida zaznam s danym klicem
// aplikuje MTF (Move To Front)
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
  size_t h = htab_hash_function(key) % t->arr_size;
  
  // Look for match
  htab_item_t* item = t->arr[h];
  htab_item_t* previous = NULL;
  while(item) {
    if(strcmp(key, item->data.key) == 0) {
      // Move To Front
      if(previous) {
      previous->next = item->next;
      item->next = t->arr[h];
      t->arr[h] = item;
      }
      return &item->data;
    }
    previous = item;
    item = item->next;
  };
  
  // If no match is found create new
  htab_item_t* new_item = htab_item_create(key, 0);
  if(new_item) {
    t->size++;
    new_item->next = t->arr[h];
    t->arr[h] = new_item;
    return &new_item->data;
  } else {
    return NULL;
  }
}