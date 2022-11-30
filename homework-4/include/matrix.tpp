#include <iostream>
#include "vector.h"

template <typename T>
Matrix<T>::Matrix(int rows, int columns){
  _rows = rows;
  _columns = columns;
  
  _ptr = new T*[_rows];
  _ptr[0] = new T[_rows * _columns];
  for (int i = 1; i < _rows; ++i) {
    _ptr[i] = _ptr[0] + i * _columns;
  }
}

template <typename T>
Matrix<T>::Matrix(const Matrix & A) : Matrix(A.num_rows(), A.num_columns()) {
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _columns; ++j) {
      _ptr[i][j] = A[i][j];
    }
  }
}

template <typename T>
Matrix<T>::~Matrix(){
  free(_ptr[0]);    
  free(_ptr);
}

template <typename T>
T * Matrix<T>::operator[](const int i) const {
  return _ptr[i];
}

template <typename T>
void Matrix<T>::print(){
  std::cout << "Matrix = [" << std::endl;
  for (int i = 0; i < _rows; ++i){      
    for (int j = 0; j < _columns; ++j){      
      std::cout << _ptr[i][j] << " "; 
    }
    std::cout << std::endl;      
  }
  std::cout << "]" << std::endl;    
}

template <typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix & x){
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _columns; ++j) {
      this->_ptr[i][j] = x._ptr[i][j];
    }
  }
  return (*this);
}

// (double x) + y
Matrix<double> operator+(const double x, const Matrix<double> & y){
  Matrix<double> out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = x + y[i][j];
    }
  }
  return out;
}
// y + (double x)
Matrix<double> operator+(const Matrix<double> & y, const double x){
  return x + y;
}

// (double x) - y
Matrix<double> operator-(const double x, const Matrix<double> & y){
  Matrix<double> out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = x - y[i][j];
    }
  }
  return out;
}
// y - (double x)
Matrix<double> operator-(const Matrix<double> & y, const double x){
  Matrix<double> out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = y[i][j] - x;
    }
  }
  return out;
}

// (double x) * y
Matrix<double> operator*(const double x, const Matrix<double> & y){
  Matrix<double> out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = x * y[i][j];
    }
  }
  return out;
}
// y * (double x)
Matrix<double> operator*(const Matrix<double> & y, const double x){
  return x * y;
}

// (double x) / y
Matrix<double> operator/(const double x, const Matrix<double> & y){
  Matrix<double> out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = x / y[i][j];
    }
  }
  return out;
}
// y / (double x)
Matrix<double> operator/(const Matrix<double> & y, const double x){
  Matrix<double> out(y.num_rows(), y.num_columns());
  for (int i = 0; i < y.num_rows(); ++i){
    for (int j = 0; j < y.num_columns(); ++j) {
      out[i][j] = y[i][j] / x;
    }
  }
  return out;
}

Matrix<double> operator+(const Matrix<double> & x, const Matrix<double> & y){
  Matrix<double> out(y.num_rows(), y.num_columns());
  if (x.num_rows() == y.num_rows() && x.num_columns() == y.num_columns()){
    for (int i = 0; i < y.num_rows(); ++i){
      for (int j = 0; j < y.num_columns(); ++j){
        out[i][j] = x[i][j] + y[i][j];
      }
    }
  }else{
    throw std::domain_error("Error: Incompatible dimensions in Matrix + operator");
    //std::cout << "Incompatible dimensions in Matrix + operator: " << x.num_rows() << "x" << x.num_columns() <<" and " << y.num_rows() << "x" << y.num_columns() << std::endl;
    //return -1;
  }
  return out;
}

Matrix<double> operator-(const Matrix<double> & x, const Matrix<double> & y){
  Matrix<double> out(y.num_rows(), y.num_columns());
  if (x.num_rows() == y.num_rows() && x.num_columns() == y.num_columns()){
    for (int i = 0; i < y.num_rows(); ++i){
      for (int j = 0; j < y.num_columns(); ++j){
        out[i][j] = x[i][j] - y[i][j];
      }
    }
  }else{
    throw std::domain_error("Error: Incompatible dimensions in Matrix - operator");
    //std::cout << "Incompatible dimensions in Matrix - operator: " << x.num_rows() << "x" << x.num_columns() <<" and " << y.num_rows() << "x" << y.num_columns() << std::endl;
    //return -1;
  }
  return out;
}

Matrix<double> operator*(const Matrix<double> & x, const Matrix<double> & y){
  Matrix<double> out(x.num_rows(), y.num_columns());
  if (x.num_columns() == y.num_rows()){
    for (int i = 0; i < x.num_rows(); ++i){
      for (int j = 0; j < y.num_columns(); ++j){
        for (int k = 0; k < y.num_rows(); ++k){
          out[i][j] += x[i][k] * y[k][j];
        }
      }
    }
  }else{
    throw std::domain_error("Error: Incompatible dimensions in Vector * operator");
    //std::cout << "Incompatible dimensions in Matrix * operator: " << x.num_rows() << "x" << x.num_columns() <<" and " << y.num_rows() << "x" << y.num_columns() << std::endl;
    //return -1;
  }
  return out;
}

Vector<double> operator*(const Matrix<double> & x, const Vector<double> & y){
  Vector<double> out(x.num_rows());
  if (x.num_columns() == y.length()){
    for (int i = 0; i < x.num_rows(); ++i){
      for (int j = 0; j < y.length(); ++j){
        out[i] += x[i][j] * y[j];
      }
    }
  }else{
    throw std::domain_error("Error: Incompatible dimensions in Matrix-Vector * operator");
    //std::cout << "Incompatible dimensions in Matrix-Vector * operator: " << x.num_rows() << "x" << x.num_columns() <<" and " << y.length() << "x1" << std::endl;
    //return -1;
  }
  return out;
}