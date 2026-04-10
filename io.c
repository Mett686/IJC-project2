
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int read_word(unsigned max, char s[max], FILE * f) {
  char c;
  while((c = fgetc(f)) != EOF && isspace(c));
  
  unsigned i = 0;
  while(c != EOF && !isspace(c) && (i < (max-1))) {
    s[i] = c;
    c = fgetc(f);
    i++;
  }
  s[i] = '\0';

  if(c == EOF && i == 0) {
    return EOF;
  }
  static bool warned = false;
  if(!warned && i == (max-1)) {
    fprintf(stderr, "Warning: read_word: exceeded word limit, ignoring rest!\n");
    warned = true;
  }

  return strlen(s);
}