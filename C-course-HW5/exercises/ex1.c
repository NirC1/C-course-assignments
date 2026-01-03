#include <stdio.h>

unsigned int largest_power_of_2(unsigned int n) {
  if (n == 0) {
    return 0;
  }
  int msb_index = 0;

  for (int i = 31; i >= 0; i--) {
    if (n & (1u << i)) {
      msb_index = i;
      break;
    }
  }
  return 1u << msb_index;
}

int main() {

  unsigned int n, L = 0;

  printf("Please enter an unsigned integer n:\n");
  scanf("%u", &n);

  L = largest_power_of_2(n);

  printf("The Largest Power of 2 Smaller or Equal to %u is: %u\n", n, L);

  return 0;
}
