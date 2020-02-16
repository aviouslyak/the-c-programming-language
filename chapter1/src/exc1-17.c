/* Write a program to print all input lines that are longer than 80 characters */
#include <stdio.h>
#define MINLENGTH 81
#define MAXLENGTH 1000

int getLine(char line[], int maxline);

int main(int argc, char* argv[]) {

    int len = 0;
    char line[MAXLENGTH];

    while ((len = getLine(line, MAXLENGTH)) > 0) {
        if (len < MINLENGTH) {
            printf("Line Contents: %s", line);
        }
    }
    return 0;
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

