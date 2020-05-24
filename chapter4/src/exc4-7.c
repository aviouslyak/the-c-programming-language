/* Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or should it just use ungetch? */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP   100
#define NUMBER  '0'
#define MAXVAL  100
#define BUFSIZE 100

int getch(void);
void ungetch(int);
void ungets(char []);

int main(int argc, char* argv[]) {

    int c, i, len;
    char s[100];

    i = 0;
    while ((s[i++] = getch()) != '\n') {
        ;
    }

    s[i - 1] = '\0';



    ungets(s);

    len = strlen(s); 
    for (int j = 0; j < len; ++j) {
    }

    return 0;
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

/* pushes an entire string back onto input */
void ungets(char s[]) {
    int c, i;

    i = 0;
    while ((c = s[i++]) != '\0') {
        ungetch(c);
    }
}
