#include "list.h"

void List_Init(list_t *L) {
  L->head = NULL;
  pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, int key) {
  // synchronization not needed
  node_t *new = malloc(sizeof(node_t));
  Book *new_book = (Book*)malloc(sizeof(Book));

  if (new == NULL || new_book == NULL) {
    perror("malloc");
    return;
  }
  new->key = key;

  Book_Init(new_book, key);
  new->book = new_book;
  
  // just lock critical section
  pthread_mutex_lock(&L->lock);
  new->next = L->head;
  L->head = new;
  pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int key) {
  int rv = -1;
  pthread_mutex_lock(&L->lock);
  node_t *curr = L->head;
  while (curr) {
    if (curr->key == key) {
      rv = 0;
      break;
    }
    curr = curr->next;
  }
  pthread_mutex_unlock(&L->lock);
  return rv; // now both success and failure
}

node_t* List_Get_Node(list_t *L, int key) {
  int rv = -1;
  pthread_mutex_lock(&L->lock);
  node_t *curr = L->head;
  while (curr) {
    if (curr->key == key) {
      rv = 0;
      break;
    }
    curr = curr->next;
  }
  pthread_mutex_unlock(&L->lock);
  return curr;
}

void List_Print(list_t *L){
  pthread_mutex_lock(&L->lock);
  node_t *curr = L->head;
  while (curr) {
    printf("%s\n", curr->book->name);
    curr = curr->next;
  }
  pthread_mutex_unlock(&L->lock);
}