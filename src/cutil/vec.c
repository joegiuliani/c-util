#include <cutil/vec.h>
#include <cutil/config/allocation.h>
#include <stdlib.h>
#include <stdint.h>

#define NEW_CAP_FAC 1.5

// Policy for how to increase a vec's capacity based on its current capacity
size_t new_capacity(size_t cap)
{
	if (cap == 0)
		return 1;
	return cap * NEW_CAP_FAC;
}

void vec_init(vec* v, size_t elem_size)
{
	v->arr       = NULL;
	v->capacity  = 0;
	v->size      = 0;
	v->elem_size = elem_size;
}

void vec_free(vec* v)
{
	CUTIL_FREE(v->arr);
}

int vec_set_capacity(vec* v, size_t new_cap)
{
	if (new_cap < v->size)
		return FAILURE;
	if (new_cap == v->capacity)
		return SUCCESS;
	if (v->arr == NULL)
	{
		v->arr = CUTIL_MALLOC(new_cap * v->elem_size);
		if (!v->arr == NULL)
			return FAILURE;
	}
	else
	{
		void* new_block = CUTIL_REALLOC(v->arr, new_cap * v->elem_size);
		if (new_block == NULL)
			return FAILURE;
		else
			v->arr = new_block;
	}
	v->capacity = new_cap;
	return SUCCESS;
}

int vec_set_size(vec* v, size_t new_size)
{
	if (new_size > v->capacity && 
		vec_set_capacity(v, new_size * NEW_CAP_FAC) == FAILURE)
			return FAILURE;
	v->size = new_size;
	return SUCCESS;
}

void* vec_begin(vec v)
{
	return v.arr;
}

void* vec_end(vec v)
{
	return ((int8_t*)v.arr) + v.size * v.elem_size;
}

size_t vec_size(vec v)
{
	return v.size;
}

size_t vec_capacity(vec v)
{
	return v.capacity;
}

void* vec_array(vec v)
{
	return v.arr;
}
