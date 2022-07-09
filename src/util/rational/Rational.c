#include "../strint/Strint.c"

typedef struct
{
    Strint numt;
    Strint deno;
} Rational;

Rational RAT_ZERO = {
    {1, "0", 0},
    {1, "1", 0}};
Rational RAT_ONE = {
    {1, "1", 0},
    {1, "1", 0}};
Rational RAT_MINUS_ONE = {
    {-1, "1", 0},
    {1, "1", 0}};

Rational negRational(Rational x)
{
    Rational neg;
    neg.numt = negative(x.numt);
    neg.deno = x.deno;
    return neg;
}
