#include "__string.h"

#if defined _MSC_VER

#ifndef __func__
#define __func__ __FUNCTION__
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#endif

#ifndef _STDARG_H /* va_list */
#include <stdarg.h>
#ifndef _STDARG_H
#define _STDARG_H
#endif
#endif

#include <ctype.h>

#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L \
	&& ! defined __TEMPLATE_ERROR
#define __TEMPLATE_ERROR
#endif

#ifdef __TEMPLATE_ERROR
#define __error__(fmt, ...)	mystring_fatal_error(__FILE__, __func__, __LINE__, fmt, __VA_ARGS__)
#define __error(fmt, ...)	__error__(fmt, __VA_ARGS__)
#else
#define __error		while (0)
#endif

#ifdef __TEMPLATE_ERROR

void
mystring_fatal_error (const char *file, const char *func, size_t line, const char *fmt, ...) {
#ifndef _24K_NOT_PRINT_ERR_MSG
	va_list ap;
	va_start(ap,fmt);
	fprintf(stderr, "_::error> in file `%s`, in function `%s` line %ld: \n\t(*/¦Ø£Ü*): ", file, func, line);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
#endif
#ifndef _24K_NOT_EXIT
	exit(24);
#endif
}

#endif

void
mystring_destroy (mystring *s)
{
	free(s->_data);
	s->_data = NULL;
	s->_size = 0;
	s->_capacity = 0;
}

char
mystring_at (const mystring *s, size_t pos)
{
	if ( pos<0 || pos>=s->_size ) {
		__error("Index out of bound, index=%d, size=%d\n", pos, s->_size);
		return 0;
	}
	return *( s->_data + pos );
}

char
mystring_front (const mystring *s)
{
	if ( ! s->_size )
		__error("read data from a mystring which is empty\n", 0);
	return *s->_data;
}

char
mystring_back (const mystring *s)
{
	if ( ! s->_size )
		__error("read data from a mystring which is empty\n", 0);
	return *(s->_data + s->_size - 1);
}

char*
mystring_data (mystring *s)
{
	return s->_data;
}

const char*
mystring_c_str (const mystring *s)
{
	return s->_data;
}

mystring_iterator
mystring_begin (mystring *s)
{
	return s->_data;
}

mystring_iterator
mystring_end (mystring *s)
{
	return s->_data + s->_size;
}

mystring_iterator
mystring_rbegin (mystring *s)
{
	return s->_data + s->_size - 1;
}

mystring_iterator
mystring_rend (mystring *s)
{
	return s->_data - 1;
}

mystring_iterator
mystring_prev (mystring *s, mystring_iterator it)
{
	if (--it < mystring_rend(s))
		__error("iterator out of bound\n", 0);
	return it;
}

mystring_iterator
mystring_next (mystring *s, mystring_iterator it)
{
	if (++it > mystring_end(s))
		__error("iterator out of bound\n", 0);
	return it;
}

int
mystring_empty (const mystring *s)
{
	if ( s->_size )
 		return 0;
	return 1;
}

size_t
mystring_size (const mystring *s)
{
	return s->_size;
}

mystring*
mystring_reserve (mystring *s, size_t new_cap)
{
	char *p;
	if (new_cap > s->_capacity) {
		p = (char*) realloc (s->_data, (new_cap + 1) * sizeof(char));
		if ( ! p )
			return NULL;
		s->_data = p;
		s->_capacity = new_cap;
	}
	return s;
}

size_t
mystring_capacity (const mystring *s)
{
	return s->_capacity;
}

mystring*
mystring_shrink_to_fit (mystring *s)
{
	if (s->_size < s->_capacity) {
		s->_data = realloc(s->_data, (s->_size + 1) * sizeof(char));
		s->_capacity = s->_size;
	}
	return s;
}

mystring*
mystring_clear (mystring *s)
{
	s->_size = 0;
	mystring_data(s)[0] = 0;
	return s;
}

mystring*
mystring_resize (mystring *s, size_t count)
{
	if (s->_size >= count) {
		s->_size = count;
		*(s->_data + count) = 0;
	} else {
		if ( mystring_reserve(s, count) ) {
			memset(s->_data + s->_size, 0, (count - s->_size) * sizeof(char));
			s->_size = count;
		} else
			return NULL;
	}
	return s;
}

