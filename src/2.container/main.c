#include <stdio.h>
#include "vector.h"

int main() {

    Vector v;
    vector_init(&v);

    vector_push(&v, 1);
    vector_push(&v, 2);
    vector_push(&v, 3);
    vector_push(&v, 4);
    vector_push(&v, 5);

    for (int i=0; i< v.size; i++) {
        printf("%d\n", vector_get(&v, i));
    }

    printf("------------------\n");

    vector_pop(&v);

    vector_erase(&v, 2);

    for (int i=0; i< v.size; i++) {
        printf("%d\n", vector_get(&v, i));
    }

    printf("size : %d\n", v.size);
    printf("capacity : %d\n", v.capacity);

    vector_free(&v);

    printf("size : %d\n", v.size);
    printf("capacity : %d\n", v.capacity);

    return 0;
}
