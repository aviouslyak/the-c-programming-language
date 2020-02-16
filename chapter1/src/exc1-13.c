/* Exercise 1-13. Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a verticle orientation is more challenging */
#include <stdio.h>
#define IN     1
#define OUT    0
#define MAXLEN 100

int main(int argc, char* argv[]) {

    int i, j, c, status, len, lengths[MAXLEN];
    c = status = len = 0;

    for (i = 0; i < MAXLEN; ++i) {
        lengths[i] = 0;
    }

    while ((c = getchar()) != EOF) {

        if (c == '\n' || c == ' ' || c == '\t' || c == '\b') {
            if (status == IN) { // At the end of a word
                lengths[len]++;
                len = 0;
            }
            status = OUT;
        } else { // Encountered/Inside word
            status = IN;
            len++;
        }
    }

    // Print histogram
    printf("\n");
    for (i = 0; i < MAXLEN; ++i) {
        if (lengths[i] != 0) {
            printf("%3d | ", i);
            for (j = 0; j < lengths[i]; ++j) {
                printf("#");
            }
            printf("\n");
        }
    }

    return 0;
}
