#include "list.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//静态函数声明区域
static type_list* Name(_Init__)();

static type_const_reference Name(_Cdata__) (type_const_iterator c_pCurrent);
static type_reference Name(_Data__) (type_iterator pCurrent);
static type_iterator Name(_Next__) (type_const_iterator c_pCurrent);
static type_iterator Name(_Prev__) (type_const_iterator c_pCurrent);

static void Name(_ConstructD) ();
static void Name(_ConstructCv) (size_type uCount, type_const_reference c_pValue);
static void Name(_ConstructC) (size_type uCount);
static void Name(_ConstructFl) (type_const_iterator c_pFirst, type_const_iterator c_pLast);
static void Name(_ConstructO) (const type_list* c_pOther);

static void Name(_Destructor__) ();

static void Name(_Assign__) (const char* c_pFormate, ...);
static void Name(_AssignCv) (size_type uCount, type_const_reference c_pValue);
static void Name(_AssignFl) (type_const_iterator c_pFirst, type_const_iterator c_pLast);

static type_reference Name(_Front__) ();
static type_reference Name(_Back__) ();

static type_iterator Name(_Begin__) ();
static type_const_iterator Name(_Cbegin__) ();
static type_iterator Name(_End__) ();
static type_const_iterator Name(_Cend__) ();

static bool Name(_Empty__) ();
static size_type Name(_Size__) ();

static void Name(_Clear__) ();

static type_iterator Name(_Insert__) (const char* c_pFormate, ...);
static type_iterator Name(_InsertPv) (type_const_iterator c_pPos, type_const_reference c_pValue);
static type_iterator Name(_InsertPcv) (type_const_iterator c_pPos, size_type uCount, type_const_reference c_pValue);
static type_iterator Name(_InsertPfl) (type_const_iterator c_pPos, type_const_iterator c_pFirst, type_const_iterator c_pLast);

static type_iterator Name(_Emplace__) (type_const_iterator c_pPos);
static void Name(_EmplaceBack__) ();
static void Name(_EmplaceFront__) ();

static type_iterator Name(_Erase__) (const char* c_pFormate, ...);
static type_iterator Name(_EraseP) (type_const_iterator c_pPos);
static type_iterator Name(_EraseFl) (type_const_iterator c_pFirst, type_const_iterator c_pLast);

static void Name(_PushBack__) (type_const_reference c_pValue);
static void Name(_PopBack__) ();
static void Name(_PushFront__) (type_const_reference c_pValue);
static void Name(_PopFront__) ();

static void Name(_Resize__) (const char* c_pFormate, ...);
static void Name(_ResizeC) (size_type uCount);
static void Name(_ResizeCv) (size_type uCount, type_const_reference c_pValue);

static void Name(_Swap__) (type_list* pOther);
static void Name(_Merge__) (type_list* pOther, bool (*pCompare)(type_const_reference c_pA, type_const_reference c_pB));

static void Name(_Splice__) (const char* c_pFormate, ...);
static void Name(_SplicePo) (type_const_iterator c_pPos, type_list* pOther);
static void Name(_SplicePoi) (type_const_iterator c_pPos, type_list* pOther, type_const_iterator c_pIt);
static void Name(_SplicePofl) (type_const_iterator c_pPos, type_list* pOther, type_const_iterator c_pFirst, type_const_iterator c_pLast);

static size_type Name(_Remove__) (type_const_reference c_pValue, bool (*pEqual)(type_const_reference c_pA, type_const_reference c_pB));
static size_type Name(_RemoveIf__) (bool (*pCondition) (type_const_reference c_pValue));
static void Name(_Reverse__) ();
static size_type Name(_Unique__) (bool (*pEqual)(type_const_reference c_pA, type_const_reference c_pB));
static void Name(_Sort__) (bool (*pCompare)(type_const_reference c_pA, type_const_reference c_pB));
static void Name(_ForEach__)(void (*pPrint)(type_const_reference c_pValue));

static type_list* Name(_g_s_this) = NULL;
static void (*Name(_s_pElemConstructor))(type_reference pData) = NULL;
static void (*Name(_s_pElemConstructorCp))(type_reference pData, type_const_reference c_pOther) = NULL;
static void (*Name(_s_pElemDestructor))(type_reference pData) = NULL;

//用户接口
inline void Name(_Rebind) (type_list* const pRebindList)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == pRebindList)
	{
		PrintError("绑定参数为空!非法!");
		return;
	}
#endif
	Name(_g_s_this) = pRebindList;
}

inline void Name(_SetElemConstructor) (void (*pConstructor)(type_reference pData))
{
	Name(_s_pElemConstructor) = pConstructor;
}

inline void Name(_SetElemConstructorCp) (void (*pConstructorCp)(type_reference pData, type_const_reference c_pOther))
{
	Name(_s_pElemConstructorCp) = pConstructorCp;
}

inline void Name(_SetElemDestructor) (void (*pDestructor)(type_reference pData))
{
	Name(_s_pElemDestructor) = pDestructor;
}

type_list* Name(_ListConstructor)(const char* c_pFormate, ...)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pFormate)
	{
		PrintError("参数为空!非法!");
		return (type_list*)INVALID_ARGUMENT;
	}
#endif
	type_list* list = Name(_Init__)();
	list->m_pElemConstructor = Name(_s_pElemConstructor);
	list->m_pElemConstructorCp = Name(_s_pElemConstructorCp);
	list->m_pElemDestructor = Name(_s_pElemDestructor);
	va_list vl;
	va_start(vl, c_pFormate);
	if (strcmp(c_pFormate, "d") == 0)		
	{
		Name(_ConstructD)();
	}
	else if (strcmp(c_pFormate, "cv") == 0)
	{
		size_type uCount = va_arg(vl, size_type);
		type_const_reference c_pValue = va_arg(vl, type_const_reference);
		Name(_ConstructCv)(uCount, c_pValue);
	}
	else if (strcmp(c_pFormate, "c") == 0)
	{
		size_type uCount = va_arg(vl, size_type);
		Name(_ConstructC)(uCount);
	}
	else if (strcmp(c_pFormate, "fl") == 0)
	{	
		type_const_iterator c_pFirst = va_arg(vl,type_const_iterator);
		type_const_iterator c_pLast = va_arg(vl, type_const_iterator);
		Name(_ConstructFl)(c_pFirst, c_pLast);
	}
	else if (strcmp(c_pFormate, "o") == 0)
	{
		const type_list* other = va_arg(vl, const type_list*);
		Name(_ConstructO)(other);
	}
	else 
	{
		PrintError("不存在这样的构造函数!非法!");
		va_end(vl);
		free(list);
		list = NULL;
		Name(_g_s_this) = NULL;
		return (type_list*)INVALID_ARGUMENT;
	}
	va_end(vl);
	return list;
}

