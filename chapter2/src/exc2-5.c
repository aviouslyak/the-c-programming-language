/* Exercise 2-5. Write the function any(s1, s2), which returns the first location in the string s1 where
 * any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard
 * library function strpbrk does the same job but returns a pointer to the location.)
 */
#include <stdio.h>

int any(char s1[], char s2[]);

int main(int argc, char* argv[]) {
    int rval;
    char s1[] = "ABCDEF";
    char s2[] = "B";

    rval = any(s1, s2);
    printf("any(s1, s2) == %d\n", rval);
    return 0;
}

int any(char s1[], char s2[]) {
    int i, j;
    char c, k;

    for (i = 0; (c = s1[i]) != '\0'; ++i) {
        for (j = 0; (k = s2[j]) != '\0'; ++j) {
            if (k == c) {
                return i;
            }
        }
    }
    return -1;
}
