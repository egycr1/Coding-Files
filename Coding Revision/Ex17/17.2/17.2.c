#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define USE_MATH_DEFINES

float DegreesToRadians(float degrees)
{
    float rad;
    rad = (M_PI*degrees)/180;
    return rad;
}

void populateArray(int size, float pData[])
{
    int i;
    for (i=0;i<size;i++)
    {
        pData[i] = DegreesToRadians(i);
    }
}

void displayArray(int size, float pData[])
{
    int i;
    for (i=0;i<size;i++)
    {
        printf("\n%3d %3.3f", i, pData[i]);
    }
}



int main()
{
    int arraySize;
    float *pData;

    printf("Array size: ");
    scanf("%d", &arraySize);

    pData = (float *) calloc(arraySize, sizeof(float));

    if (pData == NULL)
    {
        printf("\nUnable to allocate memory");
        return -1;
    }

    populateArray(arraySize, pData);

    displayArray(arraySize, pData);

    free(pData);

    return 0;
}
