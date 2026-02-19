#include <stdio.h>

int main(void)
{
    int num = 8;
    int *p;

    p = &num;

    printf("El número vale %d y se encuentra en %p\n", *p, p);
    return 0;
}
