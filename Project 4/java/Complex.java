/*
 * Lily Gomes
 * CS 280-002
 * Project 4: Complex Numbers
 * 1 July 2026
 */

public class Complex {
  private double a, b;

  public Complex() {
    this(0, 0);
  }

  public Complex(double d) {
    this(d, 0);
  }

  public Complex(double a, double b) {
    this.a = a;
    this.b = b;
  }

  public Complex conj() {
    return new Complex(a, b * -1);
  }

  public double mod() {
    return Math.sqrt(a * a + b * b);
  }

  public Complex add(Complex z) {
    return new Complex(a + z.a, b + z.b);
  }

  public Complex add(double d) {
    return new Complex(a + d, b);
  }

  public Complex sub(Complex z) {
    return new Complex(a - z.a, b - z.b);
  }

  public Complex sub(double d) {
    return new Complex(a - d, b);
  }

  public Complex mul(Complex z) {
    double real = a * z.a + (b * z.b * -1);
    double imaginary = a * z.b + b * z.a;
    return new Complex(real, imaginary);
  }

  public Complex mul(double d) {
    return new Complex(a * d, b * d);
  }

  public Complex div(Complex z) {
    Complex numerator = this.mul(z.conj());
    Complex denominator = z.mul(z.conj());
    return numerator.div(denominator.a);
  }

  public Complex div(double d) {
    return new Complex(a / d, b / d);
  }

  public String toString() {
    return "(" + a + (b == 0 ? ")" : (b < 0 ? " - " : " + ") + Math.abs(b) + "i)"); 
  }

  public static void main(String[] args) {
    Complex a = new Complex(7, 4);
    Complex b = new Complex(3, 2);

    double i = 2.4;

    System.out.println(a + " + " + b + " = " + a.add(b));
    System.out.println(a + " - " + b + " = " + a.sub(b));
    System.out.println(a + " * " + b + " = " + a.mul(b));
    System.out.println(a + " / " + b + " = " + a.div(b));

    System.out.println(a + " + " + i + " = " + a.add(i));
    System.out.println(a + " - " + i + " = " + a.sub(i));
    System.out.println(a + " * " + i + " = " + a.mul(i));
    System.out.println(a + " / " + i + " = " + a.div(i));
    
    System.out.println("|" + a + "| = " + a.mod());
    System.out.println(a + "† = " + a.conj());
  }
}
