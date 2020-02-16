/* Write a program to print a histgram of the frequencies of diffrent characters in its input. */
#include <stdio.h>

int main(int argc, char* argv[]) {
    int len, i, j, c;
    len = '~' - '!'; // Character range
    int hist[len];

    for (i = 0; i < len; ++i) {
        hist[i] = 0;
    }
    while ((c = getchar()) != EOF) {
        if (c >= '!' && c <= '~') {
            hist[c - '!']++;
        }
    }

    for (i = 0; i < len; ++i) {
        if (hist[i] != 0) {
            printf("%c | ", i + '!');

            for (j = 0; j < hist[i]; ++j) {
                printf("#");
            }
            printf("\n");
        }
    }
    return 0;
}
