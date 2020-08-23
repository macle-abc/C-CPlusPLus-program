//#define DEBUG
#ifdef DEBUG
	#define type int
#endif
#ifndef type
	#error "Must be define type!"
#endif 

#include "../abc.h"
#include "../AbcAlgorithm/algorithm.h"
#include <stdbool.h>

#define Concat(x, y) x##y
#define UseType(x, y) Concat(x, y)
#define Name(x) UseType(type, x)
#define type_node UseType(type, _node)
#define type_list UseType(type, _list)

#define type_value UseType(type, _value)
#define type_reference UseType(type, _reference)
#define type_const_reference UseType(type, _const_reference)
#define type_iterator UseType(type, _iterator)
#define type_const_iterator UseType(type, _const_iterator)


typedef struct type_node type_node;
typedef struct type_list type_list;
typedef type type_value;
typedef type * const type_reference;
typedef const type * const type_const_reference;
typedef type_node * type_iterator;
typedef const type_node * type_const_iterator;

typedef unsigned size_type;
typedef int difference_type;


struct type_node
{
	type_value m_data;
	type_iterator m_pPrev;
	type_iterator m_pNext;

	type_iterator (*next) (type_const_iterator c_pCurrent);
	type_iterator (*prev) (type_const_iterator c_pCurrent);
	type_reference (*data) (type_iterator c_pCurrent);
	type_const_reference (*cdata) (type_const_iterator c_pCurrent);
};

struct type_list
{
	type_iterator m_pList;
	type_iterator m_pHead;
	type_iterator m_pTail;
	size_type m_uSize;

	void (*m_pElemConstructor)(type_reference pData);
	void (*m_pElemConstructorCp)(type_reference pData, type_const_reference c_pOther);
	void (*m_pElemDestructor)(type_reference pData);

	void (*destructor) (); 
	void (*assign) (const char* c_pFormate, ...); 

	type_reference (*front) ();	
	type_reference (*back) ();
	type_iterator (*begin) ();
	type_const_iterator (*cbegin) ();
	type_iterator (*end) ();
	type_const_iterator (*cend) ();

	bool (*empty) ();
	size_type (*size) ();

	void (*clear) ();
	type_iterator (*insert) (const char* c_pFormate, ...);
	type_iterator (*emplace) (type_const_iterator c_pPos);
	type_iterator (*erase) (const char* c_pFormate, ...);
	void (*push_back) (type_const_reference c_pValue);
	void (*emplace_back) ();
	void (*pop_back) ();
	void (*push_front) (type_const_reference c_pValue);
	void (*emplace_front) ();
	void (*pop_front) ();
	void (*resize) (const char* c_pFormate, ...);
	void (*swap) (type_list* pOther);

	void (*merge) (type_list* pOther, bool (*pCompare)(type_const_reference c_pA, type_const_reference c_pB));
	void (*splice) (const char* c_pFormate, ...);
	size_type (*remove) (type_const_reference c_pValue, bool (*pEqual)(type_const_reference c_pA, type_const_reference c_pB));
	size_type (*remove_if) (bool (*pCondition) (type_const_reference c_pValue));
	void (*reverse) ();
	size_type (*unique) (bool (*pEqual)(type_const_reference c_pA, type_const_reference c_pB));
	void (*sort) (bool (*pCompare)(type_const_reference c_pA, type_const_reference c_pB));

	void (*for_each) (void (*pPrint)(type_const_reference c_pValue));
};

extern void Name(_Rebind) (type_list* const pRebindList);

extern type_list* Name(_ListConstructor)(const char* c_pFormate, ...);

extern void Name(_SetElemConstructor) (void (*pConstructor)(type_reference pData));

extern void Name(_SetElemConstructorCp) (void (*pConstructorCp)(type_reference pData, type_const_reference c_pOther));

extern void Name(_SetElemDestructor) (void (*pDestructor)(type_reference pData));
