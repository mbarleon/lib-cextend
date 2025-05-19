/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** heap_infos
*/

#include "memory_internal.h"

static c_extend_ptr_list_t **get_ptr_list(void)
{
    static c_extend_ptr_list_t *ptr_list = NULL;

    return &ptr_list;
}

static void free_ptr_in_list(c_extend_ptr_list_t *elem, void *ptr)
{
    if (elem->dtor) {
        elem->dtor(ptr);
    } else {
        free(ptr);
    }
}

void add_in_list(void *ptr, void (*dtor)(void *))
{
    c_extend_ptr_list_t *tmp;
    c_extend_ptr_list_t *entry;
    c_extend_ptr_list_t **ptr_list = get_ptr_list();

    if (ptr == NULL) {
        return;
    }
    entry = (c_extend_ptr_list_t *)calloc(1, sizeof(c_extend_ptr_list_t));
    if (!entry) {
        THROW(C_EXTEND_EXCEPTION_BAD_ALLOC);
    }
    entry->dtor = dtor;
    entry->ptr = ptr;
    if (!*ptr_list) {
        *ptr_list = entry;
        return;
    }
    for (tmp = *ptr_list; tmp->next; tmp = tmp->next);
    tmp->next = entry;
}

void remove_from_list(void *ptr)
{
    c_extend_ptr_list_t *tmp;
    c_extend_ptr_list_t *prev = NULL;
    c_extend_ptr_list_t **ptr_list = get_ptr_list();

    if (!ptr || !*ptr_list)
        return;
    for (tmp = *ptr_list; tmp;) {
        if (tmp->ptr != ptr) {
            prev = tmp;
            tmp = tmp->next;
            continue;
        }
        free_ptr_in_list(tmp, ptr);
        if (prev)
            prev->next = tmp->next;
        else
            *ptr_list = tmp->next;
        free(tmp);
        break;
    }
}

void free_ptr_list(void)
{
    c_extend_ptr_list_t *tmp;
    c_extend_ptr_list_t *tmp2;
    c_extend_ptr_list_t **ptr_list = get_ptr_list();

    if (!*ptr_list) {
        return;
    }
    for (tmp = *ptr_list; tmp;) {
        if (tmp->dtor) {
            tmp->dtor(tmp->ptr);
        } else {
            free(tmp->ptr);
            tmp->ptr = NULL;
        }
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
    }
}
