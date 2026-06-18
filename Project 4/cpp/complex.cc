/*
 * Lily Gomes
 * CS 280-011
 * Project 4: Complex Numbers
 * 1 July 2026
 */

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::ostream;

struct complex {
  complex(double = 0, double = 0);
  // binary infix: complex · complex
  complex operator+(const complex &) const;
  complex operator-(const complex &) const;
  complex operator*(const complex &) const;
  complex operator/(const complex &) const;
  // binary infix: complex · double
  complex operator+(double) const;
  complex operator-(double) const;
  complex operator*(double) const;
  complex operator/(double) const;
  // binary infix: double · complex
  friend complex operator+(double, const complex &);
  friend complex operator-(double, const complex &);
  friend complex operator*(double, const complex &);
  friend complex operator/(double, const complex &);
  friend ostream &operator<<(ostream &, const complex &);
  // allow autoconversion for double to complex
  complex operator=(double) const;
  // additional properties
  complex conjugate() const;
  double modulus() const;
private:
  double a;
  double b;
};

complex::complex(double a, double b) : a(a), b(b) {}

// Complex property functions
complex complex::conjugate() const {
  return complex(a, -1 * b);
}

double complex::modulus() const {
  return sqrt(a * a + b * b);
}

// Assignment overload
complex complex::operator=(double d) const {
  return complex(d, 0);
}

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
  return complex(a * d, b * d);
}

complex operator*(double d, const complex &z) {
  return complex(z.a * d, z.b * d);
}

// Division functions
complex complex::operator/(const complex &z) const {
  // Multiply both complex numbers by the conjugate of the divisor
  complex numerator = *this * z.conjugate();
  complex denominator = z * z.conjugate();
  // The denominator cancels out its imaginary term, divide the numerator by the denominator as a real number
  numerator = numerator / denominator.a;
  return numerator;
}

complex complex::operator/(const double d) const {
  return complex(a / d, b / d);
}

complex operator/(double d, const complex &z) {
  return complex(z.a / d, z.b / d);
}

// Print operator
ostream &operator<<(ostream &out, const complex &z) {
  out << '(' << z.a;
  if (z.b < 0)
    out << " - " << abs(z.b) << "i";
  else if (z.b > 0)
    out << " + " << z.b << "i";
  out << ')';
  return out;
}

// test methods
int main() {
  complex x(7, 4);
  complex y(3, 2);
  double z = 2.4;
  complex z2 = z;

  cout << x << " + " << y << " = " << x + y << endl;
  cout << x << " - " << y << " = " << x - y << endl;
  cout << x << " * " << y << " = " << x * y << endl;
  cout << x << " / " << y << " = " << x / y << endl;

  cout << x << " + " << z << " = " << x + z << endl;
  cout << x << " - " << z << " = " << x - z << endl;
  cout << x << " * " << z << " = " << x * z << endl;
  cout << x << " / " << z << " = " << x / z << endl;

  cout << z << " + " << x << " = " << z + x << endl;
  cout << z << " - " << x << " = " << z - x << endl;
  cout << z << " * " << x << " = " << z * x << endl;
  cout << z << " / " << x << " = " << z / x << endl;

  cout << "|" << x << "| = " << x.modulus() << endl;
  cout << x << "† = " << x.conjugate() << endl;
  cout << z << " = " << z2 << endl;
}