//静态函数实现区域
type_list* Name(_Init__) ()
{
	type_list* list = (type_list*)malloc(sizeof(type_list));	
	if (NULL == list)
	{
		PrintError("内存不足!分配失败!");
		return (type_list*)BAD_ALLOC;
	}
	memset(list, 0, sizeof(type_list));
	list->destructor = Name(_Destructor__);
	list->assign = Name(_Assign__);
	list->front = Name(_Front__);
	list->back = Name(_Back__);
	list->begin = Name(_Begin__);
	list->cbegin = Name(_Cbegin__);
	list->end = Name(_End__);
	list->cend = Name(_Cend__);
	list->empty = Name(_Empty__);
	list->size = Name(_Size__);
	list->clear = Name(_Clear__);
	list->insert = Name(_Insert__);
	list->emplace = Name(_Emplace__);
	list->erase = Name(_Erase__);
	list->push_back = Name(_PushBack__);
	list->emplace_back = Name(_EmplaceBack__);
	list->pop_back = Name(_PopBack__);
	list->push_front = Name(_PushFront__);
	list->emplace_front = Name(_EmplaceFront__);
	list->pop_front = Name(_PopFront__);
	list->resize = Name(_Resize__);
	list->swap = Name(_Swap__);
	list->merge = Name(_Merge__);
	list->splice = Name(_Splice__);
	list->remove = Name(_Remove__);
	list->remove_if = Name(_RemoveIf__);
	list->reverse = Name(_Reverse__);
	list->unique = Name(_Unique__);
	list->sort = Name(_Sort__);
	list->for_each = Name(_ForEach__);
	Name(_g_s_this) = list;
	return list;
}

inline type_const_reference Name(_Cdata__) (type_const_iterator c_pCurrent)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pCurrent)
	{
		PrintError("参数为空!非法!");
		return (type_reference)INVALID_ARGUMENT;
	}
	if ((type_const_iterator)97 == c_pCurrent)
	{
		PrintError("无法获取end位置上的元素!");
		return (type_reference)INVALID_ARGUMENT;
	}
	if (0U == Name(_g_s_this)->m_uSize)
	{
		PrintError("禁止在空容器上调用此函数!非法!");
		return (type_reference)INVALID_ARGUMENT;
	}
#endif
	return &(c_pCurrent->m_data);
}

inline type_reference Name(_Data__) (type_iterator pCurrent)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == pCurrent)
	{
		PrintError("参数为空!非法!");
		return (type_reference)INVALID_ARGUMENT;
	}
	if ((type_iterator)97 == pCurrent)
	{
		PrintError("无法获取end位置上的元素!");
		return (type_reference)INVALID_ARGUMENT;
	}
	if (0U == Name(_g_s_this)->m_uSize)
	{
		PrintError("禁止在空容器上调用此函数!非法!");
		return (type_reference)INVALID_ARGUMENT;
	}
#endif
	return &(pCurrent->m_data);
}

inline type_iterator Name(_Next__) (type_const_iterator c_pCurrent)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pCurrent)
	{
		PrintError("参数为空!非法!");
		return (type_iterator)INVALID_ARGUMENT;
	}
	if ((type_const_iterator)97 == c_pCurrent)
	{
		PrintError("end没有下一个!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	type_iterator p_Current = (type_iterator)c_pCurrent;
	return p_Current->m_pNext;
}

inline type_iterator Name(_Prev__) (type_const_iterator c_pCurrent)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pCurrent)
	{
		PrintError("参数为空!非法!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	if ((type_iterator)97 == c_pCurrent)
	{
		return Name(_g_s_this)->m_pTail;
	}
#ifdef ABCSTD_LIST_DEBUG
	if (c_pCurrent == Name(_g_s_this)->m_pHead)
	{
		PrintError("begin没有上一个!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	type_iterator p_Current = (type_iterator)c_pCurrent;
	return p_Current->m_pPrev;
}

#define BindFunPtrInElem do { \
	newData->data = Name(_Data__); \
	newData->cdata = Name(_Cdata__); \
	newData->prev = Name(_Prev__); \
	newData->next = Name(_Next__); \
} while (0)

void Name(_ConstructD) ()
{
	type_list* list = Name(_g_s_this);
	type_iterator newData = (type_iterator)malloc(sizeof(type_node));
	if (NULL == newData)
	{
		PrintError("内存不足!分配失败!");
		return;
	}
	memset(newData, 0, sizeof(type_node));
	newData->m_pNext = (type_iterator)97;
	BindFunPtrInElem;	
	list->m_pList = newData;	
	list->m_pHead = newData->m_pNext;
	list->m_pTail = newData;
}

inline void Name(_ConstructCv) (size_type uCount, type_const_reference c_pValue)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pValue)
	{
		PrintError("参数为空!非法!");	
		return;
	}
#endif
	Name(_ConstructD)();
	Name(_InsertPcv)((type_const_iterator)97, uCount, c_pValue);
}

void Name(_ConstructC) (size_type uCount)
{
	Name(_ConstructD)();
	type_list* list = Name(_g_s_this);
	if (NULL == list->m_pElemConstructor)
	{
		type_value temp;
		memset(&temp, 0, sizeof(type_value));
		Name(_InsertPcv)((type_const_iterator)97, uCount, &temp);
	}
	else
	{
		for (size_type index = 0U; index != uCount; ++index)
		{
			type_value temp;
			list->m_pElemConstructor(&temp);
			Name(_InsertPv)((type_const_iterator)97, &temp);
		}
	}
}

