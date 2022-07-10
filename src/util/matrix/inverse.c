#include "../rational/Rational.c"
#include "../rational/ratArithmetic.c"
#include "./determinant.c"

Rational **getInverse(Rational **matrix, int dim)
{
    Rational **inverse = (Rational **)malloc(dim * sizeof(Rational *));
    for (int i = 0; i < dim; i++)
        inverse[i] = malloc(dim * sizeof(Rational));
    Rational det = getDeterminant(matrix, dim);

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            inverse[j][i] = divRational(
                multRational(
                    (((i + j) % 2 == 0) ? RAT_ONE : RAT_MINUS_ONE),
                    getDeterminant(dim - 1, getSubmatrix(dim, matrix, i, j))),
                det);

    return inverse;
}