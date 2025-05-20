/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** memory
*/

#ifndef __CEXTEND_MEMORY_H_
    #define __CEXTEND_MEMORY_H_
    #include <stddef.h>
    #include "../../include/types.h"

void *safe_strdup(const char *restrict str);
void *safe_calloc(size_t count, size_t size, void (*dtor)(void *));
void *safe_malloc(size_t size, void (*dtor)(void *));
void *safe_realloc(void *ptr, size_t size, void (*dtor)(void *));
void *safe_valloc(size_t size, void (*dtor)(void *));
void *safe_aligned_alloc(size_t alignment, size_t size, void (*dtor)(void *));

void safe_free(void **ptr);

typedef struct {
    void *ptr;
    cextend_private_t __internals;
} smart_ptr_t;

void release_smart_ptr(smart_ptr_t **ptr);
smart_ptr_t *retain_smart_ptr(smart_ptr_t *ptr);

smart_ptr_t *create_smart_ptr(size_t size, void (*dtor)(void *));
void destroy_smart_ptr(smart_ptr_t **ptr);

smart_ptr_t *dup_smart_ptr(smart_ptr_t *ptr);
void resize_smart_ptr(smart_ptr_t **ptr, size_t size);

#endif /* !__CEXTEND_MEMORY_H_ */
