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

