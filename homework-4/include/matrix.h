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
 private:
  int _rows;
  int _columns;
  double ** _ptr;
};

#endif
