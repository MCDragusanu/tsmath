#include "../include/matrix.h"
#include <conio.h>
MATRIX::MATRIX(const std::vector<std::vector<double>> &buffer) : m_components(buffer)
{
    // Set the row count of the matrix
    row_count = m_components.size();
    // Set the column count of the matrix (0 if buffer is empty)
    column_count = m_components.size() == 0 ? 0 : buffer[0].size();
}

MATRIX::MATRIX(std::vector<std::vector<double>> &&buffer) : m_components(buffer)
{
    // Set the row count of the matrix
    row_count = m_components.size();
    // Set the column count of the matrix (0 if buffer is empty)
    column_count = m_components.size() == 0 ? 0 : buffer[0].size();
}

MATRIX::MATRIX(const MATRIX &other)
{
    // Initialize the matrix components with appropriate dimensions
    m_components = std::vector<std::vector<double>>(
        other.getRowCount(), std::vector<double>(other.getRowCount() == 0 ? 0 : other.m_components[0].size(), 0.0));

    row_count = m_components.size();

    column_count = m_components.size() == 0 ? 0 : m_components[0].size();

    // Perform element-wise copy from 'other' matrix to the new matrix
    for (size_t i = 0; i < other.getRowCount(); i++)
    {
        for (size_t j = 0; j < other.getColumnCount(); j++)
        {
            m_components[i][j] = other.m_components[i][j];
        }
    }
}

MATRIX &MATRIX::operator=(MATRIX &other)
{
    // Check for self-assignment
    if (this == &other)
    {
        return *this;
    }

    size_t n = other.m_components.size();
    size_t m = n == 0 ? 0 : other.m_components[0].size();
    // Resize current vector if dimensions differ
    m_components.resize(n);

    // Perform element-wise copy
    for (size_t i = 0; i < n; ++i)
    {
        m_components[i].resize(m);
        for (size_t j = 0; j < m; j++)
        {
            m_components[i][j] = other.m_components[i][j];
        }
    }

    return *this;
}

MATRIX::~MATRIX()
{
    m_components.clear();
}

VECTOR &MATRIX::get_row(int row_index)
{
    size_t n = m_components.size();
    bool index_is_valid = std::abs(row_index) < n;

    if (!index_is_valid)
    {
        throw -1;
    }

    auto result = std::vector<double>(m_components.at(row_index <0 ? n+row_index : row_index));

    return *new VECTOR(std::move(result));
}

const VECTOR &MATRIX::get_row_const(int row_index) const
{
    size_t n = m_components.size();
    bool index_is_valid = std::abs(row_index) < n;

    if (!index_is_valid)
    {
        throw -1;
    }

    auto result = std::vector<double>(m_components.at(row_index <0 ? n+row_index : row_index));

    return * new VECTOR(std::move(result));
}

MATRIX MATRIX::operator*(const MATRIX &other) const
{
    // Get dimensions of both matrices
    size_t nA = this->row_count, mA = this->column_count, nB = other.row_count, mB = other.column_count;

    // Check if matrices can be multiplied
    if (mA != nB)
    {
        throw -1;
    }

    // Initialize result matrix with appropriate dimensions
    MATRIX C = MATRIX(std::vector<std::vector<double>>(nA, std::vector<double>(mB, 0.0)));

    // Perform matrix multiplication
    for (size_t k = 0; k < nA; k++)
    {
        for (size_t i = 0; i < mA; i++)
        {
            for (size_t j = 0; j < nB; j++)
            {
                C.m_components[k][i] += (this->m_components[k][i] * other.m_components[j][k]);
            }
        }
    }
    return C;
}

