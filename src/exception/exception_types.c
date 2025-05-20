/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception
*/

#include "exception_internal.h"

static const char *c_extend_exception_desc[] = {
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
    if (code < C_EXTEND_EXCEPTION || code > C_EXTEND_EXCEPTION_MAX) {
        return c_extend_exception_desc[C_EXTEND_EXCEPTION_BAD_EXCEPTION];
    }
    return c_extend_exception_desc[code];
}
