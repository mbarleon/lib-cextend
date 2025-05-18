/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** logger
*/

#ifndef __C_EXTEND_LOGGER_H_
    #define __C_EXTEND_LOGGER_H_
    #include "../../include/macro.h"

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} c_extend_log_type_t;

void init_logger(void);
void logger(c_extend_log_type_t type, const char *restrict fmt, ...);
void logger_off(UNUSED c_extend_log_type_t type,
    UNUSED const char *restrict fmt, ...);


    #if defined(DEBUG)
        #define __LC_EXT_LOG logger
    #else
        #define __LC_EXT_LOG logger_off
    #endif

    #define __LC_EXT_PRT logger
    #define __C_EXTEND_INIT_LOG init_logger()

#endif /* !__C_EXTEND_LOGGER_H_ */