MATRIX MATRIX::operator*(double scalar) const noexcept
{
    size_t nA = this->row_count, mA = this->column_count;

    // Initialize result matrix with appropriate dimensions
    MATRIX C = MATRIX(std::vector<std::vector<double>>(nA, std::vector<double>(mA, 0.0)));

    // Perform scalar multiplication
    for (size_t k = 0; k < nA; k++)
    {
        for (size_t i = 0; i < mA; i++)
        {
            C.m_components[k][i] = (this->m_components[k][i] * scalar);
        }
    }
    return C;
}

MATRIX MATRIX::operator+(const MATRIX &other) const
{
    size_t nA = this->row_count, mA = this->column_count;

    // Check if matrices have the same dimensions
    if (nA != other.getRowCount() || mA != other.getColumnCount())
    {
        throw -1;
    }

    // Initialize result matrix with appropriate dimensions
    MATRIX C = MATRIX(std::vector<std::vector<double>>(nA, std::vector<double>(mA, 0.0)));

    // Perform matrix addition
    for (size_t k = 0; k < nA; k++)
    {
        for (size_t i = 0; i < mA; i++)
        {
            C.m_components[k][i] = (this->m_components[k][i] + other.m_components[k][i]);
        }
    }
    return C;
}

MATRIX MATRIX::operator-(const MATRIX &other) const
{
    size_t nA = this->row_count, mA = this->column_count;

    // Check if matrices have the same dimensions
    if (nA != other.getRowCount() || mA != other.getColumnCount())
    {
        throw -1;
    }

    // Initialize result matrix with appropriate dimensions
    MATRIX C = MATRIX(std::vector<std::vector<double>>(nA, std::vector<double>(mA, 0.0)));

    // Perform matrix subtraction
    for (size_t k = 0; k < nA; k++)
    {
        for (size_t i = 0; i < mA; i++)
        {
            C.m_components[k][i] = (this->m_components[k][i] - other.m_components[k][i]);
        }
    }
    return C;
}

MATRIX MATRIX::transpose() const noexcept
{

    size_t nA = this->row_count, mA = this->column_count;

    // Initialize result matrix with appropriate dimensions for transposition
    MATRIX C = MATRIX(std::vector<std::vector<double>>(mA, std::vector<double>(nA, 0.0)));

    // Perform matrix transposition
    for (size_t k = 0; k < nA; k++)
    {
        for (size_t i = 0; i < mA; i++)
        {
            C.m_components[k][i] = this->m_components[i][k];
        }
    }
    return C;
}

VECTOR &MATRIX::get_column(int index)
{
    size_t m = column_count;
    size_t n = row_count;
    bool index_is_valid = abs( index  ) < m;

    std::cout << m << " " << n << "\n";

    if (!index_is_valid)
    {
        throw -1;
    }

    auto* result =  new std::vector<double>(n, 0.0);

    this->print_matrix(std::cout);
    for (size_t i = 0; i < n; i++)
    {
        
        (*result)[i] = m_components[i][index < 0 ? m+index : index];
        //std::cout <<result[i]<<"\n";
    }

    auto vector = new VECTOR(std::move(*result));
   
    return *vector;
}

const VECTOR &MATRIX::get_column_const(int index) const
{
    size_t m = column_count;
    size_t n = row_count;
    bool index_is_valid =abs(index) < m;
    if (!index_is_valid)
    {
        throw -1;
    }

    auto* result =  new std::vector<double>(n, 0.0);

    
    for (size_t i = 0; i < n; i++)
    {
        
        (*result)[i] = m_components.at(i).at( index <0 ? m+index : index);
        //std::cout <<result[i]<<"\n";
    }

    auto vector = new VECTOR(std::move(*result));
  
    return *vector;
}

size_t MATRIX::getColumnCount() const noexcept
{
    return column_count;
}

size_t MATRIX::getRowCount() const noexcept
{
    return row_count;
}
void MATRIX::print_matrix(std::ostream &buff) const noexcept
{
    for (const auto &row : m_components)
    {
        buff << "[";
        for (const auto &value : row)
        {
            buff << value << " ";
        }
        buff << "]\n";
    }
}
