#include <iostream>
#include "matrix.h"

Matrix::Matrix(int rows, int columns){
  _rows = rows;
  _columns = columns;
  
  _ptr = new double*[_rows];
  _ptr[0] = new double[_rows * _columns];
  for (int i = 1; i < _rows; ++i) {
    _ptr[i] = _ptr[0] + i * _columns;
  }
}


Matrix::Matrix(const Matrix & A) : Matrix(A.num_rows(), A.num_columns()) {
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _columns; ++j) {
      _ptr[i][j] = A[i][j];
    }
  }
}

Matrix::~Matrix(){
  free(_ptr[0]);    
  free(_ptr);
}


double * Matrix::operator[](const int i) const {
  return _ptr[i];
}

void Matrix::print(){
  std::cout << "Matrix = [" << std::endl;
  for (int i = 0; i < _rows; ++i){      
    for (int j = 0; j < _columns; ++j){      
      std::cout << _ptr[i][j] << " "; 
    }
    std::cout << std::endl;      
  }
  std::cout << "]" << std::endl;    
}
