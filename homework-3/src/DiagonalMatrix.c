#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DiagonalMatrix.h"

DiagonalMatrix * allocate_DiagonalMatrix(int n){
  DiagonalMatrix * A = malloc(sizeof(DiagonalMatrix));
  A->n = n;
  A->ptr = malloc(sizeof(double) * n);
  return A;
}

void free_DiagonalMatrix(DiagonalMatrix* A){
  free(A->ptr);  
}

void print_DiagonalMatrix(DiagonalMatrix* A){
  printf("DiagonalMatrix = [\n");
  for (int i = 0; i < A->n; ++i){
    for (int j = 0; j < A->n; ++j){
      if (i == j){
        printf("%7.2f  ", A->ptr[i]);
      }else{
        printf("         ");
      }
    }
    printf("\n");    
  }
  printf("]\n");
}

DiagonalMatrix* DiagonalMatrix_copy(Matrix* A){
  int dim;
  if (A->m < A->n){
    dim = A->m;
  }else{
    dim = A->n;
  }
  DiagonalMatrix * B = allocate_DiagonalMatrix(dim);
  for (int i = 0; i < dim; ++i){
    for (int j = 0; j < dim; ++j){
      if (i == j){
        B->ptr[i] = A->ptr[i][i];
      }
    }   
  }
  return B;
}

void multiply_DiagonalMatrix_Vector(Vector* out, DiagonalMatrix* A, Vector* x){
  for (int i = 0; i < A->n; ++i){
    out->ptr[i] = A->ptr[i] * x->ptr[i];
  }
}

double time_DiagonalMatrix_multiply(void (*mul)(Vector*, DiagonalMatrix*, Vector*), Vector* out, DiagonalMatrix* A, Vector* x){
  clock_t start = clock();
  int num_samples = 100;
  for (int i = 0; i < num_samples; ++i){
    (*mul)(out, A, x);
  }
  clock_t end = clock();
  double time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
  return time_elapsed/num_samples;
}