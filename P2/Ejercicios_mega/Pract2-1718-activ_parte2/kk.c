#include <stdio.h>

int main()
{
    int x=35;
    int y=-35;
    unsigned int z=35;
    unsigned int p=-35;
    signed int q=-35;
    printf("Int(35d)=%d\n\
    Int(-35d)=%d\n\
    UInt(35u)=%u\n\
    UInt(-35u)=%u\n\
    UInt(-35d)=%d\n\
    SInt(-35u)=%u\n",x,y,z,p,p,q);


    signed int num1 = 5;
    signed int num2 = -5;

    signed int result = num1*(-1);

    printf("%d", result);

    return 0;
}