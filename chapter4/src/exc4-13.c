/*Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the string s in place.*/
#include <stdio.h>

void reverse(char[], int[]);

int main(int argc, char* argv[]) {
    char str[] = "sadaskl";
    int pos[2] = {0, 2};
    reverse(str, pos);
    printf("Reversed string = %s\n", str);
    return 0;
}

void swap(char s[], int i, int j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void reverse(char s[], int pos[]) {
    if (pos[0] == pos[1]) {
            return;
    }
    swap(s, pos[0]++, pos[1]--); 
    reverse(s, pos);  
}
