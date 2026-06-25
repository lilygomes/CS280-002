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
  // unary operator: -complex
  complex operator-() const;
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
  // binary assignment: *= complex
  complex& operator+=(const complex &);
  complex& operator+=(double);
  complex& operator-=(const complex &);
  complex& operator-=(double);
  complex& operator*=(const complex &);
  complex& operator*=(double);
  complex& operator/=(const complex &);
  complex& operator/=(double);
  // equality operator
  friend bool operator==(const complex &, const complex &);
  friend bool operator==(double, const complex &);
  friend bool operator==(const complex &, double);
  // ostream string representation
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
complex complex::operator-() const {
  return complex(a * -1, b * -1);
}

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
  double real = a * z.a - (b * z.b);
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

// Equality operator
bool operator==(const complex &z1, const complex &z2) {
  return (z1.a == z2.a) && (z1.b == z2.b);
}

bool operator==(double d, const complex &z) {
  return (z.a == d) && (z.b == 0);
}

bool operator==(const complex &z, double d) {
  return (z.a == d) && (z.b == 0);
}

// Binary assignment operator
complex& complex::operator+=(const complex &z) {
  a += z.a;
  b += z.b;
  return *this;
}

complex& complex::operator+=(double d) {
  a += d;
  return *this;
}

complex& complex::operator-=(const complex &z) {
  a -= z.a;
  b -= z.b;
  return *this;
}

complex& complex::operator-=(double d) {
  a -= d;
  return *this;
}

complex& complex::operator*=(const complex &z) {
  double real = a * z.a - b * z.b;
  double imaginary = a * z.b + b * z.a;
  a = real;
  b = imaginary;
  return *this;
}

complex& complex::operator*=(double d) {
  a *= d;
  b *= d;
  return *this;
}

complex& complex::operator/=(const complex &z) {
  complex numerator = *this * z.conjugate();
  complex denominator = z * z.conjugate();
  a = numerator.a / denominator.a;
  b = numerator.b / denominator.a;
  return *this;
}

complex& complex::operator/=(double d) {
  a /= d;
  b /= d;
  return *this;
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
  complex w(7, 4);
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
  cout << x << (x == w ? " is " : " is not ") << "equal to " << w << endl;
  // test binary assignment arithmetic
  w += y;
  cout << x << (x == w ? " is " : " is not ") << "equal to " << w << endl;
  cout << z2 << (z2 == z ? " is " : " is not ") << "equal to " << z << endl;

}
