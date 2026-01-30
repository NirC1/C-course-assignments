#include "fixed_point.h"
#include <stdio.h>
#include <stdint.h>

/* Print a fixed-point number with exactly six decimal places. */
void print_fixed(int16_t raw, int16_t q) {
    int negative = (raw < 0);
    int64_t v = raw;
    if (negative) v = -v;
    int64_t int_part  = v >> q;
    int64_t frac_part = v & ((1LL << q) - 1);
    /* Scale fractional bits to 6 decimal digits and truncate. */
    int64_t frac_scaled = (frac_part * 1000000LL) >> q;
    if (negative) putchar('-');
    printf("%lld.%06lld", (long long)int_part, (long long)frac_scaled);
}

int16_t add_fixed(int16_t a, int16_t b) {
    return (int16_t)(a + b);
}

int16_t subtract_fixed(int16_t a, int16_t b) {
    return (int16_t)(a - b);
}

int16_t multiply_fixed(int16_t a, int16_t b, int16_t q) {
    int64_t prod   = (int64_t)a * (int64_t)b;
    int64_t result = prod >> q;
    return (int16_t)result;
}

void eval_poly_ax2_minus_bx_plus_c_fixed(int16_t x,
                                         int16_t a,
                                         int16_t b,
                                         int16_t c,
                                         int16_t q) {
    int16_t x2  = multiply_fixed(x, x, q);
    int16_t ax2 = multiply_fixed(a, x2, q);
    int16_t bx  = multiply_fixed(b, x, q);
    int16_t y   = subtract_fixed(ax2, bx);
    y = add_fixed(y, c);

    printf("the polynomial output for a=");
    print_fixed(a, q);
    printf(", b=");
    print_fixed(b, q);
    printf(", c=");
    print_fixed(c, q);
    printf(" is ");
    print_fixed(y, q);
    printf("\n");
}
