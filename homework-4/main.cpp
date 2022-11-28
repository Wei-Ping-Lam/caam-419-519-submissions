#include <iostream>
#include "vector.h"
#include "matrix.h"

Vector operator*(const Matrix & x, const Vector & y){
  Vector out(x.num_rows());
  if (x.num_columns() == y.length()){
    for (int i = 0; i < x.num_rows(); ++i){
      for (int j = 0; j < y.length(); ++j){
        out[i] += x[i][j] * y[j];
      }
    }
  }else{
    std::cout << "Incompatible dimensions in Matrix-Vector * operator: " << x.num_rows() << "x" << x.num_columns() <<" and " << y.length() << "x1" << std::endl;
    return -1;
  }
  return out;
}

Matrix operator*(const Vector & x, const Matrix & y){
  Matrix out(x.length(), y.num_columns());
  if (y.num_rows() == 1){
    for (int i = 0; i < x.length(); ++i){
      for (int j = 0; j < y.num_columns(); ++j){
        out[i][j] = x[i] * y[0][j];
      }
    }
  }else{
    std::cout << "Incompatible dimensions in Vector-Matrix * operator: " << x.length() << "x1" << " and " << y.num_rows() << "x" << y.num_columns() << std::endl;
    //return -1;
  }
  return out;
}
   
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
  
  A.print();
  B.print();
  C.print();
  x.print();
  y.print();
  std::cout << "a = " << a << std::endl;
  
  Vector z = (A*B + C) * x + a * y;
  z.print();
  z = 3*z - (y - 1) / 2 + 0.5;
  z.print();
}
