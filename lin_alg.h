#include "vector.h"
#include "matrix.h"


// Namespace for solving linear systems
namespace lin_systems {
  // Solves a lower triangular linear system using forward substitution.
  VECTOR ltris(const MATRIX &A, const VECTOR &b);

  // Solves an upper triangular linear system using backward substitution.
  VECTOR utris(const MATRIX &A, const VECTOR &b);

  // Solves a linear system using Gaussian elimination with partial pivoting.
  VECTOR gpp(const MATRIX &A, const VECTOR &b);

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
  VECTOR lst_sqrs(const MATRIX& A, const VECTOR& b);
}

// Namespace for eigenvalue and eigenvector computations
namespace eigen {
  // Performs Schur factorization of a matrix.
  MATRIX shurr_factorization(const MATRIX& A);

  // Computes the eigenvectors of a matrix with eigenvectors as columns.
  MATRIX eigen_vectors(const MATRIX& A);  

  // Calculates the eigenvalues of a matrix.
  VECTOR eigen_values(const MATRIX& A);
  
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