inline void Name(_ConstructFl) (type_const_iterator c_pFirst, type_const_iterator c_pLast)
{
	Name(_ConstructD)();
	Name(_InsertPfl)((type_const_iterator)97, c_pFirst, c_pLast);
}

inline void Name(_ConstructO) (const type_list* c_pOther)
{
	Name(_ConstructD)();
	Name(_InsertPfl)((type_const_iterator)97, c_pOther->m_pHead, c_pOther->m_pTail->m_pNext);
}

inline void Name(_Destructor__) ()
{
	Name(_Clear__)();
	free(Name(_g_s_this)->m_pList);	
	free(Name(_g_s_this));		
	Name(_g_s_this) = NULL;
}

void Name(_Assign__) (const char* c_pFormate, ...)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pFormate)
	{
		PrintError("参数为空!非法!");
		return;
	}
#endif
	va_list vl;
	va_start(vl, c_pFormate);
	if (strcmp(c_pFormate, "cv") == 0)
	{
		size_type uCount = va_arg(vl, size_type);
		type_const_reference c_pValue = va_arg(vl, type_const_reference);
		va_end(vl);
		Name(_AssignCv)(uCount, c_pValue);
	}
	else if (strcmp(c_pFormate, "fl") == 0)
	{
		type_const_iterator c_pFirst = va_arg(vl, type_const_iterator);	
		type_const_iterator c_pLast = va_arg(vl, type_const_iterator);
		va_end(vl);
		Name(_AssignFl)(c_pFirst, c_pLast);
	}
	else
	{
		PrintError("不存在这样的assign函数!非法!");
		va_end(vl);
	}
}

inline void Name(_AssignCv) (size_type uCount, type_const_reference c_pValue)
{
	Name(_Clear__)();
	Name(_InsertPcv)((type_const_iterator)97, uCount, c_pValue);
}

inline void Name(_AssignFl) (type_const_iterator c_pFirst, type_const_iterator c_pLast)
{
	Name(_Clear__)();
	Name(_InsertPfl)((type_const_iterator)97, c_pFirst, c_pLast);
}

inline type_reference Name(_Front__) ()
{
#ifdef ABCSTD_LIST_DEBUG
	if (0U == Name(_g_s_this)->m_uSize)
	{
		PrintError("容器为空!非法!");
		return (type_reference)OUT_OF_RANGE;
	}
#endif
	return &(Name(_g_s_this)->m_pHead->m_data);
}

inline type_reference Name(_Back__) ()
{
#ifdef ABCSTD_LIST_DEBUG
	if (0U == Name(_g_s_this)->m_uSize)
	{
		PrintError("容器为空!非法!");
		return (type_reference)OUT_OF_RANGE;
	}
#endif
	return &(Name(_g_s_this)->m_pTail->m_data);
}


inline type_iterator Name(_Begin__) ()
{
	return Name(_g_s_this)->m_pHead;
}

inline type_const_iterator Name(_Cbegin__) ()
{
	return (type_const_iterator)Name(_g_s_this)->m_pHead;
}

inline type_iterator Name(_End__) ()
{
	return (type_iterator)97;
}

inline type_const_iterator Name(_Cend__) ()
{
	return (type_const_iterator)97;
}

inline bool Name(_Empty__) ()
{
	return !(Name(_g_s_this)->m_uSize);
}

inline size_type Name(_Size__) ()
{
	return Name(_g_s_this)->m_uSize;
}

inline void Name(_Clear__) ()
{
	Name(_EraseFl)(Name(_g_s_this)->m_pHead, (type_const_iterator)97);
}


enum Name(_insertPos)
{
	head,
	middle,
	tail
};

type_iterator Name(_Insert__) (const char* c_pFormate, ...)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pFormate)
	{
		PrintError("参数为空!非法!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	va_list vl;
	va_start(vl, c_pFormate);
	if (strcmp(c_pFormate, "pv") == 0)
	{
		type_const_iterator c_pPos = va_arg(vl, type_const_iterator);
		type_const_reference c_pValue = va_arg(vl, type_const_reference);
		va_end(vl);
		return Name(_InsertPv)(c_pPos, c_pValue);
	}
	else if (strcmp(c_pFormate, "pcv") == 0)
	{
		type_const_iterator c_pPos = va_arg(vl, type_const_iterator);
		size_type uCount = va_arg(vl, size_type);
		type_const_reference c_pValue = va_arg(vl, type_const_reference);
		va_end(vl);
		return Name(_InsertPcv)(c_pPos, uCount, c_pValue);
	}
	else if (strcmp(c_pFormate, "pfl" ) == 0)
	{
		type_const_iterator c_pPos = va_arg(vl, type_const_iterator);
		type_const_iterator c_pFirst = va_arg(vl, type_const_iterator);
		type_const_iterator c_pLast = va_arg(vl, type_const_iterator);
		va_end(vl);
		return Name(_InsertPfl)(c_pPos, c_pFirst, c_pLast);
	}
	else
	{
		PrintError("不存在这样的insert函数!非法!");
		va_end(vl);
		return (type_iterator)INVALID_ARGUMENT;
	}
}

inline type_iterator Name(_InsertPv) (type_const_iterator c_pPos, type_const_reference c_pValue)
{
	return Name(_InsertPcv)(c_pPos, 1U, c_pValue);
}

#define CopyBuiltIn do {  \
	newData = (type_iterator)malloc(sizeof(type_node)); \
	if (NULL == newData) \
	{ \
		PrintError("内存不足!分配失败!"); \
		return (type_iterator)BAD_ALLOC; \
	} \
	memset(newData, 0, sizeof(type_node)); \
	memcpy(&newData->m_data, c_pValue, sizeof(type_value)); \
	list->m_uSize++; \
	}while (0)

#define CopyExternal do { \
	newData = (type_iterator)malloc(sizeof(type_node)); \
	if (NULL == newData) \
	{ \
		PrintError("内存不足!分配失败!"); \
		return (type_iterator)BAD_ALLOC; \
	} \
	memset(newData, 0, sizeof(type_node)); \
	list->m_pElemConstructorCp(&newData->m_data, c_pValue); \
	list->m_uSize++; \
	} while (0)  

