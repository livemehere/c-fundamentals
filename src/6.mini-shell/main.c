#include <stdio.h>
#include <string.h>

int main() {

    while (1) {
        printf("$ ");
        char* input = NULL;
        size_t cap = 0;
        ssize_t len = getline(&input, &cap, stdin);

        if (len == -1) {
            perror("getline error\n");
            return 1;
        }

        printf(">(len : %zu)(len : %zu)(cap : %zu) %s", strlen(input), len, cap, input);
    }

    return 0;
}
