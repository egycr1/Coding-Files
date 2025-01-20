#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Number: ");
    scanf("%d", &n);
    if (n >= 0 && n <= 10)
    {
        printf("Number in range");
    }
    else
    {
        printf("Number is not in range");
    }
    return 0;
}