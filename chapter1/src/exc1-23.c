/* Exercise 1-23. Write a program to remove all comments from a C program. Don't forget to handle quoted strings and
 * character constants properly. C comments do not nest.
 */

#include <stdio.h>
#define MAXLEN     10000
#define NOTCOMMENT 0
#define SINGLELINE 1
#define MULTILINE  2

void decomment(char program[], int maxlen);
void copy(char to[], char from[]);

int main(int argc, char* argv[]) {

    int i;
    char c, program[MAXLEN];

    // Fill program string with the program
    i = 0;
    while ((c = getchar()) != EOF && i < MAXLEN) {
        program[i++] = c;
    }
    program[i] = '\0';

    decomment(program, MAXLEN);
    printf("Program with no comments:\n%s", program);
    return 0;
}

int isComment(char string[], int index) {
    /* Returns 0 if not a comment
     * Returns 1 if it's a singline comment
     * Returns 2 if it's a multiline comment
     */
    if (string[index] == '/') {
        if (string[index + 1] == '/') {
            return SINGLELINE;
        } else if (string[index + 1] == '*') {
            return MULTILINE;
        }
    }
    return NOTCOMMENT;
}

void decomment(char program[], int maxlen) {
    int i, j, in, status, state;
    char buffer[maxlen], c;

    i = j = 0;
    while ((c = program[i++]) != '\0' && j < maxlen) {
        if (c == '/') {
            status = isComment(program, i - 1);
            if (status == 1) {
                i++; //Skip next /
            }
        }

        if (!status) {
            buffer[j++] = c;
        } else if (status == 1 && c == '\n') {
            status = NOTCOMMENT;
        } else if (status == 2) {
            if (program[i - 1] == '*' && program[i] == '/') {
                status = NOTCOMMENT;
                i++; // Skip next char
            }
        }
    }
    copy(program, buffer);
}

void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

