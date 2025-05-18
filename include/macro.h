/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** macro
*/

#ifndef LIBC_EXT_MACRO_H_
    #define LIBC_EXT_MACRO_H_

    #define UNUSED __attribute__((unused))
    #define CLEANUP(func) __attribute__((cleanup(func)))
    #define CTOR(priority) __attribute__((constructor(priority)))

#endif /* !LIBC_EXT_MACRO_H_ */
