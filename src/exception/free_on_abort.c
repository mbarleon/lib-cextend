/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** free_on_exit
*/

#include "exception_init.h"

bool should_free_on_abort(bool abort)
{
    static bool should_free = false;

    if (abort == true) {
        should_free = true;
    }
    return should_free;
}
