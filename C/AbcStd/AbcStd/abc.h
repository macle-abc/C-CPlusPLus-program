#ifndef ABCSTD_ABC_H_
#define ABCSTD_ABC_H_

#include "error.h"
#include <stdbool.h>
#include <stdio.h>

#ifndef PRINTERROR
#define PRINTERROR
#define PrintError(warning) do {\
	fprintf(stderr, "flie:%s line:%u in %s function:%s\n", __FILE__, __LINE__, __FUNCTION__, warning); \
	} while(0)
#endif

typedef struct
{
	struct algorithm
	{
		void (*(*for_each)(void* hFirst, void* hLast, void*(*pNext)(const void* p_hCurrent), void(*pF)(const void* a)))(const void* a);

		void* (*find_if)(void* hFirst, void* hLast, void*(*pNext)(const void* p_hCurrent), bool (*pF)(const void* a));

		void* (*remove_if)(void* hFirst, void* hLast, unsigned uSize, void*(*pNext)(const void* p_hCurrent), bool (*pF)(const void* a));

		void  (*replace_if)(void* hFirst, void* hLast, unsigned uSize, void*(*pNext)(const void* p_hCurrent), bool (*pF)(const void* a), const void* c_pNewValue);

		void (*swap)(void* hA, void* hB, unsigned uSize);
	}m_algorithm;

}abcNamespace;

extern abcNamespace* Get_ABC_NameSpace();
extern void Delete_ABC_NameSpace();
#endif
