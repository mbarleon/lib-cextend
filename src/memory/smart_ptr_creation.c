/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** smart_ptr
*/

#include "memory_internal.h"

smart_ptr_t *retain_smart_ptr(smart_ptr_t *ptr)
{
    smart_ptr_internal_t *internals;

    if (!ptr || !ptr->__internals) {
        THROW(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    internals = (smart_ptr_internal_t *)ptr->__internals;
    if (internals->use_count == SIZE_MAX) {
        THROW(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    internals->use_count++;
    return ptr;
}

smart_ptr_t *create_smart_ptr(size_t size, void (*dtor)(void *))
{
    smart_ptr_internal_t *internals;
    smart_ptr_t *ptr = (smart_ptr_t *)safe_calloc(1, sizeof(smart_ptr_t),
        &free_smart_ptr);

    internals = (smart_ptr_internal_t *)malloc(sizeof(smart_ptr_internal_t));
    if (!internals) {
        remove_from_list(ptr);
        THROW(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    ptr->ptr = calloc(1, size);
    if (!ptr->ptr) {
        free(internals);
        remove_from_list(ptr);
        THROW(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    internals->dtor = dtor;
    internals->size = size;
    internals->use_count = 1;
    ptr->__internals = internals;
    return ptr;
}

smart_ptr_t *dup_smart_ptr(smart_ptr_t *ptr)
{
    smart_ptr_t *dup;
    smart_ptr_internal_t *internals;

    if (!ptr || !ptr->__internals) {
        THROW(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    internals = (smart_ptr_internal_t *)ptr->__internals;
    dup = create_smart_ptr(internals->size, internals->dtor);
    if (!dup) {
        THROW(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    memcpy(dup->ptr, ptr->ptr, internals->size);
    return dup;
}

void resize_smart_ptr(smart_ptr_t **ptr, size_t size)
{
    long long size_diff;
    smart_ptr_internal_t *internals;

    if (!ptr || !*ptr || !(*ptr)->__internals) {
        THROW(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    internals = (smart_ptr_internal_t *)(*ptr)->__internals;
    size_diff = (long long)size - (long long)internals->size;
    (*ptr)->ptr = realloc((*ptr)->ptr, size);
    if (!(*ptr)->ptr) {
        destroy_smart_ptr(ptr);
        throw(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    if (size_diff > 0) {
        memset(&((uint8_t *)(*ptr)->ptr)[internals->size], 0,
            (size_t)size_diff);
    }
    internals->size = size;
}
