#include "../include/vector.h"

VECTOR::VECTOR(const std::vector<double> &other) : m_components(other){};

VECTOR::VECTOR(std::vector<double> &&other) : m_components(std::move(other)){};

VECTOR::VECTOR(const VECTOR &other) : m_components(std::vector<double>(other.m_components)){};

VECTOR& VECTOR::operator=(const VECTOR &other)
{
  // Check for self-assignment
  if (this == &other) {
    return *this;
  }

  // Resize current vector if dimensions differ
  m_components.resize(other.m_components.size());

  // Perform element-wise copy
  for (size_t i = 0; i < m_components.size(); ++i) {
    m_components[i] = other.m_components[i];
  }

  return *this;
}

VECTOR::~VECTOR()
{
    m_components.clear();
}

VECTOR VECTOR::unit_vector() const noexcept
{
    auto n = this->dimension();
    auto magnitude = this->magnitude();
    auto result = VECTOR(std::vector<double>(n, 0.0));
    if (std::abs(magnitude) >= 1e-7)
    {
        for (size_t i = 0; i < n; i++)
        {
            result.m_components[i] = m_components[i] / magnitude;
        }
    }
    return result;
}

VECTOR VECTOR::operator+(const VECTOR &other) const
{
    size_t n = (other.dimension() == this->dimension()) * this->dimension();
    auto result = std::vector<double>(n, 0.0);
    if (n == 0)
    {
        throw -1;
    }
    for (size_t i = 0; i < n; i++)
    {
        result[i] = this->m_components[i] + other.m_components[i];
    }
    return VECTOR(result);
}

VECTOR VECTOR::operator-(const VECTOR &other) const
{
    size_t n = (other.dimension() == this->dimension()) * this->dimension();
    auto result = std::vector<double>(n, 0.0);
    if (n == 0)
    {
        throw -1;
    }
    for (size_t i = 0; i < n; i++)
    {
        result[i] = this->m_components[i] - other.m_components[i];
    }
    return VECTOR(result);
}

VECTOR VECTOR::operator*(const double scalar) const
{
    size_t n = this->dimension();
    auto result = std::vector<double>(n, 0.0);
    for (size_t i = 0; i < n; i++)
    {
        result[i] = this->m_components[i] * scalar;
    }
    return VECTOR(result);
}

double VECTOR::operator*(const VECTOR &other) const
{
    size_t n = (other.dimension() == this->dimension()) * this->dimension();
    auto result = 0.0;
    if (n == 0)
    {
        throw -1;
    }
    for (size_t i = 0; i < n; i++)
    {
        result += this->m_components[i] * other.m_components[i];
    }
    return result;
}
double VECTOR::magnitude() const noexcept
{
    size_t n = this->dimension();
    double squared_sum = 0.0;
    for (size_t i = 0; i < n; i++)
    {
        squared_sum += m_components[i] * m_components[i];
    }
    return std::sqrt(squared_sum);
}
double &VECTOR::operator[](size_t index)
{
    bool is_valid_index = index > -1 && index < dimension();
    if (!is_valid_index)
    {
        throw -1;
    }
    return m_components[index];
}
const double &VECTOR::operator[](size_t index) const
{
    bool is_valid_index = index > -1 && index < dimension();
    if (!is_valid_index)
    {
        throw -1;
    }
    return m_components.at(index);
}
size_t VECTOR::dimension() const noexcept
{
    return m_components.size();
}