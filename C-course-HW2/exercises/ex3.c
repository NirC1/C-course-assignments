#include <stdio.h>

#define MAX_TARGET 729
#define MIN_TARGET -81
#define MAX_INPUT 999
#define MIN_INPUT 0

int count_of_permutation(int a, int b, int c, int target);

int main(void) {
    int num;
    int target;

    printf("Enter a 3-digit integer:\n");
    scanf("%d", &num);
    if (num < MIN_INPUT || num > MAX_INPUT) {
        printf("Invalid input. Must be a 3-digit number.\n");
        return 0;
    }

    int digits[3];
    digits[0] = num / 100;
    digits[1] = (num % 100) / 10;
    digits[2] = num % 10;

    printf("Enter target value:\n");
    scanf("%d", &target);
    if (target < MIN_TARGET || target > MAX_TARGET) {
        printf("Invalid target. target %d is outside of range.\n", target);
        return 0;
    }
    
    int count = 0;
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
                
                count = count + count_of_permutation(a, b, c, target);              
            }
        }
    }
    printf("Found %d ways to reach the target using +, - and * operations.\n", count);
    return 0;
}

int count_of_permutation(int a, int b, int c, int target) {
    int count_p = 0;
    if (a + b + c == target) {
        count_p++;
    }
    if (a + b - c == target) {
        count_p++;
    }
    if (a + b * c == target) {
        count_p++;
    }
    if (a - b + c == target) {
        count_p++;
    }
    if (a - b - c == target) {
        count_p++;
    }
    if (a - b * c == target) {
        count_p++;
    }
    if (a * b + c == target) {
        count_p++;
    }
    if (a * b - c == target) {
        count_p++;
    }
    if (a * b * c == target) {
        count_p++;
    }
    return count_p;
}


