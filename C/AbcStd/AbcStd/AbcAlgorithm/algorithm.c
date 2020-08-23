#include "algorithm.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void (*_Algorithm_ForEach_(void* hFirst, void* hLast, void*(*pNext)(const void* p_hCurrent), void(*pF)(const void* a)))(const void*a)
{
	if (NULL == pNext || NULL == pF)
	{
		PrintError("函数指针不应为空!非法!");
		return (void (*)(const void*a))INVALID_ARGUMENT;
	}
	for (void* index = hFirst; index != hLast; )
	{
		pF(index);
		index = pNext(index);
	}
	return pF;
}

void* _Algorithm_FindIf_(void* hFirst, void* hLast, void*(*pNext)(const void* p_hCurrent), bool (*pF)(const void* a))
{
	if (NULL == pNext || NULL == pF)
	{
		PrintError("函数指针不应为空!非法!");
		return (void*)INVALID_ARGUMENT;
	}
	for (void* index = hFirst; index != hLast; index = pNext(index))

	{
		if (pF(index))
		{
			return index;
		}
	}
	return hLast;
}

void* _Algorithm_RemoveIf_(void* hFirst, void* hLast, unsigned uSize, void*(*pNext)(const void* p_hCurrent), bool (*pF)(const void* a))
{
	if (NULL == pNext || NULL == pF)
	{
		PrintError("函数指针不应为空!非法!");
		return (void*)INVALID_ARGUMENT;
	}
	hFirst = _Algorithm_FindIf_(hFirst, hLast, pNext, pF);
	if (hFirst != hLast)
	{
		for (void* index = hFirst; index != hLast; index = pNext(index))
		{
			if (!pF(index))
			{
				memcpy(hFirst, index, uSize);
				hFirst = pNext(hFirst);
			}
		}
	}
	return hFirst;
}

void _Algorithm_ReplaceIf_(void* hFirst, void* hLast, unsigned uSize, void*(*pNext)(const void* p_hCurrent), bool (*pF)(const void* a), const void* c_pNewValue)
{
	if (NULL == pNext || NULL == pF)
	{
		PrintError("函数指针不应为空!非法!");
		return;
	}
	for (; hFirst != hLast; hFirst = pNext(hFirst))	
	{
		if (pF(hFirst))
		{
			memcpy(hFirst, c_pNewValue, uSize);
		}
	}
}

void _Algorithm_Swap_(void* hA, void* hB, unsigned uSize)
{
	void* hT = malloc(uSize);
	if (NULL == hT)
	{
		PrintError("内存不足!分配失败!");
		return;
	}
	memcpy(hT, hA, uSize);
	memcpy(hA, hB, uSize);
	memcpy(hB, hT, uSize);
	free(hT);
	hT = NULL;
}
void _Algorithm_Init_(abcNamespace* abc_namespace)
{
	if (NULL == abc_namespace)
	{
		PrintError("参数为空!非法!");
		return;
	}
	abc_namespace->m_algorithm.for_each = _Algorithm_ForEach_;
	abc_namespace->m_algorithm.find_if = _Algorithm_FindIf_;
	abc_namespace->m_algorithm.remove_if = _Algorithm_RemoveIf_;
	abc_namespace->m_algorithm.replace_if = _Algorithm_ReplaceIf_;
	abc_namespace->m_algorithm.swap = _Algorithm_Swap_;
}

