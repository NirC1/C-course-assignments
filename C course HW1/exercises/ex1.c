#include <stdio.h>

int check_valid_base(int num);


int main(void){
    int number,  base;

    printf("Please enter a number (integer) and a base:\n");
    scanf("%d %d", &number, &base);

    printf("number: %d base: %d\n", number, base);

}

int check_valid_base(int num)
{
    return (16 == num) || (10 == num) || (8 == num);
}
