#include "DefenseEquipment.h"

void InitDefenseEquipment(DefenseEquipment* defenseEquipment, const char* name, int price, int physicalDefense, int magicDefense)
{
	strncpy(defenseEquipment->equipment.name, name, 80);
	defenseEquipment->equipment.price = price;
	defenseEquipment->magicDefense = magicDefense;
	defenseEquipment->physicalDefense = physicalDefense;
	defenseEquipment->equipment.type = defense;
}

int GetDefenseEquipmentPhysical(const DefenseEquipment* defenseEquipment)
{
	return defenseEquipment->physicalDefense;
}

int GetDefenseEquipmentMagic(const DefenseEquipment* defenseEquipment)
{
	return defenseEquipment->magicDefense;
}
