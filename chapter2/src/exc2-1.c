/* Exercise 2-1. Write a program to determine the ranges of char, short, int, and long variables, both signed and 
 * unsigned, by printing appropiate values from standard headers and by direct computation. Harder if you compute
 * them: determine the ranges of the various floating point types. 
 */ 
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[]) {

        printf("signed char: %d -> %d\n", SCHAR_MIN, SCHAR_MAX); 
        printf("unsigned char: %d\n", UCHAR_MAX); 

        printf("signed short: %d -> %d\n", SHRT_MIN, SHRT_MAX); 
        printf("unsigned short: %d\n", USHRT_MAX); 

        printf("signed int: %d -> %d\n", INT_MIN, INT_MAX); 
        printf("unsigned int: %u\n", UINT_MAX); 

        printf("signed long: %ld -> %ld\n", LONG_MIN, LONG_MAX);
        printf("unsigned long: %lu\n", ULONG_MAX); 
        return 0;
}
