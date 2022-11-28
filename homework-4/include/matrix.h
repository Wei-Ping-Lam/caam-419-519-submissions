#ifndef _MATRIX
#define _MATRIX

class Matrix{
 public:
  Matrix(int rows, int columns);
  Matrix(const Matrix & A);  
  ~Matrix();
  
  int num_rows() const { return _rows; };
  int num_columns() const { return _columns; };
  double * operator[](const int i) const;

  void print();
  
  Matrix & operator=(const Matrix & x);
  
 private:
  int _rows;
  int _columns;
  double ** _ptr;
};

Matrix operator+(const double x, const Matrix & y);
Matrix operator+(const Matrix & y, const double x);
Matrix operator+(const Matrix & x, const Matrix & y);

Matrix operator-(const double x, const Matrix & y);
Matrix operator-(const Matrix & y, const double x);
Matrix operator-(const Matrix & x, const Matrix & y);

Matrix operator*(const double x, const Matrix & y);
Matrix operator*(const Matrix & y, const double x);
Matrix operator*(const Matrix & x, const Matrix & y);

Matrix operator/(const double x, const Matrix & y);
Matrix operator/(const Matrix & y, const double x);


#endif
