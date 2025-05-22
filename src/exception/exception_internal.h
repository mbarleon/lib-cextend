/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** exception_internal
*/

#ifndef CEXTEND_EXCEPTION_INTERNAL_H_
    #define CEXTEND_EXCEPTION_INTERNAL_H_
    #include <stdlib.h>
    #include <string.h>

    #include "exception.h"
    #include "exception_init.h"
    #include "exception_types.h"
    #include "backtrace/backtrace.h"
    #include "../../include/cextend/logger.h"
    #include "../../include/cextend/exit/memory_exit.h"

struct __attribute__((aligned(__CEXTEND_EXCEPTION_CONTEXT_ALIGNMENT)))
    cextend_exception_internal_s {
    bool __was_used;
    cextend_exception_context_t *__prev;
};

typedef struct cextend_exception_internal_s cextend_exception_internal_t;

#endif /* !CEXTEND_EXCEPTION_INTERNAL_H_ */
