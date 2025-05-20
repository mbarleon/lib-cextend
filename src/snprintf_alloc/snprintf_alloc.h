/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** snprintf_alloc
*/

#ifndef __CEXTEND_SNPRINTF_ALLOC_H_
    #define __CEXTEND_SNPRINTF_ALLOC_H_
    #include <stdarg.h>

char *snprintf_alloc(const char *restrict format, ...);
char *vsnprintf_alloc(const char *restrict format, va_list args);

#endif /* !__CEXTEND_SNPRINTF_ALLOC_H_ */
