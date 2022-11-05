#include "vector.h"
#include "matrix.h"

#ifndef _DIAGONALMATRIX
#define _DIAGONALMATRIX

typedef struct{
  int n;
  double * ptr; 
} DiagonalMatrix;

#endif

DiagonalMatrix * allocate_DiagonalMatrix(int n);
void free_DiagonalMatrix(DiagonalMatrix* A);
void print_DiagonalMatrix(DiagonalMatrix* A);
DiagonalMatrix* DiagonalMatrix_copy(Matrix* A);
void multiply_DiagonalMatrix_Vector(Vector* out, DiagonalMatrix* A, Vector* x);
double time_DiagonalMatrix_multiply(void (*mul)(Vector*, DiagonalMatrix*, Vector*), Vector* out, DiagonalMatrix* A, Vector* x);
