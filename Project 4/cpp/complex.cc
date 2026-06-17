/*
 * Lily Gomes
 * CS 280-002
 * Project 4: Complex Numbers
 * 1 July 2026
 */

#include <iostream>

using std::ostream;

complex::complex(double a, double b) : a(a), b(b) {}

// Addition functions
complex complex::operator+(const complex &z) const {
  return complex(a + z.a, b + z.b);
}

complex complex::operator+(const double d) const {
  return complex(a + d, b);
}

complex operator+(double d, const complex &z) {
  return complex(z.a + d, z.b);
}

// Substraction functions
complex complex::operator-(const complex &z) const {
  return complex(a - z.a, b - z.b);
}

complex complex::operator-(const double d) const {
  return complex(a - d, b);
}

complex operator-(double d, const complex &z) {
  return complex(z.a - d, z.b);
}

// Multiplication functions
complex complex::operator*(const complex &z) const {
  double real = a * z.a + (b * z.b * -1);
  double imaginary = a * z.b + b * z.a;
  return complex(real, imaginary);
}

complex complex::operator*(const double d) const {
  return complex(a * d, b);
}

complex operator*(double d, const complex &z) {
  return complex(z.a * d, z.b);
}

// Division functions

// Print operator
ostream &operator<<(ostream &out, const complex &z) {
  out << '(' << z.a;
  if (z.b < 0)
    out << " - " << z.b << "i";
  else if (z.b > 0)
    out << " + " << z.b << "i";
  out << ')';
  return out;
}
