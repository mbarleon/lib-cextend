/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** zap_srv_init_log_entry
*/

#include "exits.h"
#include "../include/memory_exit.h"

DTOR(C_EXTEND_FREE_MEM_EXIT)
void c_extent_free_mem_exit(void)
{
    free_ptr_list();
}
