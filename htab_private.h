// htab_private.h
// Řešení IJC-DU2, příklad 2), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

// následující řádky zabrání násobnému vložení:
#ifndef HTAB_PRIVATE_H__
#define HTAB_PRIVATE_H__

#include "htab.h"
#include <stdlib.h>

// Prvek:
typedef struct htab_item htab_item_t;
struct htab_item {
  htab_pair_t data;
  htab_item_t* next;
};

// Tabulka:
typedef struct htab htab_t;     // typedef podle zadání
struct htab {
  size_t size;
  size_t arr_size;
  htab_item_t* arr[];
};

#endif // HTAB_PRIVATE_H__