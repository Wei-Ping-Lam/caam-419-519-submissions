#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "UpperTriangularMatrix.h"

UpperTriangularMatrix * allocate_UpperTriangularMatrix(int n){
  UpperTriangularMatrix * A = malloc(sizeof(UpperTriangularMatrix));
  A->n = n;
  int num_entries = (int) (n * (n + 1))/2;
  A->ptr = malloc(sizeof(double) * num_entries);
  return A;
}

void free_UpperTriangularMatrix(UpperTriangularMatrix* A){
  free(A->ptr);  
}

void print_UpperTriangularMatrix(UpperTriangularMatrix* A){
  printf("UpperTriangularMatrix = [\n");
  int N = A->n;
  for (int i = 0; i < A->n; ++i){
    for (int j = 0; j < A->n; ++j){
      if (i <= j){
        printf("%7.2f  ", A->ptr[i*(N - 1) - i*(i - 1)/2 + j]);
      }else{
        printf("         ");
      }
    }
    printf("\n");    
  }
  printf("]\n");
}

UpperTriangularMatrix* UpperTriangularMatrix_copy(Matrix* A){
  int dim;
  if (A->m < A->n){
    dim = A->m;
  }else{
    dim = A->n;
  }
  UpperTriangularMatrix * B = allocate_UpperTriangularMatrix(dim);
  int N = A->n;
  for (int i = 0; i < dim; ++i){
    for (int j = 0; j < dim; ++j){
      if (i <= j){
        B->ptr[i*(N - 1) - i*(i - 1)/2 + j] = A->ptr[i][j];
      }
    }   
  }
  return B;
}

void multiply_UpperTriangularMatrix_Vector(Vector* out, UpperTriangularMatrix* A, Vector* x){
  int N = A->n;
  for (int i = 0; i < A->n; ++i){
    for (int j = i; j < A->n; ++j){
      double A_ij = A->ptr[i*(N - 1) - i*(i - 1)/2 + j];
      double x_j = x->ptr[j];
      out->ptr[i] += A_ij * x_j;
    }
  }
}

double time_UpperTriangularMatrix_multiply(void (*mul)(Vector*, UpperTriangularMatrix*, Vector*), Vector* out, UpperTriangularMatrix* A, Vector* x){
  clock_t start = clock();
  int num_samples = 100;
  for (int i = 0; i < num_samples; ++i){
    (*mul)(out, A, x);
  }
  clock_t end = clock();
  double time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
  return time_elapsed/num_samples;
}