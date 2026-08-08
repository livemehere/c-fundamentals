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
