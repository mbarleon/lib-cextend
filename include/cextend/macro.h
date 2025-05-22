/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** macro
*/

#ifndef CEXTEND_MACRO_H_
    #define CEXTEND_MACRO_H_

    #define UNUSED __attribute__((unused))
    #define CLEANUP(func) __attribute__((cleanup(func)))
    #define DTOR(priority) __attribute__((destructor(priority)))
    #define CTOR(priority) __attribute__((constructor(priority)))

#endif /* !CEXTEND_MACRO_H_ */
