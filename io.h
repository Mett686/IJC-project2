// io.h
// Řešení IJC-DU2, příklad 2), 14.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#ifndef IO_H__
#define IO_H__
#include <stdio.h>

// Cte slovo ze souboru f, vraci strlen(s) nebo EOF
int read_word(unsigned max, char s[max], FILE * f);

#endif