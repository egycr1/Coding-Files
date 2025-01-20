#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define USE_MATH_DEFINES

float DegreesToRadians(float degrees, float *sn, float *cs, float *tn);

int main()
{
    int upper, lower, i;
    printf("Upper = ");
    scanf("%d", &upper);
    printf("Lower = ");
    scanf("%d", &lower);
    float rad,sn,cs,tn;
    for (i=lower;i<=upper;i++)
    {
        rad = DegreesToRadians(i, &sn, &cs, &tn);
        printf("\n%3d %3.3f %3.3f %3.3f %3.3f", i, rad, cs, sn, tn);
    }

    return 0;   
}

float DegreesToRadians(float degrees, float *sn, float *cs, float *tn)
{
    float rad;
    rad = (M_PI*degrees)/180;
    *sn = sin(rad);
    *cs = cos(rad);
    *tn = tan(rad);
    return rad;
}