#ifndef DEFENSEEQUIPMENT_H_
#define DEFENSEEQUIPMENT_H_

#define _CRT_SECURE_NO_WARNINGS
#include "Equipment.h"

//防御装备
typedef struct DefenseEquipment
{
	Equipment equipment;
	int physicalDefense;
	int magicDefense;
}DefenseEquipment;

/**初始化防御装备

 *

 * 用于初始化防御装备

 * @param [in] 
    defenseEquipment 防御装备的地址
    name             装备名
    price            价格
    physicalDefense  物理防御
    magicDefense     魔法防御

 * @param [out] 
    空

 * @return 
    空

 * @note   
    name 需要具有数据

*/
void InitDefenseEquipment(DefenseEquipment* defenseEquipment, const char* name,
	int price, int physicalDefense, int magicDefense);

//同攻击装备
int GetDefenseEquipmentPhysical(const DefenseEquipment* defenseEquipment);

//同攻击装备
int GetDefenseEquipmentMagic(const DefenseEquipment* defenseEquipment);
#endif