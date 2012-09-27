/*
 * calc.c
 *
 * Brandon Lee - bfl
 * Christopher Palmer - ctpalmer
 * Joogyoon Han - jongyoo1
 * Lawrence Tsang - ltsang
 *
 * Recreates the function of a calculator.  It accepts the input of a number,
 * operation, then another number, with whitespace in between.  If it's one of
 * the known operations, add, subtract, divide, multiply, or mod, then it will
 * perform the said operation on a new line.  If input is not in the format 
 * stated above, it will exit with the return value 0.\
 *
 */
#include <stdio.h>
#include "math.h"

int main() {
  int first, second, result = 0, cont = 0;
  char op;

  while(cont == 0) {
    /* Ensures correct formatting with number operation number */
    if(fscanf(stdin, "%d %c %d", &first, &op, &second) != 3)
      cont = 1;
    else {
	  /* Looks at the operation inputted and moves from there */
      switch(op) {
        case '+': // Refers to additive function
          result = add(first, second);
          printf("%d\n", result);
          break;
        case '-': // Refers to subtract function
          result = subtract(first, second);
          printf("%d\n", result);
          break;
        case '*': // Refers to multiply function
          result = multiply(first, second);
          printf("%d\n", result);
          break;
        case '/': // Refers to division function
          result = divide(first, second);
         printf("%d\n", result);
          break;
        case '%': // Referst to modulo function
          result = modulo(first, second);
          printf("%d\n", result);
          break;
        default : // If it's not anything as expected, exit out of the loop
          cont = 1;
      }
    }  
  }
  return 0;
}

