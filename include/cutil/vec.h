#ifndef CUTIL_VEC_H
#define CUTIL_VEC_H

// -- Todo --
// - Address endianess
// - Figure out design for letting user define a custom capacity expansion func

// -- Note --
// There seems to be an exhaustive use of comments here because I want to be as
// explicit and deterministic about the properties and behavioral guarantees of
// such a fundamental data type.
// 
// For information on c-util memory allocation and the c-util memory allocation
// macro, see <c-util/config/allocation.h>"

// -- Terms --
// vector: a resizable array type, like Java's ArrayList or C++'s std::vector
// with explict memory allocation policies
// size: the number of elements in a vec or array
// capacity: the size of the underyling array
// element size: a vec's element size in bytes
// vec: an instance of the vector type

// -- Includes --
#include <cutil/config/result.h>
#include <stddef.h>

// -- Declarations --

// An invalid vector type, implemented here as (vec)0, expanding to (void*)0,
// to be returned by vec_init()
#define VEC_INVALID ((vec)0)

// -- Declarations / Types --

// Uses the c-util memory allocation macro to allocate memory. The memory
// allocated by a vec has a lifetime ended by calling vec_free() on the vec.
// The following are simultaneously true for a valid vec v and
// an element e of v:
// 1. v was returned by vec_init()
// 2. v has not been not passed to vec_free()
// 3. v != VEC_INVALID
// 4. v's use with the vec namespace/interface causes only defined behavior
// 5. e is in v if &e == vec_array(v)+sizeof(e)*indexof(e) and
//    &e < (int8_t*)vec_array(v)+sizeof(e)*vec_size(v)
// 6. sizeof(e) == vec_elem_size(v)  
// 7. vec_size(v) <= vec_capacity(v)

typedef void* vec;

// -- Declarations / Functions --

// Disclaimer: vec functions do not check the validity of the vec in question

// Returns VEC_INVALID if the function fails.
vec vec_new(size_t init_size, size_t elem_size);

// Frees the memory allocated by the vec
void vec_free(vec);

// Sets the number of elements in the underlying array.
// Returns FAILURE if the new capacity is less than the size or if the
// operation is unsuccessful
result vec_set_capacity(vec, size_t);

// Does not allocate more memory if new size <= current size
result vec_set_size(vec, size_t);

size_t vec_size(vec);

// Returns the number of elements in the vector's underlying array such that
// vec_capacity(v) >= vec_size(v)
size_t vec_capacity(vec);

// Returns the size in bytes of an element
size_t vec_elem_size(vec);

// Returns a pointer to the underlying array
void* vec_array(vec);

// Returns the number of bytes of memory a vec has allocated with the c-util
// memory allocation macro
size_t vec_num_allocd_bytes(vec);

#endif // CUTIL_VEC_H
