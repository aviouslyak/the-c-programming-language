/* Exercise 4-10. An alternate organization uses getLine to read an entire input line;
 * this makes getch and ungetch unnecessary. Revise the calculator to use this approach. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP  100
#define NUMBER '0'
#define MAXVAL 100
#define MAXLEN 100

int getop(char[]);
void push(double);
double pop(void);
int getLine(char[], int);

char buf[MAXLEN];
int position;

int main(int argc, char* argv[]) {
    int type, len;
    double op2;
    char s[MAXOP];

    while ((len = getLine(buf, MAXLEN)) > 0) {
        position = 0;
        while ((type = getop(s)) != '\0') {
            switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: Unknown command\n");
            }
        }
    }
    return 0;
}

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = buf[position++]) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c; // not a number
    }

    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = buf[position++])) {
            ;
        }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = buf[position++])) {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF) {
        position--;
    }
    return NUMBER;
}

/* getLine:  get line into s, return length */
int getLine(char s[], int lim) {

    int c, i;

    i = 0;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') s[i++] = c;

    if (c == '\n') s[i++] = c;

    s[i] = '\0';

    return i;
}
