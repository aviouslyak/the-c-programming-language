/* Exercise 5-17. Add a field-handling capability, so sorting may be done on fields within lines,
 * each field sorted according to an independent set of options. (The index for the book was sorted with -df
 * for the index category and -n for the page numbers. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES  5000  /* max #lines to be sorted */
#define MAXLEN    1000  /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */
#define ARGS      2
#define FOLD      0
#define DIRECTORY 1

char *lineptr[MAXLINES]; /* pointers to text lines */

int args[ARGS] = {0};
int field = -1;

int readlines(char *lineptr[], int nlines);
void modifyline(char *newline, char *line);
void writelines(char *lineptr[], int nlines);

void qSort(void *[], int, int, int (*)(void *, void *));
void to_same_case(char *, char *);
void reverse(void *[], int);
int numcmp(char *, char *);
int strcmpm(char *, char *);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines, numeric, backwords, fold, c;
    numeric = backwords = fold = 0; /* command line args */

    args[FOLD] = 0;
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
            args[FOLD] = 1;
            break;

        case 'd':
            args[DIRECTORY] = 1;
            break;

        default:
            printf("sort: invalid option %c\n", c);
            return 1;
            break;
        }
    }

    if (argc >= 1 && isdigit((*argv)[0])) {
        field = atoi(*argv);
        if (field < 1) {
            printf("sort: invalid field length\n");
            return 1;
        }
        argc--;
    }

    if (argc > 0) {
        printf("sort: invalid option(s)\n");
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {

        /* modify lines based off of args */

        qSort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numcmp : strcmpm));

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

/* modifylines: modify line based off of flags */
void modifyline(char *newline, char *line) {
    char s[MAXLEN];
    int i, j, field_number;
    strcpy(newline, line);

    if (args[FOLD]) to_same_case(newline, line);

    if (args[DIRECTORY]) {
        strcpy(s, newline);
        for (i = 0, j = 0; s[i] != '\0'; i++)
            if (isalpha(s[i]) || isdigit(s[i]) || isspace(s[i])) newline[j++] = s[i];
        newline[j] = '\0';
    }

    if (field >= 0) {
        field_number = field - 1;
        i = j = 0;

        while (newline[j] != '\0' && field_number >= 0) {
            while (!isspace(newline[j]) && newline[j] != '\0') {
                s[i++] = newline[j++];
            }

            s[i] = '\0';

            if (i != 0) field_number--;

            if (isspace(newline[j])) {
                j++;
                i = 0;
            }

        }
        strcpy(newline, s);
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
void qSort(void *v[], int left, int right, int (*comp)(void *, void *)) {
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
int numcmp(char *s1, char *s2) {
    double v1, v2;
    char ns1[MAXLEN], ns2[MAXLEN];

    modifyline(ns1, s1);
    modifyline(ns2, s2);

    v1 = atof(ns1);
    v2 = atof(ns2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* strcmpm: strcmp, but modifies input */
int strcmpm(char *s1, char *s2) {
    char ns1[MAXLEN], ns2[MAXLEN];
    modifyline(ns1, s1);
    modifyline(ns2, s2);

    return strcmp(ns1, ns2);
}

/* to_same_case: converts string to all the same case for comparison */
void to_same_case(char *ns, char *s) {
    while (*s != '\0') *ns++ = tolower(*s++);
    *ns = '\0';
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
