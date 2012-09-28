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

// Adds two integers together
int add(a, b) {
  return a + b;
}

// Subtracts b from a
int subtract(a, b) {
  return a - b;
}

// Multiplies two integers together
int multiply(a, b) {
  return a * b;
}

// Divides b from a
int divide(a, b) {
  return a / b;
}

// Mods a with b
int modulo(a, b) {
  return a % b;
}
