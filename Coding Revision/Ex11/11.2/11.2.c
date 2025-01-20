#include <stdio.h>
#include <stdlib.h>

int main()
{
    float array[90];
    int i;
    for (i=0;i<90;i++)
    {
        array[i] = i;
    }
    for (i=0;i<90;i++)
    {
        printf("%3d      %3.3f\n", i, array[i]);
    }
    return 0;
}