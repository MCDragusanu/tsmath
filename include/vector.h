#pragma once

#include <vector>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#pragma once

#include <vector>
#include <cmath>
#include <iostream>

class Vector {
public:
  // Constructor using a constant reference to a std::vector<double>
  explicit Vector(const std::vector<double>& data);

  // Move constructor for efficient data transfer
  Vector(std::vector<double>&& data);

  // Constructor for creating a vector with a specific dimension and default value
  Vector(size_t dimension, double initialValue = 0.0);

  // Copy constructor for deep copying the data
  Vector(const Vector& other);

  // Copy assignment operator for deep copying the data
  Vector& operator=(const Vector& other);

  // Destructor to deallocate memory used by the Vector object
  ~Vector();

  // Calculates and returns a unit vector (magnitude 1) with the same direction
  Vector unitVector() const noexcept;

  // Vector addition (element-wise) with another Vector
  Vector operator+(const Vector& other) const;

  // Vector subtraction (element-wise) with another Vector
  Vector operator-(const Vector& other) const;

   
  // Scalar multiplication (multiply all elements by a scalar)
  Vector operator*(double scalar) const;

  // Dot product (scalar product) with another Vector
  double operator *(const Vector& other) const;

  // Calculates the magnitude (length) of the vector
  double magnitude() const noexcept;

  // Returns a reference to the element at a specific index (modification)
  double& operator[](size_t index);

  // Returns a const reference to the element at a specific index (read-only)
  const double& operator[](size_t index) const;

  // Returns the number of elements (dimension) of the vector
  size_t dimension() const noexcept;

  // Inserts a value at the beginning of the vector
  void pushFront(double value);

  // Inserts a value at the end of the vector
  void pushBack(double value);

  // Removes the last element from the vector
  void popBack();

  // Removes the first element from the vector
  void popFront();

  // Prints the vector content to an output stream
  void print(std::ostream& out) const noexcept;

private:
  std::vector<double> components;
};
