#include <iostream>

// constructor
template <typename T>
Vector<T>::Vector(const int length) {
  length_ = length;
  ptr_ = (T*) malloc(sizeof(T) * length_);
  for (int i = 0; i < length_; ++i){
    ptr_[i] = (T) 0.0;
  }
}

// copy constructor
template <typename T>
Vector<T>::Vector(const Vector & x){
  length_ = x.length();
  ptr_ = new T[length_];
  for (int i = 0; i < length_; ++i){
    ptr_[i] = x[i];
  }
}

// destructor
template <typename T>
Vector<T>::~Vector(){    
  free(ptr_);
  ptr_ = nullptr; // C++ can use nullptr instead of NULL
}

template <typename T>
void Vector<T>::print(){
  std::cout << "Vector = [" << std::endl;
  for (int i = 0; i < length_; ++i){
    std::cout << ptr_[i] << std::endl;
  }
  std::cout << "]" << std::endl;
}

template <typename T>
T & Vector<T>::operator[](const int i) const {
  return ptr_[i];
}

// overload Vector y = x;
template <typename T>
Vector<T> & Vector<T>::operator=(const Vector & x){
  for (int i = 0; i < length_; ++i){
    this->ptr_[i] = x.ptr_[i];
  }
  return (*this);
}

// (double x) + y
Vector<double> operator+(const double x, const Vector<double> & y){
  Vector<double> out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = x + y[i];
  }
  return out;
}
// y + (double x)
Vector<double> operator+(const Vector<double> & y, const double x){
  return x + y;
}

// (double x) - y
Vector<double> operator-(const double x, const Vector<double> & y){
  Vector<double> out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = x - y[i];
  }
  return out;
}
// y - (double x)
Vector<double> operator-(const Vector<double> & y, const double x){
  Vector<double> out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = y[i] - x;
  }
  return out;
}

// (double x) * y
Vector<double> operator*(const double x, const Vector<double> & y){
  Vector<double> out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = x * y[i];
  }
  return out;
}
// y * (double x)
Vector<double> operator*(const Vector<double> & y, const double x){
  return x * y;
}

// (double x) / y
Vector<double> operator/(const double x, const Vector<double> & y){
  Vector<double> out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = x / y[i];
  }
  return out;
}
// y / (double x)
Vector<double> operator/(const Vector<double> & y, const double x){
  Vector<double> out(y.length());
  for (int i = 0; i < y.length(); ++i){
    out[i] = y[i] / x;
  }
  return out;
}

Vector<double> operator+(const Vector<double> & x, const Vector<double> & y){
  Vector<double> out(x.length());
  if (x.length() == y.length()){
    for (int i = 0; i < x.length(); ++i){
      out[i] = x[i] + y[i];
    }
  }else{
    throw std::domain_error("Error: Incompatible dimensions in Vector + operator");
    //std::cout << "Incompatible dimensions in Vector + operator: " << x.length() << " and " << y.length() << std::endl;
    //return -1;
  }
  return out;
}

Vector<double> operator-(const Vector<double> & x, const Vector<double> & y){
  Vector<double> out(x.length());
  if (x.length() == y.length()){
    for (int i = 0; i < x.length(); ++i){
      out[i] = x[i] - y[i];
    }
  }else{
    throw std::domain_error("Error: Incompatible dimensions in Vector - operator");
    //std::cout << "Incompatible dimensions in Vector - operator: " << x.length() << " and " << y.length() << std::endl;
    //return -1;
  }
  return out;
}