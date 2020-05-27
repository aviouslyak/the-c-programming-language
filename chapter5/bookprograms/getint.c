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
    int n;
    getint(&n);

    printf("inputed n is %d\n", n);
    return 0;
}
