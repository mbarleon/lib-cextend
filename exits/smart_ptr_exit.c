/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** zap_srv_init_log_entry
*/

#include "exits.h"
#include "../include/cextend/exit/memory_exit.h"

DTOR(CEXTEND_FREE_MEM_EXIT)
void c_extent_free_mem_exit(void)
{
    free_ptr_list();
}
