/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** exception
*/

#include "exception_internal.h"

static const char *cextend_exception_desc[] = {
    "exception",

    "logic_error",
    "invalid_argument",
    "domain_error",
    "length_error",
    "out_of_range",
    "future_error",
    "logic_error_max",

    "runtime_error",
    "range_error",
    "overflow_error",
    "underflow_error",
    "regex_error",
    "system_error",
    "tx_exception",
    "nonexistent_local_time",
    "ambiguous_local_time",
    "format_error",
    "runtime_error_max",

    "bad_type",
    "bad_typeid",
    "bad_cast",

    "bad_function_call",

    "bad_alloc",
    "bad_array_new_length",
    "bad_alloc_max",

    "bad_exception",

    "exception_max"
};

const char *get_exception_str(const int code)
{
    if (code < CEXTEND_EXCEPTION || code > CEXTEND_EXCEPTION_MAX) {
        return cextend_exception_desc[CEXTEND_EXCEPTION_BAD_EXCEPTION];
    }
    return cextend_exception_desc[code];
}
