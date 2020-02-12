#include <stdio.h>

int main(int argc, char* argv[]) {

    char c;
    while ((c = getchar()) != EOF) {
        putchar(c);
        if (c == ' ') {
            while ((c = getchar()) != EOF && c == ' ') {
                ;
            }
            ungetc(c, stdin);
        }
    }
    return 0;
}
