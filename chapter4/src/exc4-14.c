/* Exercise 4-14. Define a macro swap(t, x, y) that interchanges to arguments of type t. (Block structure will help.) */
#include <stdio.h>
#define swap(t, x, y) do { t x ## y = x; x = y; y = x ## y; } while(0); 

int main(void)
{
        int x, y; 
        x = 1; 
        y = 2;
        printf("x = %d, y = %d\n", x, y);
        swap(int, x, y)
        printf("x = %d, y = %d\n", x, y);
        return 0;
}
