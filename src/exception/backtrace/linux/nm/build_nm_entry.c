/*
** EPITECH PROJECT, 2025
** lib-cextend [debian-gnu-linux-12-]
** File description:
** build_nm_entry
*/

#include "nm_internal.h"

static cextend_nm_file_t *find_or_create_file(const char *restrict fname)
{
    cextend_nm_file_t *new_file;
    cextend_nm_file_t **list = get_nm_file_list();

    for (cextend_nm_file_t *tmp = *list; tmp; tmp = tmp->next) {
        if (strcmp(fname, tmp->fname) == 0) {
            return tmp;
        }
    }
    new_file = safe_malloc(sizeof(*new_file), NULL);
    new_file->fname = safe_strdup(fname);
    new_file->contents = NULL;
    new_file->next = *list;
    *list = new_file;
    return new_file;
}

void add_nm_symbol(const char *restrict fname, void *ptr, char type,
    const char *name)
{
    cextend_nm_file_t *file = find_or_create_file(fname);
    cextend_nm_t *new_sym = safe_malloc(sizeof(*new_sym), NULL);

    new_sym->ptr = ptr;
    new_sym->type = type;
    new_sym->name = safe_strdup(name);
    new_sym->next = file->contents;
    file->contents = new_sym;
}

static void chose_elf(unsigned char *e_ident, const char *restrict fname,
    void *map)
{
    if (e_ident[EI_CLASS] == ELFCLASS64)
        handle_elf64(fname, map);
    else if (e_ident[EI_CLASS] == ELFCLASS32)
        handle_elf32(fname, map);
}

void build_nm_entry(const char *restrict fname)
{
    void *map;
    struct stat st;
    unsigned char *e_ident;
    int fd = open(fname, O_RDONLY);

    if (fd < 0)
        return;
    if (fstat(fd, &st) < 0) {
        close(fd);
        return;
    }
    map = mmap(NULL, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (map == MAP_FAILED)
        return;
    e_ident = (unsigned char *)map;
    chose_elf(e_ident, fname, map);
    munmap(map, (size_t)st.st_size);
}
