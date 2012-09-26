#include <stdio.h>
#include "math.h"

int main() {
  int first, second, result = 0, cont = 0;
  char op;

  while(cont == 0) {
    if(fscanf(stdin, "%d %c %d", &first, &op, &second) != 3)
      cont = 1;
    else {
      switch(op) {
        case '+':
          result = add(first, second);
          printf("%d\n", result);
          break;
        case '-':
          result = subtract(first, second);
          printf("%d\n", result);
          break;
        case '*':
          result = multiply(first, second);
          printf("%d\n", result);
          break;
        case '/':
          result = divide(first, second);
          printf("%d\n", result);
          break;
        case '%':
          result = modulo(first, second);
          printf("%d\n", result);
          break;
        default :
          cont = 1;
      }
    }  
  }
  return 0;
}

