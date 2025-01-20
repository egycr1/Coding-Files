#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, upper, lower,sum;
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
        if (i<upper)
        {
            printf("%d+", i);
        }
        else
            printf("%d",i);
        sum = sum+i;
    }
    printf("=%d", sum);
    return 0;
}