/* Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines. */
#include <stdio.h>
#define MAXLEN 1000

int getExclusiveLine(char line[], int length);
void printLiteral(char line[], int len);

int main(int argc, char* argv[]) {
    int len;
    char line[MAXLEN];

    while ((len = getExclusiveLine(line, MAXLEN)) >= 0) {
        if (len != 0) {
                printLiteral(line, MAXLEN);
        }
    }
    return 0;
}

int isWhitespace(char c) {
    if (c == '\t' || c == ' ' || c == '\b') {
        return 1;
    }
    return 0;
}

int getExclusiveLine(char line[], int maxlen) {
    int len;
    char c;

    len = 0;
    while ((c = getchar()) != EOF && c != '\n' && len < maxlen - 1) {
        line[len++] = c;
    }
    /*
     */

    /* We wrote the string, is it correct?*/
    // len - 1 is '\n'
    while (len > 0 && isWhitespace(line[len - 1])) {
        len--;
    }
    if (c == '\n' && len != 0) {
        line[len++] = c;
    }
    line[len] = '\0';
    if (c == EOF) {
        return -1;
    }

    return len;
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
