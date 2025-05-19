/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** safe_alloc
*/

#include "../memory_internal.h"

void *safe_calloc(size_t count, size_t size, void (*dtor)(void *))
{
    return safe_salloc(count, size, dtor, &calloc);
}

void *safe_aligned_alloc(size_t alignment, size_t size, void (*dtor)(void *))
{
    return safe_salloc(alignment, size, dtor, &aligned_alloc);
}
