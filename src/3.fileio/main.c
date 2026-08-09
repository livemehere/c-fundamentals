#include <stdio.h>
#include <stdlib.h>

int write_example() {
    FILE *file = fopen("hello.txt", "w");
    if (file == NULL) {
        printf("fail to open file\n");
        return 1;
    }

    fprintf(file, "Hello! C\n");
    fprintf(file, "File io test!\n");

    fclose(file);
    return 0;
}

int read_by_buffer() {
    FILE *file = fopen("hello.txt", "r");
    if (file == NULL) {
        printf("fail to open file\n");
        return 1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}

int read_by_char() {
    FILE *file = fopen("hello.txt", "r");
    if (file == NULL) {
        printf("fail to open file\n");
        return 1;
    }

    char c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }

    fclose(file);
    return 0;
}

typedef struct Player {
    int hp;
    float x;
    float y;
} Player;

int write_by_bin() {
    Player p = {
        10,
        1.5f,
        2.5f
    };

    FILE *file = fopen("player.bin", "wb");
    if (file == NULL) {
        printf("fail to open file\n");
        return 1;
    }

    fwrite(&p, sizeof(Player), 1, file);
    fclose(file);
    return 0;
}

int read_by_bin() {
    FILE *file = fopen("player.bin", "rb");
    if (file == NULL) {
        printf("fail to open file\n");
        return 1;
    }
    Player p;

    fread(&p, sizeof(Player), 1, file);
    printf(
        "%d %.2f %.2f\n",
        p.hp,
        p.x,
        p.y
    );
    fclose(file);
    return 0;
}

int read_file_all() {
    FILE *file = fopen("hello.txt", "rj");
    if (file == NULL) {
        printf("fail to open file\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    printf("file size : %ld\n", size);

    char *buffer = malloc(size + 1);
    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    printf("%s\n", buffer);

    free(buffer);
    return 0;
}

int main() {
    read_file_all();

    return 0;
}
