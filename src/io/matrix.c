#include <stdio.h>
#include <stdlib.h>
#include "../util/rational/Rational.c"
#include "./Rational.c"

Rational **getSquareMatrix(int dim)
{
    Rational **mat;

    mat = (Rational **)malloc(dim * sizeof(Rational *));
    for (int i = 0; i < dim; i++)
        mat[i] = (Rational *)malloc(dim * sizeof(Rational));

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printf("mat[%d][%d]:", i, j);
            // scanf("%d", &mat[i][j]);
            getRational(&mat[i][j]);
            puts("----------------------\n");
        }
        printf("=======================\n");
    }

    return mat;
}

void printMatrix(int dim, Rational **mat)
{
    printf("[\n");
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printRational(mat[i][j]);
            printf("\t");
        }
        printf("\n");
    }
    printf("]\n\n");
    return;
}
