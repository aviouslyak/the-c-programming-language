/* Exercise 6-1. Our version of getword does not properly handle underscores,
 * string constants, comments, or preprocessor control lines. Write a better version */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN  10000
#define BUFSIZE 1000000
#define OUT 0
#define IN 1


void ungetch(int);
int getch(void);
void ungets(char[]);
void preproccess(void);

int main() {

    char word[MAXLEN], c;
    int i;

    preproccess();

    i = 0;
    while ((c = getword(word, MAXLEN)) != EOF) printf("%5d | %s\n", i++, word);

    return 0;
}

/* val_word_char: returns 1 if character is valid for a word, 0 if not */
int val_word_char(char c) { return (c == '_' || isalnum(c)); }

/* preproccess: filter the input stream, pushing each char back onto buf */
void preproccess(void) {
    int c, k, comment, string, pre;
    char buf[BUFSIZE];
    char *p = buf;

    k = 0;
    while ((c = getch()) != EOF) {
        switch (c) {
        case '/':
            if (k == '*') {
                comment = OUT;
                continue;
            }
            break;
        case '*':
            if (k == '/') {
                comment = IN;
                p--;
            }
            break;
        case '#':
            pre = IN;
            break;
        case '"':
            if (string)
                string = OUT;
            else
                string = IN;
        case '\n':
            string = OUT;
            pre = OUT;
            break;
        default:
            break;
        }

        if (!comment && !string && !pre) *(p++) = c;
        k = c;
    }

    *p = '\0';
    ungets(buf);
}

/* getword: get next word or charactter from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF) *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!val_word_char(*w = getch())) {
            ungetch(*w);
            break;
        }

    *w = '\0';
    return word[0];
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

/* pushes an entire string back onto input */
void ungets(char s[]) {
    int i;

    i = strlen(s);
    while (i-- >= 0) ungetch(s[i]);
}
