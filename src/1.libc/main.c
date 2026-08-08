#include <stdio.h>
#include "my_libc.h"

int main() {

    const char* str = "Hello";
    printf("size of %s is : %zu\n", str, my_strlen(str));

    return 0;
}
