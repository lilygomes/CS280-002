/*
 * Lily Gomes
 * CS 280-002
 * Project 2: Recursive Descent Parsing
 * 11 June 2026
 */

#include <string.h>
#include <stdio.h>
#include <ctype.h>

const int INPUT_LEN = 80;

// O -> + | - | * | / | **
int O(char* expr) {
  if (strlen(expr) == 1) {
    switch (expr[0]) {
      case '+':
      case '-':
      case '*':
      case '/':
        return 1;
      default:
        return 0;
    }
  } else if (strlen(expr) == 2) {
    return (expr[0] == '*') && (expr[1] == '*');
  } else
    return 0;
}

// U -> + | - | !
int U(char sym) {
  switch (sym) {
    case '+':
    case '-':
    case '!':
      return 1;
    default:
      return 0;
  }
}

// C -> a | b | ... | y | z
int C(char sym) {
  // check ASCII int value of char
  return 96 < sym && sym < 123;
}

// I -> C | CI
int I(char* expr) {
  // if it is only one character
  if (strlen(expr) == 1) {
    return C(expr[0]);
  } else {
    // take first character and test the rest as another I
    char cdr[INPUT_LEN] = {0};
    strncpy(cdr, expr + 1, strlen(expr + 1));
    return C(expr[0]) && I(cdr);
  }
}

// D -> 0 | 1 | ... | 8 | 9
int D(char sym) {
  // check ASCII int val of char
  return 47 < sym && sym < 58;
}

// L -> D | DL
int L(char* expr) {
  // if one char long, only test the first symbol
  if (strlen(expr) == 1) {
    return D(expr[0]);
  } else {
    char cdr[INPUT_LEN] = {0};
    strncpy(cdr, expr + 1, strlen(expr + 1));
    return D(expr[0]) && L(cdr);
  }
}

// prevent reference error
int E(char*);

// P -> I | L | UI | UL | (E)
int P(char* expr) {
  // check first symbol of string is U
  if (U(expr[0])) {
    // test rest of expr minus starting U
    char cdr[INPUT_LEN] = {0};
    strncpy(cdr, expr + 1, strlen(expr + 1));
    return I(cdr) || L(cdr);
  }
  // otherwise check for opening brace
  else if (expr[0] == '(') {
    // test rest of expr minus braces
    char subexp[INPUT_LEN] = {0};
    strncpy(subexp, expr + 1, strlen(expr + 1) - 1);
    return E(subexp);
  }
  // otherwise just test if I or L
    return I(expr) || L(expr);
}

// E -> P O P | P
int E(char* expr) {
  // split string between separators
  char* operators = "+-/*";
  char* after = strpbrk(expr, operators);
  char op[3] = {0};
  char before[INPUT_LEN] = {0};
  // if there are operator symbols
  if (after) {
    strncpy(before, expr, strlen(expr) - strlen(after));
    // check if operator is one or two characters
    op[0] = after[0];
    if (after[1] == '*') {
      // if there's a **, ensure we don't feed it into the recursion
      op[1] = after[1];
      return P(before) && O(op) && E(after + 2);
    } else {
      return P(before) && O(op) && E(after + 1);
    }
    return 0;
  } else
    return P(expr);
}

// A -> I = E
int A(char* expr) {
  // test part before = 
  char* token = strtok(expr, "=");
  int is_I = I(token);
  // test part after =
  token = strtok(NULL, "=");
  int is_E = E(token);
  return (is_I && is_E);
}

int main(int argc, char *argv[]) {
  // usage: parser [filename]
  if (argc != 2) {
    printf("usage: %s [filename]\n", argv[0]);
    return 64;
  }
  // open input file
  FILE* input_file = fopen(argv[1], "r");
  if (input_file  == NULL) {
    printf("could not open %s\n", argv[1]);
    return 66;
  }
  // read each line of input file
  char input_line[80] = {0};
  while (fgets(input_line, INPUT_LEN, input_file) != NULL) {
    // remove newline from line
    char trimmed[80] = {0};
    int len = strlen(input_line);
    if (input_line[len - 1] == '\n') {
      strncpy(trimmed, input_line, len - 1);
      input_line[len - 1] = 0;
    } else
      strncpy(trimmed, input_line, len);
    // test 
    printf("%s is %sin the language.\n", input_line, A(trimmed) ? "" : "not ");
  }

  // when finished, close up
  fclose(input_file);
  return 0;
}
