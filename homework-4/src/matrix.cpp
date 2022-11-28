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

Matrix & Matrix::operator=(const Matrix & x){
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _columns; ++j) {
      this->_ptr[i][j] = x._ptr[i][j];
    }
  }
  return (*this);
}

// (double x) + y
Matrix operator+(const double x, const Matrix & y){
  Matrix out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = x + y[i][j];
    }
  }
  return out;
}
// y + (double x)
Matrix operator+(const Matrix & y, const double x){
  return x + y;
}

// (double x) - y
Matrix operator-(const double x, const Matrix & y){
  Matrix out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = x - y[i][j];
    }
  }
  return out;
}
// y - (double x)
Matrix operator-(const Matrix & y, const double x){
  Matrix out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = y[i][j] - x;
    }
  }
  return out;
}

// (double x) * y
Matrix operator*(const double x, const Matrix & y){
  Matrix out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = x * y[i][j];
    }
  }
  return out;
}
// y * (double x)
Matrix operator*(const Matrix & y, const double x){
  return x * y;
}

// (double x) / y
Matrix operator/(const double x, const Matrix & y){
  Matrix out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = x / y[i][j];
    }
  }
  return out;
}
// y / (double x)
Matrix operator/(const Matrix & y, const double x){
  Matrix out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = y[i][j] / x;
    }
  }
  return out;
}

Matrix operator+(const Matrix & x, const Matrix & y){
  Matrix out(y.num_rows(), y.num_columns());
  if (x.num_rows() == y.num_rows() && x.num_columns() == y.num_columns()){
    for (int i = 0; i < y.num_rows(); ++i){
      for (int j = 0; j < y.num_columns(); ++j){
        out[i][j] = x[i][j] + y[i][j];
      }
    }
  }else{
    std::cout << "Incompatible dimensions in Matrix + operator: " << x.num_rows() << "x" << x.num_columns() <<" and " << y.num_rows() << "x" << y.num_columns() << std::endl;
    //return -1;
  }
  return out;
}

Matrix operator-(const Matrix & x, const Matrix & y){
  Matrix out(y.num_rows(), y.num_columns());
  if (x.num_rows() == y.num_rows() && x.num_columns() == y.num_columns()){
    for (int i = 0; i < y.num_rows(); ++i){
      for (int j = 0; j < y.num_columns(); ++j){
        out[i][j] = x[i][j] - y[i][j];
      }
    }
  }else{
    std::cout << "Incompatible dimensions in Matrix - operator: " << x.num_rows() << "x" << x.num_columns() <<" and " << y.num_rows() << "x" << y.num_columns() << std::endl;
    //return -1;
  }
  return out;
}

Matrix operator*(const Matrix & x, const Matrix & y){
  Matrix out(x.num_rows(), y.num_columns());
  if (x.num_columns() == y.num_rows()){
    for (int i = 0; i < x.num_rows(); ++i){
      for (int j = 0; j < y.num_columns(); ++j){
        for (int k = 0; k < y.num_rows(); ++k){
          out[i][j] += x[i][k] * y[k][j];
        }
      }
    }
  }else{
    std::cout << "Incompatible dimensions in Matrix * operator: " << x.num_rows() << "x" << x.num_columns() <<" and " << y.num_rows() << "x" << y.num_columns() << std::endl;
    //return -1;
  }
  return out;
}