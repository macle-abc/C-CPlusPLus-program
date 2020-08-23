#include "abc.h"
#include <string.h>
#include <stdlib.h>

static abcNamespace* abc_namespace = NULL;

abcNamespace* Get_ABC_NameSpace()
{
	if (NULL == abc_namespace)
	{
		abc_namespace = (abcNamespace*)malloc(sizeof(abcNamespace));
		if (NULL == abc_namespace)
		{
			PrintError("ÄÚ´æ²»×ã!·ÖÅäÊ§°Ü!");
			return (abcNamespace*)BAD_ALLOC;
		}
		memset(abc_namespace, 0, sizeof(abcNamespace));
	}
	return abc_namespace;
}

void Delete_ABC_NameSpace()
{
	free(abc_namespace);
	abc_namespace = NULL;
}
