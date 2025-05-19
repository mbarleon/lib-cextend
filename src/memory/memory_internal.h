/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** memory_internal
*/

#ifndef C_EXETEND_MEMORY_INTERNAL_H_
    #define C_EXETEND_MEMORY_INTERNAL_H_
    #include <string.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include "memory.h"
    #include "../../include/exception.h"

typedef struct c_extend_ptr_list_s {
    void *ptr;
    void (*dtor)(void *);
    struct c_extend_ptr_list_s *next;
} c_extend_ptr_list_t;

void add_in_list(void *ptr, void (*dtor)(void *));
void remove_from_list(void *ptr);

void free_ptr_list(void);

void *safe_alloc(size_t size, void (*dtor)(void *),
    void *(*alloc_func)(size_t));
void *safe_salloc(size_t val, size_t size, void (*dtor)(void *),
    void *(*alloc_func)(size_t, size_t));
void *safe_palloc(void *ptr, size_t size, void (*dtor)(void *),
    void *(*alloc_func)(void *, size_t));

void free_smart_ptr(void *ptr);

typedef struct smart_ptr_internal_s {
    size_t size;
    size_t use_count;
    void (*dtor)(void *);
} smart_ptr_internal_t;

#endif /* !C_EXETEND_MEMORY_INTERNAL_H_ */
