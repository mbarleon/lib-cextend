/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** vnsprintf_alloc
*/

#include "snprintf_alloc_internal.h"

char *snprintf_alloc(const char *restrict format, ...)
{
    int len;
    char *buffer;
    va_list args;

    va_start(args, format);
    len = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (len < 0) {
        THROW(C_EXTEND_EXCEPTION_BAD_ARGS);
    }
    buffer = (char *)malloc(sizeof(char) * (size_t)(len + 1));
    if (!buffer) {
        THROW(C_EXTEND_EXCEPTION_BAD_ALLOC);
    }
    va_start(args, format);
    vsnprintf(buffer, (size_t)(len + 1), format, args);
    va_end(args);
    return buffer;
}

char *vsnprintf_alloc(const char *restrict format, va_list args)
{
    int len;
    char *buffer;
    va_list copy;

    va_copy(copy, args);
    len = vsnprintf(NULL, 0, format, copy);
    va_end(copy);
    if (len < 0) {
        THROW(C_EXTEND_EXCEPTION_BAD_ARGS);
    }
    buffer = (char *)malloc(sizeof(char) * (size_t)(len + 1));
    if (!buffer) {
        THROW(C_EXTEND_EXCEPTION_BAD_ALLOC);
    }
    va_copy(copy, args);
    vsnprintf(buffer, (size_t)(len + 1), format, copy);
    va_end(copy);
    return buffer;
}
