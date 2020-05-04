#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> 
#include "book.h"

// basic node structure
typedef struct __node_t {
  int key;
  Book *book;
  struct __node_t *next;
} node_t;

// basic list structure (one used per list)
typedef struct __list_t {
  node_t *head;
  pthread_mutex_t lock;
} list_t;

typedef struct { 
  int thread_id;
  list_t *books;
} myarg_t;

void List_Init(list_t *L);
void List_Insert(list_t *L, int key);
int List_Lookup(list_t *L, int key);
node_t* List_Get_Node(list_t *L, int key);
void List_Print(list_t *L);