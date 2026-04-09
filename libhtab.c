//libhtab.a

#include <string.h>     // size_t
#include <stdbool.h>    // bool

// Tabulka:
struct htab {
  size_t size;
  size_t arr_size;
  htab_item_t* arr[];
};
typedef struct htab htab_t;     // typedef podle zadání

struct htab_item {
  htab_pair_t data;
  htab_item_t* next;
};
typedef struct htab_item htab_item_t;

// Typy:
typedef const char * htab_key_t;        // typ klíče
typedef unsigned htab_value_t;          // typ hodnoty

// Dvojice dat v tabulce:
typedef struct htab_pair {
    htab_key_t    key;          // klíč
    htab_value_t  value;        // asociovaná hodnota
} htab_pair_t;                  // typedef podle zadání

// Rozptylovací (hash) funkce (je stejná pro všechny tabulky v programu)
// Pokud si v programu definujete stejnou funkci, použije se ta vaše.
#ifndef MY_HASH_FUNCTION
size_t htab_hash_function(const char *str) {
  unsigned long h=0;     // musí mít 32 bitů
  const unsigned char *p;
  for(p=(const unsigned char*)str; *p!='\0'; p++)
      h = 65599*h + *p;
  return h;
};
#endif

// Funkce pro operace s tabulkou:
htab_t *htab_init(size_t n) {
  htab_t* t = malloc(sizeof(htab_t) + n * sizeof(htab_item_t*));
  if(t) {
    t->size = 0;
    t->arr_size = n;
    for(unsigned i = 0; i < n; i++) {
      t->arr[i] = NULL;
    }
  };
  return t;
};                    // konstruktor tabulky
size_t htab_size(const htab_t * t) {
  return t->size;
};             // počet záznamů v tabulce
size_t htab_bucket_count(const htab_t * t) {
  return t->arr_size;
};     // velikost pole

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
};  // hledání
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
  size_t h = htab_hash_function(key) % t->arr_size;
  htab_item_t* item = t->arr[h];
  while(item && item->next) {
    if(strcmp(key, item->data.key) == 0) {
      return &item->data;
    }
    item = item->next;
  }

};  //  +vložení

bool htab_erase(htab_t * t, htab_key_t key);    // ruší zadaný záznam

// for_each: projde všechny záznamy a zavolá na ně funkci f
// Pozor: f nesmí měnit klíč .key ani přidávat/rušit položky
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data));

void htab_clear(htab_t * t) {
  for( unsigned i = 0; i < t->arr_size; i++) {
    htab_item_t* item = t->arr[i];
    while(item) {
      htab_item_t* next = item->next;
      free(item);
      t->size--;
      item = next;
    }
  }
};
    // ruší všechny záznamy
void htab_free(htab_t * t) {
  htab_clear(t);
  free(t);
};    // destruktor tabulky