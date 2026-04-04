#include <stdio.h>

void main() {
  for(int i = 0; i < 1500; i++) {
    putchar('#');
  }
  putchar('\n');
  printf("Should be too long\n");
}