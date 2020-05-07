/* Exercise 3-2. Write a function escape(s, t) that converts characters like newline and tab into visible escape
 * sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction
 * as well, converting escape sequences into the real characters
 */
#include <stdio.h>

void escape(char s[], char t[]);
void descape(char s[], char t[]);

int main(int argc, char* argv[]) {

    char t[] = "This\n\tis\tfun";
    char s[1000];
    escape(s, t);
    printf("escape(s, t) == %s\n", s);

    char t2[] = "This newline \\n is escaped\n"; 
    char s2[1000]; 
    descape(s2, t2); 
    printf("descape(s2, t2) == %s\n", s2); 
    return 0;
}

void escape(char s[], char t[]) {

    int i, j;
    char c;
    for (i = j = 0; (c = t[i]) != '\0'; ++i) {
        switch (c) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        case '\b':
            s[j++] = '\\';
            s[j++] = 'b';
            break;
        default:
            s[j++] = c;
        }
    }
    s[j] = '\0';
}

void descape(char s[], char t[]) {

    int i, j, state;
    char c;
    for (i = j = 0; (c = t[i]) != '\0'; ++i) {
        if (c == '\\') {
            state = 1;

        } else if (state) {
            switch (c) {
            case 'n':
                s[j++] = '\n';
                break;
            case 't':
                for (; j <= 4; j++) {
                    s[j] = ' ';
                }
                break;
            case 'b':
                s[j++] = '\b';
                break;
            default:
                s[j++] = c;
            }
            state = 0;
        } else {
            s[j++] = c;
        }
    }
    s[j] = '\0';
}