#define AddFirstData do { \
	newData->m_pNext = (type_iterator)97; \
	newData->m_pPrev = list->m_pList; \
	list->m_pList->m_pNext = list->m_pHead = list->m_pTail = newData; \
	} while (0) 

#define AddListHeadData do { \
	newData->m_pNext = list->m_pHead; \
	newData->m_pPrev = list->m_pList; \
	list->m_pList->m_pNext = newData; \
	list->m_pHead->m_pPrev = newData; \
	list->m_pHead = newData; \
	} while (0)

#define AddListMiddleData do { \
	newData->m_pNext = (type_iterator)c_pPos; \
	newData->m_pPrev = (type_iterator)c_pPos->m_pPrev; \
	((type_iterator)c_pPos)->m_pPrev = newData; \
	} while (0)

#define AddListTailData do { \
	newData->m_pNext = (type_iterator)97; \
	newData->m_pPrev = list->m_pTail; \
	list->m_pTail->m_pNext = newData; \
	list->m_pTail = newData; \
	} while (0)

static type_iterator s_g_TempPos = NULL;

static bool HelpEqual(const void* c_pA)
{
	if (NULL == c_pA)
		return false;
	else
		return (type_iterator)c_pA == s_g_TempPos;
}

type_iterator Name(_InsertPcv) (type_const_iterator c_pPos, size_type uCount, type_const_reference c_pValue)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pPos || NULL == c_pValue)
	{
		PrintError("参数为空!非法!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	type_list* list = Name(_g_s_this);
#ifdef ABCSTD_LIST_DEBUG
	s_g_TempPos = (type_iterator)c_pPos;
	type_iterator result = (type_iterator)_Algorithm_FindIf_((void*)list->m_pHead, (void*)97, (void *(*)(const void*))list->m_pList->next, HelpEqual);
	//c_pPos不为尾后迭代器且未找到
	if (c_pPos != (type_const_iterator)97  && result == (type_iterator)97)
	{
		PrintError("c_pPos参数无效!");
		return (type_iterator)OUT_OF_RANGE;
	}
#endif
		if (0U == uCount)
		{
			return (type_iterator)c_pPos;
		}
		type_iterator newData = NULL;
		unsigned char ucInsertPos = 0U;
		if (c_pPos != (type_const_iterator)97 && c_pPos != (type_const_iterator)list->m_pHead)
		{
			ucInsertPos = middle;
		}
		else if (c_pPos == (type_const_iterator)97)		
		{
			ucInsertPos = tail;
		}
		else 
		{
			ucInsertPos = head;
		}
		if (NULL == list->m_pElemConstructorCp)
		{
			if (list->m_uSize == 0U)
			{
				CopyBuiltIn;
				BindFunPtrInElem;
				AddFirstData;
				uCount--;
			}
			switch (ucInsertPos)
			{
			case head:
				for (size_type uIndex = 0U; uIndex != uCount; ++uIndex)
				{
					CopyBuiltIn;
					BindFunPtrInElem;
					AddListHeadData;
				}
				break;
			case middle:
				for (size_type uIndex = 0U; uIndex != uCount; ++uIndex)
				{
					CopyBuiltIn;
					BindFunPtrInElem;
					AddListMiddleData;
				}
				break;
			case tail:
				for (size_type uIndex = 0U; uIndex != uCount; ++uIndex)
				{
					CopyBuiltIn;
					BindFunPtrInElem;
					AddListTailData;
				}
				break;
			default:
				break;
			}
		}
		else
		{
			if (list->m_uSize == 0U)
			{
				CopyExternal;
				BindFunPtrInElem;
				AddFirstData;
				uCount--;
			}
			switch (ucInsertPos)
			{
			case head:
				for (size_type uIndex = 0U; uIndex != uCount; ++uIndex)
				{
					CopyExternal;
					BindFunPtrInElem;
					AddListHeadData;
				}
				break;
			case middle:
				for (size_type uIndex = 0U; uIndex != uCount; ++uIndex)
				{
					CopyExternal;
					BindFunPtrInElem;
					AddListMiddleData;
				}
				break;
			case tail:
				for (size_type uIndex = 0U; uIndex != uCount; ++uIndex)
				{
					CopyExternal;
					BindFunPtrInElem;
					AddListTailData;
				}
				break;
			default:
				break;
			}
		}
	return (type_iterator)c_pPos;
}

static type_iterator TempPFirst = NULL;
static type_iterator TempPLast = NULL;
static inline bool HelpEqualFl(const void* c_pA)
{
	return (type_iterator)c_pA == TempPFirst || (type_iterator)c_pA == TempPLast;
}

type_iterator Name(_InsertPfl) (type_const_iterator c_pPos, type_const_iterator c_pFirst, type_const_iterator c_pLast)
{
	type_list* list = Name(_g_s_this);
#ifdef ABCSTD_LIST_DEBUG
	TempPFirst = (type_iterator)c_pFirst;
	TempPLast = (type_iterator)c_pLast;
	type_iterator result = (type_iterator)_Algorithm_FindIf_((void*)list->m_pHead, (void*)97, (void*(*)(const void*))list->m_pList->next, HelpEqualFl);
	if (result != (type_iterator)97 && TempPLast != (type_iterator)97)
	{
		PrintError("元素范围不应是自身!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	type_iterator pFirst = (type_iterator)c_pFirst;
	type_iterator pLast = (type_iterator)c_pLast;
	for (; pFirst != pLast; pFirst = pFirst->m_pNext)
	{
		type_iterator insertResult =  Name(_InsertPv)(c_pPos, &pFirst->m_data);
		if (!(insertResult == (type_iterator)INVALID_ARGUMENT || insertResult == (type_iterator)OUT_OF_RANGE || insertResult == (type_iterator)BAD_ALLOC))
		{
			continue;
		}
		else
		{
			return insertResult;
		}
	}
	return (type_iterator)c_pPos;
}

type_iterator Name(_Emplace__) (type_const_iterator c_pPos)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == Name(_g_s_this)->m_pElemConstructor)
	{
		PrintError("未设置元素的构造函数!非法!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	type_list* list = Name(_g_s_this);
#ifdef ABCSTD_LIST_DEBUG
	s_g_TempPos = (type_iterator)c_pPos;
	type_iterator result = (type_iterator)_Algorithm_FindIf_((void*)list->m_pHead, (void*)97, (void *(*)(const void*))list->m_pList->next, HelpEqual);
	if (result == (type_iterator)97 && c_pPos != (type_const_iterator)97)
	{
		PrintError("c_pPos参数无效!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	type_iterator newData = (type_iterator)malloc(sizeof(type_node));
	if (NULL == newData)
	{
		PrintError("内存不足!分配失败!");
		return (type_iterator)BAD_ALLOC;
	}
	memset(newData, 0, sizeof(type_node));
	BindFunPtrInElem;
	list->m_pElemConstructor(&newData->m_data);
	list->m_uSize++;
	//判断是否是第一次插入
	if (0U == list->m_uSize)
	{
		AddFirstData;	
	}
	//判断插入的位置
	else if (c_pPos == list->cbegin())
	{
		AddListHeadData;
	}
	else if (c_pPos == list->cend())
	{
		AddListTailData;
	}
	else
	{
		AddListMiddleData;
	}
	return newData;
}

inline void Name(_EmplaceBack__) ()
{
	Name(_Emplace__)((type_const_iterator)97);
}

inline void Name(_EmplaceFront__) ()
{
	Name(_Emplace__)(Name(_g_s_this)->m_pHead);
}

type_iterator Name(_Erase__) (const char* c_pFormate, ...)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pFormate)
	{
		PrintError("参数为空!非法!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	va_list vl;
	va_start(vl, c_pFormate);
	if (strcmp(c_pFormate, "p") == 0)		
	{
		type_const_iterator c_pPos = va_arg(vl, type_const_iterator);
		va_end(vl);
		return Name(_EraseP)(c_pPos);
	}
	else if (strcmp(c_pFormate, "fl") == 0)
	{
		type_const_iterator c_pFirst = va_arg(vl, type_const_iterator);
		type_const_iterator c_pLast = va_arg(vl, type_const_iterator);
		va_end(vl);
		return Name(_EraseFl)(c_pFirst, c_pLast);
	}
	else 
	{
		PrintError("不存在这样的erase函数!非法!");
		va_end(vl);
		return (type_iterator)INVALID_ARGUMENT;
	}
}

inline type_iterator Name(_EraseP) (type_const_iterator c_pPos)
{
	return Name(_EraseFl)(c_pPos, c_pPos->m_pNext);
}

type_iterator Name(_EraseFl) (type_const_iterator c_pFirst, type_const_iterator c_pLast)
{
	if (c_pFirst == c_pLast)
	{
		return (type_iterator)NULL;
	}
	type_list* list = Name(_g_s_this); 
#ifdef ABCSTD_LIST_DEBUG
	s_g_TempPos = (type_iterator)c_pFirst;
	type_iterator result = (type_iterator)_Algorithm_FindIf_((void*)list->m_pHead, (void*)97, (void*(*)(const void*))list->m_pList->next, HelpEqual);
	if (result == (type_iterator)97 && c_pFirst != (type_const_iterator)97)
	{
		PrintError("元素范围应是自身!");
		return (type_iterator)INVALID_ARGUMENT;
	}
	s_g_TempPos = (type_iterator)c_pLast;
	result = (type_iterator)_Algorithm_FindIf_((void*)list->m_pHead, (void*)97, (void*(*)(const void*))list->m_pList->next, HelpEqual);
	if (result == (type_iterator)97 && c_pLast != (type_const_iterator)97)
	{
		PrintError("元素范围应是自身!");
		return (type_iterator)INVALID_ARGUMENT;
	}
#endif
	type_iterator pFirst = (type_iterator)c_pFirst;
	type_iterator pLast = (type_iterator)c_pLast;
	type_iterator pCurrent = NULL;
	//普通类型
	if (NULL == list->m_pElemDestructor)
	{
		pCurrent = pFirst;
		type_iterator pNext = NULL;
		type_iterator ptPrev = pFirst->m_pPrev;
		while (pCurrent != pLast)
		{
			pNext = pCurrent->m_pNext;
			free(pCurrent);
			list->m_uSize--;
			pCurrent = pNext;
		}
		if (pFirst == list->m_pHead)
		{
			if (pLast == list->m_pTail->m_pNext)
			{
				list->m_pHead = list->m_pList->m_pNext;
				list->m_pTail = list->m_pList;
			}
			else
			{
				list->m_pHead = pLast;
				pLast->m_pPrev = list->m_pList;
				list->m_pList->m_pNext = pLast;
			}
		}
		else
		{

			if (pLast == list->m_pTail->m_pNext)
			{
				list->m_pTail = ptPrev;
				ptPrev->m_pNext = (type_iterator)97;
			}
			else
			{
				ptPrev->m_pNext = pLast;
				pLast->m_pPrev = ptPrev;
			}
		}
	}
	else
	{
		pCurrent = pFirst;
		type_iterator pNext = NULL;
		type_iterator ptPrev = pFirst->m_pPrev;
		while (pCurrent != pLast)
		{
			pNext = pCurrent->m_pNext;
			list->m_pElemDestructor(&pCurrent->m_data);
			free(pCurrent);
			list->m_uSize--;
			pCurrent = pNext;
		}
		if (pFirst == list->m_pHead)
		{
			if (pLast == list->m_pTail->m_pNext)
			{
				list->m_pHead = list->m_pList->m_pNext;
				list->m_pTail = list->m_pList;
			}
			else
			{
				list->m_pHead = pLast;
				pLast->m_pPrev = list->m_pList;
				list->m_pList->m_pNext = pLast;
			}
		}
		else
		{
			if (pLast == list->m_pTail->m_pNext)
			{
				list->m_pTail = ptPrev;
				ptPrev->m_pNext = (type_iterator)97;
			}
			else
			{
				ptPrev->m_pNext = pLast;
				pLast->m_pPrev = ptPrev;
			}
		}
	}
	return pLast;
}

inline void Name(_PushBack__) (type_const_reference c_pValue)
{
	Name(_InsertPv)((type_const_iterator)97, c_pValue);	
}

inline void Name(_PopBack__) ()
{ 
#ifdef ABCSTD_LIST_DEBUG
	if (0U == Name(_g_s_this)->m_uSize)
	{
		PrintError("禁止在空容器调用此函数!非法!");
		return;
	}
#endif
	Name(_EraseP)(Name(_g_s_this)->m_pTail);
}

inline void Name(_PushFront__) (type_const_reference c_pValue)
{
	Name(_InsertPv)(Name(_g_s_this)->m_pHead, c_pValue);
}

inline void Name(_PopFront__) ()
{
#ifdef ABCSTD_LIST_DEBUG
	if (0U == Name(_g_s_this)->m_uSize)
	{
		PrintError("禁止在空容器调用此函数!非法!");
		return;
	}
#endif
	Name(_EraseP)(Name(_g_s_this)->m_pHead);
}

void Name(_Resize__) (const char* c_pFormate, ...)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pFormate)
	{
		PrintError("参数为空!非法!");
		return;
	}
#endif
	va_list vl;
	va_start(vl, c_pFormate);
	if (strcmp(c_pFormate, "c") == 0)		
	{
		size_type uCount = va_arg(vl, size_type);
		Name(_ResizeC)(uCount);
	}
	else if (strcmp(c_pFormate, "cv") == 0)
	{
		size_type uCount = va_arg(vl, size_type);
		type_const_reference c_pValue = va_arg(vl, type_const_reference);
		Name(_ResizeCv)(uCount, c_pValue);
	}
	else 
	{
		PrintError("不存在这样的resize函数!非法!");
		va_end(vl);
		return;
	}
	va_end(vl);

}

void Name(_ResizeC) (size_type uCount)
{
	type_list* list = Name(_g_s_this);
	if (list->m_uSize > uCount)
	{
		type_iterator pCurrent = Name(_g_s_this)->m_pHead;
		while(uCount)
		{
			pCurrent = pCurrent->m_pNext;
			uCount--;
		}
		Name(_EraseFl)((type_const_iterator)pCurrent, (type_const_iterator)97);
	}
	else
	{
		size_type uDValue = uCount - list->size();
		if (NULL == list->m_pElemConstructor)
		{
			for(size_type index = 0U; index != uDValue; ++index)
			{
				type_iterator newData = (type_iterator)malloc(sizeof(type_node));
				if (NULL == newData)
				{
					PrintError("内存不足!分配失败!");
					return;
				}
				memset(newData, 0, sizeof(type_node));
				BindFunPtrInElem;
				AddListTailData;
				list->m_uSize++;
			}
		}
		else
		{
			for (size_type index = 0U; index != uDValue; ++index)
			{
				Name(_EmplaceBack__)();
			}
		}
	}
}

void Name(_ResizeCv) (size_type uCount, type_const_reference c_pValue)
{
#ifdef ABCSTD_LIST_DEBUG
	if (c_pValue == NULL)
	{
		PrintError("参数为空!非法!");
		return;
	}
#endif
	if (Name(_g_s_this)->m_uSize > uCount)
	{
		type_iterator pCurrent = Name(_g_s_this)->m_pHead;
		while(uCount)
		{
			pCurrent = pCurrent->m_pNext;
			uCount--;
		}
		Name(_EraseFl)((type_const_iterator)pCurrent, (type_const_iterator)97);
	}
	else
	{
		Name(_InsertPcv)((type_const_iterator)97, uCount - Name(_g_s_this)->m_uSize, c_pValue);
	}
}

void Name(_Swap__) (type_list* pOther)
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == pOther)
	{
		PrintError("参数为空!非法!");
		return;
	}
#endif
	_Algorithm_Swap_(&Name(_g_s_this)->m_uSize, &pOther->m_uSize, sizeof(size_type));
	_Algorithm_Swap_(&Name(_g_s_this)->m_pHead, &pOther->m_pHead, sizeof(type_iterator));
	_Algorithm_Swap_(&Name(_g_s_this)->m_pTail, &pOther->m_pTail, sizeof(type_iterator));
	_Algorithm_Swap_(&Name(_g_s_this)->m_pList, &pOther->m_pList, sizeof(type_iterator));
}

void Name(_Merge__) (type_list* pOther, bool (*pCompare)(type_const_reference c_pA, type_const_reference c_pB)) //小于等于为真
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == pOther || NULL == pCompare)
	{
		PrintError("参数为空!非法!");
		return;
	}
