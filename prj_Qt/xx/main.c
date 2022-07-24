#include <stdio.h>
#include <stdlib.h>
int main()
{
    int integer1=10;
    int integer2=100;
    int sum;

    printf("enter first integer\n");
    scanf(" %f", &integer1);
    printf("enter second integer\n");
    scanf(" %f ", &integer2);

    sum = integer1 + integer2;

    printf("sum is %d\n", sum);

}
