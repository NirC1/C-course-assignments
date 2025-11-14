#include <stdio.h>

// TODO: add your recursive function implementation here

int main() {
  unsigned int num;
  unsigned int result;

  // Prompt user for input
  printf("Please insert a non-negative integer:\n");
  scanf("%u", &num);

  // TODO: Call the recursive function and display result

  // Prompt result to user
  printf("The number of even digits in %u is: %u\n", num, result);
  return 0;
}
