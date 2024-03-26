
#pragma once
#include <stdlib.h>
#include "matrix.h"
#include "macros.h"

// Namespace for solving linear systems
namespace lin_systems {
  // Solves a lower triangular linear system using forward substitution.
  Vector ltris(const MATRIX &A, const Vector &b);

  // Solves an upper triangular linear system using backward substitution.
  Vector utris(const MATRIX &A, const Vector &b);

  // Solves a linear system using Gaussian elimination with partial pivoting.
  Vector gpp(const MATRIX &A, const Vector &b);

  // Computes the inverse of a square matrix (if it exists).
  MATRIX inverse(const MATRIX& A);
}

// Namespace for matrix factorization techniques
namespace factorization {
  // Performs LU decomposition of a matrix (Doolittle factorization).
  std::pair<MATRIX, MATRIX> doolittle(const MATRIX &A);

  // Performs LU decomposition of a matrix (Crout factorization).
  std::pair<MATRIX, MATRIX> crout(const MATRIX &A);

  // Computes the QR decomposition of a matrix.
  std::pair<MATRIX, MATRIX> qr(const MATRIX &A);
}

// Namespace for creating Householder and Givens reflectors
namespace reflectors {
  // Creates a Householder reflection matrix.
  MATRIX mk(const MATRIX& A, size_t i, size_t k);

  // Constructs a Householder reflector.
  MATRIX householder(const MATRIX &A, size_t i, size_t k);

  // Constructs a Givens reflector.
  MATRIX givens(const MATRIX &A, size_t i, size_t k);
}

// Namespace for solving least squares problems
namespace lst_sqr {
  // Solves a least squares problem using the least squares method.
  Vector lst_sqrs(const MATRIX& A, const Vector& b);
}

// Namespace for eigenvalue and eigenVector computations
namespace eigen {
  // Performs Schur factorization of a matrix.
  MATRIX shurr_factorization(const MATRIX& A);

  // Computes the eigenVectors of a matrix with eigenVectors as columns.
  MATRIX eigen_Vectors(const MATRIX& A);  

  // Calculates the eigenvalues of a matrix.
  Vector eigen_values(const MATRIX& A);
  
  // Computes the determinant of a square matrix by using svd.
  double determinant(const MATRIX& A);
}

// Namespace for singular value decomposition (SVD)
namespace svd {
  // Computes the singular value decomposition (SVD) of a matrix.
  std::vector<MATRIX> svd(const MATRIX& A);

  // Calculates the pseudo-inverse of a matrix.
  MATRIX pseudo_inverse(const MATRIX& A);

  
}

namespace TSA {
  Vector polynomial_division(Vector& p , const Vector& q ,   double tolerance = 1e-7);
  Vector convolution(const Vector& u , const Vector& v, double tolerance = 1e-7);
}