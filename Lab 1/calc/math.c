/*
 * math.c
 *
 * Brandon Lee - bfl
 * Christopher Palmer - ctpalmer
 * Joogyoon Han - jongyoo1
 * Lawrence Tsang - ltsang
 *
 * Helper function for calc.c.  Has a separate function for adding, subtracting
 * multiplying, dividing, and modulating. 
 *
 */
#include <stdio.h>
#include "math.h"

int add(a, b) {
  return a + b;
}

int subtract(a, b) {
  return a - b;
}

int multiply(a, b) {
  return a * b;
}

int divide(a, b) {
  return a / b;
}

int modulo(a, b) {
  return a % b;
}
