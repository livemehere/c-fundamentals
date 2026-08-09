#pragma once
#include <stddef.h>

size_t my_strlen(const char *str);

void* my_memcpy(void* dest, const void* src, size_t n);

void* my_memset(void* ptr, int value, size_t n);

int my_strcmp(const char* a, const char* b);