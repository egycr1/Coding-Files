#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

int main()
{
    float r,h;
    float SA;
    printf("r = ");
    scanf("%f", &r);
    printf("h = ");
    scanf("%f", &h);

    SA = 2*M_PI*pow(r,2)+2*M_PI*r*h;
    
    printf("Surface Area = %.2f\n",SA);

    return 0;
}