#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    while (1) {
        printf("$ ");
        // fflush(stdout);

        char *input = NULL;
        size_t linecapp = 0;
        ssize_t len = getline(&input, &linecapp, stdin);
        if (len == -1) {
            perror("getline failed\n");
        }

        // printf("%zu, %p, %s", len, input, input);
        input[strcspn(input, "\n")] = '\0';

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed\n");
            free(input);
            continue;
        }

        /* child */
        if (pid == 0) {
            char *args[] = {input, NULL};
            execvp(args[0], args);

            /* rich on failed only */
            perror("exec failed");
            _exit(127);
        }

        /* parent (me) */
        wait(NULL);
        free(input);
    }
    return 0;
}
