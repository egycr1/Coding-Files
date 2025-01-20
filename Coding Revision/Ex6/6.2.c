#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int A = 60, B = 13, R;

    R = A & B;
    printf("A & B = %#04x\n", R);
    printf("A | B = %#x\n", A | B);
    printf("A ^ B = %#x\n", A^B);
    printf("~ A = %#x\n", ~A);
    printf("A << 2 = %#x\n", A << 2);
    printf("A >> 2 = %#x\n", A >> 2);

    return 0;
}
