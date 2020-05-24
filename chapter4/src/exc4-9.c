/* Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF correctly.
 * Decide what their properties ought to be if an EOF is pushed back, then implement your design/ */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);

int main(int argc, char* argv[]) {
    int c = 0;

    ungetch(EOF); 

    while ((c = getch()) != EOF) {
            putchar(c); 
    }

    return 0;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else if (c != EOF) {
        printf("added %c\n", c);
        buf[bufp++] = c;
    }
}
