/* Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa, that is convert an integer into a string by calling a recursive routine. */
#include <stdio.h>

void itoa(int n, char s[]);

int main(int argc, char* argv[]) {
    int n = 0;
    char s[100];
    scanf("%d", &n);
    printf("You entered n = %d\n", n);

    itoa(n, s);
    printf("As a string n = %s\n", s);

    return 0;
}

int wrap(int n, char s[], int i) {

    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }

    if (n / 10) {
        i = wrap(n / 10, s, i);
    }
    s[i++] = n % 10 + '0';
    return i;
}

void itoa(int n, char s[]) {
    int i = 0;
    i = wrap(n, s, 0);
    s[i] = '\0';
}
