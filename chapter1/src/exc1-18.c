/* Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines. */
#include <stdio.h>
#define MAXLEN 1000

int getExclusiveLine(char line[], int length);

int main(int argc, char* argv[]) {
    int len;
    char line[MAXLINE];

    while ((len = getExclusiveLine(line, MAXLEN)) > 0) {
        printf("%s\n", line);
    }
    return 0;
}

int isWhitespace(char c) {
    if (c == '\t' || c == ' ' || c == '\b') {
        return 1
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
    if (c == '\n') {
        line[len++] = c;
    }

    /* We wrote the string, is it correct?*/
    while (len > 0 && isWhitespace(line[len - 1])) {
            
    }
}

