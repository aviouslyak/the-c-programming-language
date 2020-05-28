/* Exercise 5-5. Write versions of the library functions
 * strncpy , strncat , and strncmp , which operate on at most the first n characters
 * of their argument strings. For example, strncpy(s,t,n) copies at most
 * n characters of t to s . Full descriptions are in Appendix B. */

#include <stdio.h>
#include <string.h>

#define CLEAR while ((c = getchar()) != '\n' && c != EOF) {}

char* strnCpy(char*, const char*, int);
char* strnCat(char*, const char*, int);
int strnCmp(const char*, const char*, int);

int main() {
    char c;

    printf("----------- strncpy Test --------\n");
    char copyto[1000];
    char copyfrom[] = "This is to be copy from";

    int n;
    printf("How many characters to be copied: ");
    if (scanf("%d", &n) == 1) {
        strnCpy(copyto, copyfrom, n);
        printf("Copied string: %s\n", copyto);
    } else {
        printf("Error: Invalid int\n");
    }

    printf("------------ strcat test -------------\n");

    CLEAR
    
    char catb[10000] = "this is the beginning";
    char catted[] = "this will be put on the end";

    printf("How many characters to be catted: ");
    if (scanf("%d", &n) == 1) {
        strnCat(catb, catted, n);
        printf("Catted string: %s\n", catb);
    } else {
        printf("Error: Invalid int\n");
    }

    printf("------------------- strcmp -----------------\n"); 
    int result; 
    char string1[] = "abcdefgh"; 
    char string2[] = "accdefgi";

    CLEAR 


    printf("How many characters to be compared: ");
    if (scanf("%d", &n) == 1) {
        printf("string1 = %s\nstring2 = %s\n", string1, string2); 
        result = strnCmp(string1, string2, n);
        printf("result: %d\n", result);
    } else {
        printf("Error: Invalid int\n");
    }

    return 0;
}

/* Copy at most n characters of string ct to s; returns s.
 * Pad with '\0's if t has fewer than n characters */
char* strnCpy(char* s, const char* ct, int n) {
    int i, nulled;
    char* r = s;

    nulled = 0;
    for (i = 0; i < n; i++) {
        if (!nulled) {
            if (!*ct) // *ct is null
                nulled = 1;
            *r++ = *ct++;
        } else
            *r++ = '\0';
    }
    *r = '\0';

    return s;
}

/* concatenate at most n characters of string ct to string s,
 * terminate s with '\0'; return s. */
char* strnCat(char* s, const char* ct, int n) {
    int i;
    char* r = s + strlen(s);

    for (i = 0; i < n; i++) *r++ = *ct++;
    *r = '\0';

    return s;
}

/* Compare at most n characters of string cs to string ct;
 * return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct. */
int strnCmp(const char* ct, const char* cs, int n) {
    int i;
    for (i = 0; i < n && *ct == *cs; i++, cs++, ct++)
        if (*ct == '\0') return 0;

    if (i == n) // loop finished 
        return 0; 

    return *cs - *ct; 
}
