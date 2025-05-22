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

### Memory:

```
NAME
    safe_strdup, safe_malloc, safe_valloc, safe_realloc, safe_calloc,
    safe_aligned_alloc, safe_free, retain_smart_ptr, create_smart_ptr,
    dup_smart_ptr, destroy_smart_ptr, release_smart_ptr, resize_smart_ptr,
    free_ptr_list - garbage collected memory allocation

SYNOPSIS
    #include <cextend/memory.h>

    void *safe_strdup(const char *restrict str);

    void *safe_malloc(size_t size, void (*dtor)(void *));

    void *safe_valloc(size_t size, void (*dtor)(void *));

    void *safe_realloc(void *ptr, size_t size, void (*dtor)(void *));

    void *safe_calloc(size_t count, size_t size, void (*dtor)(void *));

    void *safe_aligned_alloc(size_t alignment, size_t size,
        void (*dtor)(void *));

    void safe_free(void **ptr);

    smart_ptr_t *create_smart_ptr(size_t size, void (*dtor)(void *));

    smart_ptr_t *retain_smart_ptr(smart_ptr_t *ptr);

    smart_ptr_t *dup_smart_ptr(smart_ptr_t *ptr);

    void release_smart_ptr(smart_ptr_t **ptr);

    void destroy_smart_ptr(smart_ptr_t **ptr);

    void resize_smart_ptr(smart_ptr_t **ptr, size_t size);

    #include <cextend/exits/memory_exit.h>

    void free_ptr_list(void);

DESCRIPTION
    The safe_strdup function performs a strdup(3) call with the string passed
    as parameter. On success, it returns the newly allocated string. On
    failure, it throws CEXTEND_EXCEPTION_BAD_ALLOC (see <cextend/exception.h>).
    The newly allocated pointer will be freed automatically at the end of the
    execution of the program. If you want to free it manually, use safe_free.

    The safe_malloc function performs a malloc(3) call with the passed
    parameters. The dtor parameter is the function that should be called to
    destroy the pointer. If dtor is NULL, it will default to free(3). On
    success, it returns the newly allocated string. On failure, it throws
    CEXTEND_EXCEPTION_BAD_ALLOC (see <cextend/exception.h>). The newly
    allocated pointer will be freed automatically at the end of the execution
    of the program. If you want to free it manually, use safe_free.

    The safe_valloc function performs a valloc(3) call with the passed
    parameters. The dtor parameter is the function that should be called to
    destroy the pointer. If dtor is NULL, it will default to free(3). On
    success, it returns the newly allocated string. On failure, it throws
    CEXTEND_EXCEPTION_BAD_ALLOC (see <cextend/exception.h>). The newly
    allocated pointer will be freed automatically at the end of the execution
    of the program. If you want to free it manually, use safe_free.

    The safe_realloc function performs a realloc(3) call with the passed
    parameters. The dtor parameter is the function that should be called to
    destroy the pointer. If dtor is NULL, it will default to free(3). On
    success, it returns the newly allocated string. On failure, it throws
    CEXTEND_EXCEPTION_BAD_ALLOC (see <cextend/exception.h>). The newly
    allocated pointer will be freed automatically at the end of the execution
    of the program. If you want to free it manually, use safe_free.

    The safe_calloc function performs a calloc(3) call with the passed
    parameters. The dtor parameter is the function that should be called to
    destroy the pointer. If dtor is NULL, it will default to free(3). On
    success, it returns the newly allocated string. On failure, it throws
    CEXTEND_EXCEPTION_BAD_ALLOC (see <cextend/exception.h>). The newly
    allocated pointer will be freed automatically at the end of the execution
    of the program. If you want to free it manually, use safe_free.

    The safe_aligned_alloc function performs an aligned_alloc(3) call with the
    passed parameters. The dtor parameter is the function that should be called
    to destroy the pointer. If dtor is NULL, it will default to free(3). On
    success, it returns the newly allocated string. On failure, it throws
    CEXTEND_EXCEPTION_BAD_ALLOC (see <cextend/exception.h>). The newly
    allocated pointer will be freed automatically at the end of the execution
    of the program. If you want to free it manually, use safe_free.

    The safe_free function frees the pointer allocated by safe allocations.
    It uses the dtor that was given at the creation of the pointer if it was
    not NULL, otherwise it calls free(3). The pointer is set to NULL after its
    deletion.

    The create_smart_ptr function creates a smart pointer that will be freed
    automatically at the end of the execution of the program. The size
    parameter is the size of the inner pointer, and the dtor parameter is the
    function that will be used to free the inner pointer. The dtor parameter
    defaults to free if it is set to null On success, it returns the newly
    created smart pointer. On failure, it throw CEXTEND_EXCEPTION_BAD_ALLOC.
    In order to free the smart pointer manually, you can eiteher release all
    its references or destroy it.

    The retain_smart_ptr function returns the smart pointer and increase its
    reference count.

    The dup_smart_ptr function returns a newly allocated copy of the smart
    pointer.

    The release_smart_ptr function decreases the smart pointer reference count.
    It also sets the current pointer reference to NULL.

    The destroy_smart_ptr function frees the smart pointer. It also sets the
    current pointer reference to NULL.

    The resize_smart_ptr function calls realloc(3) on the smart pointer inner
    pointer.

    The free_ptr_list function frees all the smart pointers and the pointers
    allocated by safe_allocs. It is recommended to call it in a function with
    __attribute__((destructor)).

EXAMPLE
    #include <cextend/memory.h>
    #include <cextend/memory_exit.h>

    typedef enum {
        CEXTEND_MIN_EXIT = 101,
        CEXTEND_FREE_MEM_EXIT
    } cextend_destructor_priotiries_t;

    __attribute__((destructor(CEXTEND_FREE_MEM_EXIT)))
    void c_extent_free_mem_exit(void)
    {
        free_ptr_list();
    }

    int main(void)
    {
        smart_ptr_t *ptr = create_smart_ptr(5, NULL);
        smart_ptr_t *ptr2 = retain_smart_ptr(ptr);
        smart_ptr_t *ptr3;
        void *ptr4 = safe_malloc(sizeof(int), NULL);

        *ptr4 = 4;
        strcpy(ptr->ptr, "test");
        // Newly allocated pointer
        ptr3 = dup_smart_ptr(ptr);
        strcpy(ptr2->ptr, "abdc");
        release_smart_ptr(&ptr);
        resize_smart_ptr(&ptr2, 7);
        strcpy(ptr2->ptr, "abdcef");
        resize_smart_ptr(&ptr2, 5);
        strcpy(ptr2->ptr, "abdc");
        // ptr2 is freed here.
        release(ptr2);
        // ptr3 and ptr4 will be freed here.
    }
```
---

