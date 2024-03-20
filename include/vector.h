#pragma once

#include <vector>
#include <cmath>
#include <stdlib.h>
#include <iostream>
class VECTOR
{
public:
  // Constructor that takes a constant reference to a std::vector<double>.
  VECTOR(const std::vector<double>& buffer);
  // Move constructor that efficiently transfers ownership of data from a temporary std::vector.
  VECTOR(std::vector<double>&& buffer);

  // Copy constructor that creates a deep copy of the data to avoid unintended side effects.
  VECTOR(const VECTOR& other);

  // Copy assignment operator that performs a deep copy of the data.
  VECTOR& operator=(const VECTOR& other);

  // Destructor deallocates any memory used by the VECTOR object.
  ~VECTOR();

  // Calculates and returns a unit vector (vector with magnitude 1) in the same direction as this vector.
  VECTOR unit_vector() const noexcept;

  // Vector addition. Performs element-wise addition with another VECTOR object.
  VECTOR operator+(const VECTOR& other) const;

  // Vector subtraction. Performs element-wise subtraction with another VECTOR object.
  VECTOR operator-(const VECTOR& other) const ;

  // Scalar multiplication. Multiplies all elements of the vector by a scalar value.
  VECTOR operator*(double scalar) const ;

  // Dot product (scalar product). Calculates the dot product between this vector and another VECTOR.
  double operator*(const VECTOR& other) const ;

  // Calculates the magnitude (length) of the vector.
  double magnitude() const noexcept;

  // Returns a reference to the element at a specific index (allows modification).
  double& operator[](size_t index);

  // Returns a const reference to the element at a specific index (read-only access).
  const double& operator[](size_t index) const;

  // Returns the number of elements (dimension) of the vector.
  size_t dimension() const noexcept;

  void print_vector(std::ostream& out) const noexcept{
        out << "[";
        for(size_t i = 0 ; i < m_components.size() ; i++){
           out << m_components[i];
           if(i < m_components.size() -1){
            out << " ";
           }
        }
        out<<"]\n";
  }
protected:
    std::vector<double> m_components;
};