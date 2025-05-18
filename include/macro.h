/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** macro
*/

#ifndef C_EXTEND_MACRO_H_
    #define C_EXTEND_MACRO_H_

    #define UNUSED __attribute__((unused))
    #define CLEANUP(func) __attribute__((cleanup(func)))
    #define CTOR(priority) __attribute__((constructor(priority)))

#endif /* !C_EXTEND_MACRO_H_ */
