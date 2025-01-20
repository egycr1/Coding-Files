#include <stdio.h>
#include <stdlib.h>

int main()
{
    int age;
    printf("How old are you? ");
    scanf("%d", &age);
    if (age<=5)
        printf("Still a baby");
    else if (age>5 && age<=12)
        printf("The junior years");
    else if (age>12 && age<=20)
        printf("Teenage years");
    else
        printf("Downhill all the way now!");
    
    return 0;
}