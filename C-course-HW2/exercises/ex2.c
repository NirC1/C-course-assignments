#include <stdio.h>

unsigned int digital_root(unsigned int num);

int main() {
  unsigned int num;
  unsigned int result;

  // Prompt user for input
  printf("Please insert a non-negative integer:\n");
  scanf("%u", &num);

  result = digital_root(num);

  // Prompt result to user
  printf("The repeated sum of digits in %u is: %u\n", num, result);
  return 0;
}

unsigned int digital_root(unsigned int num)
{
  if ( num < 10 ){
    return num;
  }
  unsigned int sum = 0;
  for (; num > 0 ; num = num / 10){
    sum += num % 10;
  }
  return digital_root(sum);
}
