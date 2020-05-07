/* Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The third argument is
 * a minimum field width; the converted number must be padded with blanks on the left if necessary to make
 * it wide enough.
 */
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int width);

int main(int argc, char* argv[]) {

    char string[1000];
    int width, n;
    width = 5;
    n = 10;
    itoa(n, string, width);
    printf("%d == %s\n", n, string);
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

void itoa(int n, char s[], int width) {

    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;

    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) {
        s[i++] = '-';
    }
    if (i < width) {
        for (; i < width; i++) {
            s[i] = ' ';
        }
    } 
    s[i] = '\0';
    reverse(s);
}

