#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TridiagonalMatrix.h"

TridiagonalMatrix * allocate_TridiagonalMatrix(int n){
  double ** ptr = malloc(sizeof(double*) * 3);
  ptr[0] = malloc(sizeof(double) * (n-1));
  ptr[1] = malloc(sizeof(double) * n);
  ptr[2] = malloc(sizeof(double) * (n-1));
  
  TridiagonalMatrix * A = malloc(sizeof(TridiagonalMatrix));
  A->n = n;
  A->ptr = ptr;
  return A;
}

void free_TridiagonalMatrix(TridiagonalMatrix* A){
  free(A->ptr[0]);
  free(A->ptr[1]);
  free(A->ptr[2]);
  free(A->ptr);
}

void print_TridiagonalMatrix(TridiagonalMatrix* A){
  printf("TridiagonalMatrix = [\n");
  for (int i = 0; i < A->n; ++i){
    for (int j = 0; j < A->n; ++j){
      if (j - i == 1){
        printf("%7.2f  ", A->ptr[0][j-1]);
      }else if (i == j){
        printf("%7.2f  ", A->ptr[1][j]);
      }else if (i - j == 1){
        printf("%7.2f  ", A->ptr[2][j]);
      }else{
        printf("         ");
      }
    }
    printf("\n");    
  }
  printf("]\n");
}

TridiagonalMatrix* TridiagonalMatrix_copy(Matrix* A){
  int dim;
  if (A->m < A->n){
    dim = A->m;
  }else{
    dim = A->n;
  }
  TridiagonalMatrix * B = allocate_TridiagonalMatrix(dim);
  for (int i = 0; i < dim; ++i){
    for (int j = 0; j < dim; ++j){
      if (j - i == 1){
        B->ptr[0][j-1] = A->ptr[i][j];
      }else if (i == j){
        B->ptr[1][j] = A->ptr[i][j];
      }else if (i - j == 1){
        B->ptr[2][j] = A->ptr[i][j];
      }
    }   
  }
  return B;
}

void multiply_TridiagonalMatrix_Vector(Vector* out, TridiagonalMatrix* A, Vector* x){
  for (int i = 0; i < A->n - 1; ++i){
    out->ptr[i] += A->ptr[0][i] * x->ptr[i+1];
    out->ptr[i] += A->ptr[1][i] * x->ptr[i];
    out->ptr[i+1] += A->ptr[2][i] * x->ptr[i];
  }
  out->ptr[A->n - 1] += A->ptr[1][A->n - 1] * x->ptr[A->n - 1];
}

double time_TridiagonalMatrix_multiply(void (*mul)(Vector*, TridiagonalMatrix*, Vector*), Vector* out, TridiagonalMatrix* A, Vector* x){
  clock_t start = clock();
  int num_samples = 100;
  for (int i = 0; i < num_samples; ++i){
    (*mul)(out, A, x);
  }
  clock_t end = clock();
  double time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
  return time_elapsed/num_samples;
}