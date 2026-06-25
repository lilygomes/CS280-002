# Lily Gomes
# CS 280-011
# Project 4: Complex Numbers
# 1 July 2026

import math

class complexnum:
    def __init__(self, a = 0, b = 0):
        self.a = a
        self.b = b

    def conjugate(self):
        return complexnum(self.a, self.b * -1)

    def modulus(self):
        return math.sqrt(self.a * self.a + self.b * self.b)

    def __add__(self, other):
        if isinstance(other, float):
            return complexnum(self.a + other, self.b)
        elif isinstance(other, complexnum):
            return complexnum(self.a + other.a, self.b + other.b)
        else:
            raise TypeError

    def __sub__(self, other):
        if isinstance(other, float):
            return complexnum(self.a - other, self.b)
        elif isinstance(other, complexnum):
            return complexnum(self.a - other.a, self.b - other.b)
        else:
            raise TypeError

    def __mul__(self, other):
        if isinstance(other, float):
            return complexnum(self.a * other, self.b * other)
        elif isinstance(other, complexnum):
            real = self.a * other.a - self.b * other.b
            imaginary = self.a * other.b + self.b * other.a
            return complexnum(real, imaginary)
        else:
            raise TypeError

    def __truediv__(self, other):
        if isinstance(other, float):
            return complexnum(self.a / other, self.b / other)
        elif isinstance(other, complexnum):
            num = self * other.conjugate()
            den = other * other.conjugate()
            return complexnum(num.a / den.a, num.b / den.a)
        else:
            raise TypeError

    def __radd__(self, other):
        return self + other

    def __rtruediv__(self, other):
        return complexnum(other) / self

    def __rmul__(self, other):
        return self * other

    def __rsub__(self, other):
        return complexnum(other) - self

    def __eq__(self, other):
        return (self.a == other.a) and (self.b == other.b)

    def __str__(self):
        imaginary = ''
        if (self.b < 0):
            imaginary += ' - ' + str(abs(self.b)) + 'i'
        elif (self.b > 0):
            imaginary += ' + ' + str(abs(self.b)) + 'i'
        return '(' + str(self.a) + imaginary + ')'

if __name__ == '__main__':

    a = complexnum(7, 4)
    b = complexnum(3, 2)

    i = 2.4

    print('%s + %s = %s' % (a, b, a + b))
    print('%s - %s = %s' % (a, b, a - b))
    print('%s * %s = %s' % (a, b, a * b))
    print('%s / %s = %s' % (a, b, a / b))

    print('%s + %f = %s' % (a, i, a + i))
    print('%s - %f = %s' % (a, i, a - i))
    print('%s * %f = %s' % (a, i, a * i))
    print('%s / %f = %s' % (a, i, a / i))

    print('%f + %s = %s' % (i, a, i + a))
    print('%f - %s = %s' % (i, a, i - a))
    print('%f * %s = %s' % (i, a, i * a))
    print('%f / %s = %s' % (i, a, i / a))

    print('|%s| = %s' % (a, a.modulus()))
    print('%s† = %s' % (a, a.conjugate()))
    print('%s is%s equal to %s' % (a, "" if a == b else " not", b))
    b += complexnum(4, 2)
    print('%s is%s equal to %s' % (a, "" if a == b else " not", b))
