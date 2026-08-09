#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
    int *data;
    size_t size;
    size_t capacity;
} Vector;


static inline void vector_init(Vector *v) {
    v->size = 0;
    v->capacity = 4;
    v->data = malloc(sizeof(int) * v->capacity);
    if (!v->data) {
        v->capacity = 0;
    }
}

static inline int vector_get(Vector *v, size_t index) {
    if (index >= v->size) {
        printf("can not get %lu of vector", index);
        return -1;
    }
    return v->data[index];
}

static inline bool vector_resize(Vector *v) {
    size_t new_capacity = v->capacity == 0 ? 4 : v->capacity * 2;
    int *temp = realloc(v->data, sizeof(int) * new_capacity);
    if (temp) {
        v->data = temp;
        v->capacity = new_capacity;
        return true;
    } else {
        // FAIL to get memory
        printf("fail to realloc vector\n");
        return false;
    }
}

static inline void vector_push(Vector *v, int value) {
    if (v->size >= v->capacity) {
        if (!vector_resize(v)) return;
    }

    v->data[v->size] = value;
    v->size++;
}

static inline bool vector_pop(Vector *v) {
    if (v->size == 0) {
        return false;
    }

    v->size--;
    v->data[v->size] = 0;

    return true;
}

static inline bool vector_erase(Vector *v, size_t index) {
    if (index >= v->size) {
        return false;
    }

    memmove(&v->data[index], &v->data[index+1], sizeof(int) * (v->size - index - 1));
    v->size--;

    return true;
}

static inline bool vector_insert(Vector*v, size_t index, int value) {
    if (index > v->size) {
        return false;
    }

    if (v->size >= v->capacity) {
       if (!vector_resize(v)) {
           return false;
       }
    }


    memmove(&v->data[index+1], &v->data[index], sizeof(int) * (v->size - index));
    v->data[index] = value;
    v->size++;

    return true;
}


static inline void vector_free(Vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}
