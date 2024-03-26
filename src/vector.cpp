#include "../include/Vector.h"

Vector::Vector(const std::vector<double> &other) : components(other){};

Vector::Vector(std::vector<double> &&other) : components(std::move(other)){};

Vector::Vector(const Vector &other) : components(std::vector<double>(other.components)){};

Vector &Vector::operator=(const Vector &other)
{
    // Check for self-assignment
    if (this == &other)
    {
        return *this;
    }

    // Resize current Vector if dimensions differ
    components.resize(other.components.size());

    // Perform element-wise copy
    for (size_t i = 0; i < components.size(); ++i)
    {
        components[i] = other.components[i];
    }

    return *this;
}
Vector::Vector(size_t dimension , double default_value):components(dimension , default_value){}
Vector::~Vector()
{
    components.clear();
}

Vector Vector::unitVector() const noexcept
{
    auto n = this->dimension();
    auto magnitude = this->magnitude();
    auto result = Vector(std::vector<double>(n, 0.0));
    if (std::abs(magnitude) >= 1e-7)
    {
        for (size_t i = 0; i < n; i++)
        {
            result.components[i] = components[i] / magnitude;
        }
    }
    return result;
}

Vector Vector::operator+(const Vector &other) const
{
    size_t n = (other.dimension() == this->dimension()) * this->dimension();
    auto result = std::vector<double>(n, 0.0);
    if (n == 0)
    {
        throw -1;
    }
    for (size_t i = 0; i < n; i++)
    {
        result[i] = this->components[i] + other.components[i];
    }
    return Vector(result);
}

Vector Vector::operator-(const Vector &other) const
{
    size_t n = (other.dimension() == this->dimension()) * this->dimension();
    auto result = std::vector<double>(n, 0.0);
    if (n == 0)
    {
        throw -1;
    }
    for (size_t i = 0; i < n; i++)
    {
        result[i] = this->components[i] - other.components[i];
    }
    return Vector(result);
}

Vector Vector::operator*(const double scalar) const
{
    size_t n = this->dimension();
    auto result = std::vector<double>(n, 0.0);
    for (size_t i = 0; i < n; i++)
    {
        result[i] = this->components[i] * scalar;
    }
    return Vector(result);
}

double Vector::operator*(const Vector &other) const
{
    size_t n = (other.dimension() == this->dimension()) * this->dimension();
    auto result = 0.0;
    if (n == 0)
    {
        throw -1;
    }
    for (size_t i = 0; i < n; i++)
    {
        result += this->components[i] * other.components[i];
    }
    return result;
}
double Vector::magnitude() const noexcept
{
    size_t n = this->dimension();
    double squared_sum = 0.0;
    for (size_t i = 0; i < n; i++)
    {
        squared_sum += components[i] * components[i];
    }
    return std::sqrt(squared_sum);
}
double &Vector::operator[](size_t index)
{

    bool is_valid_index = index >= 0 && index < dimension();
    /*if (!is_valid_index)
    {
        throw -1;
    }
   */
    return components[index];
}
const double &Vector::operator[](size_t index) const
{

    bool is_valid_index = index >= 0 && index < dimension();
    /*if (!is_valid_index)
    {
        throw -1;
    }*/

    return components.at(index);
}
size_t Vector::dimension() const noexcept
{
    return components.size();
}

void Vector::pushFront(double value)
{
    components.insert(components.begin(), value);
}
void Vector::pushBack(double value)
{
    components.insert(components.end(), value);
}
void Vector::popBack()
{
    components.pop_back();
}
void Vector::print(std::ostream &out) const noexcept
{
    out << "[";
    for (size_t i = 0; i < components.size(); i++)
    {
        out << components[i];
        if (i < components.size() - 1)
        {
            out << " ";
        }
    }
    out << "]\n";
}
void Vector::popFront()
{
    components.erase(components.begin());
}