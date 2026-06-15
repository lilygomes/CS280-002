/*
 * Lily Gomes
 * CS 280-002
 * Project 2: Recursive Descent Parsing
 * 11 June 2026
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
  // A -> I = E
  static boolean A(String expr) {
    String terms[] = expr.split("=");
    for (String term : terms) System.out.println(term); // TODO remove
    if (terms.length == 2)
      // check if first part is a string of letters (therefore, I)
      return terms[0].matches("[a-z]+") && E(terms[1]);
    else
      return false;
  }

  // E -> P O P | P
  static boolean E(String expr) {
    // check if expr contains symbols that would be operators
    String tokens[] = expr.split("\+|\-|\*{1,2}|\/");
    if () {
      String before = expr.substring(0, operatorIndex);
      String after = expr.substring(operatorIndex + 1, expr.length());
      System.out.println(before + " " + expr.charAt(operatorIndex) + " " + after); // TODO remove
      // if **, trim second *
      if (after.charAt(0) == '*')
        after = after.substring(1, after.length());
      return P(before) && P(after);
    } else
      return P(expr);
  }

  // P -> I | L | UI | UL | (E)
  static boolean P(String expr) {
    switch (expr.charAt(0)) {
      case '+':
      case '-':
      case '!':
        return P(expr.substring(1));
      case '(':
        return P(expr.substring(1, expr.length() - 2));
      default:
        // checks if expression is string of letters or string of digits
        return expr.matches("[a-z]+") || expr.matches("[0-9]+");
    }
  }

  public static void main(String[] args) {
    // check for proper usage
    if (args.length != 1) {
      System.out.println("error: incorrect arguments\nusage: parser [filename]");
      System.exit(64);
    } 
    // try to open file
    File inFile = new File(args[0]);
    try (Scanner inScan = new Scanner(inFile)) {
      while (inScan.hasNextLine()) {
        // remove trailing newline
        String inLine = inScan.nextLine().strip();
        System.out.printf("%s is %sin the language.\n", inLine, (A(inLine) ? "" : "not "));
      }
    } catch (FileNotFoundException e) {
      System.out.println("error: could not find \"" + args[1] + '"');
      System.exit(66);
    }
  }
}
