/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** backtrace
*/

#include "backtrace.h"

void print_stacktrace(void)
{
    Dl_info info;
    void *buffer[__CEXTEND_STACKTRACE_SIZE];
    int nptrs = backtrace(buffer, __CEXTEND_STACKTRACE_SIZE);

    for (int i = __CEXTEND_BT_NPTRS_MIN; i <
        nptrs - __CEXTEND_BT_NPTRS_SUB; ++i) {
        if (dladdr(buffer[i], &info)) {
            CEXTEND_PRT(LOG_ERROR, "    %s %p: %s (%s)",
                i == __CEXTEND_BT_NPTRS_MIN ? "at" : "by", buffer[i],
                info.dli_sname ? info.dli_sname : "???",
                info.dli_fname ? info.dli_fname : "???");
        } else {
            CEXTEND_PRT(LOG_ERROR, "    %s %p: [no symbol info]",
                i == __CEXTEND_BT_NPTRS_MIN ? "at" : "by", buffer[i]);
        }
    }
}
