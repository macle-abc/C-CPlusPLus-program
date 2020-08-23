#ifndef type
#error: no define "type", need [#define type ...] before [#include "array.h"]
#else

#include <stdio.h> // FILE, fwrite, fread
#include <stdlib.h> // malloc, free, qsort
#include <string.h> // memset
#include <stdarg.h> // va_list

typedef struct s{
	type* data;
	int length;
	int capacity;
}array;

array new_array(int n, ...); // 初始化数组, 并设置n个元素
int array_add(array* arr,type const t); // 增加一个元素到数组末尾
// a.length 数组长度
// a.data[i] 访问或设置元素
int array_insert(array* arr, int index, type const t); // 在index处插入一个元素t
int array_insert_many(array* arr, int index, int n, type* ta); // 插入多个元素
int array_remove(array*, int index); // 删除index处元素
int array_remove_many(array*, int index, int n); // 删除index处开始的n个元素
int array_set_length(array*, int new_length); // 设置数组长度
void array_clear(array*); // 删除数组内所有元素
void delete_array(array*); // 释放数组内存
void array_sort(array*, int (*cmp)(const type*, const type*)); // 根据cmp给数组排序



#undef type

#endif