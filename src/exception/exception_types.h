/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception_types
*/

#ifndef EXCEPTION_TYPES_H_
    #define EXCEPTION_TYPES_H_
    #include <setjmp.h>
    #include <stdbool.h>

    #define __LIBC_EXT_EXCEPTION_CONTEXT_ALIGNMENT 16

typedef enum {
    LIBC_EXT_EXCEPTION_OK = 0,

    LIBC_EXT_EXCEPTION_BAD_ARGS,
    LIBC_EXT_EXCEPTION_BAD_ALLOC,

    LIBC_EXT_EXCEPTION_MAX
} libc_ext_exception_types_t;

struct __attribute__((aligned(__LIBC_EXT_EXCEPTION_CONTEXT_ALIGNMENT)))
    libc_ext_exception_context_s {
    sigjmp_buf __env;
    bool __was_used;
    struct libc_ext_exception_context_s *__prev;
};

typedef struct libc_ext_exception_context_s libc_ext_exception_context_t;

#endif /* !EXCEPTION_TYPES_H_ */
