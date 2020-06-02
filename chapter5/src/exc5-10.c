
/* Exercise 5-10. Write the program expr which evaluates a reverse Polish expression
 * from the command line, where each operator or operand is a seperate argument
 * For example,
 *      expre 2 3 4 + *
 * evaluates 2 x (3+4).
 */

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

char buf[MAXLEN];
int position;

int main(int argc, char* argv[]) {
    int type, len;
    double op2;
    char s[MAXOP];
    char* bufp = buf;

    /* fill buf with args */
    if (argc == 1) {
        printf("Usage: expre nums ops\n");
    }

    while (--argc > 0) {
        ++argv;
        for (; (*bufp = *argv[0]++) != '\0'; bufp++)
            ;
        *bufp++ = ' ';
    }
    *bufp = '\0';
    /* evaluate buf */

    position = 0;
    do {
        type = getop(s);
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
        case '\0':
            printf("\t%.8g", pop());
            break;
        default:
            printf("error: Unknown command\n");
            break;
        }
    } while (type != '\0');

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

