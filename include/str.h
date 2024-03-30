#ifndef STR_H
#define STR_H

// -- Includes --
#include <vec.h>
#include <stdint.h>

// -- Declarations --

#define STR_NPOS SIZE_MAX

// str is a char vec
typedef vec str;

// Initializes a str for use with the str interface.
void str_init(str* s);

// Returns the index of the first occurrence of c in s at or past index offset
// or STR_NPOS if none was found
size_t str_find(str s, char c, size_t offset);

// Creates a new string of s's elements a to b inclusive and puts it in out.
result str_sub(str s, size_t a, size_t b, str* out);

#endif // STR_H