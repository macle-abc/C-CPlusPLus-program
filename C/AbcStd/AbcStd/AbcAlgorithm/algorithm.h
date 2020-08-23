#ifndef ABCSTD_ABCALGORITHM_ALGORITHM_H_
#define ABCSTD_ABCALGORITHM_ALGORITHM_H_

#include "../abc.h"

extern void _Algorithm_Init_(abcNamespace* abc_namespace);

extern void (* _Algorithm_ForEach_(void* hFirst, void* hLast, void*(*pNext)(const void* p_hCurrent), void(*pF)(const void* a)))(const void* a);

extern void* _Algorithm_FindIf_(void* hFirst, void* hLast, void*(*pNext)(const void* p_hCurrent), bool (*pF)(const void* a));

extern void* _Algorithm_RemoveIf_(void* hFirst, void* hLast, unsigned uSize, void*(*pNext)(const void* p_hCurrent), bool (*pF)(const void* a));

extern void _Algorithm_ReplaceIf_(void* hFirst, void* hLast, unsigned uSize, void*(*pNext)(const void* p_hCurrent), bool (*pF)(const void* a), const void* c_pNewValue);

extern void _Algorithm_Swap_(void* hA, void* hB, unsigned uSize);

#endif
