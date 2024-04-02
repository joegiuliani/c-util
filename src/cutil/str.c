#include <cutil/str.h>
#include <stdlib.h>
#include <string.h>

void add_null_termination(str s)
{
	((char*)vec_array(s))[str_len(s)] = '\0';
}

str str_init(size_t init_size)
{
	vec v = vec_init(init_size, sizeof(char));
	// If the compiler does not optimize this away when
	// VEC_INVALID == STR_INVALID then I will scream
	if (v == VEC_INVALID) return STR_INVALID;
	return v;
}

size_t str_find(str s, char c, size_t offset)
{
	if (offset >= str_len(s) - 1) return STR_NPOS;
	return strchr(str_cstr(s) + offset, c);
}

result str_sub(str s, size_t a, size_t b, str out)
{
	if (a > b) return FAILURE;
	const size_t sub_size = min(b, str_len(s)) - a;
	if (vec_set_size(out, sub_size+1) != SUCCESS)
		return FAILURE;
	if (memcpy(str_cstr(out), str_cstr(s) + a, sub_size) == NULL)
		return FAILURE;
	add_null_termination(out);
	return SUCCESS;
}

size_t str_len(str s)
{
	return vec_size(s) - 1;
}

const char* str_cstr(str s)
{
	return vec_array(s);
}

result str_adds(str s, str x)
{
	const size_t copy_offset = str_len(s);
	if (vec_set_size(s, str_len(s) + str_len(x) + 1) != SUCCESS)
		return FAILURE;
	if (memcpy(str_cstr(s) + copy_offset, str_cstr(x), str_len(x)) == NULL)
		return FAILURE;
	add_null_termination(s);
	return SUCCESS;
}

result str_combine(str a, str b, str out)
{
	if (a == out) return str_adds(a, b);
	if (b == out) return str_adds(b, a);
	if (vec_set_size(out, str_len(a) + str_len(b) + 1) != SUCCESS)
		return FAILURE;
	if (memcpy(str_cstr(out), str_cstr(a), str_len(a)) == NULL)
		return FAILURE;
	if (memcpy(str_cstr(out) + str_len(a), str_cstr(b), str_len(b)) == NULL)
		return FAILURE;
	add_null_termination(out);
	return SUCCESS;
}
