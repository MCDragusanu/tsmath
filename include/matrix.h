
#pragma once

#include "vector.h"
#include <iostream>

class MATRIX
{
public:
  // Constructor that takes a constant reference to a std::vector<float>. (Consider potential type mismatch)
  MATRIX(const std::vector<std::vector<double>> &buffer);

  // Move constructor that efficiently transfers ownership of data from a temporary std::vector<double>.
  MATRIX(std::vector<std::vector<double>> &&buffer);

  // Copy constructor that creates a deep copy of the data to avoid unintended side effects.
  MATRIX(const MATRIX &other);

  // Copy assignment operator that performs a deep copy of the data.
  MATRIX &operator=(MATRIX &other);

  // Destructor deallocates any memory used by the MATRIX object.
  ~MATRIX();

  // Returns a reference to the row at a specific index (allows modification).
  VECTOR& get_row(int row_index);

  // Returns a const reference to the row at a specific index (read-only access).
  const VECTOR& get_row_const(int row_index) const;

  // Matrix multiplication. Performs matrix multiplication with another MATRIX object.
  MATRIX operator*(const MATRIX &other) const;

  // Scalar multiplication. Multiplies all elements of the matrix by a scalar value.
  MATRIX operator*(double scalar) const noexcept;

  // Matrix addition. Performs element-wise addition with another MATRIX object.
  MATRIX operator+(const MATRIX &other) const;

  // Matrix subtraction. Performs element-wise subtraction with another MATRIX object.
  MATRIX operator-(const MATRIX &other) const;

  // Transposes the matrix, swapping rows and columns.
  MATRIX transpose() const noexcept;

  // Returns a specific column of the matrix as a VECTOR object.
  VECTOR& get_column(int index);

  // Returns a specific column of the matrix as a VECTOR object.
  const VECTOR& get_column_const(int index) const;

  // Returns the number of columns in the matrix.
  size_t getColumnCount() const noexcept;

  // Returns the number of rows in the matrix.
  size_t getRowCount() const noexcept;

  void print_matrix(std::ostream& buff) const noexcept;

protected:
  // Internal data storage for the matrix elements.
  std::vector<std::vector<double>> m_components;

  // Dimensions of the matrix (number of rows and columns).
  size_t column_count, row_count;
};