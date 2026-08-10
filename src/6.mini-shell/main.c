#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef enum {
    BUILTIN_NONE,
    BUILTIN_HANDLED,
    BUILTIN_EXIT
} BuiltinResult;

BuiltinResult run_builtin(char *args[]) {
    if (strcmp(args[0], "exit") == 0) {
        return BUILTIN_EXIT;
    }

    if (strcmp(args[0], "cd") == 0) {
        return BUILTIN_HANDLED;
    }

    return BUILTIN_NONE;
}

int main() {
    while (1) {
        printf("$ ");
        // fflush(stdout);

        /* get clean input */
        char *input = NULL;
        size_t linecapp = 0;
        ssize_t len = getline(&input, &linecapp, stdin);
        if (len == -1) {
            perror("getline failed\n");
        }
        input[strcspn(input, "\n")] = '\0';

        /* tokenize */
        char *args[64];
        int argc = 0;
        char *token = strtok(input, " ");
        while (token != NULL && argc < (sizeof(args) / sizeof(args[0])) - 1) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        /* internal command */
        BuiltinResult result = run_builtin(args);
        if (result == BUILTIN_EXIT) {
            free(input);
            break;
        }

        if (result == BUILTIN_HANDLED) {
            free(input);
            continue;
        }

        /* run command */
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed\n");
            free(input);
            continue;
        }

        /* child */
        if (pid == 0) {
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
