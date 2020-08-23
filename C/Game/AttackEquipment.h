#ifndef ATTACKEQUIPMENT_H_
#define ATTACKEQUIPMENT_H_
#include "Equipment.h"

//攻击装备
typedef struct AttackEquipment
{
	Equipment equipment;
	int physicalDamage;
	int magicDamage;
}AttackEquipment;

/**初始化攻击装备

 *

 * 用于初始化攻击装备

 * @param [in] 
    attackEquipment 攻击装备结构地址
    name            装备名
    price           价格
    physicalDamage  物理攻击
    magicDamage     魔法攻击

 * @param [out] 
    空

 * @return 
    空

 * @note   
    name 需要具有数据

*/
void InitAttackEquipment(AttackEquipment* attackEquipment, const char* name,
	int price, int physicalDamage, int magicDamage);

/**获取攻击装备物理攻击

 *

 * 用于获取攻击装备物理攻击

 * @param [in] 
    attackEquipment 需要获取的物理装备

 * @param [out] 
    int

 * @return 
    攻击装备的物理攻击值


 * @note 

*/
int GetAttackEquipmentPhysicalDamage(const AttackEquipment* attackEquipment);

/**获取攻击装备魔法攻击

 *

 * 用于获取攻击装备魔法攻击

 * @param [in] 
    attackEquipment 需要获取的物理装备

 * @param [out] 
    int

 * @return 
    攻击装备的魔法攻击值


 * @note 

*/
int GetAttackEquipmentMagicDamage(const AttackEquipment* attackEquipment);

#endif