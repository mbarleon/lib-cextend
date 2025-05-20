/*
** EPITECH PROJECT, 2025
** lib-cextend [debian-gnu-linux-12-]
** File description:
** nm
*/

#include "nm_internal.h"

cextend_nm_file_t **get_nm_file_list(void)
{
    static cextend_nm_file_t *list = NULL;

    return &list;
}

static bool file_in_list(const char *restrict fname)
{
    cextend_nm_file_t **list = get_nm_file_list();

    if (!list || !*list) {
        return false;
    }
    for (cextend_nm_file_t *tmp = *list; tmp; tmp = tmp->next) {
        if (strcmp(fname, tmp->fname) == 0) {
            return true;
        }
    }
    return false;
}

const char *do_nm(void *ptr, const char *restrict fname)
{
    const char *symname = NULL;

    if (!file_in_list(fname)) {
        build_nm_entry(fname);
    }
    symname = get_symname_from_entry(ptr, fname);
    return symname ? symname : "???";
}
