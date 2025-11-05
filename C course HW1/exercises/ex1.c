#include <stdio.h>

int check_valid_base(int base);

char sign(int num);
int absolute_value(int num);


int main(void){
    int number,  base;

    printf("Please enter a number (integer) and a base:\n");
    scanf("%d %d", &number, &base); // the user enters a base-10 number and base

    while(!check_valid_base(base)){
        printf("Invalid base %d\n", base);
        printf("Please enter a valid base [8,10,16]:\n");

        scanf("%d", &base);
    }

    printf("Here is some information about the given numbers: %d\n", number);

    printf("Its sign is: %c\n", sign(number));

    printf("Decimal representation of the absolute value: %d\n", absolute_value(number));
    
    
    
    return 0;
}

int check_valid_base(int base)
{
    return (16 == base) || (10 == base) || (8 == base);
}


char sign(int num){
    if( 0 == num )
        return '0';
    else if(num > 0)
        return '+';
    else
        return '-';
}

int absolute_value(int num)
{
    return num < 0 ? -num : num;
}
