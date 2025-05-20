/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** logger
*/

#ifndef CEXTEND_LOGGER_H_
    #define CEXTEND_LOGGER_H_
    #include "logger/logger.h"

    #define CEXTEND_INIT_LOG __CEXTEND_INIT_LOG
    #define CEXTEND_LOG(type, fmt, ...) __LC_EXT_LOG(type, fmt, ##__VA_ARGS__)
    #define CEXTEND_PRT(type, fmt, ...) __LC_EXT_PRT(type, fmt, ##__VA_ARGS__)

#endif /* !CEXTEND_LOGGER_H_ */
