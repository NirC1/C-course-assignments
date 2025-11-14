#include <stdio.h>

int count_num_even_digits(int num, int count);

int main() {
  unsigned int num;
  unsigned int result;

  // Prompt user for input
  printf("Please insert a non-negative integer:\n");
  scanf("%u", &num);

  result = count_num_even_digits(num, 0);

  // Prompt result to user
  printf("The number of even digits in %u is: %u\n", num, result);
  return 0;
}

/*
  receives num and count (0) and calls itself with count +1 if the last digit is even
  calls itself with count +0 if last digit isn't even, returns if the number doesn't contain any more digits.
*/
int count_num_even_digits(int num, int count)
{
  if ( num  == 0 ){
    return count;
  }

  int digit = 0;
  digit = num % 10;
  if ( 0 == digit || ((digit % 2) == 1) ){
    return count_num_even_digits(num / 10, count);
  }else{
    return count_num_even_digits(num / 10, count +1);
  }
}
