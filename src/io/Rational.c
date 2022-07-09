#include <stdio.h>
#include <stdlib.h>
#include "./Strint.c"
#include "../util/strint/Strint.c"
#include "../util/rational/Rational.c"

int getRational(Rational *dest)
{
    printf(">> Numerator = ");
    getStrint(&(dest->numt));
    printf(">> Denominator = ");
    getStrint(&(dest->deno));
    putchar('\n');

    return 1;
}

void printRational(Rational x)
{
    printStrint(x.numt);
    puts(" / ");
    printStrint(x.deno);
}
