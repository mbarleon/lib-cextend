/*
** EPITECH PROJECT, 2025
** libc-extension
** File description:
** exception
*/

#ifndef CEXTEND_EXCEPTION_H_
    #define CEXTEND_EXCEPTION_H_
    #include "exception/exception.h"
    #include "exception/exception_types.h"

    #define INIT_TRY __INIT_TRY
    #define TRY(code, ctxt) __TRY(code, ctxt)
    #define CATCH(code, expected) __CATCH(code, expected)
    #define CATCH_ALL __CATCH_ALL
    #define CATCH_END(code) __CATCH_END(code)
    #define END_TRY __END_TRY
    #define THROW(code) __THROW__(code)

#endif /* !CEXTEND_EXCEPTION_H_ */
