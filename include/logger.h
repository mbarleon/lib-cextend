/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** logger
*/

#ifndef LIBC_EXT_LOGGER_H_
    #define LIBC_EXT_LOGGER_H_
    #include "../src/logger/logger.h"

    #define LIBC_EXT_INIT_LOG __LIBC_EXT_INIT_LOG
    #define LIBC_EXT_LOG(type, fmt, ...) __LC_EXT_LOG(type, fmt, ##__VA_ARGS__)
    #define LIBC_EXT_PRT(type, fmt, ...) __LC_EXT_PRT(type, fmt, ##__VA_ARGS__)

#endif /* !LIBC_EXT_LOGGER_H_ */
