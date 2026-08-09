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

    /* strcmp */
    int res = my_strcmp("Hellb", "Hellb");
    printf("res : %d, %s\n", res, res != 0 ? "diff" : "same");

    /* memcpy for string */
    char src[] = "ABCD";
    char dest[100];
    my_memcpy(dest, src, sizeof(src));
    printf("copied %s\n",dest);

    /* strcat */
    char before[50] = "KONG";
    printf("size : %lu\n", sizeof(before));
    my_strcat(before, " is KING");
    printf("concat %s\n",before);
    printf("size : %lu\n", sizeof(before));


    return 0;
}
