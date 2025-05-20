/*
** EPITECH PROJECT, 2025
** lib-cextend [debian-gnu-linux-12-]
** File description:
** nm_internal
*/

#ifndef CEXTEND_NM_INTERNAL_H_
    #define CEXTEND_NM_INTERNAL_H_
    #include <elf.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <linux/limits.h>

    #define __CEXTEND_NM_MAPPING_LINE_SIZE 512
    #define __CEXTEND_NM_MAPPING_MAPS_PATH_LEN 64

    #include "nm.h"
    #include "../../../../../include/memory.h"

typedef struct cextend_nm_s {
    void *ptr;
    char type;
    char *name;
    struct cextend_nm_s *next;
} cextend_nm_t;

typedef struct cextend_nm_file_s {
    char *fname;
    cextend_nm_t *contents;
    struct cextend_nm_file_s *next;
} cextend_nm_file_t;

cextend_nm_file_t **get_nm_file_list(void);

void build_nm_entry(const char *restrict fname);
void add_nm_symbol(const char *restrict fname, void *ptr, char type,
    const char *name);
void handle_elf32(const char *restrict fname, void *map);
void handle_elf64(const char *restrict fname, void *map);

const char *get_symname_from_entry(void *ptr, const char *restrict fname);

#endif /* !CEXTEND_NM_INTERNAL_H_ */