mystring*
mystring_insert (mystring *s, size_t pos, char t)
{
	char *p, *p1;
	if ( pos<0 || pos>s->_size ) {
		__error("Index out of bound, index=%d, size=%d\n", pos, s->_size);
		return NULL;
	}
	if ( s->_size == s->_capacity && ! mystring_reserve(s, s->_capacity * 2U) )
		return NULL;
	p = s->_data + pos;
	p1 = s->_data + s->_size;
	while ( p1 > p )
		*p1 = *(p1-1), --p1;
	*p = t;
	++s->_size;
	*( mystring_data(s) + mystring_size(s) ) = 0;
	return s;
}

mystring*
mystring_erase (mystring *s, size_t pos)
{
	char *p, *p1;
	if (pos<0 || pos>=s->_size) {
		__error("Index out of bound, index=%d, size=%d\n", pos, s->_size);
		return NULL;
	}
	p = s->_data + pos;
	p1 = s->_data + s->_size;
	while ( p < p1 )
		*p = *(p+1), ++p;
	*( mystring_data(s) + --s->_size ) = 0;
	return s;
}

mystring*
mystring_push_back (mystring *s, char t)
{
	return mystring_insert(s, s->size(s), t);
}

mystring*
mystring_pop_back (mystring *s)
{
	return mystring_erase(s, s->size(s)-1);
}

mystring*
mystring_assign (mystring *s, const char *cs)
{
	int c;
	size_t i;
	mystring_clear(s);
	for (i=0; ; ++i) {
		c = cs[i];
		if ( ! c )
			return s;
		if ( ! mystring_push_back(s, c) )
			return NULL;
	}
}

mystring*
mystring_write (mystring *s, FILE *fp)
{
	fwrite(&s->_size, sizeof(size_t), 1, fp);
	fwrite(mystring_data(s), sizeof(char), mystring_size(s), fp);
	return s;
}

mystring*
mystring_read (mystring *s, FILE *fp)
{
	size_t size;
	mystring_init(s);
	fread(&size, sizeof(size_t), 1, fp);
	mystring_reserve(s, size);
	fread(mystring_data(s), sizeof(char), size, fp);
	s->_size = size;
	return s;
}

mystring*
mystring_save (mystring *s, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "w");
	if ( ! fp )
		return NULL;
	mystring_write(s, fp);
	fclose(fp);
	return s;
}

mystring*
mystring_load (mystring *s, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	if ( ! fp )
		return NULL;
	mystring_read(s, fp);
	fclose(fp);
	return s;
}

mystring*
mystring_add (mystring *s, const mystring *s1)
{
	if ( ! s->reserve(s, s->size(s) + s1->size(s1)) )
		return NULL;
	strncpy(s->data(s)+s->size(s), s1->c_str(s1), s1->size(s1));
	s->_size += s1->size(s1);
	*( s->data(s) + s->size(s) ) = 0;
	return s;
}

mystring*
mystring_append (mystring *s, const char *cs)
{
	mystring s1;

	mystring_init(&s1);
	s1.assign(&s1, cs);
	return s->add(s, &s1);
}

int
mystring_compare (const mystring *s, const mystring *s1)
{
	return strcmp(s->c_str(s), s1->c_str(s1));
}

mystring*
mystring_replace (mystring *s, size_t pos, size_t count, const char *cs)
{
	char *p, *p1, *p2;
	size_t len = strlen(cs);

	if ( ! s->reserve( s, s->size(s) + len - count) )
		return NULL;
	if (len < count) {
		p = s->data(s) + s->size(s);
		p1 = s->data(s) + pos + len;
		p2 = s->data(s) + pos + count;
		while (p2 < p)
			*p1 = *p2, ++p1, ++p2;
	} else if (len > count) {
		p = s->data(s) + pos + count;
		p1 = s->data(s) + s->size(s) - 1;
		p2 = s->data(s) + s->size(s) - 1 + len - count;
		while (p1 >= p)
			*p2 = *p1, --p1, --p2;
	}
	strncpy(s->data(s) + pos, cs, len);
	s->_size += len - count;
	*( s->data(s) + s->size(s) ) = 0;
	return s;
}

int
mystring_find (const mystring *s, size_t pos, const char *cs)
{
	char *p;
	p = strstr(s->c_str(s) + pos, cs);
	if ( ! p )
		return -1;
	return p - s->c_str(s);
}

int
mystring_find_first_of (const mystring *s, size_t pos, const char *cs)
{
	char *p;
	p = strpbrk(s->c_str(s) + pos, cs);
	if ( ! p )
		return -1;
	return p - s->c_str(s);
}

int
mystring_find_first_not_of (const mystring *s, size_t pos, const char *cs)
{
	size_t n;
	n = strspn(s->c_str(s) + pos, cs);
	if ( pos + n == s->size(s) )
		return -1;
	return pos + n;
}

