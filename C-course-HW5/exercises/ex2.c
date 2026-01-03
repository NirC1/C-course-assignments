#include <stdbool.h>
#include <stdio.h>

bool is_binary_palindrome(unsigned int n) {
  if (n == 0) {
    return true;
  }
 
  int left = 0;
  for (int i = 31; i >= 0; i--) {
    if (n & (1u << i)) {
      left = i;
      break;
    }
  }
  int right = 0;
 
  while (left > right) {
    unsigned int bit_left = (n >> left) & 1u;
    unsigned int bit_right = (n >> right) & 1u;
    if (bit_left != bit_right) {
      return false;
    }
    left--;
    right++;
  }
  return true;
}

int main() {

  unsigned int n;
  bool result;

  printf("Please enter an unsigned integer n:\n");
  scanf("%u", &n);

  result = is_binary_palindrome(n);

  printf("The binary representation of %u is %s\n", n,
         result ? "a palindrome" : "not a palindrome");

  return 0;
}
