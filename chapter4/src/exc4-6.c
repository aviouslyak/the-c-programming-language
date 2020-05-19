/* Exercise 4-5. Add access to library functions like sin, exp, and pow. See <math.h> in Appendix B, section 4. */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP       100
#define NUMBER      '0'
#define MAXVAL      100
#define BUFSIZE     100
#define SIN         '!'
#define COS         '"'
#define TAN         '#'
#define POW         '^'
#define EXP         '$'
#define JUNK        '|'
#define UNDEFINED   '('
#define NOTVALID    ')'
#define LASTUSEDVAR '@'

int getop(char[]);
void push(double);
double pop(void);
double peek(void);
double last_used = 0;

int main(int argc, char* argv[]) {
    int type;
    double op2;
    char s[MAXOP];
    double val;

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            val = atof(s);
            last_used = val;
            push(val);
            break;
        case '+':
            val = pop() + pop();
            last_used = val;
            push(val);
            break;
        case '*':
            val = pop() * pop();
            last_used = val;
            push(val);
            break;
        case '-':
            op2 = pop();
            val = pop() - op2;
            last_used = val;
            push(val);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0) {
                val = pop() / op2;
                last_used = val;
                push(val);
            }
            break;
        case '%':
            op2 = pop();
            val = (int)pop() % (int)op2;
            push(val);
            break;

        case POW:
            op2 = pop();
            double val = pow(pop(), op2);
            last_used = val;
            push(val);
            break;

        case TAN:
            val = (tan(pop()));
            last_used = val;
            push(val);
            break;

        case EXP:
            val = (exp(pop()));
            last_used = val;
            push(val);
            break;

        case COS:
            val = (cos(pop()));
            last_used = val;
            push(val);
            break;

        case SIN:
            val = (sin(pop()));
            last_used = val;
            push(val);
            break;

        case NOTVALID:
            printf("error: Unvalid assignment\n");
            break;
        case UNDEFINED:
            printf("error: Undefined\n");
            break; 
        case '\n':
            printf("\t%.8g\n", pop());
            break;

        default:
            printf("error: Unknown command\n");
            break;
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
int filled[26] = {0};

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
    int i, c, validNum, varName;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }

    s[1] = '\0';
    if (c != LASTUSEDVAR && !isdigit(c) && c != '.' && c != '-' && !isalpha(c)) {
        return c; // not a number
    }

    i = 0;

    if (isalpha(c)) {
        s[0] = tolower(c); // ignore case, rewrite in lower case
        while (isalpha(s[++i] = c = tolower(getch()))) {
            ;
        }

        s[i] = '\0';

        if (strlen(s) == 1) { // assignment or recall

            varName = s[0];

            if (c == '=') { // assignment
                // get value
                validNum = 0;
                c = getch();
                i = 0;

                if (c == '-') {
                    c = getch();
                    if (!isdigit(c) && c != '.') {
                        ungetch(c);
                        return '-';
                    }
                    s[0] = c;
                    ungetch(c);
                }

                if (isdigit(c)) {
                    s[0] = c;
                    validNum = 1;
                    while (isdigit(s[++i] = c = getch())) {
                        ;
                    }
                }

                if (c == '.') {
                    s[0] = c;
                    validNum = 1;
                    while (isdigit(s[++i] = c = getch())) {
                        ;
                    }
                }
                s[i] = '\0';

                if (!validNum) {
                    ungetch(c);
                    return NOTVALID;
                }

                vars[varName - 'a'] = atof(s);
                filled[varName - 'a'] = 1;

                if (c != EOF) {
                    ungetch(c);
                }

                return NUMBER;
            }

            else {
                if (c != EOF) {
                    ungetch(c);
                }
                if (varName >= 'a' && varName <= 'z' && filled[varName - 'a'] == 1) {
                    sprintf(s, "%g", (double)vars[varName - 'a']);
                    return NUMBER;
                } else {
                    return UNDEFINED;
                }
            }
        }

        if (c != EOF) {
            ungetch(c);
        }

        return ftoc(s);
    }

    if (c == LASTUSEDVAR) {
        sprintf(s, "%g", (double)last_used);
        return NUMBER;
    }

    if (c == '-') { // is c negative or a subtraction sign
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
