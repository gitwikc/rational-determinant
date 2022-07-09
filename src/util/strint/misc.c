#define max(a, b) ((a) > (b)) ? (a) : (b);
#define min(a, b) ((a) < (b)) ? (a) : (b);

char *intToString(int x)
{
    int len = ((int)log10(x) + 1);
    char *s = calloc(len, sizeof(char));
    int i = 0;
    while (x > 0)
    {
        s[len - i++ - 1] = '0' + (x % 10);
        x /= 10;
    };
    return s;
}
