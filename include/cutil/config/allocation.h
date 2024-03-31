#ifndef CUTIL_CONFIG_ALLOCATION_H
#define CUTIL_CONFIG_ALLOCATION_H

// -- Purpose --
// The user may bind their own functions to any of the c-util memory allocation
// macros for customization. 

// -- Instructions --
// Bind functions before including this
// header, but note that any c-util header may also include this header, so 
// it would be good practice to bind custom functions before including any
// c-util header

// -- Constraints --
// Any function bound by the user must match the signature of the default c-lib
// function. e.g. If binding foo() to CUTIL_MALLOC, then foo must be
// void* foo(size_t).

// Any function bound by the user must match the return policy of the default
// c-util function. e.g. If binding foo() to CUTIL_MALLOC, then foo() must return
// a pointer to the block allocated, or NULL if unsuccessful.

// -- Includes --

#include <stdlib.h>

// -- Definitions --

// c-util memory allocation macros

#ifndef CUTIL_MALLOC
#define CUTIL_MALLOC malloc
#endif

#ifndef CUTIL_REALLOC
#define CUTIL_REALLOC realloc
#endif

#ifndef CUTIL_FREE
#define CUTIL_FREE free
#endif

#endif // CUTIL_CONFIG_ALLOCATION_H