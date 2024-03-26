#include "../include/Vector.h"

Vector::Vector(const std::vector<double>& other) : components(other) {}

Vector::Vector(std::vector<double>&& other) : components(std::move(other)) {}

Vector::Vector(const Vector& other) : components(other.components) {}

Vector& Vector::operator=(const Vector& other) {
  if (this == &other) {
    return *this;
  }

  components.resize(other.components.size());
  for (size_t i = 0; i < components.size(); ++i) {
    components[i] = other.components[i];
  }
  return *this;
}

Vector::Vector(size_t dimension, double default_value) : components(dimension, default_value) {}

Vector::~Vector() = default;  // Use the default destructor

Vector Vector::unitVector() const noexcept {
  auto n = dimension();
  auto magnitude = this->magnitude();
  if (std::abs(magnitude) < 1e-7) {
    // Handle near-zero magnitude case (return zero vector)
    return Vector(n, 0.0);
  }

  Vector result(n, 0.0);
  for (size_t i = 0; i < n; ++i) {
    result.components[i] = components[i] / magnitude;
  }
  return result;
}

Vector Vector::operator+(const Vector& other) const {
  if (dimension() != other.dimension()) {
    throw std::invalid_argument("Vectors must have the same dimension for addition");
  }

  size_t n = dimension();
  std::vector<double> result(n);
  for (size_t i = 0; i < n; ++i) {
    result[i] = components[i] + other.components[i];
  }
  return Vector(result);
}

Vector Vector::operator-(const Vector& other) const {
  // Reuse logic from addition with appropriate error handling
  return *this + ( other * -1);
}

Vector Vector::operator*(const double scalar) const {
  size_t n = dimension();
  std::vector<double> result(n);
  for (size_t i = 0; i < n; ++i) {
    result[i] = components[i] * scalar;
  }
  return Vector(result);
}

double Vector::operator*(const Vector& other) const {
  if (dimension() != other.dimension()) {
    throw std::invalid_argument("Vectors must have the same dimension for dot product");
  }

  size_t n = dimension();
  double result = 0.0;
  for (size_t i = 0; i < n; ++i) {
    result += components[i] * other.components[i];
  }
  return result;
}

double Vector::magnitude() const noexcept {
  size_t n = dimension();
  double squared_sum = 0.0;
  for (size_t i = 0; i < n; ++i) {
    squared_sum += components[i] * components[i];
  }
  return std::sqrt(squared_sum);
}

double& Vector::operator[](size_t index) {
  if (index < 0 || index >= dimension()) {
    throw std::out_of_range("Index out of bounds");
  }
  return components[index];
}

const double& Vector::operator[](size_t index) const {
  if (index < 0 || index >= dimension()) {
    throw std::out_of_range("Index out of bounds");
  }
  return components.at(index);
}

size_t Vector::dimension() const noexcept {
  return components.size();
}

void Vector::pushFront(double value) {
  components.insert(components.begin(), value);
}

void Vector::pushBack(double value) {
  components.push_back(value);
}

void Vector::popBack() {
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