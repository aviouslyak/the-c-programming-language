/* Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value? */

#include <ctype.h>
#include <stdio.h>
#define BUFSIZE 100

int getch(void);
void ungetch(int c);
int getfloat(double* pf);

int main(int argc, char* argv[]) {
    double p;
    int r;

    r = getfloat(&p);

    printf("getfloat returned %d\n", r);
    if (r > 0) {
        printf("p = %f\n", p);
    }
    return 0;
}

int getfloat(double* pf) {
    int c, sign, place;

    while (isspace(c = getch())) {
        ;
    }

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        c = getch();
    }

    if (!isdigit(c) && c != '.') {
        ungetch(c);
        return 0;
    }

    for (*pf = 0; isdigit(c); c = getch()) {
        *pf = 10 * *pf + (c - '0');
    }

    if (c != '.') {
        if (c != EOF) {
            ungetch(c);
        }
        *pf *= sign;
        return c;
    }

    c = getch();
    place = 1;
    for (; isdigit(c); c = getch()) {
        *pf = 10 * *pf + (c - '0');
        place *= 10;
    }

    if (c != EOF) {
        ungetch(c);
    }

    *pf *= sign;
    *pf /= place;

    return c;
}
char buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}

