/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** exception
*/

#ifndef LIBC_EXT_EXCEPTION_H_
    #define LIBC_EXT_EXCEPTION_H_
    #include "../src/exception/exception.h"
    #include "../src/exception/exception_types.h"

    #define INIT_TRY __INIT_TRY
    #define TRY(code, ctxt) __TRY(code, ctxt)
    #define CATCH(code, expected) __CATCH(code, expected)
    #define CATCH_ALL __CATCH_ALL
    #define CATCH_CODE_END(code) __CATCH_CODE_END(code)
    #define END_TRY __END_TRY
    #define THROW(code) __THROW__(code)

#endif /* !LIBC_EXT_EXCEPTION_H_ */
