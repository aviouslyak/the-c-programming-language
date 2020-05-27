/* Exercise 5-4. Write the function strend(s,t) ,
 * which returns 1 if the string t occurs at the end of the string s,
 * and zero otherwise. */
#include <stdio.h>
#include <string.h>

int strend(char*, char*);

int main(int argc, char argv[]) {
    char string1[] = "Avi has this string at the end";
    char string2[] = "Not on the end";
    char string3[] = "end";

    int end1, end2;

    end1 = strend(string1, string2);
    end2 = strend(string1, string3);

    printf("Strings are: \n");
    printf("string1 = %s\nstring2 = %s\nstring3 = %s\n", string1, string2, string3);
    printf("strend(string1, string2) = %d\n", end1);
    printf("strend(string1, string3) = %d\n", end2);

    return 0;
}

int strend(char* s, char* t) {
    int lent, lens;
    lent = strlen(t);
    lens = strlen(s);

    if (lent < lens) {
        s += lens - lent;
    } else {
        return -1; // string t bigger than string s 
    }

    return strcmp(s, t) ? 0 : 1; 
    
}
