#include <stdio.h>
#include "my_libc.h"

int main() {
    int a = 10;
    int b;
    my_memcpy(&b, &a, sizeof(a));

    printf("a : %d, b: %d\n", a, b);

    return 0;
}
