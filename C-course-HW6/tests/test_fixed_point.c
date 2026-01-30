#include "../exercises/fixed_point.h"
#include <stdio.h>

int main() {
    printf("testing addition:\n");
    // test addition
    int16_t a = 16384; // 1.0 in Q14
    int16_t b = 8192;  // 0.5 in Q14
    int16_t result = add_fixed(a, b);
    printf("1.0 + 0.5 = ");
    print_fixed(result, 14);
    printf("\n");

    printf("testing subtraction:\n");
    // test subtraction
    a = 16384; // 1.0 in Q14
    b = 8192;  // 0.5 in Q14
    result = subtract_fixed(a, b);
    printf("1.0 - 0.5 = ");
    print_fixed(result, 14);
    printf("\n");

    // test subtraction resulting in negative
    a = 8192;  // 0.5 in Q14
    b = 16384; // 1.0 in Q14
    result = subtract_fixed(a, b);
    printf("0.5 - 1.0 = ");
    print_fixed(result, 14);
    printf("\n");

    printf("testing multiplication:\n");
    // test multiplication
    a = 16384; // 1.0 in Q14
    b = 8192;  // 0.5 in Q14
    result = multiply_fixed(a, b, 14);  // Q14 multiplication
    printf("1.0 * 0.5 = ");
    print_fixed(result, 14);
    printf("\n");

    // test multiplication resulting in negative
    a = -16384; // -1.0 in Q14
    b = 8192;   // 0.5 in Q14
    result = multiply_fixed(a, b, 14);  // Q14 multiplication
    printf("-1.0 * 0.5 = ");
    print_fixed(result, 14);
    printf("\n");

    // test multiplication resulting in value greater than 1
    a = 24576; // 1.5 in Q14
    b = 16384; // 1.0 in Q14
    result = multiply_fixed(a, b, 14);  // Q14 multiplication
    printf("1.5 * 1.0 = ");
    print_fixed(result, 14);
    printf("\n");

    // test multiplication resulting in zero
    a = 0;     // 0.0 in Q14
    b = 16384; // 1.0 in Q14
    result = multiply_fixed(a, b, 14);  // Q14 multiplication
    printf("0.0 * 1.0 = ");
    print_fixed(result, 14);
    printf("\n");

    // evaluate polynomial 200 1002 1200 9012 12 (a b c q)
    printf("testing polynomial evaluation:\n");
    int16_t x = 200;   // 200 in Q12
    int16_t a_poly = 1002;  // 1002 in Q12
    int16_t b_poly = 1200;  // 1200 in Q12
    int16_t c_poly = 9012;  // 9012 in Q12
    int16_t q_poly = 12;    // Q12
    eval_poly_ax2_minus_bx_plus_c_fixed(x, a_poly, b_poly, c_poly, q_poly);

    // 10200 4000 4900 2000 14
    x = 10200;   // 10200 in Q14
    a_poly = 4000;  // 4000 in Q14
    b_poly = 4900;  // 4900 in Q14
    c_poly = 2000;  // 2000 in Q14
    q_poly = 14;    // Q14
    eval_poly_ax2_minus_bx_plus_c_fixed(x, a_poly, b_poly, c_poly, q_poly);


    return 0;
}