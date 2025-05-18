/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** snprintf_alloc
*/

#ifndef LIBC_EXT_SNPRINTF_ALLOC_H_
    #define LIBC_EXT_SNPRINTF_ALLOC_H_
    #include <stdarg.h>

char *snprintf_alloc(const char *restrict format, ...);
char *vsnprintf_alloc(const char *restrict format, const va_list args);

#endif /* !LIBC_EXT_SNPRINTF_ALLOC_H_ */
