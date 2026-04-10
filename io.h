

#ifndef IO_H__
#define IO_H__
#include <stdio.h>

// Cte slovo ze souboru f, vraci strlen(s) nebo EOF
int read_word(unsigned max, char s[max], FILE * f);

#endif