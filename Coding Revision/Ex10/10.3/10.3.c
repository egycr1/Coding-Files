#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float DegreesToRadians(float degrees);

int main()
{
    int i, upper, lower;
    printf("Lower limit: ");
    scanf("%d", &lower);
    printf("\nUpper limit: ");
    scanf("%d", &upper);
    printf("\n");
    if (lower>upper)
    {
        int hold;
        hold = lower;
        lower = upper;
        upper = hold;
    }
    for (i=lower;i<=upper;i++)
    {
        printf("%d  %.2f\n", i, DegreesToRadians((float) i));
    }
    return 0;
}

float DegreesToRadians(float degrees)
{
    float rad;
    rad = (M_PI*degrees)/180;
    return rad;
}