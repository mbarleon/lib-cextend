/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception
*/

#include "exception_internal.h"

static void print_stacktrace(void)
{
    void *buffer[__CEXTEND_STACKTRACE_SIZE];
    int nptrs = backtrace(buffer, __CEXTEND_STACKTRACE_SIZE);
    char **symbols = backtrace_symbols(buffer, nptrs);

    if (symbols == NULL) {
        CEXTEND_LOG(LOG_ERROR, "backtrace symbols could not be loaded");
        return;
    }
    for (int i = 0; i < nptrs; ++i) {
        CEXTEND_PRT(LOG_ERROR, "%s", symbols[i]);
    }
    free(symbols);
}

static cextend_exception_context_t *get_exception_stack(
    cextend_exception_context_t *new, const bool fetch)
{
    static __thread cextend_exception_context_t *exception_stack = NULL;

    if (fetch == false) {
        exception_stack = new;
    }
    return exception_stack;
}

static void *init_internals(void)
{
    cextend_exception_internal_t *internal = (cextend_exception_internal_t *)
        aligned_alloc(__CEXTEND_EXCEPTION_CONTEXT_ALIGNMENT,
        sizeof(cextend_exception_internal_t));

    if (!internal) {
        CEXTEND_LOG(LOG_ERROR, "could not allocate memory for try");
        return NULL;
    }
    memset(internal, 0, sizeof(cextend_exception_internal_t) / sizeof(char));
    internal->__was_used = false;
    internal->__prev = get_exception_stack(NULL, true);
    return internal;
}

static void check_stack(const cextend_exception_context_t *ctxt,
    const int code)
{
    if (ctxt && ctxt->__internals) {
        return;
    } else if (ctxt == NULL) {
        CEXTEND_PRT(LOG_ERROR, "Uncaught exception: %s",
            get_exception_str(code));
    } else {
        CEXTEND_PRT(LOG_ERROR, "Exception stack was illegaly modified");
    }
    print_stacktrace();
    abort();
}

static bool catch_code_helper(int code, int expected, int min, int max)
{
    return expected == min && code >= min && code <= max;
}

cextend_exception_context_t *init_try(void)
{
    cextend_exception_context_t *ctxt = (cextend_exception_context_t *)
        aligned_alloc(__CEXTEND_EXCEPTION_CONTEXT_ALIGNMENT,
        sizeof(cextend_exception_context_t));

    if (!ctxt) {
        CEXTEND_LOG(LOG_ERROR, "could not allocate memory for try");
        throw(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    memset(ctxt, 0, sizeof(cextend_exception_context_t) / sizeof(char));
    ctxt->__internals = init_internals();
    if (!ctxt->__internals) {
        free(ctxt);
        throw(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    get_exception_stack(ctxt, false);
    return ctxt;
}

void end_try(void)
{
    cextend_exception_internal_t *internal;
    cextend_exception_context_t *ctxt = get_exception_stack(NULL, true);

    if (ctxt) {
        internal = (cextend_exception_internal_t *)ctxt->__internals;
        get_exception_stack(internal->__prev, false);
        free(internal);
        free(ctxt);
    }
}

void throw(int code)
{
    cextend_exception_context_t *ctxt = get_exception_stack(NULL, true);
    cextend_exception_internal_t *internal = ctxt ?
        (cextend_exception_internal_t *)ctxt->__internals : NULL;

    check_stack(ctxt, code);
    if (internal->__was_used == true) {
        end_try();
        ctxt = get_exception_stack(NULL, true);
        check_stack(ctxt, code);
        internal = ctxt ?
            (cextend_exception_internal_t *)ctxt->__internals : NULL;
    }
    internal->__was_used = true;
    siglongjmp(ctxt->__env, code);
}

bool catch_code(int code, int expected)
{
    if (catch_code_helper(code, expected, CEXTEND_EXCEPTION,
        CEXTEND_EXCEPTION_MAX)) {
        return true;
    }
    if (catch_code_helper(code, expected, CEXTEND_EXCEPTION_LOGIC_ERROR,
        CEXTEND_EXCEPTION_LOGIC_ERROR_MAX)) {
        return true;
    }
    if (catch_code_helper(code, expected, CEXTEND_EXCEPTION_RUNTIME_ERROR,
        CEXTEND_EXCEPTION_RUNTIME_ERROR_MAX)) {
        return true;
    }
    if (catch_code_helper(code, expected, CEXTEND_EXCEPTION_BAD_ALLOC,
        CEXTEND_EXCEPTION_BAD_ALLOC_MAX)) {
        return true;
    }
    return code == expected;
}

void catch_end(const int code)
{
    end_try();
    throw(code);
}
