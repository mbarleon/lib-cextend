/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** logger_internal
*/

#ifndef CEXTEND_LOGGER_INTERNAL_H_
    #define CEXTEND_LOGGER_INTERNAL_H_

    #include <stdio.h>
    #include <stddef.h>
    #include <stdarg.h>
    #include <string.h>
    #include <stdbool.h>
    #include <pthread.h>

    #include "logger.h"
    #include "logger_init.h"

    #define CEXTEND_LOGGER_CRED "\x1b[31m"
    #define CEXTEND_LOGGER_CRESET "\x1b[0m"
    #define CEXTEND_LOGGER_CYELLOW "\x1b[33m"
    #define CEXTEND_LOGGER_CPURPLE "\x1b[35m"

    #define CEXTEND_LOGGER_INFO_STR "INFO"
    #define CEXTEND_LOGGER_WARNING_STR "WARNING"
    #define CEXTEND_LOGGER_ERROR_STR "ERROR"

    #define CEXTEND_LOGGER_ANSI_FMT_EXTRA 15
    #define CEXTEND_LOGGER_MAX_FORMAT_SIZE 2048

typedef struct {
    const char *type_str;
    const char *type_color;
    FILE *type_stream;
} cextend_logger_type_infos_t;

#endif /* !CEXTEND_LOGGER_INTERNAL_H_ */
