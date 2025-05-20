/*
** EPITECH PROJECT, 2025
** lib-cextend [debian-gnu-linux-12-]
** File description:
** get_symname_entry
*/

#include "nm_internal.h"

static int resolve_and_compare(const char *a, const char *b)
{
    char ra[PATH_MAX];
    char rb[PATH_MAX];

    return realpath(a, ra) && realpath(b, rb) && strcmp(ra, rb) == 0;
}

static int parse_maps_line(const char *line, uintptr_t ptrs[3],
    char **path_start)
{
    *path_start = strrchr(line, ' ');
    if (!*path_start)
        return 0;
    if (sscanf(line, "%lx-%lx %*s %lx", &ptrs[0], &ptrs[1], &ptrs[2]) != 3)
        return 0;
    ++(*path_start);
    (*path_start)[strcspn(*path_start, "\n")] = '\0';
    return 1;
}

static int is_ptr_in_range(uintptr_t ptr, uintptr_t start, uintptr_t end)
{
    return ptr >= start && ptr < end;
}

static int set_ptrs(uintptr_t *base, uintptr_t *offset, FILE *maps,
    uintptr_t ptrs[3])
{
    *base = ptrs[0];
    *offset = ptrs[2];
    fclose(maps);
    return 1;
}

static int find_mapping(const char *fname, uintptr_t ptr,
    uintptr_t *base, uintptr_t *offset)
{
    FILE *maps;
    char *path_start;
    uintptr_t ptrs[3];
    char line[__CEXTEND_NM_MAPPING_LINE_SIZE];
    char maps_path[__CEXTEND_NM_MAPPING_MAPS_PATH_LEN];

    snprintf(maps_path, sizeof(maps_path), "/proc/%d/maps", getpid());
    maps = fopen(maps_path, "r");
    if (!maps)
        return 0;
    while (fgets(line, sizeof(line), maps)) {
        if (!parse_maps_line(line, ptrs, &path_start))
            continue;
        if (resolve_and_compare(path_start, fname) &&
            is_ptr_in_range(ptr, ptrs[0], ptrs[1]))
            return set_ptrs(base, offset, maps, ptrs);
    }
    fclose(maps);
    return 0;
}

static const char *find_best_symbol(cextend_nm_file_t *file, uintptr_t addr)
{
    uintptr_t best_addr = 0;
    const char *best_name = NULL;

    for (cextend_nm_t *sym = file->contents; sym; sym = sym->next) {
        if ((uintptr_t)sym->ptr <= addr && (uintptr_t)sym->ptr >= best_addr) {
            best_addr = (uintptr_t)sym->ptr;
            best_name = sym->name;
        }
    }
    return best_name;
}

const char *get_symname_from_entry(void *ptr, const char *fname)
{
    uintptr_t addr;
    uintptr_t base = 0;
    uintptr_t offset = 0;
    cextend_nm_file_t **list = get_nm_file_list();

    if (!list || !*list)
        return NULL;
    if (!find_mapping(fname, (uintptr_t)ptr, &base, &offset))
        return NULL;
    addr = (uintptr_t)ptr - base + offset;
    for (cextend_nm_file_t *file = *list; file; file = file->next)
        if (strcmp(file->fname, fname) == 0)
            return find_best_symbol(file, addr);
    return NULL;
}
