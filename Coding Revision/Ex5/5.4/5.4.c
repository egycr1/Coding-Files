#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

int main()
{
    float r = 5;
    float vol, SA;

    vol = (4*M_PI*pow(r,2))/3;
    SA = 4*M_PI*pow(r,2);
    
    printf("Volume = %.2f\n",vol);
    printf("Surface Area = %.2f\n",SA);

    return 0;
}