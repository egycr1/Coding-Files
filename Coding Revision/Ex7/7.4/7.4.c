#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    char name[50];
    printf("What's your name? ");
    gets(name);
    printf("Hello %s", name);

    return 0;
}