/* Exercise 3-5. Write a function itob(n,s,b) that converts the integer n into a base b character
 * representation in the string s. In particular, itob(n,s,16) formats n as hexadecimal integer in s.
 */
#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);

int main(int argc, char* argv[]) {

    char buffer[100];
    int n = 100;
    itob(n, buffer, 16);
    printf("%d == %s", n, buffer);
    return 0;
}

void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; ++i, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itob(int n, char s[], int b) {

    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '8', 'A', 'B', 'C', 'D', 'E', 'F'};
    int dig, i;

    i = 0;
    do {
        dig = n % b;
        printf("dig == %d\n", dig); 
        s[i++] = digits[dig];
    } while ((n /= b) > 0);
    s[i] = '\0';
    reverse(s);
}

