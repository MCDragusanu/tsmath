#include "../include/lin_alg.h"
#include <sstream>





// Consider removing conio.h if not used for console input/output
// #include <conio.h>

// Function to find the degree of the highest non-zero coefficient in a polynomial Vector
size_t findHighestDegree(const Vector &polynomial, double tolerance = 1e-7)
{
    for (size_t i = 0; i < polynomial.dimension(); ++i)
    {
        if (std::abs(polynomial[i]) > tolerance)
        {
            return polynomial.dimension() - i - 1;
        }
    }
    
    return -1;
}

// Function to perform convolution of two Vectors
Vector TSA::convolution(const Vector &u, const Vector &v, double tolerance)
{
    size_t n = u.dimension();
    size_t m = v.dimension();

    // Result Vector with size n + m initialized to zeros
    Vector result(n + m, 0.0);

    // Perform element-wise multiplication and accumulation
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t k = 0; k < m; ++k)
        {
            result[i + k] += u[i] * v[k];
        }
    }

    // Trim leading zeros from the result
    size_t first = 0;
    while (std::abs(result[first]) < tolerance && first < result.dimension())
    {
        result.popFront();
    }

    // Consider removing trailing zero trimming if not needed
    result.popBack();

    return result;
}

// Function to construct the T Vector used in polynomial division
Vector constructT(const Vector &quotient, const Vector &divisor)
{
    size_t n = quotient.dimension() + divisor.dimension() - 1;
    size_t k = quotient.dimension();
    size_t l = divisor.dimension();

    // T Vector with size n initialized to zeros
    Vector t(n, 0.0);

    // Calculate element-wise product of quotient and flipped divisor
    // (Multiplying with flipped divisor is equivalent to convolution)
    for (size_t i = 0; i < k; ++i)
    {
        for (size_t j = 0; j < l; ++j)
        {
            t[n - (i + j + 1)] += quotient[k - i - 1] * divisor[l - j - 1];
        }
    }

    return t;
}

// Function to perform polynomial division
Vector TSA::polynomial_division(Vector &dividend, const Vector &divisor, double tolerance)
{

    size_t degreeDividend = findHighestDegree(dividend, tolerance);
    size_t degreeDivisor = findHighestDegree(divisor, tolerance);
    size_t degreeQuotient = degreeDividend - degreeDivisor;

    // Quotient Vector with size degreeQuotient + 1 initialized to zeros
    Vector quotient(degreeQuotient + 1, 0.0);

    DEBUG(std::cout << "Degree of dividend: " << degreeDividend << std::endl;
    std::cout << "Degree of divisor: " << degreeDivisor << std::endl;
    std::cout << "Degree of quotient: " << degreeQuotient << std::endl;);

    while (degreeDividend >= degreeDivisor)
    {
        // Calculate coefficient of the current term in the quotient
        double coefficient = dividend[dividend.dimension() - degreeDividend - 1] /
                             divisor[divisor.dimension() - 1 - degreeDivisor];
        quotient[quotient.dimension() - 1 - degreeQuotient] = coefficient;

        DEBUG(std::cout << "Coefficient: " << coefficient << std::endl;
        std::cout << "Current quotient: ";
        quotient.print(std::cout););

        // Construct temporary Vector with the coefficient at the appropriate position
        Vector temp(degreeQuotient + 1, 0.0);
        temp[temp.dimension() - degreeDividend + degreeDivisor -1] = coefficient;

        DEBUG(std::cout << "Temporary Vector: ";
        temp.print(std::cout);)

        // Calculate T Vector using constructed temporary Vector and divisor
        Vector t = constructT(temp, divisor);

        DEBUG(std::cout << "T Vector: ";
        t.print(std::cout);)
        dividend = dividend - t;

        degreeDividend--;
        degreeQuotient--;
        dividend.popFront();
    }
    return quotient;
}
