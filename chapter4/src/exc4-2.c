/* Exercise 4-2. Extend atof to handle scientific notation in the form
 *      123.45e-6
 * where a floating-point number may be followed by e or E and an optionally signed exponent.
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>

#define MAXLINE 100

double atof(char s[]);

int main(int argc, char* argv[]) {
    char c, buffer[MAXLINE];
    double dob;
    int i = 0;

    while ((c = getchar()) != EOF) {
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    putchar('\n');
    dob = atof(buffer);
    printf("%s == %f\n", buffer, dob);
    return 0;
}

double atof(char s[]) {

    double val, power, scinot, rval;
    int i, sign, operator;

    for (i = 0; isspace(s[i]); ++i) {
        ;
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.') {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
    }

    operator=(s[i] == '-') ? -1 : 1;

    if (s[i] == '-' || s[i] == '+') {
        i++;
    }
    for (scinot = 0; isdigit(s[i]); ++i) {
        scinot = 10.0 * scinot + (s[i] - '0');
    }

    power /= pow(10, scinot * operator);

    rval = sign * val / power;
    return rval;
}

