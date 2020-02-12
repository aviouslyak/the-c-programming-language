/* Exercise 1-12. Write a program that prints its input one word per line */
#include <stdio.h>
#define IN  1
#define OUT 0

int main(int argc, char* argv[]) {

    int c, status = 0;

    while ((c = getchar()) != EOF) {

        if (c == '\n' || c == ' ' || c == '\t' || c == '\b') {
            if (status == IN) {
                putchar('\n');
            }
            status = OUT;
        } else {
            status = IN;
            putchar(c);
        }
    }

    return 0;
}
