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

// E -> P O P | P
int E(char* expr) {
  return 1; // TODO finish
}

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

// P -> I | L | UI | UL | (E)
// U -> + | - | !
// C -> a | b | ... | y | z
int C(char* expr) {
  // check for null input
  if (expr == NULL)
    return 0;
  // make sure it is a letter and only one letter
  return isalpha(*expr) && (strlen(expr) == 1);
}

// I -> C | CI
int I(char* expr) {
  // check for null input
  if (expr == NULL)
    return 0;
  // if it is only one character
  if (strlen(expr) == 1) {
    return C(expr);
  } else {
    // take first character and test the rest as another I
    char car[2] = {0};
    strncpy(car, expr, 1);
    char cdr[INPUT_LEN] = {0};
    strncpy(cdr, expr + 1, strlen(expr + 1));
    return C(car) && I(cdr);
  }
}

// L -> D | DL
// D -> 0 | 1 | ... | 8 | 9

// A -> I = E
int A(char* expr) {
  char* token = strtok(expr, "=");
  int is_I = I(token);
  token = strtok(token, "=");
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
    // remove newline from file
    char trimmed[80] = {0};
    int len = strlen(input_line);
    if (input_line[len - 1] == '\n')
      strncpy(trimmed, input_line, len - 1);
    else
      strncpy(trimmed, input_line, len);
    // test 
    printf("%s is %sin the language.\n", input_line, A(trimmed) ? "" : "not ");
  }

  // when finished, close up
  fclose(input_file);
  return 0;
}
