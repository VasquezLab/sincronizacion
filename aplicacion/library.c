#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "list.h"

int total_succes = 0;
int total_fail = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *loan (void *i);

int main(int argc, char const *argv[]){

  printf("Initializing list of available books \n\n");
  clock_t begin = clock();

  // Crear lista de libros
  list_t *books;
  books = (list_t*) malloc(sizeof(list_t));
  List_Init(books);

  // Llenar la lista de libros
  for (int i = 0; i < 10000; i++) {
    List_Insert(books, i);
  }
  
  // Crear el arreglo de hilos
  pthread_t offices[4];
 
  // Inicializar argumentos de cada hilo
  myarg_t args[] = { 
    { 0, books },
    { 1, books },
    { 2, books },
    { 3, books }
  };

  // Crear cada hilo
  for (int i = 0; i < 4; i++) {
    pthread_create(&offices[i], NULL, &loan, &args[i]);
  }

  // Esperar a que se ejecuten los hilos
  for (int i = 0; i < 4; i++) {
    pthread_join(offices[i], NULL);
  }

  clock_t end = clock();

  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\nSimulation done! \nExecution time: %f\n\n", time_spent);

  printf("Total successful loans %d \nTotal failed loans %d\n\n", total_succes, total_fail);
  printf("Number of remaining available books %d\n", 10000 - total_succes);

  return 0;
}

void *loan (void *arg) {
  int success = 0;
  int fail = 0;
  
  myarg_t *args = (myarg_t *) arg;
  list_t *books = args->books;
  node_t *book_node;

  int thread_id = args->thread_id;
  int *seed = malloc(sizeof(int));
  *seed = args->thread_id;

  unsigned int *mystate = seed;
  *mystate = time(NULL) ^ getpid() ^ pthread_self(); // XOR multiple values together to get a semi-unique seed
  printf("[Office %d]: \t Seed=%u\n", thread_id,*mystate);

  for (int i = 0; i < 1000; i++) {
    int rand1 = rand_r(mystate) % 10000;

    pthread_mutex_lock(&mutex);
      book_node = List_Get_Node(books, rand1);

      if (Book_Is_Available(book_node->book)) {
        Book_Loan(book_node->book);
        success++;
      } else {
        fail++;
      }
    pthread_mutex_unlock(&mutex);
  }
  pthread_mutex_lock(&mutex);
    total_succes += success;
    total_fail += fail;
  pthread_mutex_unlock(&mutex);

  printf("[Office %d]: \t Succes=%d \t Fail=%d\n", thread_id, success, fail);
}