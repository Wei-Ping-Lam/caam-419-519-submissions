#include <iostream>
#include "vector.h"
#include "matrix.h"
	      
int main(void){
  Matrix A(6,4);
  Matrix B(4,5);
  Matrix C(6,5);

  for (int i = 0; i < A.num_rows(); ++i){
    for (int j = 0; j < A.num_columns(); ++j){
      A[i][j] = (double) (i+j);
    }
  }
  for (int i = 0; i < B.num_rows(); ++i){
    for (int j = 0; j < B.num_columns(); ++j){
      B[i][j] = (double) 1 / (i + j + 1);
    }
  }
  for (int i = 0; i < C.num_rows(); ++i){
    for (int j = 0; j < C.num_columns(); ++j){
      C[i][j] = (double) i * j;
    }
  }
    
  Vector x(5);
  for (int i = 0; i < x.length(); ++i){
    x[i] = i;
  }
  Vector y(6);
  for (int i = 0; i < y.length(); ++i){
    y[i] = 1 - i;
  }

  double a = 1.5;

}
