/* Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid representation as zero. Fix it and push such a character back onto the input */
#include <ctype.h>
#include <stdio.h>
#define BUFSIZE 100

int getch(void);
void ungetch(int c);

char buf[BUFSIZE];
int bufp = 0;

int getint(int* pn) {
    int c, sign;

    while (isspace(c = getch())) {
        ;
    }

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }

    if (!isdigit(c)) {
        ungetch(c);
        return 0;
    }

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }

    return c;
}
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}

int main(int argc, char* argv[]) {
    int n, r;

    r = getint(&n); 
    if (r > 0) {
        printf("n = %d\n", n);
    } else {
        printf("invalid int, r = %d\n", r); 
    }
    return 0;
}
