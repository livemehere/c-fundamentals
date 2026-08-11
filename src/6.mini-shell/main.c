#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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
        const char *path = args[1];
        if (path == NULL) {
            path = getenv("HOME");
            if (path == NULL) {
                fprintf(stderr, "cd: HOME is not set\n");
                return BUILTIN_HANDLED;
            }
        } else if (args[2] != NULL) {
            fprintf(stderr, "cd: too many arguments\n");
            return BUILTIN_HANDLED;
        }

        if (chdir(path) == -1) {
            perror("cd");
        }

        return BUILTIN_HANDLED;
    }

    return BUILTIN_NONE;
}

ssize_t read_input(char **input) {
    size_t linecapp = 0;
    ssize_t len = getline(input, &linecapp, stdin);
    if (len == -1) {
        if (ferror(stdin)) {
            perror("getline\n");
        }
        return len;
    }
    (*input)[strcspn(*input, "\n")] = '\0';
    return len;
}

void tokenize_input(char * input, char ** arr) {
    size_t argc = 0;
    char *token = strtok(input, " ");
    while (token != NULL && argc < (sizeof(*arr) / sizeof(*arr[0])) - 1) {
        arr[argc++] = token;
        token = strtok(NULL, " ");
    }
    arr[argc] = NULL;
}

int main(void) {
    while (1) {
        printf("$ ");
        // fflush(stdout);

        char *input = NULL;
        ssize_t len = read_input(&input);
        if (len == -1) {
            free(input);
            break;
        }

        /* tokenize */
        char *args[64];
        tokenize_input(input, args);
        if (args[0] == NULL) {
            free(input);
            continue;
        }

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
            char* output_file = NULL;
            for (int i=0; args[i] != NULL; i++) {
                if (strcmp(args[i], ">") == 0) {
                    output_file = args[i+1];
                    args[i] = NULL;
                    break;
                }
            }
            int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("open");
                _exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) == -1) {
                perror("dup2");
                close(fd);
                _exit(1);
            }
            close(fd);
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
