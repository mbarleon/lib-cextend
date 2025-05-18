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

    #define __C_EXTEND_EXCEPTION_CONTEXT_ALIGNMENT 16

typedef enum {
    C_EXTEND_EXCEPTION_OK = 0,

    C_EXTEND_EXCEPTION_BAD_ARGS,
    C_EXTEND_EXCEPTION_BAD_ALLOC,

    C_EXTEND_EXCEPTION_MAX
} c_extend_exception_types_t;

struct __attribute__((aligned(__C_EXTEND_EXCEPTION_CONTEXT_ALIGNMENT)))
    c_extend_exception_context_s {
    sigjmp_buf __env;
    void *__internals;
};

typedef struct c_extend_exception_context_s c_extend_exception_context_t;

typedef volatile int vint_t;
typedef vint_t c_extend_exception_code_t;

#endif /* !EXCEPTION_TYPES_H_ */
