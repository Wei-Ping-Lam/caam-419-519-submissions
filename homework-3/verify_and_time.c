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
  
  // Diagonal matrix-vector multiplication
  Matrix * diagA = allocate_Matrix(n, n);
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < n; ++j){
      if (i == j){
        diagA->ptr[i][j] = (double) (i+j);
      }else{
        diagA->ptr[i][j] = 0.0;
      }
    }
  }
  Vector * diagOutA = allocate_Vector(n);
  multiply_Matrix_Vector(diagOutA, diagA, x);
  DiagonalMatrix * diagB = DiagonalMatrix_copy(diagA);
  Vector * diagOutB = allocate_Vector(n);
  multiply_DiagonalMatrix_Vector(diagOutB, diagB, x);
  Vector * diagOutBA = allocate_Vector(n);
  for (int i = 0; i < n; ++i){
    diagOutBA->ptr[i] = diagOutB->ptr[i] - diagOutA->ptr[i];
  }
  printf("The norm of the difference between the two matrix-vector products for Diagonal Matrix is %.2e.\n", norm(diagOutBA));
  
  // Upper Triangular matrix-vector multiplication
  Matrix * upperTriA = allocate_Matrix(n, n);
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < n; ++j){
      if (i <= j){
        upperTriA->ptr[i][j] = (double) (i+j);
      }else{
        upperTriA->ptr[i][j] = 0.0;
      }
    }
  }
  Vector * upperTriOutA = allocate_Vector(n);
  multiply_Matrix_Vector(upperTriOutA, upperTriA, x);
  UpperTriangularMatrix * upperTriB = UpperTriangularMatrix_copy(upperTriA);
  Vector * upperTriOutB = allocate_Vector(n);
  multiply_UpperTriangularMatrix_Vector(upperTriOutB, upperTriB, x);
  Vector * upperTriOutBA = allocate_Vector(n);
  for (int i = 0; i < n; ++i){
    upperTriOutBA->ptr[i] = upperTriOutB->ptr[i] - upperTriOutA->ptr[i];
  }
  printf("The norm of the difference between the two matrix-vector products for Upper Triangular Matrix is %.2e.\n", norm(upperTriOutBA));
  
  // Tridiagonal matrix-vector multiplication
  Matrix * triDiagA = allocate_Matrix(n, n);
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < n; ++j){
      if ((i - j <= 1) && (i - j >= -1)){
        triDiagA->ptr[i][j] = (double) (i+j);
      }else{
        triDiagA->ptr[i][j] = 0.0;
      }
    }
  }
  Vector * triDiagOutA = allocate_Vector(n);
  multiply_Matrix_Vector(triDiagOutA, triDiagA, x);
  TridiagonalMatrix * triDiagB = TridiagonalMatrix_copy(triDiagA);
  Vector * triDiagOutB = allocate_Vector(n);
  multiply_TridiagonalMatrix_Vector(triDiagOutB, triDiagB, x);
  Vector * triDiagOutBA = allocate_Vector(n);
  for (int i = 0; i < n; ++i){
    triDiagOutBA->ptr[i] = triDiagOutB->ptr[i] - triDiagOutA->ptr[i];
  }
  printf("The norm of the difference between the two matrix-vector products for Tridiagonal Matrix is %.2e.\n", norm(triDiagOutBA));
  
  Vector * out = allocate_Vector(n);
  for (int i = 0; i < n; ++i){
    out->ptr[i] = 0.0;
  }
  
  // Diagonal matrix-vector multiplication
  Matrix * A = allocate_Matrix(n, n);
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < n; ++j){
      A->ptr[i][j] = 0.0;
    }
  }
  DiagonalMatrix * B = DiagonalMatrix_copy(A);
  UpperTriangularMatrix * C = UpperTriangularMatrix_copy(A);
  TridiagonalMatrix * D = TridiagonalMatrix_copy(A);
  
  double time_elapsedA = time_Matrix_multiply(&multiply_Matrix_Vector, out, A, x);
  //printf("Matrix multiplication: time elapsed = %g seconds\n", time_elapsedA);
  
  // Timing diagonal matrix-vector multiplication
  double time_elapsedB = time_DiagonalMatrix_multiply(&multiply_DiagonalMatrix_Vector, out, B, x);
  printf("Diagonal Matrix multiplication: average time elapsed = %g seconds\n", time_elapsedB);
  printf("Diagonal Matrix multiplication is about %.2f times faster than Matrix multiplication\n", (time_elapsedA/time_elapsedB));
  
  // Timing upper triangular matrix-vector multiplication
  double time_elapsedC = time_UpperTriangularMatrix_multiply(&multiply_UpperTriangularMatrix_Vector, out, C, x);
  printf("Upper Triangular Matrix multiplication: average time elapsed = %g seconds\n", time_elapsedC);
  printf("Upper Triangular Matrix multiplication is about %.2f times faster than Matrix multiplication\n", (time_elapsedA/time_elapsedC));
  
  // Timing tridiagonal matrix-vector multiplication
  double time_elapsedD = time_TridiagonalMatrix_multiply(&multiply_TridiagonalMatrix_Vector, out, D, x);
  printf("Tridiagonal Matrix multiplication: average time elapsed = %g seconds\n", time_elapsedD);
  printf("Tridiagonal Matrix multiplication is about %.2f times faster than Matrix multiplication\n", (time_elapsedA/time_elapsedD));
  
  free_Vector(x);
  free_Matrix(diagA);
  free_Matrix(upperTriA);
  free_Matrix(triDiagA);
  free_DiagonalMatrix(diagB);
  free_UpperTriangularMatrix(upperTriB);
  free_TridiagonalMatrix(triDiagB);
  free_Vector(diagOutA);
  free_Vector(diagOutB);
  free_Vector(diagOutBA);
  free_Vector(upperTriOutA);
  free_Vector(upperTriOutB);
  free_Vector(upperTriOutBA);
  free_Vector(triDiagOutA);
  free_Vector(triDiagOutB);
  free_Vector(triDiagOutBA);
  free_Matrix(A);
  free_DiagonalMatrix(B);
  free_UpperTriangularMatrix(C);
  free_TridiagonalMatrix(D);
  free_Vector(out);
}