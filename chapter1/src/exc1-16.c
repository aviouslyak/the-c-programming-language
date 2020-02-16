/* Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily long input lines, and as much as possible of the text */
#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int maxline);
void copy(char to[], char from[]);

int main(int argc, char* argv[]) {
    int len, max;
    char c;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = getLine(line, MAXLINE)) > 0) {
        if (line[len - 1] != '\n') {
            while ((c = getchar()) != EOF) {
                if (c == '\n') {
                    len++;
                    break;
                }
                len++;
            }
        }

        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) {
        printf("%s\n", longest);
        printf("Longest Line: %d\n", max);
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

void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}
