/* Exercise 2-3. Write the function htoi(s), which converts a string of hexadecimal digits (including an optional
 * 0x or 0X into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F.
 */
#include <ctype.h>
#include <stdio.h>
#include <math.h>

int htoi(char hexa[]);
int digToNum(char c); 

int main(int argc, char* argv[]) {

    char hexa[] = "0x7FEA89";
    int dec;
    dec = htoi(hexa);
    printf("%s == %d\n", hexa, dec); 
    return 0;
}

int htoi(char hexa[]) {

    char c;
    int dec, flag, len, dig, i;
    dec = flag = i = len = dig = 0;

    for (; hexa[len] != '\0'; len++) {
        ;
    }
    if (hexa[i] != '\0' && hexa[i] == '0' && hexa[i + 1] == 'x' || hexa[i + 1] == 'X') {
        i = 2;
        len -= 2; 
    }
    for (; (c = hexa[i]) != '\0'; ++i, len--) {
        dig = digToNum(c);     
        if (dig == -1) {
                return -1; 
        }
        dec += dig * pow(16, len - 1); 
    }

    return dec; 
}

int digToNum(char c) {
    if (isdigit(c)) {
        return c - '0';
    }
    c = tolower(c);

    if (c == 'a') {
        return 10;
    } else if (c == 'b') {
        return 11;
    } else if (c == 'c') {
        return 12;
    } else if (c == 'd') {
        return 13;
    } else if (c == 'e') {
        return 14;
    } else if (c == 'f') {
        return 15;
    }

    return -1;
}

