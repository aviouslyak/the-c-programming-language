/* Exercise 2-4. Write an alternate version of squeeze(s1, s2) that deletes each character in s1 that matches any
 * character in the string s2.
 */
#include <stdio.h>
#define MAXLEN 1000

void squeeze(char s1[], char s2[]);
void copy(char to[], char from[]);

int main(int argc, char* argv[]) {

    char s1[] = "ABCDEF";
    char s2[] = "FGHIJK";
    printf("s1 before squeeze(): %s\n", s1); 
    squeeze(s1, s2);
    printf("s1 after squeeze(): %s\n", s1); 

    return 0;
}

void squeeze(char s1[], char s2[]) {
    char c, k, buffer[MAXLEN];
    int i, j, l, place;
    place = 1;
    /* For every char in s1
     * if that char is in s2
     * dont place in buffer
     * else
     * place it in buffer
     */
    for (i = l = 0; (c = s1[i]) != '\0'; ++i) {
        for (j = 0; (k = s2[j]) != '\0'; ++j) {
            if (c == k) {
                place = 0;
            }
        }
        if (place) {
            buffer[l++] = c;
        }
        place = 1;
    }
    buffer[l] = '\0';
    copy(s1, buffer);
}

void copy(char to[], char from[]) {

    int i;
    for (i = 0; (to[i] = from[i]) != '\0'; ++i) {
        ;
    }
    to[i++] = '\0';
}
