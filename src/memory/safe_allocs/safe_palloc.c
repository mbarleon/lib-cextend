/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** safe_alloc
*/

#include "../memory_internal.h"

void *safe_realloc(void *ptr, size_t size, void (*dtor)(void *))
{
    return safe_palloc(ptr, size, dtor, &realloc);
}
