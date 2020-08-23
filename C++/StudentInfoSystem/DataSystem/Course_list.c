
#include "genlib.h"
#include <string.h>
typedef struct Couse
{
	string m_cId;//课程号
	string m_cName;//课程名
	string m_teacher;//教师名
}Course;
/*
typedef struct{
	...
}your_type;
#define __list_t	your_type
*/

#define __list_t Course

#include "__list_h.h"
#include "__list_c.h"

void DestructCourse(Course* cou)
{
	free(cou->m_cId);
	free(cou->m_cName);
	free(cou->m_teacher);
}
void CopyCourse(Course* des, const Course* src)
{
	des->m_cId = (string)malloc(strlen(src->m_cId) + 1);
	des->m_cName = (string)malloc(strlen(src->m_cName) + 1);
	des->m_teacher = (string)malloc(strlen(src->m_teacher) + 1);
	strcpy(des->m_cId, src->m_cId);
	strcpy(des->m_cName, src->m_cName);
	strcpy(des->m_teacher, src->m_teacher);
}