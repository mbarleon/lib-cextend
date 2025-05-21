/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** backtrace
*/

#ifndef CEXTEND_BACKTRACE_H_
    #define CEXTEND_BACKTRACE_H_

    #define __CEXTEND_STACKTRACE_SIZE 256

    #if !defined(_GNU_SOURCE) && defined(__linux__)
        #define _GNU_SOURCE
        #define __CEXTEND_BT_DEFINE_GNU_SOURCE
    #endif

    #if defined(__APPLE__)
        #define __CEXTEND_BT_NPTRS_SUB 1
        #define __CEXTEND_BT_NPTRS_MIN 1
    #else
        #define __CEXTEND_BT_NPTRS_SUB 3
        #define __CEXTEND_BT_NPTRS_MIN 1
    #endif

    #include <dlfcn.h>
    #include <execinfo.h>

    #include "../../../include/logger.h"

void print_stacktrace(void);

    #if defined(__CEXTEND_BT_DEFINE_GNU_SOURCE)
        #undef _GNU_SOURCE
    #endif
#endif /* !CEXTEND_BACKTRACE_H_ */
