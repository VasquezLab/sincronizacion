#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 

typedef struct __book{
  int id;
  char name[10];
  int num_pages;
  int pub_year;
  bool available;
} Book;

void Book_Init(Book *b, int id);
void Book_Loan(Book *b);
void Book_Return(Book *B);
bool Book_Is_Available(Book *B);