#include <stdio.h>

int main(void)
{
    int array[10];
    int i;

    for (i = 0; i < 10; i++)
        array[i] = i + 10;

    for (i = 0; i < 10; i++)
        printf("Value at index %d = %d\n", i, array[i]);

    return 0;
}