#include "vector.h"
#include "matrix.h"

#ifndef _TRIDIAGONALMATRIX
#define _TRIDIAGONALMATRIX

typedef struct{
  int n;
  double ** ptr; 
} TridiagonalMatrix;

#endif

TridiagonalMatrix * allocate_TridiagonalMatrix(int n);
void free_TridiagonalMatrix(TridiagonalMatrix* A);
void print_TridiagonalMatrix(TridiagonalMatrix* A);
TridiagonalMatrix* TridiagonalMatrix_copy(Matrix* A);
void multiply_TridiagonalMatrix_Vector(Vector* out, TridiagonalMatrix* A, Vector* x);
double time_TridiagonalMatrix_multiply(void (*mul)(Vector*, TridiagonalMatrix*, Vector*), Vector* out, TridiagonalMatrix* A, Vector* x);