#endif
	if (pOther == Name(_g_s_this))
	{
		return;
	}
	if (0U == pOther->m_uSize)
	{
		return;
	}
	type_list* list = Name(_g_s_this);
	if (0U == list->m_uSize)
	{
		list->swap(pOther);
		return;
	}
	list->m_uSize += pOther->m_uSize;
	pOther->m_uSize = 0U;
	pOther->m_pHead = (type_iterator)97;
	type_iterator mayNewTail = pOther->m_pTail;
	pOther->m_pTail = pOther->m_pList;

	type_iterator pListCurrent = list->m_pList->m_pNext;
	type_iterator pOtherCurrent = pOther->m_pList->m_pNext;
	type_iterator pList = list->m_pList;

	list->m_pHead = pCompare(&pListCurrent->m_data, &pOtherCurrent->m_data) ? pListCurrent : pOtherCurrent;
	while (pListCurrent != (type_iterator)97 && pOtherCurrent != (type_iterator)97)
	{
		if (pCompare(&pListCurrent->m_data, &pOtherCurrent->m_data))	
		{
			pList->m_pNext = pListCurrent;
			pListCurrent->m_pPrev = pList;
			pListCurrent = pListCurrent->m_pNext;
		}
		else
		{
			pList->m_pNext = pOtherCurrent;
			pOtherCurrent->m_pPrev = pList;
			pOtherCurrent = pOtherCurrent->m_pNext;
		}
		pList = pList->m_pNext;
	}
	if (pListCurrent != (type_iterator)97)
	{
		pList->m_pNext = pListCurrent;	
		pListCurrent->m_pPrev = pList;
	}
	if (pOtherCurrent != (type_iterator)97)
	{
		pList->m_pNext = pOtherCurrent;
		pOtherCurrent->m_pPrev = pList;
		list->m_pTail = mayNewTail;
	}
	pOther->m_pList->m_pNext = (type_iterator)97;
}

