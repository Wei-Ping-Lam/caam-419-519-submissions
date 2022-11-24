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

private:
  int length_;
  double * ptr_;
};

#endif
