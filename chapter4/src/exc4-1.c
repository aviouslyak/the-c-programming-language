/* Exercise 4-1. Write the function strrinedex(s,t), which returns the position of the rightmost
 * occurrence of t in s, or -1 if there is none.
 */
#include <stdio.h>
#define MAXLINE 1000

int getLine(char s[], int lim);
int strrindex(char s[], char t[]); 

int main(int argc, char* argv[]) {

    char line[MAXLINE];
    char pattern[] = "vi";
    int found;

    while (getLine(line, MAXLINE) > 0) {
        found = strrindex(line, pattern);
        printf("Right most occurence: %d\n", found);
    }
    return 0;
}
int getLine(char s[], int lim) {

    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int strrindex(char s[], char t[]) {

    int i, j, k, l;
    int occurrences[1000];

    l = 0;
    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
            ;
        }
        if (k > 0 && t[k] == '\0') {
            occurrences[l++] = i;
        }
    }

    int max = -1;
    for (i = 0; i < l; ++i) {
        if (occurrences[i] > max) {
            max = occurrences[i];
        }
    }

    return max;
}
