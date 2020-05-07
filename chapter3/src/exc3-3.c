/* Exercise 3-3. Write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list
 * abc...xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z
 * Arrange that a leading or trailing - is taken literally.
 */
#include <ctype.h>
#include <stdio.h>
#define MAXLEN 1000

int getInput(char input[]);
void expand(char s1[], char s2[]);

int main(int argc, char* argv[]) {

    char input[MAXLEN];
    getInput(input);

    printf("Raw Input: %s\n", input);
    char expanded[MAXLEN];
    expand(input, expanded);
    printf("Expanded Input: %s\n", expanded);
    return 0;
}

int getInput(char input[]) {
    int i = 0;
    char c;
    while ((c = getchar()) != EOF) {
        input[i++] = c;
    }
    input[i] = '\0';
    return i;
}

int areSame(char c1, char c2) {

    if (isdigit(c1) && isdigit(c2)) {
        return 1;
    } else if ((c1 >= 65 && c1 <= 90) && (c2 >= 65 && c2 <= 90)) {
        return 1;
    } else if ((c1 >= 97 && c1 <= 122) && (c2 >= 97 && c2 <= 122)) {
        return 1;
    } else {
        return 0;
    }
}
void expand(char s1[], char s2[]) {

    int i, j, p1, p2;
    char c;
    for (i = j = 0; (c = s1[i]) != '\0'; ++i) {
        if (c == '-' && i != 0 && areSame(s1[i - 1], s1[i + 1])) {
            p1 = s1[i - 1] + 1;
            p2 = s1[i + 1] - 1;
            for (; p1 <= p2; ++p1) {
                s2[j++] = p1;
            }
        } else {
            s2[j++] = c;
        }

        s2[j] = '\0';
    }
}
