/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception
*/

#include "exception_internal.h"

static const char *c_extend_exception_description[] = {
    "no exception",

    "bad arguments",
    "bad alloc",

    "unknown exception"
};

const char *get_exception_str(const int code)
{
    if (code < C_EXTEND_EXCEPTION_OK || code > C_EXTEND_EXCEPTION_MAX) {
        return c_extend_exception_description[C_EXTEND_EXCEPTION_MAX];
    }
    return c_extend_exception_description[code];
}
