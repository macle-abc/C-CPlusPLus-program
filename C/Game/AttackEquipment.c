#include "AttackEquipment.h"
void InitAttackEquipment(AttackEquipment* attackEquipment, const char* name, int price, int physicalDamage, int magicDamage)
{
	strncpy(attackEquipment->equipment.name, name, 80);
	attackEquipment->equipment.price = price;
	attackEquipment->physicalDamage = physicalDamage;
	attackEquipment->magicDamage = magicDamage;
	attackEquipment->equipment.type = attack;
}

int GetAttackEquipmentPhysicalDamage(const AttackEquipment* attackEquipment)
{
	return attackEquipment->physicalDamage;
}

int GetAttackEquipmentMagicDamage(const AttackEquipment* attackEquipment)
{
	return attackEquipment->magicDamage;
}
