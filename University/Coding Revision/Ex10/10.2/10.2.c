#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define USE_MATH_DEFINES

float DegreesToRadians(float degrees);

int main()
{
    float deg, rad;
    printf("Angle in degrees: ");
    scanf("%f", &deg);
    rad = DegreesToRadians(deg);
    printf("%f degrees = %f radians", deg, rad);
    return 0;   
}

float DegreesToRadians(float degrees)
{
    float rad;
    rad = (M_PI*degrees)/180;
    return rad;
}
