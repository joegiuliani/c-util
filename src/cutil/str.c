#include <cutil/str.h>
#include <stdlib.h>
#include <string.h>

void str_init(str* s)
{
	vec_init(s, sizeof(char));
}

size_t str_find(str s, char c, size_t offset)
{
	if (offset >= s.size) exit(1);
	return strchr((char*)s.arr + offset, c);
}

result str_sub(str s, size_t a, size_t b, str* out)
{
	if (a > b || b > s.size - 1) exit(1);
	const size_t size = b - a + 1;
	str_init(out);
	if (vec_set_capacity(out, size) != SUCCESS)
		return FAILURE;
	if (memcpy(out->arr, (char*)s.arr + a, size) == NULL)
		return FAILURE;
}
