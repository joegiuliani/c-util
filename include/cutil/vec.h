#ifndef VEC_H
#define VEC_H

// -- Todo --
//  - Try to figure out how to hide implementation of vec since the user should
// NOT be able to access vec fields.
//  - Add vec_elem_size() and vec_array() functions to remove need for user to
// access fields of vec.
//  - Implement new header scheme, e.g.
// -- Includes --
// #include <result.h>
// -- Includes std --
// #include <stddef.h>
// ...
// -- Declarations Structs --
// -- Declarations Structs vec--
// typedef struct vec_t vec;

// -- Includes --
#include <cutil/config/result.h>
#include <stddef.h>

// -- vec_t Implementation --
// The struct itself is implementation defined and only made visible so that 
// the user can allocate it.
// arr: The pointer to the memory block for the underlying array. Can be NULL.
// size: the number of elements
// capacity: the size of the memory block we allocated, if any, otherwise 0
// elem_size: the size in bytes of a vec element
typedef struct vec_t
{
	void* arr;
	size_t size;
	size_t capacity;
	size_t elem_size;
} vec;

// -- Declarations --

// Initializes a vec for use with the vec interface. elem_size is the size of
// an element in bytes.
void vec_init(vec* v, size_t elem_size);

// Frees the memory used by the vec, setting the arr field to NULL. All other
// members of the vec struct are left unchanged.
void vec_free(vec* v);

// Sets the number of elements in the vec's underlying array.
// Returns FAILURE if the new capacity is less than the vec's size or if the
// operation is unsuccessful
result vec_set_capacity(vec*, size_t);

result vec_set_size(vec* v, size_t new_size);

// Returns a pointer to the first element in the vec, if any
void* vec_begin(vec v);

// Returns a pointer to the end of the vec, immediately past the last element
// so that, in theory, vec_end(v) == &arr[v.size]
void* vec_end(vec v);

size_t vec_size(vec v);

// Returns the number of elements in the vec's underlying array such that
// vec_capacity(v) >= vec_size(v)
size_t vec_capacity(vec v);

// Returns a pointer to the underlying array
void* vec_array(vec v);

#endif // VEC_H
