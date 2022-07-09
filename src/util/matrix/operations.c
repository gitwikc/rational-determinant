#include <stdio.h>
#include <stdlib.h>
#include "../strint/Strint.c"
#include "../rational/Rational.c"

Rational **getSubmatrix(int dim, Rational **matrix, int remRow, int remCol)
{
    Rational **susmat;

    susmat = (Rational **)malloc((dim - 1) * sizeof(Rational *));
    for (int i = 0; i < dim - 1; i++)
        susmat[i] = (Rational *)malloc((dim - 1) * sizeof(Rational));

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            if (i != remRow && j != remCol)
                susmat[i - (i > remRow)][j - (j > remCol)] = matrix[i][j];

    return susmat;
}
