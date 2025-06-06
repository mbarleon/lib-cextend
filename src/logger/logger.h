/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** logger
*/

#ifndef __CEXTEND_LOGGER_H_
    #define __CEXTEND_LOGGER_H_
    #include "../../include/cextend/macro.h"

typedef enum {
    CEXTEND_LOG_INFO,
    CEXTEND_LOG_WARNING,
    CEXTEND_LOG_ERROR
} cextend_log_type_t;

__attribute__((format(printf, 2, 3)))
int logger(cextend_log_type_t type, const char *restrict fmt, ...);
int logger_off(UNUSED cextend_log_type_t type,
    UNUSED const char *restrict fmt, ...);


    #if defined(CEXTEND_DEBUG)
        #define __CEXT_LOG logger
    #else
        #define __CEXT_LOG logger_off
    #endif

    #define __CEXT_PRT logger

#endif /* !__CEXTEND_LOGGER_H_ */
