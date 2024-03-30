
#include <vec.h>
#include <stdio.h>

int main()
{
	vec v;
	vec* vp = &v;

	vec_init(vp, sizeof(char));
	vec_set_size(vp, 1);

	*(char*)v.arr = 'a';

	printf("Front: %c, Size: %zu", *((char*)v.arr), v.size);

	return 0;
}