#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    char name[50];
    int age;
    printf("\nWhat's your name? ");
    gets(name);
    printf("\nHow old are you? ");
    scanf("%d", &age);
    printf("\nHello %s", name);
    printf("\nYou are %d years old", age);


    return 0;
}