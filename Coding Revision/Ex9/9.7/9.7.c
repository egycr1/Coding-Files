#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
        printf("%d  %.0f\n", i, pow(i,2));
    }
    return 0;
}