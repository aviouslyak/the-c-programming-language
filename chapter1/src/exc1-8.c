#include <stdio.h>

int main(int argc, char* argv[]) {

    int newlines = 0;
    int blanks = 0;
    int tabs = 0;
    char c = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            newlines++;
        } else if (c == '\t') {
            blanks++;
        } else if (c == ' ') {
            blanks++;
        }
    }

    printf("\nThere are %d newlines,\n", newlines);
    printf("There are %d tabs,\n", tabs);
    printf("There are %d blanks\n", blanks);
    return 0;
    return 0;
}
