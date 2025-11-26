#include <stdio.h>

unsigned int digital_root(unsigned int num);
unsigned int sum_of_digits(unsigned int num);

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
  unsigned int sum = sum_of_digits(num);
  return digital_root(sum);
}

unsigned int sum_of_digits(unsigned int num)
{
  if (num < 10){
    return num; // the sum of a one digit number is the number
  }
  return sum_of_digits(num / 10) + (num % 10);
}
