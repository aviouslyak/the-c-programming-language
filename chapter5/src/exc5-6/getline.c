#include <stdio.h>
#define MAXLEN 1000

int getLine(char s[], int lim);

int main(int argc, char* argv[]) {

    int lim;
    char line[MAXLEN];

    while ((lim = getLine(line, MAXLEN)) > 0) 
       printf("%s\n", line); 

    return 0;
}

int getLine(char* s, int lim) {
    int c, i;
    char *p = s; 

    for (;  lim > 0 && (c = getchar()) != EOF && c != '\n'; s++) {
        *s = c;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - p;
}


