#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strArithmetic.c"

typedef struct
{
    int sign;
    char *digits;
    int lastIndex;
} Strint;

char *strintToString(Strint strint)
{
    char *string;
    sprintf(string, "%c%s\n", (strint.sign < 0) ? '-' : '\0', strint.digits);
    return string;
}

const Strint ONE = {1, "1", 0}, ZERO = {1, "0", 0};

Strint negative(Strint x)
{
    Strint neg = {-x.sign, x.digits, x.lastIndex};
    return neg;
}

/**
 * Compare absolute values of two Strints
 */
int compareAbs(Strint x1, Strint x2)
{
    int result = 0;
    if (x1.lastIndex < x2.lastIndex)
        result = -1;
    else if (x1.lastIndex > x2.lastIndex)
        result = 1;
    else
        for (int i = 0; i < x1.lastIndex; i++)
        {
            if ((result = x1.digits[i] - x2.digits[i]) != 0)
                return result;
        }

    return result;
}

/**
 * Comapares two Strints.
 * Returns positive int if x1 > x2
 * Returns negative int if x1 < x2
 * Returns 0 if x1 == x2
 */
int compare(Strint x1, Strint x2)
{
    if (x1.sign > 0 && x2.sign < 0)
        return 1;
    if (x1.sign < 0 && x2.sign > 0)
        return -1;

    int result = compareAbs(x1, x2);

    if (x1.sign < 0 && x2.sign < 0)
        result = -result;

    return result;
}

int equal(Strint x1, Strint x2) { return compare(x1, x2) == 0; }

/*
 * Maximum of two Strints
 */
Strint maxInt(Strint x1, Strint x2)
{
    return (compare(x1, x2) > 0) ? x1 : x2;
}

/*
 * Minimum of two Strints
 */
Strint minInt(Strint x1, Strint x2)
{
    return (compare(x1, x2) < 0) ? x1 : x2;
}

// ===============================================
Strint addStrint(Strint x1, Strint x2)
{
    Strint sum;
    if (x1.sign == x2.sign)
    {
        Strint big = maxInt(x1, x2), small = minInt(x1, x2);
        sum.sign = x1.sign;
        sum.digits = addString(big.digits, small.digits);
    }
    else
    {
        // Identify larger number and its sign
        int comp = compareAbs(x1, x2);
        Strint larger = (comp > 0) ? x1 : x2, smaller = (comp < 0) ? x1 : x2;
        sum.sign = larger.sign;
        sum.digits = subtString(larger.digits, smaller.digits);
    }
    return sum;
}

Strint subtStrint(Strint x1, Strint x2)
{
    Strint diff = addStrint(x1, negative(x2));
    return diff;
}

Strint multStrint(Strint x1, Strint x2)
{
    char *prodDigits = multString(x1.digits, x2.digits);
    Strint product = {
        (x1.sign == x2.sign) ? 1 : -1,
        prodDigits,
        strlen(prodDigits) - 1};
    return product;
}
