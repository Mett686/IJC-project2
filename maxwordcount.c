// maxwordcount.c
// Řešení IJC-DU2, příklad 2), 14.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "io.h"

#define BUFF_SIZE 100 // Maximalni delka slova
#define BUCKET_COUNT 5000 // Pocet bucketu v htab
// Optimalni pocet bucketu pro hashovaci funkci v htablib
// je polovina az dvojnasob poctu vstupu
// proto 5000 jakozto prumerna slovni zasoba

static unsigned count_threshold = 0;

#ifdef MY_HASH_FUNCTION
#include <stdint.h>
size_t htab_hash_function(const char *str) {
  uint32_t hash = 5381;
  int c;

  while ((c = *str++))
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}
#endif

void print_most_common(htab_pair_t* data) {
  if(data->value >= count_threshold)
    fprintf(stdout, "%s\t%u\n", data->key, data->value);
}

bool htab_inc_add(htab_t* t, char* key) {
  htab_pair_t* pair = htab_lookup_add(t, key);
  if(pair) {
    pair->value++;
    if(count_threshold < pair->value)
      count_threshold = pair->value;
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Error: htab_inc_add: htab_lookup_add returned NULL\n");
    return EXIT_FAILURE;
  }
}

int main() {
  htab_t* table = htab_init(BUCKET_COUNT);
  char buffer[BUFF_SIZE];
  while(read_word(BUFF_SIZE, buffer, stdin) != EOF) {
    if(htab_inc_add(table, buffer)) return EXIT_FAILURE;
  }
  htab_for_each(table, &print_most_common);
  htab_free(table);

  return EXIT_SUCCESS;
}