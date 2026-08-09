#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_libc.h"

int main() {

    char* s1 = malloc(6);
    strcpy(s1, "Hello");
    printf("size : %lu\n", strlen(s1)); // 5
    s1 = realloc(s1, 12);
    printf("size : %lu\n", strlen(s1)); // 5
    strcat(s1, " world");
    printf("res : %s\n", s1);
    printf("size : %lu\n", strlen(s1)); // 11



    return 0;
}
