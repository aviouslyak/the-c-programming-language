/* Exercise 4-6. Add comands for handling variables. (It's easy to provide twenty-six variable single-letter names.)
 * Add a variable for the most recently printed value.
 */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP   100
#define NUMBER  '0'
#define MAXVAL  100
#define BUFSIZE 100
#define SIN     '!'
#define COS     '"'
#define TAN     '#'
#define POW     '^'
#define EXP     '$'
#define JUNK    '|'
#define VAR     '?'

int getop(char[]);
void push(double);
double pop(void);
double peek(void);

int main(int argc, char* argv[]) {
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            printf("before pushing\n");
            push(atof(s));
            printf("after pushing\n");
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
        case '%':
            op2 = pop();
            push((int)pop() % (int)op2);
            break;

        case POW:
            op2 = pop();
            double val = pow(pop(), op2);
            push(val);
            break;
        case TAN:
            push(tan(pop()));
            break;
        case EXP:
            push(exp(pop()));
            break;
        case COS:
            push(cos(pop()));
            break;
        case SIN:
            push(sin(pop()));
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: Unknown command\n");
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

double peek(void) {
    if (sp > 0) {
        return val[sp];

    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getch(void);
void ungetch(int);

int vars[26];

/* ftoc: translates function name into one letter char */
char ftoc(char s[]) {
    if (strcmp(s, "sin") == 0) {
        return SIN;
    } else if (strcmp(s, "cos") == 0) {
        return COS;
    } else if (strcmp(s, "tan") == 0) {
        return TAN;
    } else if (strcmp(s, "exp") == 0) {
        return EXP;
    } else if (strcmp(s, "pow") == 0) {
        return POW;
    } else {
        return JUNK;
    }
}
/* getop: get next operator or numeric operand */
int getop(char s[]) {
    vars[0] = 1;
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }

    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-' && !isalpha(c)) {
        printf("returning %c here\n", c);
        return c; // not a number } i = 0;
    }

    if (isalpha(c)) {
        c = tolower(c);
        while (isalpha(s[++i] = c = tolower(getch()))) {
            ;
        }
        s[i] = '\0';
        if (c != EOF) {
            ungetch(c);
        }

        printf("strlen(s) == %d\n", strlen(s));
        if (strlen(s) == 1) { /* Is it a variable */
            sprintf(s, "%f", vars[c - 'a']);
            return NUMBER;
        }
        return ftoc(s);
    }

    if (c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            return '-';
        }
        ungetch(c);
    }

    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }

    if (c == '.') {
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
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
