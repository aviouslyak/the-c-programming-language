#include <stdio.h>

int main(int argc, char* argv[]) {
    int running = 1;
    while (running) {
        running = getchar() != EOF;
        printf("getchar() != EOF = %d\n", running);
    }
    return 0;
}
