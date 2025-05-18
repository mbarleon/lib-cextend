/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** snprintf_alloc
*/

#ifndef C_EXTEND_SNPRINTF_ALLOC_H_
    #define C_EXTEND_SNPRINTF_ALLOC_H_
    #include <stdarg.h>

char *snprintf_alloc(const char *restrict format, ...);
char *vsnprintf_alloc(const char *restrict format, const va_list args);

#endif /* !C_EXTEND_SNPRINTF_ALLOC_H_ */
