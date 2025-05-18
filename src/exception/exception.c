/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception
*/

#include "exception_internal.h"

static const char *libc_ext_exception_description[] = {
    "no exception",

    "bad arguments",
    "bad alloc",

    "unknown exception"
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

static void *init_internals(void)
{
    libc_ext_exception_internal_t *internal = (libc_ext_exception_internal_t *)
        aligned_alloc(__LIBC_EXT_EXCEPTION_CONTEXT_ALIGNMENT,
        sizeof(libc_ext_exception_internal_t));

    if (!internal) {
        LIBC_EXT_LOG(LOG_ERROR, "could not allocate memory for try");
        return NULL;
    }
    memset(internal, 0, sizeof(libc_ext_exception_internal_t) / sizeof(char));
    internal->__was_used = false;
    internal->__prev = get_exception_stack(NULL, true);
    return internal;
}

static void check_stack(const libc_ext_exception_context_t *ctxt,
    const int code)
{
    if (ctxt && ctxt->__internals) {
        return;
    } else if (ctxt == NULL) {
        LIBC_EXT_PRT(LOG_ERROR, "Uncaught exception: %s",
            get_exception_str(code));
    } else {
        LIBC_EXT_PRT(LOG_ERROR, "Exception stack was illegaly modified");
    }
    print_stacktrace();
    abort();
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
    ctxt->__internals = init_internals();
    if (!ctxt->__internals) {
        free(ctxt);
        throw(LIBC_EXT_EXCEPTION_BAD_ALLOC);
    }
    get_exception_stack(ctxt, false);
    return ctxt;
}

void end_try(void)
{
    libc_ext_exception_internal_t *internal;
    libc_ext_exception_context_t *ctxt = get_exception_stack(NULL, true);

    if (ctxt) {
        internal = (libc_ext_exception_internal_t *)ctxt->__internals;
        get_exception_stack(internal->__prev, false);
        free(internal);
        free(ctxt);
    }
}

void throw(int code)
{
    libc_ext_exception_context_t *ctxt = get_exception_stack(NULL, true);
    libc_ext_exception_internal_t *internal = ctxt ?
        (libc_ext_exception_internal_t *)ctxt->__internals : NULL;

    check_stack(ctxt, code);
    if (internal->__was_used == true) {
        end_try();
        ctxt = get_exception_stack(NULL, true);
        check_stack(ctxt, code);
        internal = ctxt ?
            (libc_ext_exception_internal_t *)ctxt->__internals : NULL;
    }
    internal->__was_used = true;
    siglongjmp(ctxt->__env, code);
}

void catch_end(const int code)
{
    end_try();
    throw(code);
}
