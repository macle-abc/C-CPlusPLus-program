#include "Equipment.h"
#define type Equipment*
#include "array.h"
#define type Equipment*
static int array_reserve(array*, int new_cap); // À©ÈÝÊý×é

array
new_array(int n, ...)
{
	array a;

	va_list ap;

	a.data = (type*)malloc(10 * sizeof(type));
	a.length = 0;
	a.capacity = 10;

	if (n > 0) {
		va_start(ap, n);
		array_insert_many(&a, 0, n, va_arg(ap, type*));
		va_end(ap);
	}

	return a;
}

void
delete_array(array* arr)
{
	free(arr->data);
	arr->data = NULL;
	arr->length = 0;
	arr->capacity = 0;
}

int
array_reserve(array* arr, int new_cap)
{
	type* p;
	if (new_cap > arr->capacity) {
		p = (type*)realloc(arr->data, new_cap * sizeof(type));
		if (!p)
			return 0;
		arr->data = p;
		arr->capacity = new_cap;
	}
	return 1;
}

int
array_set_length(array* arr, int new_length)
{
	if (new_length < 0)
		return 0;
	if (new_length > arr->length) {
		if (array_reserve(arr, new_length))
			memset(arr->data + arr->length, 0, (new_length - arr->length) * sizeof(type));
		else
			return 0;
	}
	arr->length = new_length;
	return 1;
}

int
array_insert(array* arr, int index, type const t)
{
	type* p;
	if (index < 0 || index > arr->length)
		return 0;
	if (arr->length == arr->capacity && !array_reserve(arr, arr->capacity << 1))
		return 0;
	p = arr->data + index;
	memmove(p + 1, p, (arr->length - index) * sizeof(type));
	*p = t;
	++arr->length;
	return 1;
}

int
array_insert_many(array* arr, int index, int n, type* ta)
{
	int i;
	int new_length = arr->length + n;
	type* p;

	if (index < 0 || index > arr->length || n < 0)
		return 0;
	if (new_length > arr->capacity && !array_reserve(arr, new_length))
		return 0;
	p = arr->data + index;
	memmove(p + n, p, (arr->length - index) * sizeof(type));
	for (i = 0; i < n; ++i)
		p[i] = ta[i];
	arr->length += n;
	return 1;
}

int
array_remove(array* arr, int index)
{
	return array_remove_many(arr, index, 1);
}

int
array_remove_many(array* arr, int index, int n)
{
	type* p;
	if (index < 0 || index >= arr->length || n < 1)
		return 0;
	if (index + n > arr->length)
		n = arr->length - index;
	p = arr->data + index;
	arr->length -= n;
	memmove(p, p + n, (arr->length - index) * sizeof(type));
	return 1;
}

int
array_add(array* arr, type const t)
{
	return array_insert(arr, arr->length, t);
}

void
array_clear(array* arr)
{
	array_set_length(arr, 0);
}

void
array_sort(array* arr, int (*cmp)(const type*, const type*))
{
	qsort(arr->data, arr->length, sizeof(type), (int (*)(const void*, const void*))cmp);
}
