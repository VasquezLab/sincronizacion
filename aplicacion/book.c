#include "book.h"

void Book_Loan(Book *B) {
  if (B->available){
    B->available = !B->available;
  }
  return;
}

void Book_Return(Book *B) {
  if (!B->available){
    B->available = !B->available;
  }
  return;
}

void Book_Init(Book *B, int id) {
  B->id = id;
  snprintf(B->name, 10, "Book_%d", id);
  B->num_pages = 100;
  B->pub_year = 2020;
  B->available = true;
}

bool Book_Is_Available(Book *B) {
  return B->available;
}