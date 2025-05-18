/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception_internal
*/

#ifndef C_EXTEND_EXCEPTION_INTERNAL_H_
    #define C_EXTEND_EXCEPTION_INTERNAL_H_
    #include <stdlib.h>
    #include <string.h>
    #include <execinfo.h>

    #include "exception.h"
    #include "exception_types.h"
    #include "../../include/logger.h"

    #define __C_EXTEND_STACKTRACE_SIZE 100

struct __attribute__((aligned(__C_EXTEND_EXCEPTION_CONTEXT_ALIGNMENT)))
    c_extend_exception_internal_s {
    bool __was_used;
    c_extend_exception_context_t *__prev;
};

typedef struct c_extend_exception_internal_s c_extend_exception_internal_t;

#endif /* !C_EXTEND_EXCEPTION_INTERNAL_H_ */
