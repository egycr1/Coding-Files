#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define USE_MATH_DEFINES

float DegreesToRadians(float degrees);

int main()
{
    float array[90];
    int i;
    for (i=0;i<90;i++)
    {
        array[i] = DegreesToRadians((float) i);
    }
    for (i=0;i<90;i++)
    {
        printf("%3d      %3.3f\n", i, array[i]);
    }
    return 0;
}

float DegreesToRadians(float degrees)
{
    float rad;
    rad = (M_PI*degrees)/180;
    return rad;
}