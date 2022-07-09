#include <stdio.h>
#include <stdlib.h>
#include "../util/strint/Strint.c"

void printStrint(Strint strint)
{
    printf("%s", strintToString(strint));
}

void printlnStrint(Strint strint)
{
    printf("%s\n", strintToString(strint));
}

int getStrint(Strint *dest)
{
    size_t size = 100;
    int index = 0;
    char sign = getchar();

    if (sign != '+' && sign != '-')
    {
        fputs("ERROR: Invalid sign. `+` or `-` expected.", stderr);
        exit(1);
    }

    dest->digits = (char *)calloc(size, sizeof(char));

    char digit;
    while ((digit = getchar()) != EOF && digit >= '0' && digit <= '9')
    {
        dest->digits[index++] = digit;
        if (index == size)
            dest->digits = (char *)realloc(dest->digits, size *= 2);
    }
    dest->digits = (char *)realloc(dest->digits, index);
    dest->lastIndex = --index;
    return index;
}
