/*
** EPITECH PROJECT, 2025
** coding-style-war-crimes
** File description:
** exception
*/

#ifndef __LIBC_EXT_EXCEPTION_H_
    #define __LIBC_EXT_EXCEPTION_H_
    #include "exception_types.h"

libc_ext_exception_context_t *init_try(void);
void end_try(void);
void throw(int code);
const char *get_exception_str(const int code);
void catch_code_end(const int code);

    #define __INIT_TRY init_try()
    #define __TRY(code, ctxt) if ((code = sigsetjmp((ctxt)->__env, 0)) == 0)
    #define __CATCH(code, expected) else if (code == expected)
    #define __CATCH_ALL else
    #define __CATCH_CODE_END__(code) catch_code_end(code)
    #define __CATCH_CODE_END(code) CATCH_ALL __CATCH_CODE_END__(code)
    #define __END_TRY end_try()
    #define __THROW__(code) throw(code)

#endif /* !__LIBC_EXT_EXCEPTION_H_ */