mystring*
mystring_reverse(mystring *s)
{
	int c;
	mystring_iterator it, it1;

	it = s->begin(s);
	it1 = s->rbegin(s);

	while (it < it1) {
		c = *it;
		*it = *it1;
		*it1 = c;
		it = s->next(s, it);
		it1 = s->prev(s, it1);
	}
	return s;
}

int
mystring_find_last_of (const mystring *s, size_t pos, const char *cs)
{
	char *p;
	mystring _s1, *s1=&_s1;
	mystring_init(s1) -> assign(s1, s->c_str(s)) -> reverse(s1);

	pos = s1->size(s1) - pos - 1;
	p = strpbrk(s1->c_str(s1) + pos, cs);
	pos = s1->size(s1) - (p - s1->c_str(s1)) - 1;
	s1->destroy(s1);
	if ( ! p )
		return -1;
	return pos;
}

int
mystring_find_last_not_of (const mystring *s, size_t pos, const char *cs)
{
	size_t n;
	mystring _s1, *s1=&_s1;
	mystring_init(s1) -> assign(s1, s->c_str(s)) -> reverse(s1);

	pos = s1->size(s1) - pos - 1;
	n = strspn(s1->c_str(s1) + pos, cs);
	pos += n;
	pos = s1->size(s1) - pos - 1;
	s1->destroy(s1);
	if ( pos == s1->size(s1) )
		return -1;
	return pos;
}

mystring*
mystring_fgetline(mystring *s, FILE *fp, int delim)
{
	int c;
	s->clear(s);
	for (;;) {
		c = fgetc(fp);
		if (c == EOF || c == delim)
			break;
		s->push_back(s, c);
	}
	return s;
}

mystring*
mystring_getline(mystring *s)
{
	return mystring_fgetline(s, stdin, '\n');
}

mystring*
mystring_fgets(mystring *s, FILE *fp)
{
	int c;
	s->clear(s);
	for (;;) {
		c = fgetc(fp);
		if ( ! isspace(c) )
			break;
	}
	if (c == EOF)
		return s;
	ungetc(c, stdin);
	for (;;) {
		c = fgetc(fp);
		if (c == EOF)
			break;
		if ( isspace(c) ) {
			ungetc(c, stdin);
			break;
		}
		s->push_back(s, c);
	}
	return s;
}

mystring*
mystring_gets(mystring *s)
{
	return mystring_fgets(s, stdin);
}

mystring*
mystring_swap(mystring *s1, mystring *s2)
{
	char *p;
	size_t i;

	p = s1->_data;
	s1->_data = s2->_data;
	s2->_data = p;

	i = s1->_size;
	s1->_size = s2 ->_size;
	s2->_size = i;

	i = s1->_capacity;
	s1->_capacity = s2 ->_capacity;
	s2->_capacity = i;
	return s1;
}

mystring*
mystring_split(const mystring *s, size_t pos1, size_t pos2)
{
	size_t i;
	mystring *substr = (mystring*)malloc(sizeof(mystring));

	mystring_init(substr);

	for (i=pos1; i<pos2; ++i)
		substr->push_back(substr, s->at(s, i));

	return substr;
}

mystring*
mystring_init (mystring *s)
{
	s->_data = (char*) malloc ((0x4 + 1) * sizeof(char));
	if ( ! s->_data )
		return NULL;
	*s->_data = 0;
	s->_size = 0;
	s->_capacity = 0x4;

#define _(f)		s->f = mystring##_##f

	s->length = mystring_size;

	_(at);
	_(front);
	_(back);
	_(data);
	_(c_str);
	_(begin);
	_(end);
	_(rbegin);
	_(rend);
	_(prev);
	_(next);
	_(empty);
	_(size);
	_(reserve);
	_(capacity);
	_(shrink_to_fit);
	_(clear);
	_(resize);
	_(insert);
	_(erase);
	_(push_back);
	_(pop_back);
	_(assign);
	_(write);
	_(read);
	_(save);
	_(load);
	_(destroy);
	_(add);
	_(append);
	_(compare);
	_(replace);
	_(find);
	_(find_first_of);
	_(find_first_not_of);
	_(reverse);
	_(find_last_of);
	_(find_last_not_of);
	_(fgetline);
	_(getline);
	_(fgets);
	_(gets);
	_(swap);
	_(split);

#undef _

	return s;
}

#undef __error
#undef __error__

#ifdef __TEMPLATE_ERROR
#undef __TEMPLATE_ERROR
#endif