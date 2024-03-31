#include <cutil/str.h>
#include <stdlib.h>
#include <string.h>

void add_null_termination(str* s)
{
	((char*)vec_array(*s))[str_len(*s)] = '\0';
}

void str_init(str* s)
{
	vec_init(s, sizeof(char));
}

size_t str_find(str s, char c, size_t offset)
{
	if (offset >= s.size - 1) return STR_NPOS;
	return strchr((char*)s.arr + offset, c);
}

result str_sub(str s, size_t a, size_t b, str* out)
{
	if (a > b) return FAILURE;
	const size_t sub_size = min(b, str_len(s)) - a;
	str_init(out);
	if (vec_set_size(out, sub_size+1) != SUCCESS)
		return FAILURE;
	add_null_termination(out);
	if (memcpy(str_cstr(*out), str_cstr(s) + a, sub_size) == NULL)
		return FAILURE;
	return SUCCESS;
}

size_t str_len(str s)
{
	return vec_size(s) - 1;
}

const char* str_cstr(str s)
{
	return s.arr;
}

result str_adds(str* s, str x)
{
	const size_t copy_offset = str_len(*s);
	if (vec_set_size(s, str_len(*s) + str_len(x) + 1) != SUCCESS)
		return FAILURE;
	add_null_termination(s);
	if (memcpy(str_cstr(*s) + copy_offset, str_cstr(x), str_len(x)) == NULL)
		return FAILURE;
	return SUCCESS;
}
