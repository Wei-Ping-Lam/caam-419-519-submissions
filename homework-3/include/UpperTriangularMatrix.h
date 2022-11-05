#include "vector.h"
#include "matrix.h"

#ifndef _UPPERTRIANGULARMATRIX
#define _UPPERTRIANGULARMATRIX

typedef struct{
  int n;
  double * ptr; 
} UpperTriangularMatrix;

#endif

UpperTriangularMatrix * allocate_UpperTriangularMatrix(int n);
void free_UpperTriangularMatrix(UpperTriangularMatrix* A);
void print_UpperTriangularMatrix(UpperTriangularMatrix* A);
UpperTriangularMatrix* UpperTriangularMatrix_copy(Matrix* A);
void multiply_UpperTriangularMatrix_Vector(Vector* out, UpperTriangularMatrix* A, Vector* x);
double time_UpperTriangularMatrix_multiply(void (*mul)(Vector*, UpperTriangularMatrix*, Vector*), Vector* out, UpperTriangularMatrix* A, Vector* x);
