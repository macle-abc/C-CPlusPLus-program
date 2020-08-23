#ifndef EQUIPMENT_H_
#define EQUIPMENT_H_

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>

//装备的类型
enum EquipmentType
{
	normal,
	attack,
	defense,
	alloy
};

//所有装备共享此结构
typedef struct Equipment
{
	char name[81];
	int price;
	int type;
}Equipment;

/**获取装备类型
*

 * 根据equipment获取装备类型

 * @param [in] 
	equipment		想要获取类型的装备地址

 * @param [out]
	int

 * @return 
	装备的类型		
	
* @see  
	 详情上述装备类型枚举

 * @note

*/
int GetEquipmentType(const Equipment* equipment);

//以下如同攻击装备
void InitEquipment(Equipment* equipment, const char* name, int price);

const char* GetEquipmentName(const Equipment* equipment);

int GetEquipmentPrice(const Equipment* equipment);
void SetEquipmentName(Equipment* equipment, const char* name);
void SetEquipmentPrice(Equipment* equipment, int price);

#endif