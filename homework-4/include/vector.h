#ifndef _VECTOR
#define _VECTOR

class Vector{
public:
  Vector(const int length);
  Vector(const Vector & x);
  ~Vector();
  
  int length(void) const{ return length_; }  
  void print();

  // for indexing (e.g., x[i] = 1.0);  
  double & operator[](const int i) const;
  
  Vector & operator=(const Vector & x);
  
private:
  int length_;
  double * ptr_;
};

Vector operator+(const double x, const Vector & y);
Vector operator+(const Vector & y, const double x);
Vector operator+(const Vector & x, const Vector & y);

Vector operator-(const double x, const Vector & y);
Vector operator-(const Vector & y, const double x);
Vector operator-(const Vector & x, const Vector & y);

Vector operator*(const double x, const Vector & y);
Vector operator*(const Vector & y, const double x);
double operator*(const Vector & x, const Vector & y);

Vector operator/(const double x, const Vector & y);
Vector operator/(const Vector & y, const double x);

#endif
