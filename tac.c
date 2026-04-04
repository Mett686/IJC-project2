// tac.c
// Řešení IJC-DU2, příklad a), 31.4.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1024

typedef struct node{
  char line[MAX_LEN];
  struct node* next;
} Node_t;

typedef struct {
  Node_t* head;
  unsigned count;
} List;


void list_init(List * list) {
  list->head = NULL; // proc nejde dat nullptr
  list->count = 0;
}

Node_t * list_ins_first(List* list,char* line) {
  Node_t * node = malloc(sizeof(Node_t));
  if(!node) {
    fprintf(stderr, "list_ins_first: malloc: failed!\n");
  } else {
    strcpy(node->line, line);
    node->next = list->head;
    list->head = node;
    list->count++;
  }
  return node;
}

void list_print(List * list) {
  Node_t * node = list->head;
  while(node) {
    fprintf(stdout, "%s", node->line);
    node = node->next;
  }
}

unsigned list_size(List * list) {
  return list->count;
}

void list_free(List * list) {
  unsigned count = list->count;
  Node_t * node = list->head;
  while(node) {
    Node_t * next = node->next;
    free(node);
    node = next;
    count--;
  }
  if(count) {
    fprintf(stderr, "list_free: Weird count after free: %u\n", count);
  }
  list->head = NULL; //NULL again
  list->count = 0;
}

int main(int argc, char **argv) {

  unsigned limit = 0;
  char * path = NULL;

  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      switch (argv[i][1])
      {
      case 'l':
        sscanf(argv[i+1], "%u", &limit);
        i++;
        break;
      
      default:
        fprintf(stderr, "Invalid argument: %s\n", argv[i]);
        break;
      }
    } else {
      path = argv[i];
    }
  }

  // Open file or leave stdin
  FILE* file = stdin;
  if(path) {
    file = fopen(path, "r");
    if(!file) {
      fprintf(stderr, "Failed to open %s", path);
      exit(EXIT_FAILURE);
    }
  }

  // Initialize reverse list and control variables
  List reverse_list;
  list_init(&reverse_list);
  char buffer[MAX_LEN];
  bool err_printed = false;
  unsigned lines_read = 0;

  // Loop through whole file or unil limit is reached (if set)
  while(fgets(buffer, MAX_LEN, file) && (!limit || lines_read < limit)) {
    // Check for line cut short
    if(strlen(buffer) == MAX_LEN-1 && buffer[MAX_LEN-1] != '\n') {
      buffer[MAX_LEN-1] = '\n';
      // Print error only once
      if(!err_printed) {
      fprintf(stderr, "Warning, line was too long. Ignoring rest.\n");
      err_printed = true;
      }
      // Throw away rest
      int c;
      while ((c = fgetc(file)) != '\n' && c != EOF);
    }
    
    list_ins_first(&reverse_list, buffer);
    if(limit) lines_read++;
  }

  list_print(&reverse_list);
  list_free(&reverse_list);
  exit(EXIT_SUCCESS);
}
