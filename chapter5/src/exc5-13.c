/* Exercise 5-13. Write the program tail, which prints the last n lines of its input.
 * By default, n is 10, say, but it can be changed by an optional argument, so that
 *
 * tail -n
 *
 * prints the last n lines. The program should behave rationally no matter how unreasonable
 * the input or the value of n. Write the program so it makes the best use of available storage;
 * lines should be stored as in the sorting program of Section 5.6,
 * not in a two-dimensional array of fixed size. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN    1000
#define MAXLINES  10000
#define ALLOCSIZE 10000

int tail(char **, int, int);
int readlines(char **, int);

int main(int argc, char *argv[]) {
    int nlines, n;
    char *lineptr[MAXLINES];

    n = 10;
    if (argc == 2) {
        n = atoi(++argv[1]); 
    }
    else if (argc > 2) {
        printf("Usage: tail -n\n");
        return -1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        return tail(lineptr, nlines, n);
    } else {
        printf("error: input too large\n");
        return 1;
    }


    return 0;
}

/* tail: prints last n lines of lineptr, returns 0 on success
 * and -1 on failure */
int tail(char *lineptr[], int nlines, int n) {

    if (n > nlines) {
        printf("error: n too large; not enough lines\n");
        return -1;
    } else if (n < 0) {
        printf("error: n is negative\n"); 
        return -1; 
    }

    lineptr += nlines - n;
    for (; n > 0; lineptr++, n--) {
        printf("%s\n", *lineptr);
    }

    return 0;
}

int getLine(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getLine(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int getLine(char *s, int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) s[i] = c;

    if (c == '\n') {

        s[i] = c;

        ++i;
    }

    s[i] = '\0';

    return i;
}

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *alloc(int n) {                          /* returns pointer to n characters */
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else {               /* not enough room */
        return 0;
    }
}
