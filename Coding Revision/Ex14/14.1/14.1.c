#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define USE_MATH_DEFINES

void CartToPolar(float x, float y, float *r, float *theta);

int main()
{
    float x,y,r,theta;
    printf("x = ");
    scanf("%f", &x);
    printf("\ny = ");
    scanf("%f", &y);
    CartToPolar(x, y, &r, &theta);
    printf("\nr = %f\n", r);
    printf("\ntheta = %f", theta);
}

void CartToPolar(float x, float y, float *r, float *theta)
{
    *r = sqrt(x*x+y*y);
    *theta = y/x;
}