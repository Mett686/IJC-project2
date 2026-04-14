// htab_hash_function.c
// Řešení IJC-DU2, příklad 2), 14.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include "htab_private.h"
#include <stdint.h>

// Vraci hash
size_t htab_hash_function(const char *str) {
  uint32_t h=0;     // musí mít 32 bitů
  const unsigned char *p;
  for(p=(const unsigned char*)str; *p!='\0'; p++)
      h = 65599*h + *p;
  return h;
}