// maxwordcount.c
// Řešení IJC-DU2, příklad 1), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "io.h"

#define BUFF_SIZE 100

static unsigned count_threshold = 0;

////////////////////////////////////////////////////////////////////////////////////

void table_header_print(htab_t* table) {
  fprintf(stdout, "Table size: %ld\nBucket count: %ld\n", htab_size(table), htab_bucket_count(table));
}

///////////////////////////////////////////////


void data_print(htab_pair_t* data) {
  fprintf(stdout, "%s\t%d\n", data->key, data->value);
}

void print_most_common(htab_pair_t* data) {
  if(data->value == count_threshold)
    fprintf(stdout, "%s\t%d\n", data->key, data->value);
}

bool htab_inc_add(htab_t* t, char* key) {
  htab_pair_t* pair = htab_lookup_add(t, key);
  if(pair) {
    pair->value++;
    if(count_threshold < pair->value)
      count_threshold = pair->value;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

int main() {
  htab_t* table = htab_init(50);
  table_header_print(table);
  htab_for_each(table, &data_print);

  char buffer[BUFF_SIZE];
  unsigned len = 0;
  while((len = read_word(BUFF_SIZE, buffer, stdin)) != (unsigned)EOF) {
    htab_inc_add(table, buffer);
  }
  printf("Max count: %u\n", count_threshold);
  table_header_print(table);
  htab_for_each(table, &print_most_common);
  htab_free(table);

  return EXIT_SUCCESS;
}