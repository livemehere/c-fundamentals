#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    char input[255];

    while (1) {
        printf("$ ");
        fgets(input, sizeof(input), stdin);
        char* token = strtok(input, " ");
        printf("token : %s", token);
        token = strtok(NULL, " ");

        int pid = fork();

        if (pid == 0) {
            execlp(input, input, NULL);
            perror("exec failed");
            return 1;
        }else {
            wait(NULL);
        }
    }

    return 0;
}
