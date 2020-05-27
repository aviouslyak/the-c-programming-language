/* Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s . */
#include <stdio.h>

void strcat(char*, char*);

int main(int argc, char argv[]) {
    char string1[100] = "This is a string";
    char string2[100] = " and this goes on the end";

    strcat(string1, string2);

    printf("string2 on string1 : %s\n", string1);

    return 0;
}

void strcat(char* s, char* t) {
    printf("running\n");
    while (*s++ != '\0')
        ;

    s--;
    while ((*s++ = *t++) != '\0')
        ;

    *s = '\0';
}
