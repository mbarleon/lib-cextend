/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception_internal
*/

#ifndef LIBC_EXT_EXCEPTION_INTERNAL_H_
    #define LIBC_EXT_EXCEPTION_INTERNAL_H_
    #include <stdlib.h>
    #include <string.h>
    #include <execinfo.h>

    #include "exception.h"
    #include "exception_types.h"
    #include "../../include/logger.h"

    #define __LIBC_EXT_STACKTRACE_SIZE 100

struct __attribute__((aligned(__LIBC_EXT_EXCEPTION_CONTEXT_ALIGNMENT)))
    libc_ext_exception_internal_s {
    bool __was_used;
    libc_ext_exception_context_t *__prev;
};

typedef struct libc_ext_exception_internal_s libc_ext_exception_internal_t;

#endif /* !LIBC_EXT_EXCEPTION_INTERNAL_H_ */