void Name(_Splice__) (const char* c_pFormate, ...)
{

#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pFormate)
	{
		PrintError("参数为空!非法!");
		return;
	}
#endif
	va_list vl;
	va_start(vl, c_pFormate);
	if (strcmp(c_pFormate, "po") == 0)
	{
		type_const_iterator c_pPos = va_arg(vl, type_const_iterator);
		type_list* pOther = va_arg(vl, type_list*);
		Name(_SplicePo)(c_pPos, pOther);
	}
	else if (strcmp(c_pFormate, "poi") == 0)
	{
		type_const_iterator c_pPos = va_arg(vl, type_const_iterator);
		type_list* pOther = va_arg(vl, type_list*);
		type_const_iterator c_pIt = va_arg(vl, type_const_iterator); 
		Name(_SplicePoi)(c_pPos, pOther, c_pIt);
	}
	else if (strcmp(c_pFormate, "pofl") == 0)
	{
		type_const_iterator c_pPos = va_arg(vl, type_const_iterator);
		type_list* pOther = va_arg(vl, type_list*);
		type_const_iterator c_pFirst = va_arg(vl, type_const_iterator);
		type_const_iterator c_pLast = va_arg(vl, type_const_iterator);
		Name(_SplicePofl)(c_pPos, pOther, c_pFirst, c_pLast);
	}
	else
	{
		PrintError("不存在这样的splice函数!非法!");
	}
	va_end(vl);
}

