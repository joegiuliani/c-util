#ifndef ALLOCATION_H
#define ALLOCATION_H

// -- Purpose --
// The user may bind their own functions to any of the c-lib memory allocation
// macros for customization. 

// -- Instructions --
// Bind functions before including this
// header, but note that any c-lib header may also include this header, so 
// it would be good practice to bind custom functions before including any
// c-lib header

// -- Constraints --
// Any function bound by the user must match the signature of the default c-lib
// function. e.g. If binding foo() to C_LIB_MALLOC, then foo must be
// void* foo(size_t).

// Any function bound by the user must match the return policy of the default
// c-lib function. e.g. If binding foo() to C_LIB_MALLOC, then foo() must return
// a pointer to the block allocated, or NULL if unsuccessful.

// -- Includes --

#include <stdlib.h>

// -- Definitions --

// c-lib memory allocation macros

#ifndef C_LIB_MALLOC
#define C_LIB_MALLOC malloc
#endif

#ifndef C_LIB_REALLOC
#define C_LIB_REALLOC realloc
#endif

#ifndef C_LIB_FREE
#define C_LIB_FREE free
#endif

#endif ALLOCATION_H