/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** init_memory_entry
*/

#include "entries.h"
#include "../include/entries/exception_init.h"

CTOR(CEXTEND_INIT_MEMORY_ENTRY)
void init_memory_entry(void)
{
    should_free_on_abort(true);
}