static void Name(_SplicePo) (type_const_iterator c_pPos, type_list* pOther)
{
	Name(_SplicePofl)(c_pPos, pOther, pOther->m_pHead, (type_const_iterator)97);
}

static void Name(_SplicePoi) (type_const_iterator c_pPos, type_list* pOther, type_const_iterator c_pIt)
{
	Name(_SplicePofl)(c_pPos, pOther, c_pIt, c_pIt->m_pNext);
}

void Name(_SplicePofl) (type_const_iterator c_pPos, type_list* pOther, type_const_iterator c_pFirst, type_const_iterator c_pLast)
{
	type_list* list = Name(_g_s_this);
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pPos || NULL == pOther || NULL == c_pFirst || NULL == c_pLast)
	{
		PrintError("参数为空!非法!");
		return;
	}
	if (list == pOther)
	{
		PrintError("pOther参数不应是自身!");
		return;
	}
	s_g_TempPos = (type_iterator)c_pFirst;
	type_iterator result = (type_iterator)_Algorithm_FindIf_((void*)pOther->m_pHead, (void*)97, (void *(*)(const void*))pOther->m_pList->next, HelpEqual);
	if (result == (type_iterator)97 && c_pFirst != (type_const_iterator)97)
	{
		PrintError("c_pFirst应为pOther容器中的范围!");
		return;
	}
	s_g_TempPos = (type_iterator)c_pLast;
	result = (type_iterator)_Algorithm_FindIf_((void*)pOther->m_pHead, (void*)97, (void *(*)(const void*))pOther->m_pList->next, HelpEqual);
	if (result == (type_iterator)97 && c_pLast != (type_const_iterator)97)
	{
		PrintError("c_pLast应为pOther容器中的范围!");
		return;
	}
	s_g_TempPos = (type_iterator)c_pPos;
	result = (type_iterator)_Algorithm_FindIf_((void*)pOther->m_pHead, (void*)97, (void *(*)(const void*))pOther->m_pList->next, HelpEqual);
	if (result != (type_iterator)97)
	{
		PrintError("c_pPos不应为pOther容器中的范围!");
		return;
	}
	s_g_TempPos = (type_iterator)c_pPos;
	result = (type_iterator)_Algorithm_FindIf_((void*)list->m_pHead, (void*)97, (void *(*)(const void*))list->m_pList->next, HelpEqual);
	if (result == (type_iterator)97 && c_pPos != (type_const_iterator)97)
	{
		PrintError("c_pPos应为自身容器中的范围!");
		return;
	}
	if (0U == pOther->m_uSize)
	{
		PrintError("pOther容器为空!");
		return;
	}
#endif
	type_iterator pFirst = (type_iterator)c_pFirst;
	type_iterator pLast = (type_iterator)c_pLast;
	type_iterator pPos = (type_iterator)c_pPos;
	type_iterator pCurrent = pFirst;
	type_iterator pTempLastPrev = NULL;
	if (pLast == (type_iterator)97)
	{
		pTempLastPrev = pOther->m_pTail;
	}
	else 
	{
		pTempLastPrev = pLast->m_pPrev;
	}
	unsigned uCount = 0U;
	while (pCurrent != pLast)
	{
		uCount++;
		pCurrent = pCurrent->m_pNext;
	}
	pOther->m_uSize -= uCount;	
	if (pFirst != pOther->m_pHead)
	{
		if (pLast == (type_iterator)97)
		{
			pOther->m_pTail = pFirst;
			pFirst->m_pNext = (type_iterator)97;
		}
		else 
		{
			pFirst->m_pPrev->m_pNext = pLast;
			pLast->m_pPrev = pFirst->m_pPrev;
		}
	}
	else
	{
		if (pLast == (type_iterator)97)
		{
			pOther->m_pList->m_pNext = (type_iterator)97;
			pOther->m_pHead = (type_iterator)97;
			pOther->m_pTail = pOther->m_pList;
		}
		else
		{
			pOther->m_pList->m_pNext = pLast;
			pLast->m_pPrev = pOther->m_pList;
			pOther->m_pHead = pLast;
		}
	}
	if (0U == list->m_uSize)
	{
		list->m_pHead = pFirst;
		list->m_pTail = pTempLastPrev;
		list->m_pList->m_pNext = pFirst;
		pFirst->m_pPrev = list->m_pList;
		pTempLastPrev->m_pNext = (type_iterator)97;
		list->m_uSize += uCount;
		return;
	}
	list->m_uSize += uCount;
	if (pPos == list->m_pHead)
	{
		list->m_pList->m_pNext = pFirst;
		pFirst->m_pPrev = list->m_pList;
		pTempLastPrev->m_pNext = pPos;
		pPos->m_pPrev = pTempLastPrev;	
		list->m_pHead = pFirst;
	}
	else if (pPos == (type_iterator)97)
	{
		list->m_pTail->m_pNext = pFirst;
		pFirst->m_pPrev = list->m_pTail;
		pTempLastPrev->m_pNext = (type_iterator)97;
		list->m_pTail = pTempLastPrev;
	}
	else
	{
		pPos->m_pPrev->m_pNext = pFirst;
		pFirst->m_pPrev = pPos->m_pPrev;
		pTempLastPrev = pPos;
		pPos->m_pPrev = pTempLastPrev;
	}
}

