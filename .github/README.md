<h1 align="center">
  LIB-CEXTEND - 2025<br>
  <img src="https://raw.githubusercontent.com/catppuccin/catppuccin/main/assets/palette/macchiato.png" width="600px" alt="color palette"/>
  <br>
</h1>

<p align="center">
  Not C, not C++, C+<br>
</p>

---

## Usage

Clone the repository

```bash
git clone git@github.com:mbarleon/lib-cextend.git
```

Build the project

```bash
./build.sh
```

Copy the library to a directory recognized by the dynamic loader, and the header files to one included in the compiler's search path.

---

## Functionalities

For now, the current functionalities have been implemented.

### Exceptions:

```
NAME
    INIT_TRY, TRY, CATCH, CATCH_ALL, CATCH_END, END_TRY, THROW,
    should_free_on_abort - exception handling

SYNOPSIS
    #include <cextend/exception.h>

    cextend_exception_context_t *INIT_TRY

    TRY(cextend_exception_code_t code, cextend_exception_context_t *ctxt)

    CATCH(cextend_exception_code_t code, cextend_exception_code_t expected)

    CATCH_END(cextend_exception_code_t code)

    CATCH_ALL

    END_TRY

    THROW(cextend_exception_code_t code)

    ---

    #include <cextend/entries/exception_init.h>

    bool should_free_on_abort(bool abort);

DESCRIPTION
    The INIT_TRY macro creates the context for the TRY block. In case of an
    error, it may throw CEXTEND_EXCEPTION_BAD_ALLOC.

    The TRY macro instanciates a TRY block. It takes as its arguments a code
    and a context initialized by INIT_TRY. The code is supposed to be
    initialized to 0.

    The CATCH macro catches an exception or exception block. It takes as its
    arguments the same code as TRY and the code or block it expects. Multiple
    CATCH block can be put after one another in order to catch multiple
    exceptions and/or blocks.

    The CATCH_END macro is expected after the last CATCH block. It takes as its
    arguments the same code as TRY.

    The CATCH_ALL macro catches all the possible exceptions. It is compatible
    with CATCH and can replace CATCH_END.

    The END_TRY macro ends the TRY block and frees the context.

    The THROW macro takes an exception code as its context and throws it. If
    the exception is caught somewhere lower in the stack, it will jump to this
    point in the stack. Otherwise, the program will be aborted.

    The should_free_on_abort function takes as its argument a boolean. It tells
    the CEXTEND library if it should free the memory allocated by
    smart_pointers and safe_allocs (<cextend/memory.h>) before aborting (true)
    or not (false). It is recommended to call this function in a function with
    __attribute__((constructor)).

EXAMPLE

    #include <stdio.h>
    #include <cextend/exception.h>

    static void unsafe_func2(void)
    {
        THROW(CEXTEND_EXCEPTION_LOGIC_ERROR);
    }

    static void unsafe_func1(void)
    {
        cextend_exception_code_t code = 0;
        cextend_exception_context_t *ctxt = INIT_TRY;

        TRY(code, ctxt) {
            unsafe_func2();
        } CATCH(code, CEXTEND_EXCEPTION_BAD_ALLOC) {
            fprintf(stderr, "Bad alloc!\n");
        } CATCH_ALL {
            THROW(CEXTEND_EXCEPTION_LOGIC_ERROR);
        }
        END_TRY;
    }

    int main(void)
    {
        cextend_exception_code_t code = 0;
        cextend_exception_context_t *ctxt = INIT_TRY;

        TRY(code, ctxt) {
            unsafe_func1();
        } CATCH(code, CEXTEND_EXCEPTION_LOGIC_ERROR) {
            return 84;
        } CATCH_END(code);
        END_TRY;
        return 0;
    }

LIST OF EXCEPTIONS

    CEXTEND_EXCEPTION

    CEXTEND_EXCEPTION_LOGIC_ERROR
    CEXTEND_EXCEPTION_INVALID_ARGUMENT
    CEXTEND_EXCEPTION_DOMAIN_ERROR
    CEXTEND_EXCEPTION_LENGTH_ERROR
    CEXTEND_EXCEPTION_OUT_OF_RANGE
    CEXTEND_EXCEPTION_FUTURE_ERROR
    CEXTEND_EXCEPTION_LOGIC_ERROR_MAX

    CEXTEND_EXCEPTION_RUNTIME_ERROR
    CEXTEND_EXCEPTION_RANGE_ERROR
    CEXTEND_EXCEPTION_OVERFLOW_ERROR
    CEXTEND_EXCEPTION_UNDERFLOW_ERROR
    CEXTEND_EXCEPTION_REGEX_ERROR
    CEXTEND_EXCEPTION_SYSTEM_ERROR
    CEXTEND_EXCEPTION_TX_EXCEPTION
    CEXTEND_EXCEPTION_NONEXISTENT_LOCAL_TIME
    CEXTEND_EXCEPTION_AMBIGUOUS_LOCAL_TIME
    CEXTEND_EXCEPTION_FORMAT_ERROR
    CEXTEND_EXCEPTION_RUNTIME_ERROR_MAX

    CEXTEND_EXCEPTION_BAD_TYPE
    CEXTEND_EXCEPTION_BAD_TYPEID
    CEXTEND_EXCEPTION_BAD_CAST

    CEXTEND_EXCEPTION_BAD_FUNCTION_CALL

    CEXTEND_EXCEPTION_BAD_ALLOC
    CEXTEND_EXCEPTION_BAD_ARRAY_NEW_LENGTH
    CEXTEND_EXCEPTION_BAD_ALLOC_MAX

    CEXTEND_EXCEPTION_BAD_EXCEPTION

    CEXTEND_EXCEPTION_MAX

ATTRIBUTES

┌───────────────────────────────────────────────────┬───────────────┬─────────┐
│Interface                                          │ Attribute     │ Value   │
├───────────────────────────────────────────────────┼───────────────┼─────────┤
│INIT_TRY, TRY, CATCH, CATCH_ALL, CATCH_END,        │               │         │
│END_TRY, THROW, should_free_on_abort               │ Thread safety │ MT-Safe │
│                                                   │               │         │
└───────────────────────────────────────────────────┴───────────────┴─────────┘
```

---

## WARNING

Dear Epitech students, this library was developped in accordance with Epitech's C coding-style (as of 2025), as it was used in my own projects. However, using it directly in your projects may result in a grade penalty (e.g., -42). Use it with caution, and do not add it to your repository unless you have explicit approval from your local pedagogical staff.
