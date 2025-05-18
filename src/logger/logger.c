/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** logger
*/

#include "logger_internal.h"

static pthread_mutex_t *get_mtx(void)
{
    static pthread_mutex_t logger_mtx = PTHREAD_MUTEX_INITIALIZER;

    return &logger_mtx;
}

static bool is_logger_init(bool init)
{
    static bool is_init = false;

    if (init == true) {
        is_init = true;
    }
    return is_init;
}

static libc_ext_logger_type_infos_t get_infos(const libc_ext_log_type_t type)
{
    switch (type) {
        case LOG_INFO:
            return (libc_ext_logger_type_infos_t)
                {LIBC_EXT_LOGGER_INFO_STR, LIBC_EXT_LOGGER_CYELLOW, stdout};
        case LOG_WARNING:
            return (libc_ext_logger_type_infos_t)
                {LIBC_EXT_LOGGER_WARNING_STR, LIBC_EXT_LOGGER_CPURPLE, stderr};
        case LOG_ERROR:
            return (libc_ext_logger_type_infos_t)
                {LIBC_EXT_LOGGER_ERROR_STR, LIBC_EXT_LOGGER_CRED, stderr};
        default:
            return (libc_ext_logger_type_infos_t)
                {NULL, NULL, NULL};
    }
}

static bool handle_logger_errors(const size_t fmt_size, const size_t type_len)
{
    if (is_logger_init(false) == false) {
        fprintf(stderr, "%s[ERROR]: Logger is not initialized.%s\n",
            LIBC_EXT_LOGGER_CRED, LIBC_EXT_LOGGER_CRESET);
        fflush(stderr);
        return false;
    }
    if (fmt_size >= LIBC_EXT_LOGGER_MAX_FORMAT_SIZE) {
        fprintf(stderr, "%s[ERROR]: Logger format is too big.%s\n",
            LIBC_EXT_LOGGER_CRED, LIBC_EXT_LOGGER_CRESET);
        fflush(stderr);
        return false;
    }
    if (type_len == 0) {
        fprintf(stderr, "%s[ERROR]: Unknown logger type.%s\n",
            LIBC_EXT_LOGGER_CRED, LIBC_EXT_LOGGER_CRESET);
        fflush(stderr);
        return false;
    }
    return true;
}

static bool get_format(libc_ext_logger_type_infos_t *infos,
    const libc_ext_log_type_t type, const char *restrict fmt,
    char *restrict new_fmt)
{
    size_t type_len;
    size_t new_fmt_size;

    *infos = get_infos(type);
    type_len = infos->type_str ? strlen(infos->type_str) : 0;
    new_fmt_size = strlen(fmt) + type_len + LIBC_EXT_LOGGER_ANSI_FMT_EXTRA;
    if (handle_logger_errors(new_fmt_size, type_len) == false) {
        return false;
    }
    snprintf(new_fmt, LIBC_EXT_LOGGER_MAX_FORMAT_SIZE, "%s[%s]: %s%s\n",
        infos->type_color, infos->type_str, fmt, LIBC_EXT_LOGGER_CRESET);
    return true;
}

static void log_print(libc_ext_logger_type_infos_t *infos,
    const char *restrict new_fmt, va_list args)
{
    pthread_mutex_t *logger_mtx = get_mtx();

    pthread_mutex_lock(logger_mtx);
    vfprintf(infos->type_stream, new_fmt, args);
    fflush(infos->type_stream);
    pthread_mutex_unlock(logger_mtx);
}

void init_logger(void)
{
    get_mtx();
    is_logger_init(true);
}

void logger(const libc_ext_log_type_t type, const char *restrict fmt, ...)
{
    va_list args;
    libc_ext_logger_type_infos_t infos;
    char new_fmt[LIBC_EXT_LOGGER_MAX_FORMAT_SIZE];

    get_format(&infos, type, fmt, new_fmt);
    va_start(args, fmt);
    log_print(&infos, new_fmt, args);
    va_end(args);
}

void logger_off(UNUSED libc_ext_log_type_t type,
    UNUSED const char *restrict fmt, ...)
{
}
