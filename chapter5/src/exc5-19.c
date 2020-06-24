/* Exercise 5-19. Modify undcl so that it does not add redundant parentheses to declarations */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE  10000
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;        /* type of last token */
char token[MAXTOKEN]; /* last token string */
char out[1000];       /*output string*/

int main() {
    int type;
    int put_pointer;
    char temp[MAXTOKEN];

    put_pointer = 0;
    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) { /* is it a function or an array*/
                if (put_pointer) {
                    put_pointer = 0;
                    sprintf(temp, "(*%s)%s", out, token);
                    strcpy(out, temp);
                } else
                    strcat(out, token);
            } else if (put_pointer) {
                put_pointer = 0;
                sprintf(temp, "*%s", out); /* no need for parenthesis */
                strcpy(out, temp);
            } else if (type == '*')
                put_pointer = 1;
            else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        }
        printf("%s\n", out);
    }
    return 0;
}

int gettoken(void) { /* return next token */
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());) *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;

    } else
        return tokentype = c;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}

void flush(void) { bufp = 0; }
