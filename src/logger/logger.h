/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** logger
*/

#ifndef __LIBC_EXT_LOGGER_H_
    #define __LIBC_EXT_LOGGER_H_
    #include "../../include/macro.h"

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} libc_ext_log_type_t;

void init_logger(void);
void logger(libc_ext_log_type_t type, const char *restrict fmt, ...);
void logger_off(UNUSED libc_ext_log_type_t type,
    UNUSED const char *restrict fmt, ...);


    #if defined(DEBUG)
        #define __LC_EXT_LOG logger
    #else
        #define __LC_EXT_LOG logger_off
    #endif

    #define __LC_EXT_PRT logger
    #define __LIBC_EXT_INIT_LOG init_logger()

#endif /* !__LIBC_EXT_LOGGER_H_ */
