#ifndef _VECTOR
#define _VECTOR

template <typename T>
class Vector{
public:
  Vector(const int length);
  Vector(const Vector & x);
  ~Vector();
  
  int length(void) const{ return length_; }  
  void print();

  // for indexing (e.g., x[i] = 1.0);  
  T & operator[](const int i) const;
  
  Vector & operator=(const Vector & x);
  
private:
  int length_;
  T * ptr_;
};

#include "vector.tpp"

/*
Vector<double> operator+(const double x, const Vector<double> & y);
Vector<double> operator+(const Vector<double> & y, const double x);
Vector<double> operator+(const Vector<double> & x, const Vector<double> & y);

Vector<double> operator-(const double x, const Vector<double> & y);
Vector<double> operator-(const Vector<double> & y, const double x);
Vector<double> operator-(const Vector<double> & x, const Vector<double> & y);

Vector<double> operator*(const double x, const Vector<double> & y);
Vector<double> operator*(const Vector<double> & y, const double x);
double operator*(const Vector<double> & x, const Vector<double> & y);

Vector<double> operator/(const double x, const Vector<double> & y);
Vector<double> operator/(const Vector<double> & y, const double x);
*/

#endif
