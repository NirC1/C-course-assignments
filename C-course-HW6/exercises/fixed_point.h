#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <stdint.h>

/* Print a fixed-point number with exactly six decimal places. */
void print_fixed(int16_t raw, int16_t q);

/* Add two fixed-point numbers. */
int16_t add_fixed(int16_t a, int16_t b);

/* Subtract two fixed-point numbers. */
int16_t subtract_fixed(int16_t a, int16_t b);

/* Multiply two fixed-point numbers, shifting right by q bits. */
int16_t multiply_fixed(int16_t a, int16_t b, int16_t q);

/* Evaluate a polynomial a*x^2 - b*x + c at x (all fixed-point), printing the result. */
void eval_poly_ax2_minus_bx_plus_c_fixed(int16_t x,
                                         int16_t a,
                                         int16_t b,
                                         int16_t c,
                                         int16_t q);

#endif /* FIXED_POINT_H */
