#include <stdio.h>
#include <string.h>

#include "my_libc.h"

int main() {
    /* strlen */
    const char* name = "Kong";
    int name_len = my_strlen(name);
    printf("name %s len : %d\n", name, name_len);

    /* memcpy */
    int a = 10;
    int b;
    my_memcpy(&b, &a, sizeof(a));
    printf("a : %d, b: %d\n", a, b);

    /* memset - 1(byte) */
    char str[11];
    my_memset(str, 'A', sizeof(str) - 1);
    str[10] = '\0';
    printf("str[10] : %s\n", str);

    /* memset - 2(none-byte) */
    int arr[10];
    my_memset(arr, 0, sizeof(arr));
    printf("arr[10] : %p\n", arr);

    int res = my_strcmp("Hellb", "Hellb");
    printf("res : %d, %s\n", res, res != 0 ? "diff" : "same");

    char k = '\0';
    if (k) {
        printf("yes\n");
    }else {
        printf("no\n");
    }

    return 0;
}
