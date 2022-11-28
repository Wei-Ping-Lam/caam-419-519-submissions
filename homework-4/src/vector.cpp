#include <iostream>
#include "vector.h"

// constructor
Vector::Vector(const int length) {
  length_ = length;
  ptr_ = (double*) malloc(sizeof(double) * length_);
  for (int i = 0; i < length_; ++i){
    ptr_[i] = 0.0;
  }
}

// copy constructor
Vector::Vector(const Vector & x){
  length_ = x.length();
  ptr_ = new double[length_];
  for (int i = 0; i < length_; ++i){
    ptr_[i] = x[i];
  }
}

// destructor
Vector::~Vector(){    
  free(ptr_);
  ptr_ = nullptr; // C++ can use nullptr instead of NULL
}

void Vector::print(){
  std::cout << "Vector = [" << std::endl;
  for (int i = 0; i < length_; ++i){
    std::cout << ptr_[i] << std::endl;
  }
  std::cout << "]" << std::endl;
}

double & Vector::operator[](const int i) const {
  return ptr_[i];
}

// overload Vector y = x;
Vector & Vector::operator=(const Vector & x){
  for (int i = 0; i < length_; ++i){
    this->ptr_[i] = x.ptr_[i];
  }
  return (*this);
}

// (double x) + y
Vector operator+(const double x, const Vector & y){
  Vector out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = x + y[i];
  }
  return out;
}
// y + (double x)
Vector operator+(const Vector & y, const double x){
  return x + y;
}

// (double x) - y
Vector operator-(const double x, const Vector & y){
  Vector out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = x - y[i];
  }
  return out;
}
// y - (double x)
Vector operator-(const Vector & y, const double x){
  Vector out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = y[i] - x;
  }
  return out;
}

// (double x) * y
Vector operator*(const double x, const Vector & y){
  Vector out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = x * y[i];
  }
  return out;
}
// y * (double x)
Vector operator*(const Vector & y, const double x){
  return x * y;
}

// (double x) / y
Vector operator/(const double x, const Vector & y){
  Vector out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = x / y[i];
  }
  return out;
}
// y / (double x)
Vector operator/(const Vector & y, const double x){
  Vector out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = y[i] / x;
  }
  return out;
}

Vector operator+(const Vector & x, const Vector & y){
  Vector out(x.length());
  if (x.length() == y.length()){
    for (int i = 0; i < x.length(); ++i){
      out[i] = x[i] + y[i];
    }
  }else{
    std::cout << "Incompatible dimensions in Vector + operator: " << x.length() << " and " << y.length() << std::endl;
    return -1;
  }
  return out;
}

Vector operator-(const Vector & x, const Vector & y){
  Vector out(x.length());
  if (x.length() == y.length()){
    for (int i = 0; i < x.length(); ++i){
      out[i] = x[i] - y[i];
    }
  }else{
    std::cout << "Incompatible dimensions in Vector - operator: " << x.length() << " and " << y.length() << std::endl;
    return -1;
  }
  return out;
}

double operator*(const Vector & x, const Vector & y){
  double out = 0.0;
  if (x.length() == y.length()){
    for (int i = 0; i < x.length(); ++i){
      out += (x[i] * y[i]);
    }
  }else{
    std::cout << "Incompatible dimensions in Vector * operator: " << x.length() << " and " << y.length() << std::endl;
    return -1;
  }
  return out;
}