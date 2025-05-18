/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** snprintf_alloc
*/

#ifndef __C_EXTEND_SNPRINTF_ALLOC_H_
    #define __C_EXTEND_SNPRINTF_ALLOC_H_
    #include <stdarg.h>

char *snprintf_alloc(const char *restrict format, ...);
char *vsnprintf_alloc(const char *restrict format, va_list args);

#endif /* !__C_EXTEND_SNPRINTF_ALLOC_H_ */
