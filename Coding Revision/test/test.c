#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    char r;
    scanf("%c", r);
    if (isdigit(r))
        printf("r is valid");
    else
        printf("r is invalid");
}