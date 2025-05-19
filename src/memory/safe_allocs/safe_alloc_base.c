/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** safe_alloc
*/

#include "../memory_internal.h"

static void push_to_list(void **ptr, void (*dtor)(void *))
{
    c_extend_exception_code_t code = 0;
    c_extend_exception_context_t *ctxt = INIT_TRY;

    TRY(code, ctxt) {
        add_in_list(*ptr, dtor);
    } CATCH(code, C_EXTEND_EXCEPTION_BAD_ALLOC) {
        free(*ptr);
        *ptr = NULL;
        THROW(C_EXTEND_EXCEPTION_BAD_ALLOC);
    } CATCH_END(code);
    END_TRY;
}

void *safe_alloc(size_t size, void (*dtor)(void *),
    void *(*alloc_func)(size_t))
{
    void *ptr = alloc_func(size);

    if (!ptr) {
        THROW(C_EXTEND_EXCEPTION_BAD_ALLOC);
    }
    push_to_list(&ptr, dtor);
    return ptr;
}

void *safe_salloc(size_t val, size_t size, void (*dtor)(void *),
    void *(*alloc_func)(size_t, size_t))
{
    void *ptr = alloc_func(val, size);

    if (!ptr) {
        THROW(C_EXTEND_EXCEPTION_BAD_ALLOC);
    }
    push_to_list(&ptr, dtor);
    return ptr;
}

void *safe_palloc(void *ptr, size_t size, void (*dtor)(void *),
    void *(*alloc_func)(void *, size_t))
{
    void *new_ptr = alloc_func(ptr, size);

    if (!new_ptr) {
        THROW(C_EXTEND_EXCEPTION_BAD_ALLOC);
    }
    push_to_list(&new_ptr, dtor);
    return new_ptr;
}

void safe_free(void *ptr)
{
    remove_from_list(ptr);
}
