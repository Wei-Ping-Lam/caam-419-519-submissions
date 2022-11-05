#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

Matrix* allocate_Matrix(int m, int n){
  double ** ptr = malloc(sizeof(double*) * m);

  // allocate contiguous memory for the
  // row-major storage of A
  ptr[0] = malloc(sizeof(double) * m * n);
  for (int i = 1; i < m; ++i){
    ptr[i] = ptr[0] + i * n;
  }

  // return a pointer to a new matrix object
  Matrix * A = malloc(sizeof(Matrix));
  A->m = m;
  A->n = n;
  A->ptr = ptr;
  return A;
}

void free_Matrix(Matrix *A){
  free(A->ptr[0]); 
  free(A->ptr);  
}

void print_Matrix(Matrix * A){
  printf("A = [\n");
  for (int i = 0; i < A->m; ++i){
    for (int j = 0; j < A->n; ++j){
      printf("%7.2f  ", A->ptr[i][j]);
    }
    printf("\n");    
  }
  printf("]\n");
}

void multiply_Matrix_Vector(Vector* out, Matrix* A, Vector* x){
  for (int i = 0; i < A->m; ++i){
    for (int j = 0; j < A->n; ++j){
      out->ptr[i] += A->ptr[i][j] * x->ptr[j];
    }
  }
}

double time_Matrix_multiply(void (*mul)(Vector*, Matrix*, Vector*), Vector* out, Matrix* A, Vector* x){
  clock_t start = clock();
  int num_samples = 100;
  for (int i = 0; i < num_samples; ++i){
    (*mul)(out, A, x);
  }
  clock_t end = clock();
  double time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
  return time_elapsed/num_samples;
}