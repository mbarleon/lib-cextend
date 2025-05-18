/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** logger
*/

#ifndef C_EXTEND_LOGGER_H_
    #define C_EXTEND_LOGGER_H_
    #include "../src/logger/logger.h"

    #define C_EXTEND_INIT_LOG __C_EXTEND_INIT_LOG
    #define C_EXTEND_LOG(type, fmt, ...) __LC_EXT_LOG(type, fmt, ##__VA_ARGS__)
    #define C_EXTEND_PRT(type, fmt, ...) __LC_EXT_PRT(type, fmt, ##__VA_ARGS__)

#endif /* !C_EXTEND_LOGGER_H_ */
