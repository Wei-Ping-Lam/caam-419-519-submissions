#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "DiagonalMatrix.h"
#include "UpperTriangularMatrix.h"
#include "TridiagonalMatrix.h"

int main(void){

  int n = 5;
  
  Matrix * A = allocate_Matrix(n, n);
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < n; ++j){
      A->ptr[i][j] = (double) (i+j);
    }
  }
  
  // Printing diagonal matrix
  DiagonalMatrix * B = DiagonalMatrix_copy(A);
  printf("Running Diagonal Matrix...\n");
  print_DiagonalMatrix(B);
  
  // Printing upper triangular diagonal matrix
  UpperTriangularMatrix * C = UpperTriangularMatrix_copy(A);
  printf("Running Upper Triangular Matrix...\n");
  print_UpperTriangularMatrix(C);
  
  // Printing tridiagonal matrix
  TridiagonalMatrix * D = TridiagonalMatrix_copy(A);
  printf("Running Tridiagonal Matrix...\n");
  print_TridiagonalMatrix(D);
  
  free_DiagonalMatrix(B);
  free_UpperTriangularMatrix(C);
  free_TridiagonalMatrix(D);
  free_Matrix(A);

}

