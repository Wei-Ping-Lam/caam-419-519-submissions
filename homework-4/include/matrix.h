#ifndef _MATRIX
#define _MATRIX

template <typename T>
class Matrix{
 public:
  Matrix(int rows, int columns);
  Matrix(const Matrix & A);  
  ~Matrix();
  
  int num_rows() const { return _rows; };
  int num_columns() const { return _columns; };
  T * operator[](const int i) const;

  void print();
  
  Matrix & operator=(const Matrix & x);
  
 private:
  int _rows;
  int _columns;
  T ** _ptr;
};

#include "matrix.tpp"

/*
Matrix<double> operator+(const double x, const Matrix<double> & y);
Matrix<double> operator+(const Matrix<double> & y, const double x);
Matrix<double> operator+(const Matrix<double> & x, const Matrix<double> & y);

Matrix<double> operator-(const double x, const Matrix<double> & y);
Matrix<double> operator-(const Matrix<double> & y, const double x);
Matrix<double> operator-(const Matrix<double> & x, const Matrix<double> & y);

Matrix<double> operator*(const double x, const Matrix<double> & y);
Matrix<double> operator*(const Matrix<double> & y, const double x);
Matrix<double> operator*(const Matrix<double> & x, const Matrix<double> & y);

Matrix<double> operator/(const double x, const Matrix<double> & y);
Matrix<double> operator/(const Matrix<double> & y, const double x);
*/

#endif
