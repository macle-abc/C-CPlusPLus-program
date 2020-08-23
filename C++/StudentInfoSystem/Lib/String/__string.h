#ifndef _24K_STRING
#define _24K_STRING

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

typedef char* mystring_iterator;

typedef struct mystring {
	char* _data;
	size_t _size;
	size_t _capacity;

	char (*at)(const struct mystring*, size_t);
	char (*front)(const struct mystring*);
	char (*back)(const struct mystring*);
	char* (*data)(struct mystring*);
	const char* (*c_str)(const struct mystring*);

	mystring_iterator(*begin)(struct mystring*);
	mystring_iterator(*end)(struct mystring*);
	mystring_iterator(*rbegin)(struct mystring*);
	mystring_iterator(*rend)(struct mystring*);
	mystring_iterator(*prev)(struct mystring*, mystring_iterator);
	mystring_iterator(*next)(struct mystring*, mystring_iterator);

	int (*empty)(const struct mystring*);
	size_t(*size)(const struct mystring*);
	size_t(*length)(const struct mystring*);
	struct mystring* (*reserve)(struct mystring*, size_t);
	size_t(*capacity)(const struct mystring*);
	struct mystring* (*shrink_to_fit)(struct mystring*);
	struct mystring* (*clear)(struct mystring*);
	struct mystring* (*resize)(struct mystring*, size_t);

	struct mystring* (*insert)(struct mystring*, size_t, char);
	struct mystring* (*erase)(struct mystring*, size_t);
	struct mystring* (*push_back)(struct mystring*, char);
	struct mystring* (*pop_back)(struct mystring*);
	struct mystring* (*assign)(struct mystring*, const char*);

	struct mystring* (*write)(struct mystring*, FILE*);
	struct mystring* (*read)(struct mystring*, FILE*);
	struct mystring* (*save)(struct mystring*, const char*);
	struct mystring* (*load)(struct mystring*, const char*);

	void (*destroy)(struct mystring*);

	struct mystring* (*add)(struct mystring*, const struct mystring*);
	struct mystring* (*append)(struct mystring*, const char*);
	int (*compare)(const struct mystring*, const struct mystring*);
	struct mystring* (*replace)(struct mystring*, size_t, size_t, const char*);

	int (*find)(const struct mystring*, size_t, const char*);
	int (*find_first_of)(const struct mystring*, size_t, const char*);
	int (*find_first_not_of)(const struct mystring*, size_t, const char*);
	struct mystring* (*reverse)(struct mystring*);
	int (*find_last_of)(const struct mystring*, size_t, const char*);
	int (*find_last_not_of)(const struct mystring*, size_t, const char*);

	struct mystring* (*fgetline)(struct mystring*, FILE*, int);
	struct mystring* (*getline)(struct mystring*);
	struct mystring* (*fgets)(struct mystring*, FILE*);
	struct mystring* (*gets)(struct mystring*);

	struct mystring* (*swap)(struct mystring*, struct mystring*);
	struct mystring* (*split)(const struct mystring*, size_t, size_t);

}mystring;

/* s->function(s, ...); */

char mystring_at(const mystring* s, size_t pos);
/* 返回 s 的第pos个字符,  pos>=0  */

char mystring_front(const mystring* s);
/* 返回 s 的第一个字符 */

char mystring_back(const mystring* s);
/* 返回 s 的最后一个字符 */

char* mystring_data(mystring* s);
/* 返回 s 的字符串地址 */

const char* mystring_c_str(const mystring* s);
/* 返回 s 的字符串地址, 不可修改, 建议在输出时使用 */

int mystring_empty(const mystring* s);
/* 判断 s 是否为空字符串 */

size_t mystring_size(const mystring* s);
size_t mystring_length(const mystring* s);
/* 返回 s 的长度, 2个函数一样 */

mystring* mystring_reserve(mystring* s, size_t new_cap);
/* 确保 s 有new_cap个字符的空间, 避免mystring增长时多次realloc */

size_t mystring_capacity(const mystring* s);
/* 返回 s 的内存大小 */

mystring* mystring_shrink_to_fit(mystring* s);
/* 使 s 的内存大小适应它的长度, 释放多余的内存 */

mystring* mystring_clear(mystring* s);
/* 清空字符串内容, s长度变为0 */

mystring* mystring_resize(mystring* s, size_t count);
/* 强行调整s的长度 */

mystring* mystring_insert(mystring* s, size_t pos, char c);
/* 在pos位置插入字符c */

mystring* mystring_erase(mystring* s, size_t pos);
/* 删除pos位置的字符 */

mystring* mystring_push_back(mystring* s, char c);
/* 在s的末尾追加字符c */

mystring* mystring_pop_back(mystring* s);
/* 删除s的最后一个字符 */

mystring* mystring_assign(mystring* s, const char* cs);
/* 清空字符串s内容, 把字符串cs赋值给s */

mystring* mystring_add(mystring* s, const mystring* s1);
/* 把mystring s1追加到s末尾 */

mystring* mystring_append(mystring* s, const char* cs);
/* 把字符串cs追加到s末尾 */

int mystring_compare(const mystring* s, const mystring* s1);
/* 比较s, s1大小  返回 s - s1 */

mystring* mystring_replace(mystring* s, size_t pos, size_t count, const char* cs);
/* 把s的pos位置开始的count个字符替换为cs字符串 */

int mystring_find(const mystring* s, size_t pos, const char* cs);
/* 从s的pos位置开始查找cs字符串 */

int mystring_find_first_of(const mystring* s, size_t pos, const char* cs);
/* 从s的pos位置开始查找 包含在 cs字符串 中的字符, 返回其下标, 没找到返回-1 */

int mystring_find_first_not_of(const mystring* s, size_t pos, const char* cs);
/* 从s的pos位置开始查找 不在 cs字符串 中的字符, 返回其下标, 没找到返回-1 */

int mystring_find_last_of(const mystring* s, size_t pos, const char* cs);
/* 从s的pos位置开始[向前]查找 包含在 cs字符串 中的字符, 返回其下标, 没找到返回-1 */

int mystring_find_last_not_of(const mystring* s, size_t pos, const char* cs);
/* 从s的pos位置开始[向前]查找 不在 cs字符串 中的字符, 返回其下标, 没找到返回-1 */

mystring* mystring_reverse(mystring* s);
/* 将字符串内容倒置 */

mystring* mystring_fgetline(mystring* s, FILE* fp, int delim);
/* 从文件fp读取字符到s, 自动扩展s内存, 直到遇到字符delim, 读取并抛弃字符delim */

mystring* mystring_getline(mystring* s);
/* 读取一行, 相当于 fgetline(s, stdin, '\n'); */

mystring* mystring_fgets(mystring* s, FILE* fp);
/* 从文件读取字符串 相当于 fscanf fp,%s  忽略前后空白字符 */

mystring* mystring_gets(mystring* s);
/* 相当于 fgets(s, stdin); */

mystring* mystring_init(mystring* s);
/* 初始化mystring s */

void mystring_destroy(mystring* s);
/* 释放s申请的内存, s将被置于 未初始化 状态 */

mystring* mystring_swap(mystring* s1, mystring* s2);
/* 交换字符串s1与s2的内容 */

mystring* (*split)(const mystring* s, size_t pos1, size_t pos2);
/* 返回字符串 s 的 [pos1, pos2) 的 子字符串, 不改变原字符串 */

#endif