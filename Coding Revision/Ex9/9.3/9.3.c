#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[50];
    printf("What's your name? ");
    scanf("%s", name);
    while (1)
    {
        printf("\n%s", name);
    }
}