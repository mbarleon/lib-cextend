/*
** EPITECH PROJECT, 2025
** lib-cextend [debian-gnu-linux-12-]
** File description:
** elf32
*/

#include "nm_internal.h"

static Elf32_Shdr *find_section32(Elf32_Shdr *shdr, int shnum,
    const char *shstrtab, const char *name)
{
    for (int i = 0; i < shnum; ++i)
        if (shdr[i].sh_type == SHT_STRTAB && strcmp(shstrtab +
            shdr[i].sh_name, name) == 0) {
            return &shdr[i];
        }
    return NULL;
}

static Elf32_Shdr *find_section_type32(Elf32_Shdr *shdr, int shnum,
    uint32_t type)
{
    for (int i = 0; i < shnum; ++i) {
        if (shdr[i].sh_type == type) {
            return &shdr[i];
        }
    }
    return NULL;
}

static void parse_symbols32(const char *restrict fname, void *map,
    Elf32_Shdr *symtab_hdr, Elf32_Shdr *strtab_hdr)
{
    int type;
    Elf32_Sym *symtab = (Elf32_Sym *)((char *)map + symtab_hdr->sh_offset);
    char *strtab = (char *)map + strtab_hdr->sh_offset;
    size_t symcount = symtab_hdr->sh_size / sizeof(Elf32_Sym);

    for (size_t i = 0; i < symcount; ++i) {
        type = ELF32_ST_TYPE(symtab[i].st_info);
        if ((type == STT_FUNC || type == STT_OBJECT) &&
            symtab[i].st_name && strtab[symtab[i].st_name]) {
            add_nm_symbol(fname, (void *)(uintptr_t)symtab[i].st_value,
                type == STT_FUNC ? 'T' : 'D', strtab + symtab[i].st_name);
        }
    }
}

void handle_elf32(const char *restrict fname, void *map)
{
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)map;
    Elf32_Shdr *shdr = (Elf32_Shdr *)((char *)map + ehdr->e_shoff);
    char *shstrtab = (char *)map + shdr[ehdr->e_shstrndx].sh_offset;
    Elf32_Shdr *symtab_hdr = find_section_type32
        (shdr, ehdr->e_shnum, SHT_SYMTAB);
    Elf32_Shdr *strtab_hdr = find_section32
        (shdr, ehdr->e_shnum, shstrtab, ".strtab");

    if (!symtab_hdr || !strtab_hdr) {
        symtab_hdr = find_section_type32(shdr, ehdr->e_shnum, SHT_DYNSYM);
        strtab_hdr = find_section32(shdr, ehdr->e_shnum, shstrtab, ".dynstr");
    }
    if (symtab_hdr && strtab_hdr) {
        parse_symbols32(fname, map, symtab_hdr, strtab_hdr);
    }
}
