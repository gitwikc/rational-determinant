// #include "./util/strint/misc.c"
// #include "./util/strint/strArithmetic.c"
// #include "./util/strint/Strint.c"
#include "./io/Strint.c"
#include "./io/matrix.c"
#include "./util/rational/Rational.c"
#include "./util/matrix/inverse.c"

int main()
{

    printf("Welcome to inverse calculator!!!\n\n");
    printf("Matrix dimension = ");
    int dim;
    scanf("%d", &dim);
    Rational **matrix = getSquareMatrix(dim);
    Rational **inverse = getInverse(matrix, dim);
    puts("You entered:\n");
    printMatrix(matrix, dim);
    puts("\n\nInverse is:\n");
    printMatrix(inverse, dim);

    return 0;
}
