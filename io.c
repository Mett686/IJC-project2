// io.c
// Řešení IJC-DU2, příklad 2), 14.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


int read_word(unsigned max, char s[max], FILE * f) {
  static bool warned = false;
  int c;
  while(isspace(c = fgetc(f)));
  
  unsigned i = 0;
  while(c != EOF && !isspace(c)) {
    if(i < (max-1)) {
      s[i] = c;
      i++;
    } else if(!warned) {
      fprintf(stderr, "Warning: read_word: exceeded word limit, ignoring rest!\n");
      warned = true;
    }
    c = fgetc(f);
  }
  s[i] = '\0';

  if(c == EOF && i == 0) {
    return EOF;
  }

  return (int)i;
}