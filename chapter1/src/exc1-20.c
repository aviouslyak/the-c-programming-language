/* Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume
 * a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?
 */
#include <stdio.h>
#define MAXLEN 1000

void entab(char line[], int maxlen, int n);
int getLine(char s[], int lim);
void copy(char to[], char from[]);

int main(int argc, char* argv[]) {

    char line[MAXLEN] = "This is a long string\t\tThose were some tabs";
    int n = 1; 

    printf("String: %s\n", line);
    entab(line, MAXLEN, n);
    printf("String after entab(): %s\n", line);

    return 0;
}

void entab(char line[], int maxlen, int n) {
    int i, j, l;
    char entabed[maxlen], c;

    for (i = 0, j = 0; j < maxlen && (c = line[i]) != '\0'; ++i) {
        if (c != '\t') {
            entabed[j++] = c;
        } else {
            l = 0;
            while (l < n) {
                entabed[j++] = ' ';
                l++;
            }
        }
    }

    if (j < maxlen) {
        entabed[j] = '\t';
    }

    copy(line, entabed);
}
int getLine(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

