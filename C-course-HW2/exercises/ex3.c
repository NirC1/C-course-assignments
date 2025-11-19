
#include <stdio.h>

#define MAX_TARGET 729  // 9 * 9 * 9
#define MIN_TARGET -81  // 0 - 9 * 9
#define MAX_INPUT 999   // largest three‑digit number
#define MIN_INPUT 0     // smallest three‑digit number

int minValGlobal;
int maxValGlobal;


int evaluate(int a, int b, int c, char op1, char op2);
void compute_range(int digits[3]);


int evaluate(int a, int b, int c, char op1, char op2) {
    // both operators are multiplication
    if (op1 == '*' && op2 == '*') {
        return a * b * c;
    }
    // first is multiplication, second is addition or subtraction
    if (op1 == '*' && op2 != '*') {
        int left = a * b;
        return (op2 == '+') ? (left + c) : (left - c);
    }
    // first is addition or subtraction, second is multiplication
    if (op1 != '*' && op2 == '*') {
        int right = b * c;
        return (op1 == '+') ? (a + right) : (a - right);
    }
    // both are addition or subtraction; evaluate left to right
    int tmp = (op1 == '+') ? (a + b) : (a - b);
    return (op2 == '+') ? (tmp + c) : (tmp - c);
}


void compute_range(int digits[3]) {
    char ops[3] = {'+', '-', '*'};
    // initialise to opposite extremes so that any computed value will update
    minValGlobal = MAX_TARGET;
    maxValGlobal = MIN_TARGET;
    // iterate over all permutations of the three digits
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (j == i) {
                continue;
            }
            for (int k = 0; k < 3; ++k) {
                if (k == i || k == j) {
                    continue;
                }
                int a = digits[i];
                int b = digits[j];
                int c = digits[k];
                // iterate over all combinations of the two operators
                for (int op1 = 0; op1 < 3; ++op1) {
                    for (int op2 = 0; op2 < 3; ++op2) {
                        int value = evaluate(a, b, c, ops[op1], ops[op2]);
                        if (value < minValGlobal) {
                            minValGlobal = value;
                        }
                        if (value > maxValGlobal) {
                            maxValGlobal = value;
                        }
                    }
                }
            }
        }
    }
}

int main(void) {
    int number;
    int target;
    // prompt user for a three‑digit integer
    printf("Enter a 3-digit integer:\n");
    // read the input and validate
    if (scanf("%d", &number) != 1 || number < MIN_INPUT || number > MAX_INPUT) {
        printf("Invalid input. Must be a 3-digit number.\n");
        return 0;
    }
    // extract the digits; leading zeros are preserved via integer division
    int digits[3];
    digits[0] = number / 100;
    digits[1] = (number / 10) % 10;
    digits[2] = number % 10;
    // compute the range of possible target values
    compute_range(digits);
    // prompt for the target value
    printf("Enter target value:\n");
    if (scanf("%d", &target) != 1) {
        // on invalid input, we cannot determine a specific value; use '?' per specification
        printf("Invalid target. target ? is outside of range.\n");
        return 0;
    }
    // check if the target is within the achievable range
    if (target < minValGlobal || target > maxValGlobal) {
        printf("Invalid target. target %d is outside of range.\n", target);
        return 0;
    }
    // count the number of ways to reach the target using all permutations and operator combinations
    int ways = 0;
    char ops[3] = {'+', '-', '*'};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (j == i) {
                continue;
            }
            for (int k = 0; k < 3; ++k) {
                if (k == i || k == j) {
                    continue;
                }
                int a = digits[i];
                int b = digits[j];
                int c = digits[k];
                for (int op1 = 0; op1 < 3; ++op1) {
                    for (int op2 = 0; op2 < 3; ++op2) {
                        if (evaluate(a, b, c, ops[op1], ops[op2]) == target) {
                            ++ways;
                        }
                    }
                }
            }
        }
    }
    printf("Found %d ways to reach the target using +, - and * operations.\n", ways);
    return 0;
}
