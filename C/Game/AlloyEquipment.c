#include "AlloyEquipment.h"

void InitAlloyeEquipment(AlloyeEquipment* alloyeEquipment, const AttackEquipment* attackEquipment,
	const DefenseEquipment* defenseEquipment)
{
	alloyeEquipment->attackEquipment = *attackEquipment;
	alloyeEquipment->defenseEquipment = *defenseEquipment;
	char buff[81] = { 0 };
	int len = strlen(attackEquipment->equipment.name);
	strncat(buff, attackEquipment->equipment.name, 80);
	strncat(buff, "-with-", 80 - len);
	len += strlen("-with-");
	strncat(buff, defenseEquipment->equipment.name, 80 - len);
	strncpy(alloyeEquipment->attackEquipment.equipment.name, buff, 80);
	alloyeEquipment->attackEquipment.equipment.price = (int)(1.5 * attackEquipment->equipment.price +
		defenseEquipment->equipment.price);
	alloyeEquipment->attackEquipment.equipment.type = alloy;
}
