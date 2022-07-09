#include "Rational.c"

Rational addRational(Rational x1, Rational x2)
{
    Rational sum;
    sum.numt = addStrint(multStrint(x1.numt, x2.deno), multStrint(x1.deno, x2.numt));
    sum.deno = multStrint(x1.deno, x2.deno);
    return sum;
}

Rational subtRational(Rational x1, Rational x2)
{
    return addRational(x1, negRational(x2));
}

Rational multRational(Rational x1, Rational x2)
{
    Rational product;
    product.numt = multStrint(x1.numt, x2.numt);
    product.deno = multStrint(x1.deno, x2.deno);
    return product;
}

Rational divRational(Rational x1, Rational x2)
{
    Rational quot;
    quot.numt = multStrint(x1.numt, x2.deno);
    quot.deno = multStrint(x2.numt, x1.deno);
    return quot;
}
