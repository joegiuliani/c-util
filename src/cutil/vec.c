#include <cutil/vec.h>
#include <cutil/config/allocation.h>
#include <stdlib.h>
#include <stdint.h>

// -- Definitions -- 

#define NEW_CAP_FAC  1.5
#define HEADER_SIZE  (sizeof(size_t)*3) 
#define DATA_SIZE(v) (*((int8_t*)(v) + sizeof(size_t)*0))
#define CAPACITY(v)  (*((int8_t*)(v) + sizeof(size_t)*1))
#define ELEM_SIZE(v) (*((int8_t*)(v) + sizeof(size_t)*2))
#define DATA(v)      (*((int8_t*)(v) + sizeof(size_t)*3))
#define HEAP_SIZE(v) (HEADER_SIZE + DATA_SIZE(v))

// Policy for how to increase a vec's capacity based on its current capacity
size_t new_capacity(size_t cap)
{
	if (cap == 0)
		return 1;
	return cap * NEW_CAP_FAC;
}

// -- Definitions / Functions / vec --

vec vec_new(size_t init_size, size_t elem_size)
{
	vec v = (vec)malloc(HEADER_SIZE + init_size * elem_size);
	if (v == NULL) return VEC_INVALID;
	DATA_SIZE(v) = init_size;
	CAPACITY(v) = init_size;
	ELEM_SIZE(v) = elem_size;
	return v;
}

void vec_free(vec v)
{
	CUTIL_FREE(v);
}

int vec_set_capacity(vec v, size_t new_cap)
{
	if (new_cap < DATA_SIZE(v))
		return FAILURE;
	if (new_cap == CAPACITY(v))
		return SUCCESS;
	void* new_block = CUTIL_REALLOC(v, HEADER_SIZE + new_cap * ELEM_SIZE(v));
	if (new_block == NULL)
		return FAILURE;
	CAPACITY(v) = new_cap;
	return SUCCESS;
}

int vec_set_size(vec v, size_t new_size)
{
	if (new_size > CAPACITY(v) && 
		vec_set_capacity(v, new_size * NEW_CAP_FAC) == FAILURE)
			return FAILURE;
	DATA_SIZE(v) = new_size;
	return SUCCESS;
}

void* vec_begin(vec v)
{
	return DATA(v);
}

void* vec_end(vec v)
{
	return ((int8_t*)DATA(v)) + DATA_SIZE(v) * ELEM_SIZE(v);
}

size_t vec_size(vec v)
{
	return DATA_SIZE(v);
}

size_t vec_capacity(vec v)
{
	return CAPACITY(v);
}

size_t vec_elem_size(vec v)
{
	return ELEM_SIZE(v);
}

void* vec_array(vec v)
{
	return DATA(v);
}
