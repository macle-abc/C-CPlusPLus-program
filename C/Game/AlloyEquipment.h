#ifndef ALLOYEQUIPMENT_H_
#define ALLOYEQUIPMENT_H_
#define _CRT_SECURE_NO_WARNINGS

#include "AttackEquipment.h"
#include "DefenseEquipment.h"

//合金装备(攻击装备+防御装备)融合
typedef struct AlloyeEquipment
{
	AttackEquipment attackEquipment;
	DefenseEquipment defenseEquipment;

}AlloyeEquipment;

/**初始化合金装备

 *

 * 用于初始化合金装备

 * @param [in] 
    alloyeEquipment 合金装备结构的地址 
    attackEquipment 用于合成的攻击装备结构的地址
    defenseEquipment 用于合成的防御装备结构的地址
    
 * @param [out] 
    无 

 * @return 
    无


 * @note   
    用于合成的攻防装备必须具有自己的数据

*/
void InitAlloyeEquipment(AlloyeEquipment* alloyeEquipment,
 const AttackEquipment* attackEquipment,
	const DefenseEquipment* defenseEquipment);

#endif
