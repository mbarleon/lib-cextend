/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** smart_ptr
*/

#include "memory_internal.h"

void free_smart_ptr(void *ptr)
{
    smart_ptr_internal_t *internals;
    smart_ptr_t *my_ptr = (smart_ptr_t *)ptr;

    if (!my_ptr) {
        return;
    }
    if (my_ptr->__internals) {
        internals = (smart_ptr_internal_t *)my_ptr->__internals;
        if (internals->dtor) {
            internals->dtor(my_ptr->ptr);
        } else {
            free(my_ptr->ptr);
            my_ptr->ptr = NULL;
        }
        free(my_ptr->__internals);
    }
    free(my_ptr);
}

void release_smart_ptr(smart_ptr_t *ptr)
{
    smart_ptr_internal_t *internals;

    if (!ptr || !ptr->__internals) {
        return;
    }
    internals = (smart_ptr_internal_t *)ptr->__internals;
    if (internals->use_count <= 0) {
        return;
    }
    internals->use_count--;
    if (internals->use_count == 0) {
        destroy_smart_ptr(ptr);
    }
}

void destroy_smart_ptr(smart_ptr_t *ptr)
{
    remove_from_list(ptr);
}
