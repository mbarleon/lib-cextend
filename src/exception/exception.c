/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception
*/

#include "exception_internal.h"

static const char *libc_ext_exception_description[] = {
    "No exception",

    "bad arguments",
    "bad alloc",

    "Unknown exception"
};

static void print_stacktrace(void)
{
    void *buffer[__LIBC_EXT_STACKTRACE_SIZE];
    int nptrs = backtrace(buffer, __LIBC_EXT_STACKTRACE_SIZE);
    char **symbols = backtrace_symbols(buffer, nptrs);

    if (symbols == NULL) {
        LIBC_EXT_LOG(LOG_ERROR, "backtrace symbols could not be loaded");
        return;
    }
    for (int i = 0; i < nptrs; i++) {
        LIBC_EXT_PRT(LOG_ERROR, "%s", symbols[i]);
    }
    free(symbols);
}

static libc_ext_exception_context_t *get_exception_stack(
    libc_ext_exception_context_t *new, const bool fetch)
{
    static __thread libc_ext_exception_context_t *exception_stack = NULL;

    if (fetch == false) {
        exception_stack = new;
    }
    return exception_stack;
}

const char *get_exception_str(const int code)
{
    if (code < LIBC_EXT_EXCEPTION_OK || code > LIBC_EXT_EXCEPTION_MAX) {
        return libc_ext_exception_description[LIBC_EXT_EXCEPTION_MAX];
    }
    return libc_ext_exception_description[code];
}

libc_ext_exception_context_t *init_try(void)
{
    libc_ext_exception_context_t *ctxt = (libc_ext_exception_context_t *)
        aligned_alloc(__LIBC_EXT_EXCEPTION_CONTEXT_ALIGNMENT,
        sizeof(libc_ext_exception_context_t));

    if (!ctxt) {
        LIBC_EXT_LOG(LOG_ERROR, "could not allocate memory for try");
        throw(LIBC_EXT_EXCEPTION_BAD_ALLOC);
    }
    memset(ctxt, 0, sizeof(libc_ext_exception_context_t) / sizeof(char));
    ctxt->__was_used = false;
    ctxt->__prev = get_exception_stack(NULL, true);
    get_exception_stack(ctxt, false);
    return ctxt;
}

void end_try(void)
{
    libc_ext_exception_context_t *ctxt = get_exception_stack(NULL, true);

    if (ctxt) {
        get_exception_stack(ctxt->__prev, false);
        free(ctxt);
    }
}

void throw(int code)
{
    libc_ext_exception_context_t *stack = get_exception_stack(NULL, true);

    if (stack == NULL) {
        LIBC_EXT_PRT(LOG_ERROR, "Uncaught exception: %s",
            get_exception_str(code));
        print_stacktrace();
        abort();
    } else if (stack->__was_used == true) {
        end_try();
        stack = get_exception_stack(NULL, true);
    }
    stack->__was_used = true;
    siglongjmp(stack->__env, code);
}

void catch_code_end(const int code)
{
    end_try();
    throw(code);
}
