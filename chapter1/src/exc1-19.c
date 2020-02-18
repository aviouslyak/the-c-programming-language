/* Exercise 1-19. Write a function reverse(s) that reverses tje character string s. Use it to write a prgoram that reverses its input a line at a time. */
#include <stdio.h>
#define MAXLEN 1000

int getLine(char line[], int len);
void reverse(char line[]);
void copy(char to[], char from[]);

int main(int argc, char* argv[]) {

    int len;
    char c, line[MAXLEN];

    while ((len = getLine(line, MAXLEN)) > 0) {
        reverse(line);
        printf("%s\n", line);
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

void reverse(char line[]) {

    int i, j, newline;
    char reversed[MAXLEN];
    newline = j = 0;
    for (i = 0; line[i] != '\0'; ++i)
        ;
    for (; i > 0; i--) {
        if (line[i - 1] != '\n') {
            reversed[j++] = line[i - 1];
        } else {
            newline = 1;
        }
    }
    if (newline) {
            reversed[j++] = '\n';
    }
    reversed[j] = '\0';
    copy(line, reversed);
}

