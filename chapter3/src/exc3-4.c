/* Exercise 3-4. In a two's complement number representation our version of itoa does not handle the largest
 * negative number, that is, the vault of n equal to -(2^(wordsize - 1)). Explain why not. Modify it to print
 * that value correctly, regardless of the machine on which it runs.
 */
#include <limits.h>
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);

int main(int argc, char* argv[]) {

    char integer[1000];
    printf("Minimum int: %d\n", INT_MIN);
    itoa(INT_MIN, integer);
    printf("Minimum int According to itoa: %s\n", integer);
    return 0;
}

void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; ++i, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
void itoa(int n, char s[]) {

    int i, sign;
    unsigned int un; 

    un = n; 
    if ((sign = un) < 0) {
        un = -un;
    }
    i = 0;
    do {
        s[i++] = un % 10 + '0';
    } while ((un /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}
