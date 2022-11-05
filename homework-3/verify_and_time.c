#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "matrix.h"
#include "DiagonalMatrix.h"
#include "UpperTriangularMatrix.h"
#include "TridiagonalMatrix.h"

int main(void){
  
  int n = 100;
  
  Vector * x = allocate_Vector(n);
  for (int i = 0; i < n; ++i){
    x->ptr[i] = i+1;
  }
  
  Matrix * A = allocate_Matrix(n, n);
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < n; ++j){
      A->ptr[i][j] = (double) (i+j);
    }
  }
  Vector * outA = allocate_Vector(n);
  multiply_Matrix_Vector(outA, A, x);
  
  // Diagonal matrix-vector multiplication
  DiagonalMatrix * B = DiagonalMatrix_copy(A);
  Vector * outB = allocate_Vector(n);
  multiply_DiagonalMatrix_Vector(outB, B, x);
  Vector * outBA = allocate_Vector(n);
  for (int i = 0; i < n; ++i){
    outBA->ptr[i] = outB->ptr[i] - outA->ptr[i];
  }
  printf("The norm of the difference between the two matrix-vector products for Diagonal Matrix is %f.\n", norm(outBA));
  
  // Upper Triangular matrix-vector multiplication
  UpperTriangularMatrix * C = UpperTriangularMatrix_copy(A);
  Vector * outC = allocate_Vector(n);
  multiply_UpperTriangularMatrix_Vector(outC, C, x);
  Vector * outCA = allocate_Vector(n);
  for (int i = 0; i < n; ++i){
    outCA->ptr[i] = outC->ptr[i] - outA->ptr[i];
  }
  printf("The norm of the difference between the two matrix-vector products for Upper Triangular Matrix is %f.\n", norm(outCA));
  
  // Tridiagonal matrix-vector multiplication
  TridiagonalMatrix * D = TridiagonalMatrix_copy(A);
  Vector * outD = allocate_Vector(n);
  multiply_TridiagonalMatrix_Vector(outD, D, x);
  Vector * outDA = allocate_Vector(n);
  for (int i = 0; i < n; ++i){
    outDA->ptr[i] = outD->ptr[i] - outA->ptr[i];
  }
  printf("The norm of the difference between the two matrix-vector products for Tridiagonal Matrix is %f.\n", norm(outDA));
  
  double time_elapsedA = time_Matrix_multiply(&multiply_Matrix_Vector, outA, A, x);
  printf("Matrix multiplication: time elapsed = %g seconds\n", time_elapsedA);
  
  // Timing diagonal matrix-vector multiplication
  double time_elapsedB = time_DiagonalMatrix_multiply(&multiply_DiagonalMatrix_Vector, outB, B, x);
  printf("Diagonal Matrix multiplication: time elapsed = %g seconds\n", time_elapsedB);
  printf("Diagonal Matrix multiplication is about %.2f times faster than Matrix multiplication\n", (time_elapsedA/time_elapsedB));
  
  // Timing upper triangular matrix-vector multiplication
  double time_elapsedC = time_UpperTriangularMatrix_multiply(&multiply_UpperTriangularMatrix_Vector, outC, C, x);
  printf("Upper Triangular Matrix multiplication: time elapsed = %g seconds\n", time_elapsedC);
  printf("Upper Triangular Matrix multiplication is about %.2f times faster than Matrix multiplication\n", (time_elapsedA/time_elapsedC));
  
  // Timing tridiagonal matrix-vector multiplication
  double time_elapsedD = time_TridiagonalMatrix_multiply(&multiply_TridiagonalMatrix_Vector, outD, D, x);
  printf("Tridiagonal Matrix multiplication: time elapsed = %g seconds\n", time_elapsedD);
  printf("Tridiagonal Matrix multiplication is about %.2f times faster than Matrix multiplication\n", (time_elapsedA/time_elapsedD));
  
  free_Vector(x);
  free_Matrix(A);
  free_DiagonalMatrix(B);
  free_UpperTriangularMatrix(C);
  free_TridiagonalMatrix(D);
  free_Vector(outA);
  free_Vector(outB);
  free_Vector(outC);
  free_Vector(outD);
  free_Vector(outBA);
  free_Vector(outCA);
  free_Vector(outDA);
  
}