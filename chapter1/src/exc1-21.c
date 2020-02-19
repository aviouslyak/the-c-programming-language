/* Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing.
 * Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?
 */
#include <stdio.h>
#define MAXLEN 1000

void detab(char line[], int maxlen, int n);
int getLine(char s[], int lim);
void copy(char to[], char from[]);
void printLiteral(char line[], int len);

int main(int argc, char* argv[]) {

    char line[MAXLEN] = "This is a long string  Those were some tabs  Tabs b gone";
    int n = 2;

    printf("String: ");
    printLiteral(line, MAXLEN);
    detab(line, MAXLEN, n);
    printf("String after detab(): ");
    printLiteral(line, MAXLEN);

    return 0;
}

void detab(char line[], int maxlen, int n) {
    int i, j, spaces;
    char detabed[MAXLEN], c;
    spaces = 0;

    for (i = j = 0; (c = line[i]) != '\0'; ++i) {
        if (c != ' ') {
            if (spaces > 0) {
                for (; spaces > 0; --spaces) {
                    detabed[j++] = ' ';
                }
            }
            detabed[j++] = c;
            spaces = 0;
        } else {
            spaces++;
            if (spaces >= n) {
                detabed[j++] = '\t';
                spaces = 0;
            }
        }
    }
    detabed[j] = '\0';

    copy(line, detabed);
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

void printLiteral(char line[], int len) {
    int i;
    char c;
    for (i = 0; i < len && (c = line[i]) != '\0'; ++i) {
        if (c == '\t') {
            putchar('\\');
            putchar('t');
        } else if (c == ' ') {
            putchar('$');
        } else if (c == '\b') {
            putchar('\\');
            putchar('b');
        } else if (c == '\n') {
            putchar('\\');
            putchar('n');
        } else {
            putchar(c);
        }
    }
    putchar('\n');
}

