#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "matrix.h"

int main(void){

  int m = 5;
  int n = 5;
  Matrix * A = allocate_Matrix(m, n);
  Vector * x = allocate_Vector(n);

  for (int i = 0; i < m; ++i){
    for (int j = 0; j < n; ++j){
      A->ptr[i][j] = (double) (i+j);
    }
  }
  for (int j = 0; j < n; ++j){
    x->ptr[j] = j+1;
  }

  print_Matrix(A);
  print_Vector(x);

  // test matrix-vector multiplication
  Vector * out = allocate_Vector(m);
  multiply_Matrix_Vector(out, A, x);
  print_Vector(out);
  printf("The norm of A*x is %f\n", norm(out));
  
  free_Matrix(A);
  free_Vector(x);
  free_Vector(out);

}