### Logger:

```
NAME CEXTEND_LOG, CEXTEND_PRT, CEXTEND_INIT_LOG - logger

SYNOPSIS
    #include <cextend/logger.h>

    int CEXTEND_LOG(const cextend_log_type_t type,
        const char *restrict fmt, ...)

    int CEXTEND_PRT(const cextend_log_type_t type,
        const char *restrict fmt, ...)

    #include <cextend/entries/logger_init.h>

    CEXTEND_INIT_LOG

DESCRIPTION
    The CEXTEND_LOG macro takes a type (LOG_INFO, LOG_WARNING, LOG_ERROR), a
    format (see printf(3) for more informations) and optional variadic
    arguments depending on the format. It returns the number of characters
    printed. This macro will only print if DEBUG was defined before the
    inclusion of the <cextend/logger.h> header.

    The CEXTEND_PRT macro takes a type (LOG_INFO, LOG_WARNING, LOG_ERROR), a
    format (see printf(3) for more informations) and optional variadic
    arguments depending on the format. It returns the number of characters
    printed.

    The CEXTEND_INIT_LOG macro initializes the logger. It is recommended to
    call this macro in a function with __attribute__((constructor)).

EXAMPLE
    #include <cextend/logger.h>
    #include <cextend/entries/logger_init.h>

    typedef enum {
        CEXTEND_MIN_ENTRY = 101,
        CEXTEND_INIT_LOG_ENTRY
    } cextend_constructor_priotiries_t;

    __attribute__((constructor(CEXTEND_INIT_LOG_ENTRY)))
    void cextend_init_log_entry(void)
    {
        CEXTEND_INIT_LOG;
    }

    int main(void)
    {
        CEXTEND_LOG(LOG_ERROR, "This will not print!");
        CEXTEND_PRT(LOG_INFO, "But this will [%d]!", 42);
        return 0;
    }

EXAMPLE 2
    #define DEBUG
    #include <cextend/logger.h>
    #include <cextend/entries/logger_init.h>

    typedef enum {
        CEXTEND_MIN_ENTRY = 101,
        CEXTEND_INIT_LOG_ENTRY
    } cextend_constructor_priotiries_t;

    __attribute__((constructor(CEXTEND_INIT_LOG_ENTRY)))
    void cextend_init_log_entry(void)
    {
        CEXTEND_INIT_LOG;
    }

    int main(void)
    {
        CEXTEND_LOG(LOG_ERROR, "This will print!");
        CEXTEND_PRT(LOG_INFO, "This will too [%d]!", 42);
        return 0;
    }

ATTRIBUTES
┌───────────────────────────────────────────────────┬───────────────┬─────────┐
│Interface                                          │ Attribute     │ Value   │
├───────────────────────────────────────────────────┼───────────────┼─────────┤
│CEXTEND_LOG, CEXTEND_PRT, CEXTEND_INIT_LOG         │ Thread safety │ MT-Safe │
└───────────────────────────────────────────────────┴───────────────┴─────────┘
```

---

## WARNING

Dear Epitech students, this library was developped in accordance with Epitech's C coding-style (as of 2025), as it was used in my own projects. However, using it directly in your projects may result in a grade penalty (e.g., -42). Use it with caution, and do not add it to your repository unless you have explicit approval from your local pedagogical staff.
