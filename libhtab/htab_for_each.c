// htab_for_each.c
// Řešení IJC-DU2, příklad a), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "libhtab/htab_private.h"

// for_each: projde všechny záznamy a zavolá na ně funkci f
// Pozor: f nesmí měnit klíč .key ani přidávat/rušit položky
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
  for(unsigned bucket_idx = 0; bucket_idx < htab_bucket_count(t); bucket_idx++) {
    htab_item_t* item = t->arr[bucket_idx];
    while(item) {
      f(&item->data);
    }
  }
}