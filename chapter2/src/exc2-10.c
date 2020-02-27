/* Exercise 2-10. Rewrite the function lower, which converts upper case letters to lower case, with a conditional operator instead of if-else
 */
#include <stdio.h>

char lower(char c); 

int main(int argc, char *argv[]) {

        char c = getchar(); 
        printf("c == %c\n", c); 
        printf("lower(c) == %c\n", lower(c));         
        return 0;
}

char lower(char c) {

        return (c >= 65 && c <= 90) ? c + 32: c;  
}

