#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter an integer");
    scanf("%d", &n);
    if (n==0)
        printf("Black");
    else if (n==1)
        printf("Brown");
    else if (n==2)
        printf("Red");
    else if (n==3)
        printf("Orange");
    else if (n==4)
        printf("Yellow");
    else if (n==5)
        printf("Green");
    else if (n==6)
        printf("Blue");
    else if (n==7)
        printf("Violet");
    else if (n==8)
        printf("Grey");
    else if (n==9)
        printf("White");
    else
        printf("Invalid Input");
    
    return 0;
}