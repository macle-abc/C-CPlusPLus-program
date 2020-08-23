#include "Equipment.h"

int GetEquipmentType(const Equipment* equipment)
{
	return equipment->type;
}

void InitEquipment(Equipment* equipment, const char* name, int price)
{
	strncpy(equipment->name, name, 80);
	equipment->price = price;
	equipment->type = normal;
}

const char* GetEquipmentName(const Equipment* equipment)
{
	return equipment->name;
}

int GetEquipmentPrice(const Equipment* equipment)
{
	return equipment->price;
}

void SetEquipmentName(Equipment* equipment, const char* name)
{
	strncpy(equipment->name, name, 80);
}

void SetEquipmentPrice(Equipment* equipment, int price)
{
	equipment->price = price;
}
