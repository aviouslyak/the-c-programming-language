/* Exercise 5-20. Expand dcl to handle declarations wtih function argument types, qualifiers like const, and so on */



/*
 *
 * EXERCISE IS WIP 
 *
 *
 */ 
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE  10000
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { NONVALID, VALID };
enum { OUT, IN };

void dcl(int *);
void dirdcl(int *);

int gettoken(void);
void flush(void);
int tokentype;           /* type of last token */
int status;              /* is the declaration valid or not */
int local;               /* in argument list */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
int args[1000];          /* argument list */
char out[1000];          /* output string */

int main() { /* convert declaration to words */
    while (gettoken() != EOF) {
        status = VALID;
        strcpy(datatype, token);
        out[0] = '\0';
        name[0] = '\0';
        args[0] = '\0';
        dcl(out);
        if (tokentype != '\n') printf("syntax error\n");

        if (!status)
            flush();
        else
            printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/* dcl: parse a daclarator */
void dcl(int *output) {
    int ns;

    for (ns = 0; gettoken() == '*';) /* count *'s */
        ns++;
    dirdcl(output);
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

/* dirdcl: parse a direct declarator */
void dirdcl(int *output) {
    int type;

    if (tokentype == '(') {

        if (!name[0]) { /* we went into the first paren "tree" and discovered out name, and exited. No we are in a new one */
            dcl(args);
        } else 
            dcl(output);
        if (tokentype != ')') {
            printf("error: missing )\n");
            status = NONVALID;
        } else if (!name[0]) { /* returning from a function */ 
           strcat(out, " function taking");
             
        }
    } else if (tokentype == NAME)
        strcpy(name, token);
    else {
        printf("error: expected name or (dcl)\n");
        status = NONVALID;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(output, " function returning");
        else {
            strcat(output, " array");
            strcat(output, token);
            strcat(output, " of");
        }
    }

    if (tokentype == '(') {
        dirdcl(output);
    }
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
