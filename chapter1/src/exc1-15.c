/* Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to use a function for conversion. */
#include <stdio.h>

/* Original:
 *
 * main ()
 * {
 *  int fahr, celsius;
 *  int lower, upper, step;
 *
 *  lower = 0;
 *  upper = 300;
 *  step = 20;
 *
 *  fahr = lower;
 *  while (fahr <= upper) {
 *      celsius = 5 * (fahr-32) / 9;
 *      printf("%d\t%d\n", fahr, celsius);
 *      fahr = fahr + step;
 *  }
 *} */

int fahrToCelsius(int);
int main(int argc, char* argv[]) {
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celsius = fahrToCelsius(fahr);
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}

int fahrToCelsius(int fahr) { return 5 * (fahr - 32) / 9; }
