/* Exercise 5-15. Add the option -f to fold upper and lower case together, so that case distinctions are not made during sorting;
 * for example, a and A compare equal */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES  5000  /* max #lines to be sorted */
#define MAXLEN    1000  /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qSort(void *[], int, int, int (*)(const void *, const void *));
void to_same_case(char *);
void reverse(void *[], int);
int numcmp(const char *, const char *, int);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines, numeric, backwords, fold, c;
    numeric = backwords = fold = 0; /* command line args */

    while (--argc > 0 && (*++argv)[0] == '-') {
        c = (*argv)[1];
        switch (c) {
        case 'n':
            numeric = 1;
            break;

        case 'r':
            backwords = 1;
            break;

        case 'f':
            fold = 1;
            break;

        default:
            printf("sort: invalid option %c\n", c);
            return 1;
            break;
        }
    }

    if (argc > 1) {
        printf("sort: invalid option(s)\n");
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qSort((void **)lineptr, 0, nlines - 1, (int (*)(const void *, const void *))(numeric ? numcmp : strcmp));

        if (backwords) reverse((void **)lineptr, nlines);
        writelines(lineptr, nlines);
        return 0;

    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int getLine(char *, int);
char *alloc(int);

/* readlines: read input lines */
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

/* getLine: read a line into s, return length */
int getLine(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qSort(void *v[], int left, int right, int (*comp)(const void *, const void *)) {
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right) return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0) swap(v, ++last, i);
    swap(v, left, last);
    qSort(v, left, last - 1, comp);
    qSort(v, last + 1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* to_same_case: converts string to all the same case for comparison */
void to_same_case(char *s) {
    while (*s++ != '\0') {
        *s = tolower(*s);
    }
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* reverse: reverse the contents of v */
void reverse(void *v[], int len) {
    int beg = 0;
    len--;
    for (; beg < len; beg++, len--) swap(v, beg, len);
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