static struct 
{
	const type_value* pValue;
	bool (*pEqual)(type_const_reference c_pA, type_const_reference c_pB);
}TempRemove; 

static inline bool HelpRemove (type_const_reference c_pValue)
{
	if (NULL == c_pValue)
	{
		return false;
	}
	return TempRemove.pEqual((type_const_reference)TempRemove.pValue, c_pValue);
}

static size_type Name(_Remove__) (type_const_reference c_pValue, bool (*pEqual)(type_const_reference c_pA, type_const_reference c_pB))
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == c_pValue || NULL == pEqual)
	{
		PrintError("参数为空!非法!");
		return 0U;
	}
#endif
	TempRemove.pEqual = pEqual;
	TempRemove.pValue = (const type*)c_pValue;
	return Name(_RemoveIf__)(HelpRemove);
}

size_type Name(_RemoveIf__) (bool (*pCondition) (type_const_reference c_pValue))
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == pCondition)
	{
		PrintError("参数为空!非法!");
		return 0U;
	}
#endif
	type_list* list = Name(_g_s_this);
	size_type uCount = 0U;
	for (type_iterator it = list->begin(); it != list->end(); )
	{
		type_iterator result = (type_iterator) _Algorithm_FindIf_((void*)it, (void*)97, (void*(*)(const void*))list->m_pList->next, (bool (*)(const void*))pCondition);
		if (result != list->cend())
		{
			uCount++;
			it = list->erase("p", result);
		}
		else
		{
			it = it->m_pNext;
		}
	}
	return uCount;
}

void Name(_Reverse__) ()
{
	type_list* list = Name(_g_s_this);
	if (0U == list->m_uSize)
	{
		return;
	}
	type_iterator pCurrent = list->m_pList->m_pNext;
	type_iterator pNext = NULL;
	for (size_type index = 0U; index != list->m_uSize; ++index)
	{
		pNext = pCurrent->m_pNext;
		_Algorithm_Swap_(&pCurrent->m_pNext, &pCurrent->m_pPrev, sizeof(pCurrent->m_pNext));
		pCurrent = pNext;
	}
	_Algorithm_Swap_(&list->m_pHead, &list->m_pTail, sizeof(list->m_pTail));
	list->m_pTail->m_pNext = (type_iterator)97;
	list->m_pHead->m_pPrev = list->m_pList;
	list->m_pList->m_pNext = list->m_pHead;
}

size_type Name(_Unique__) (bool (*pEqual)(type_const_reference c_pA, type_const_reference c_pB))
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == pEqual)
	{
		PrintError("参数为空!非法!");
		return 0U;
	}
#endif
	if (0U == Name(_g_s_this)->m_uSize)
	{
		return 0U;
	}
	size_type uCount = 0U;
	type_iterator pCurrent = Name(_g_s_this)->m_pList->m_pNext;
	type_iterator pNext = pCurrent->m_pNext;
	while (pNext != (type_iterator)97)
	{
		if (pEqual(&pCurrent->m_data, &pNext->m_data))
		{
			uCount++;
			pNext = Name(_g_s_this)->erase("p", pNext);
		}
		else
		{
			pCurrent = pCurrent->m_pNext;
			pNext = pNext->m_pNext;
		}
	}
	return uCount;
}

static bool (*TempCompare) (type_const_reference c_pA, type_const_reference c_pB) = NULL;
static int HelpCompare(const void* c_pA, const void* c_pB)
{
	type_iterator* pa = (type_iterator*)c_pA;
	type_iterator* pb = (type_iterator*)c_pB;
	if (TempCompare(&((*pa)->m_data), &((*pb)->m_data)))
	{
		return -1;
	}
	else 
	{
		return 1;
	}
	return 0;
}

void Name(_Sort__) (bool (*pCompare)(type_const_reference c_pA, type_const_reference c_pB))
{
#ifdef ABCSTD_LIST_DEBUG
	if (NULL == pCompare)
	{
		PrintError("参数为空!非法!");
		return;
	}
#endif
	type_list* list = Name(_g_s_this);
	type_list* carry = Name(_ListConstructor)("d");
	type_list* arr[64] = { 0 };
	for (int i = 0; i != 64; ++i)
	{
		arr[i] = Name(_ListConstructor)("d");
	}
	int fill = 0;
	while (list->m_uSize)
	{
		Name(_Rebind)(carry);
		Name(_SplicePofl)(carry->m_pHead, list, list->m_pHead, list->m_pHead->m_pNext);
		int i = 0;
		while (i < fill && arr[i]->m_uSize)
		{
			Name(_Rebind)(arr[i]);	
			arr[i]->merge(carry, pCompare);
			Name(_Rebind)(carry);
			carry->swap(arr[i++]);
		}
		carry->swap(arr[i]);
		if (i == fill)
		{
			++fill;
		}
	}
	for (int i = 1; i != fill; ++i)
	{
		Name(_Rebind)(arr[i]);
		arr[i]->merge(arr[i - 1], pCompare);
	}
	Name(_Rebind)(list);
	list->swap(arr[fill - 1]);
	for (int i = 0; i != 64; ++i)
	{
		Name(_Rebind)(arr[i]);
		arr[i]->destructor();
	}
	Name(_Rebind)(list);
}

void Name(_ForEach__)(void (*pPrint)(type_const_reference pData))
{
	type_list* list = Name(_g_s_this);
	_Algorithm_ForEach_((void*)list->m_pHead, (void*)97, (void*(*)(const void*))list->m_pList->next, (void (*)(const void*))pPrint);
}
