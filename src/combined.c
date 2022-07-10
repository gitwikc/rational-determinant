#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// ======================== Strint Integer =======================
#define max(a, b) ((a) > (b)) ? (a) : (b);
#define min(a, b) ((a) < (b)) ? (a) : (b);

char *intToString(int x)
{
    int len = ((int)log10l(x) + 1);
    char *s = calloc(len, sizeof(char));
    int i = 0;
    while (x > 0)
    {
        s[len - i++ - 1] = '0' + (x % 10);
        x /= 10;
    };
    return s;
}

char *addString(char *x1, char *x2)
{
    int maxLength = max(strlen(x1), strlen(x2));
    int minLength = min(strlen(x1), strlen(x2));
    if (strlen(x1) == minLength)
    {
        char *temp = x1;
        x1 = x2;
        x2 = temp;
    }
    //   printf("%s %s \n", x1, x2);
    int *nSum = (int *)calloc(maxLength + 1, sizeof(int));
    for (int i = 0; i < maxLength; i++)
    {
        int d1 = x1[maxLength - 1 - i] - '0';
        int d2 = (i < minLength) ? x2[minLength - 1 - i] - '0' : 0;
        int dSum = nSum[maxLength - i] + d1 + d2;
        nSum[maxLength - i] = dSum % 10;
        nSum[maxLength - i - 1] = dSum / 10;
    }

    char *cSum = (char *)malloc((maxLength + 1) * sizeof(char));
    for (int i = 0; i <= maxLength; i++)
    {
        cSum[i] = '0' + nSum[i];
    }

    return cSum;
}

char *subtString(char *x1, char *x2)
{
    int maxLength = max(strlen(x1), strlen(x2));
    int minLength = min(strlen(x1), strlen(x2));
    if (strlen(x1) == minLength)
    {
        char *temp = x1;
        x1 = x2;
        x2 = temp;
    }
    //   printf("%s %s \n", x1, x2);
    int *nDiff = (int *)calloc(maxLength, sizeof(int));

    int carry = 0;
    for (int i = 0; i < maxLength; i++)
    {
        int d1 = x1[maxLength - i - 1] - '0' + carry;
        int d2 = (i < minLength) ? x2[minLength - i - 1] - '0' : 0;
        int dDiff = d1 - d2;
        if (dDiff < 0)
        {
            dDiff = d1 + 10 - d2;
            carry = -1;
        }
        else
            carry = 0;
        nDiff[maxLength - i - 1] = dDiff;
    }
    char *sDiff = (char *)calloc(maxLength, sizeof(char));
    for (int i = 0; i < maxLength; i++)
        sDiff[i] = nDiff[i] + '0';

    free(nDiff);
    return sDiff;
}

char *multString(char *x1, char *x2)
{
    int len1 = strlen(x1);
    int len2 = strlen(x2);
    if (len1 == 0 || len2 == 0)
        return "0";

    // Store product digits reversed
    int *result = (int *)calloc(len1 + len2, sizeof(int));

    int inx1 = 0;
    int inx2 = 0;

    // x1: R -> L
    for (int i = len1 - 1; i >= 0; i--, inx1++)
    {
        int carry = 0;
        int d1 = x1[i] - '0';

        // Shift res of mult w digit to left by 1 place
        inx2 = 0;

        // x2: R -> L
        for (int j = len2 - 1; j >= 0; j--)
        {
            int d2 = x2[j] - '0';
            int dSum = d1 * d2 + result[inx1 + inx2] + carry;

            carry = dSum / 10;
            result[inx1 + inx2] = dSum % 10;
            inx2++;
        }
        // Carry forward
        result[inx1 + inx2] += min(carry, 0);
    }

    // Ignore zeros on right
    int lastNonZeroIndex = len1 + len2 - 1;
    while (lastNonZeroIndex >= 0 && result[lastNonZeroIndex] == 0)
        lastNonZeroIndex--;

    // If all 0 => one of params = 0
    if (lastNonZeroIndex == -1)
        return "0";

    // generate the result string
    char *s = (char *)malloc(lastNonZeroIndex * sizeof(char));

    int lastNonZeroIndexCopy = lastNonZeroIndex;
    while (lastNonZeroIndexCopy >= 0)
        s[lastNonZeroIndexCopy] = result[lastNonZeroIndexCopy--] + '0';

    char *revs = (char *)calloc((lastNonZeroIndex + 1), sizeof(char));
    for (int i = 0; i <= lastNonZeroIndex; i++)
    {
        revs[i] = s[lastNonZeroIndex - i];
    }

    return revs;
}

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

// =========================== Rational ======================

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

// ============================= Matrix ===================
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

Rational getDeterminant(Rational **matrix, int dim)
{
    if (dim == 1)
        return matrix[0][0];

    Rational det = {1, "0", 0};
    for (int i = 0; i < dim; i++)
    {
        Rational multSign = {{(i % 2 == 0 ? 1 : -1), "1", 0}, {1, "1", 0}};
        det = multRational(multRational(matrix[0][i],
                                        getDeterminant(getSubmatrix(dim, matrix, 0, i), dim - 1)),
                           multSign);
    }

    return det;
}

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
                    getDeterminant(getSubmatrix(dim, matrix, i, j), dim - 1)),
                det);

    return inverse;
}

// ==================== Input & Output =================
// --------------- String Integer --------------

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

    fflush(stdin);
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

// --------------------- Rational -------------------
int getRational(Rational *dest)
{
    printf("\n>> Numerator = ");
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

// ----------------- Matrix ------------------
Rational **getSquareMatrix(int dim)
{
    Rational **mat;

    mat = (Rational **)malloc(dim * sizeof(Rational *));
    for (int i = 0; i < dim; i++)
        mat[i] = (Rational *)malloc(dim * sizeof(Rational));

    for (int i = 0; i < dim; i++) {
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

void printMatrix(int dim, Rational **mat) {
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

// =============== MAIN ==================
int main() {

    printf("Welcome to inverse calculator!!!\n\n");
    printf("Matrix dimension = ");
    int dim;
    scanf("%d", &dim);
    Rational **matrix = getSquareMatrix(dim);
    Rational **inverse = getInverse(matrix, dim);
    puts("You entered:\n");
    printMatrix(dim, matrix);

    if (getDeterminant(matrix, dim).numt.digits[0] == '0')
    {
        printf("Singular matrix does not have inverse...");
        exit(1);
    }

    puts("\n\nInverse is:\n");
    printMatrix(dim, inverse);

    return 0;
}
