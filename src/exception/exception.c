/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception
*/

#include "exception_internal.h"

static void print_stacktrace(void)
{
    void *buffer[__C_EXTEND_STACKTRACE_SIZE];
    int nptrs = backtrace(buffer, __C_EXTEND_STACKTRACE_SIZE);
    char **symbols = backtrace_symbols(buffer, nptrs);

    if (symbols == NULL) {
        C_EXTEND_LOG(LOG_ERROR, "backtrace symbols could not be loaded");
        return;
    }
    for (int i = 0; i < nptrs; ++i) {
        C_EXTEND_PRT(LOG_ERROR, "%s", symbols[i]);
    }
    free(symbols);
}

static c_extend_exception_context_t *get_exception_stack(
    c_extend_exception_context_t *new, const bool fetch)
{
    static __thread c_extend_exception_context_t *exception_stack = NULL;

    if (fetch == false) {
        exception_stack = new;
    }
    return exception_stack;
}

static void *init_internals(void)
{
    c_extend_exception_internal_t *internal = (c_extend_exception_internal_t *)
        aligned_alloc(__C_EXTEND_EXCEPTION_CONTEXT_ALIGNMENT,
        sizeof(c_extend_exception_internal_t));

    if (!internal) {
        C_EXTEND_LOG(LOG_ERROR, "could not allocate memory for try");
        return NULL;
    }
    memset(internal, 0, sizeof(c_extend_exception_internal_t) / sizeof(char));
    internal->__was_used = false;
    internal->__prev = get_exception_stack(NULL, true);
    return internal;
}

static void check_stack(const c_extend_exception_context_t *ctxt,
    const int code)
{
    if (ctxt && ctxt->__internals) {
        return;
    } else if (ctxt == NULL) {
        C_EXTEND_PRT(LOG_ERROR, "Uncaught exception: %s",
            get_exception_str(code));
    } else {
        C_EXTEND_PRT(LOG_ERROR, "Exception stack was illegaly modified");
    }
    print_stacktrace();
    abort();
}

static bool catch_code_helper(int code, int expected, int min, int max)
{
    return expected == min && code >= min && code <= max;
}

c_extend_exception_context_t *init_try(void)
{
    c_extend_exception_context_t *ctxt = (c_extend_exception_context_t *)
        aligned_alloc(__C_EXTEND_EXCEPTION_CONTEXT_ALIGNMENT,
        sizeof(c_extend_exception_context_t));

    if (!ctxt) {
        C_EXTEND_LOG(LOG_ERROR, "could not allocate memory for try");
        throw(C_EXTEND_EXCEPTION_BAD_ALLOC);
    }
    memset(ctxt, 0, sizeof(c_extend_exception_context_t) / sizeof(char));
    ctxt->__internals = init_internals();
    if (!ctxt->__internals) {
        free(ctxt);
        throw(C_EXTEND_EXCEPTION_BAD_ALLOC);
    }
    get_exception_stack(ctxt, false);
    return ctxt;
}

void end_try(void)
{
    c_extend_exception_internal_t *internal;
    c_extend_exception_context_t *ctxt = get_exception_stack(NULL, true);

    if (ctxt) {
        internal = (c_extend_exception_internal_t *)ctxt->__internals;
        get_exception_stack(internal->__prev, false);
        free(internal);
        free(ctxt);
    }
}

void throw(int code)
{
    c_extend_exception_context_t *ctxt = get_exception_stack(NULL, true);
    c_extend_exception_internal_t *internal = ctxt ?
        (c_extend_exception_internal_t *)ctxt->__internals : NULL;

    check_stack(ctxt, code);
    if (internal->__was_used == true) {
        end_try();
        ctxt = get_exception_stack(NULL, true);
        check_stack(ctxt, code);
        internal = ctxt ?
            (c_extend_exception_internal_t *)ctxt->__internals : NULL;
    }
    internal->__was_used = true;
    siglongjmp(ctxt->__env, code);
}

bool catch_code(int code, int expected)
{
    if (catch_code_helper(code, expected, C_EXTEND_EXCEPTION,
        C_EXTEND_EXCEPTION_MAX)) {
        return true;
    }
    if (catch_code_helper(code, expected, C_EXTEND_EXCEPTION_LOGIC_ERROR,
        C_EXTEND_EXCEPTION_LOGIC_ERROR_MAX)) {
        return true;
    }
    if (catch_code_helper(code, expected, C_EXTEND_EXCEPTION_RUNTIME_ERROR,
        C_EXTEND_EXCEPTION_RUNTIME_ERROR_MAX)) {
        return true;
    }
    if (catch_code_helper(code, expected, C_EXTEND_EXCEPTION_BAD_ALLOC,
        C_EXTEND_EXCEPTION_BAD_ALLOC_MAX)) {
        return true;
    }
    return code == expected;
}

void catch_end(const int code)
{
    end_try();
    throw(code);
}
