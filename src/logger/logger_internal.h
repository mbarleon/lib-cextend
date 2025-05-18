/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** logger_internal
*/

#ifndef C_EXTEND_LOGGER_INTERNAL_H_
    #define C_EXTEND_LOGGER_INTERNAL_H_

    #include <stdio.h>
    #include <stddef.h>
    #include <stdarg.h>
    #include <string.h>
    #include <stdbool.h>
    #include <pthread.h>

    #include "logger.h"

    #define C_EXTEND_LOGGER_CRED "\x1b[31m"
    #define C_EXTEND_LOGGER_CRESET "\x1b[0m"
    #define C_EXTEND_LOGGER_CYELLOW "\x1b[33m"
    #define C_EXTEND_LOGGER_CPURPLE "\x1b[35m"

    #define C_EXTEND_LOGGER_INFO_STR "INFO"
    #define C_EXTEND_LOGGER_WARNING_STR "WARNING"
    #define C_EXTEND_LOGGER_ERROR_STR "ERROR"

    #define C_EXTEND_LOGGER_ANSI_FMT_EXTRA 15
    #define C_EXTEND_LOGGER_MAX_FORMAT_SIZE 2048

typedef struct {
    const char *type_str;
    const char *type_color;
    FILE *type_stream;
} c_extend_logger_type_infos_t;

#endif /* !C_EXTEND_LOGGER_INTERNAL_H_ */
