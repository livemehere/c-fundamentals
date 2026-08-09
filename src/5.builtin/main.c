#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int main() {
    /* len */
    // char* s = "kong";
    // size_t len = strlen(s);
    // printf("len : %zu\n", len); // 4
    // printf("sizeof : %zu\n", sizeof(s)); // 8

    /* copy */
    // char src[] = "hello, world";
    // char dest[100]; // (x) char* dest;
    // strcpy(dest, src);
    // printf("%s, %s", src, dest);

    /* cat */
    // char buf[100] = "Hello";
    // strcat(buf, " world");
    // printf("%s", buf);

    /* cmp */
    // char* name = "Kong";
    // int res = strcmp(name, "Kong");
    // printf("%d", res);

    /* find char and replace(strchr, strrchr) */
    // char text[50] = "Hello";
    // char *p = strrchr(text, 'l');
    // strncpy(p, "K", 1);
    // printf("%s", text);

    /* find str */
    // char text[100] = "hello world";
    // char* found = strstr(text, "wo");
    // strcpy(found, "WORLD");
    // printf("%s", text);

    /* tokenize */
    // char* save;
    // char input[] = "ls -al /temp";
    // char* token = strtok_r(input, " ", &save);
    // while (token) {
    //     printf("%s\n", token);
    //     token = strtok_r(NULL, " ", &save);
    // }

    /* memcpy */
    // typedef struct Player {
    //     int hp; // 4
    //     char name[50]; // 50
    // } Player;
    // printf("%zu\n", sizeof(Player)); // 56(54 + padding 2)
    //
    // Player p1 = {
    //     10,
    //     "Kong"
    // };
    // Player p2;
    //
    // memcpy(&p2, &p1, sizeof(Player));
    // p1.hp = 999;
    // printf("%d, %s", p2.hp, p2.name);


    /* memmove */
    // int arr[5] = {1, 2, 3, 4};
    // memmove(&arr[3], &arr[2], sizeof(int) * 2); // 1, 2, 3(x), 3, 4
    // arr[2] = 99;
    // for (int i = 0; i < ARRAY_SIZE(arr); i++) {
    //     printf("%d, ", arr[i]);
    // }

    /* memset */
    // int arr[10];
    // memset(arr, 0, sizeof(arr));
    // for (int i = 0; i < ARRAY_SIZE(arr); i++) {
    //     printf("%d, ", arr[i]);
    // }

    /* string -> number */
    /* simple */
    // int value = atoi("abc");
    // printf("%d", value);
    /* complex */
    // char* end;
    // int value = strtol("FF abc", &end, 16);
    // printf("%d\n", value);
    // printf("%s\n", end);

    /* format */
    // char buff[50];
    // snprintf(buff, sizeof(buff), "hp=%d", 10);
    // printf("%s", buff);




    return 0;
}
