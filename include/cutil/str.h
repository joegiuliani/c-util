#ifndef CUTIL_STR_H
#define CUTIL_STR_H

// -- Includes --
#include <cutil/vec.h>
#include <stdint.h>

// -- Declarations --

#define STR_NPOS SIZE_MAX

// -- Declarations Types --

// str is a char vec
typedef vec str;

// -- Declarations Functions --

// Initializes a str for use with the str interface.
void str_init(str* s);

// Returns the index of the first occurrence of c in s at or past index offset
// or STR_NPOS if none was found
size_t str_find(str s, char c, size_t offset);

// Initializes the specified substring from a to min(b-1,s.size-1) and places
// it in out
result str_sub(str s, size_t a, size_t b, str* out);

size_t str_len(str s);

// The lifetime of the returned string is managed by the owner of of the passed
// str
const char* str_cstr(str s);

result str_adds(str* s, str x);

#endif // CUTIL_STR_H