/* Exercise 4-8. Suppose there will never be more than one character of pushback. Modify getch and ungetch accordingly */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL  100
#define BUFSIZE 100

int getch(void);
void ungetch(int);

int main(int argc, char* argv[]) { return 0; }

char bufchar;
int assigned = 0;

int getch(void) {
    if (assigned) {
        assigned = 0;
        return bufchar;
    }
    return getchar();
}

void ungetch(int c) {
    if (assigned) {
        printf("ungetch: too many characters\n");
    } else {
        bufchar = c;
        assigned = 1;
    }
}
