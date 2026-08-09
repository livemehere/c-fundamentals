#include "my_libc.h"

size_t my_strlen(const char *str) {
    size_t len = 0;

    /*
     * hello\0
     * h = 1
     * e = 2
     * l = 3
     * l = 4
     * o = 5
     * \0
     */
    while (str[len] != '\0') {
        len++;
    }

    return len;
}

void * my_memcpy(void *dest, const void *src, size_t n) {
    // type free, copy by byte
    char* d = dest;
    const char* s = src;

    for (size_t i=0; i<n; i++) {
        d[i] = s[i];
    }

    return dest;
}

void * my_memset(void *ptr, int value, size_t n) {
    unsigned char* p = ptr;

    for (size_t i =0; i< n; i++) {
       p[i] = value;
    }

    return ptr;
}

int my_strcmp(const char *a, const char *b) {
    while (*a != '\0' && *a == *b) {
        ++a;
        ++b;
    }

    return (int)(unsigned char)*a - (int)(unsigned char)*b;

}
