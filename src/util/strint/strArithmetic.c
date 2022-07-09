#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.c"

// int max(int x1, int x2) { return (x1 > x2) ? x1 : x2; }
// int min(int x1, int x2) { return (x1 < x2) ? x1 : x2; }

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

// int main()
// {
//     printf("%s\n", multString("91", "120"));
//     printf("%d\n", strcmp("230", "232"));

//     return 0;
// }
