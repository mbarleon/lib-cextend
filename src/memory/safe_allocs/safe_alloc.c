/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** safe_alloc
*/

#include "../memory_internal.h"

void *safe_malloc(size_t size, void (*dtor)(void *))
{
    return safe_alloc(size, dtor, &malloc);
}

void *safe_valloc(size_t size, void (*dtor)(void *))
{
    return safe_alloc(size, dtor, &valloc);
}

void *safe_strdup(const char *restrict str)
{
    void *ptr = safe_alloc(sizeof(char) * (strlen(str) + 1), NULL, &malloc);

    strcpy((char *)ptr, str);
    return ptr;
}
