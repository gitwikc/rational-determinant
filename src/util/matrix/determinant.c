#include "./util/strint/Strint.c"
#include "./util/rational/Rational.c"
#include "./util/rational/ratArithmetic.c"
#include "./operations.c"

Rational getDeterminant(Rational **matrix, int dim)
{
    if (dim == 1)
        return matrix[0][0];

    Rational det = {1, "0", 0};
    for (int i = 0; i < dim; i++)
    {
        Rational multSign = {{(i % 2 == 0 ? 1 : -1), "1", 0}, {1, "1", 0}};
        det = multRational(multRational(matrix[0][i],
                                        getDeterminant(dim - 1, getSubmatrix(dim, matrix, 0, i))),
                           multSign);
    }

    return det;
}
