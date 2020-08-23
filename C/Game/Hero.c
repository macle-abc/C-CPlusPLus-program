#include "Hero.h"
#include "macro.h"

static int RemoveHeroEquipment(Hero* hero, int index);
static int Crit(Hero* me, Hero* that);
static int NormalAttack(Hero* me, Hero* that);
static int DamageTaken(Hero* me, int damageValue);

void InitHero(Hero* hero, const char* name, int money, int health, int physicalDamage, int magicalDamage, int physicalDefense, int magicalDefense)
{
	hero->equipment = new_array(0);
	strncpy(hero->name, name, 80);
	hero->money = money;
	hero->health = health;
	hero->physicalDamage = physicalDamage;
	hero->magicalDamage = magicalDamage;
	hero->physicalDefense = physicalDefense;
	hero->magicalDefense = magicalDefense;
}

void ResetHero(Hero* hero, const char* name, int money, int reset_equip, Equipment* equip)
{
	if (reset_equip) 
	{
		while (hero->equipment.length)
		{
				array_remove(&hero->equipment, hero->equipment.length - 1);
		}
		if (equip) 
		{
			hero->money = 9999;
			HeroBuyEquipment(hero, equip);
		}
	}
	strncpy(hero->name, name, 80);
	hero->health = 100;
	hero->money = money;
}

void DestroyHero(Hero* hero)
{
	while (hero->equipment.length)
	{
		array_remove(&hero->equipment, hero->equipment.length - 1);
	}
	delete_array(&hero->equipment);
}

const char* GetHeroName(const Hero* hero)
{
	return hero->name;
}

int GetHeroHealth(const Hero* hero)
{
	return hero->health;
}

int GetHeroPhysicalDamage(const Hero* hero)
{
	return hero->physicalDamage;
}

int GetHeroMagicalDamage(const Hero* hero)
{
	return hero->magicalDamage;
}

int GetHeroPhysicalDefense(const Hero* hero)
{
	return hero->physicalDefense;
}

int GetHeroMagicalDefense(const Hero* hero)
{
	return hero->magicalDefense;
}

int GetHeroEquipmentNumber(const Hero* hero)
{
	return hero->equipment.length;
}

int GetHeroMoney(const Hero* hero)
{
	return hero->money;
}

Equipment* GetHeroEquipmentByIndex(const Hero* hero, int index)
{
	if (index >= 0 && index < hero->equipment.length)
	{
		return  hero->equipment.data[index];
	}
	else 
	{
		return NULL;
	}
}

int GetHeroRealPhysicalDamage(const Hero* hero)
{
	int result = GetHeroPhysicalDamage(hero);
	for (int i = 0; i != hero->equipment.length; ++i)
	{
		if (GetEquipmentType(hero->equipment.data[i]) == attack)
		{
			result += GetHeroPhysicalDamage(hero);
		}
	}
	return result;
}

int GetHeroRealMagicalDamage(const Hero* hero)
{
	int result = GetHeroMagicalDamage(hero);
	for (int i = 0; i != hero->equipment.length; ++i)
	{
		if (GetEquipmentType(hero->equipment.data[i]) == attack)
		{
			result += GetHeroMagicalDamage(hero);
		}
	}
	return result;
}

int GetHeroRealPhysicalDefense(const Hero* hero)
{
	int result = GetHeroPhysicalDefense(hero);
	for (int i = 0; i != hero->equipment.length; ++i)
	{
		if (GetEquipmentType(hero->equipment.data[i]) == defense)
		{
			result += GetDefenseEquipmentPhysical((const DefenseEquipment*)hero->equipment.data[i]);
		}
	}
	return result;
}

int GetHeroRealMagicalDefense(const Hero* hero)
{
	int result = GetHeroMagicalDefense(hero);
	for (int i = 0; i != hero->equipment.length; ++i)
	{
		if (GetEquipmentType(hero->equipment.data[i]) == defense)
		{
			result += GetDefenseEquipmentMagic((const DefenseEquipment*)hero->equipment.data[i]);
		}
	}
	return result;
}

double GetHeroCritChance(const Hero* hero)
{
	return (hero->money >= C_CRIT_MONEY) ? 1.0 : (double)hero->money / C_CRIT_MONEY;
}

int HeroIsAlive(const Hero* hero)
{
	return hero->health > 0;
}

void PrintHeroInfo(const Hero* hero)
{
	SET_WHITE;
	printf("┌─────────────────────────────────────────────────┬────────────────────────┐ \n");
	printf("│  ");
	SET_CYAN;
	printf("%-16s", GetHeroName(hero));
	SET_WHITE;
	printf("[HP] ");
	if (GetHeroHealth(hero) >= 50) 
	{
		SET_GREEN; 
	}
	else if (GetHeroHealth(hero) >= 20)
	{
		SET_YELLOW; 
	}
	else 
	{
		SET_RED; 
	}
	printf("%3d", GetHeroHealth(hero));
	SET_WHITE;
	printf("    [Crit Chance] %3d", (int)(100 * GetHeroCritChance(hero)));
	printf("%% │       Equipments       │ \n");
	printf("│  [MONEY] $%-7d[Equipment] ", GetHeroMoney(hero));
	if (GetHeroEquipmentNumber(hero))
	{
		printf("%d", GetHeroEquipmentNumber(hero));
	}
	else
	{
		printf("-");
	}
	printf("                  ├────────────────────────┤ \n");
	printf("│  [Attack Damage] %4d = %3d", GetHeroRealPhysicalDamage(hero), GetHeroPhysicalDamage(hero));
	for (int i = 0; i < GetHeroEquipmentNumber(hero); i++)
	{
		if (GetEquipmentType(GetHeroEquipmentByIndex(hero, i)) == attack || 
			GetEquipmentType(GetHeroEquipmentByIndex(hero, i)) == alloy)
		{	
			AttackEquipment* attackEquipmentPtr = (AttackEquipment*)GetHeroEquipmentByIndex(hero, i);
			printf(" + %3d", GetAttackEquipmentPhysicalDamage(attackEquipmentPtr));
		}
		else
		{
			printf(" + %3d", 0);
		}
	}
	for (int j = 0; j < 3 - GetHeroEquipmentNumber(hero); j++) 
	{
		printf("      ");
	}
	printf("   │");
	if (GetHeroEquipmentNumber(hero) >= 1) 
	{
		printf("  0. %19s%s", GetEquipmentName(GetHeroEquipmentByIndex(hero, 0)), "│ ");
	}
	else 
	{
		printf("                        │ ");
	}
	printf("\n");
	printf("│  [Ability Power] %4d = %3d", GetHeroRealMagicalDamage(hero), GetHeroMagicalDamage(hero));
	for (int i = 0; i < GetHeroEquipmentNumber(hero); i++)
	{
		if (GetEquipmentType(GetHeroEquipmentByIndex(hero, i)) == attack || 
			GetEquipmentType(GetHeroEquipmentByIndex(hero, i)) == alloy)
		{
			AttackEquipment* attackEquipmentPtr = (AttackEquipment*)GetHeroEquipmentByIndex(hero, i);
			printf(" + %3d", GetAttackEquipmentMagicDamage(attackEquipmentPtr));
		}
		else
		{
			printf(" + %3d", 0);
		}
	}
	for (int j = 0; j < 3 - GetHeroEquipmentNumber(hero); j++)
	{
		printf("      ");
	}
	printf("   │");
	if (GetHeroEquipmentNumber(hero) >= 2) 
	{
		printf("  1. %19s%s", GetEquipmentName(GetHeroEquipmentByIndex(hero, 1)), "│ ");
	}
	else 
	{
		printf("                        │ ");
	}
	printf("\n");
	printf("│  [Armor]         %4d = %3d", GetHeroRealPhysicalDefense(hero), GetHeroPhysicalDefense(hero));
	for (int i = 0; i < GetHeroEquipmentNumber(hero); i++) 
	{
		if (GetEquipmentType(GetHeroEquipmentByIndex(hero, i)) == defense || 
			GetEquipmentType(GetHeroEquipmentByIndex(hero, i)) == alloy)
		{
			DefenseEquipment* defenseEquipmentPtr = (DefenseEquipment*)GetHeroEquipmentByIndex(hero, i);
			printf(" + %3d", GetDefenseEquipmentPhysical(defenseEquipmentPtr));
		}
		else
		{
			printf(" + %3d", 0);
		}
	}
	for (int j = 0; j < 3 - GetHeroEquipmentNumber(hero); j++) 
	{
		printf("      ");
	}
	printf("   │");
	if (GetHeroEquipmentNumber(hero) >= 3) 
	{
		printf("  2. %19s%s", GetEquipmentName(GetHeroEquipmentByIndex(hero, 2)), "│ ");
	}
	else 
	{
		printf("                        │ ");
	}
	printf("\n");
	printf("│  [Magic Defence] %4d = %3d", GetHeroRealMagicalDefense(hero), GetHeroMagicalDefense(hero));
	for (int i = 0; i < GetHeroEquipmentNumber(hero); i++)
	{
		if (GetEquipmentType(GetHeroEquipmentByIndex(hero, i)) == defense || 
			GetEquipmentType(GetHeroEquipmentByIndex(hero, i)) == alloy)
		{
			DefenseEquipment* defenseEquipmentPtr = (DefenseEquipment*)GetHeroEquipmentByIndex(hero, i);
			printf(" + %3d", GetDefenseEquipmentMagic(defenseEquipmentPtr));
		}
		else
		{
			printf(" + %3d", 0);
		}
	}
	for (int j = 0; j < 3 - GetHeroEquipmentNumber(hero); j++)
	{
		printf("      ");
	}
	printf("   │                        │ \n");
	printf("└─────────────────────────────────────────────────┴────────────────────────┘ ");
}

int HeroBuyEquipment(Hero* hero, Equipment* equip)
{
	if (hero->money < GetEquipmentPrice(equip))
	{
		SET_CYAN;
		PrintError(GetHeroName(hero));
		SET_WHITE;
		PrintError(" has only ");
		SET_RED;
		fprintf(stderr, "$%d", hero->money);
		SET_WHITE;
		PrintError(". Not enough to buy a ");
		SET_RED;
		fprintf(stderr, "$%d ", GetEquipmentPrice(equip));
		SET_CYAN;
		PrintError(GetEquipmentName(equip));
		SET_WHITE;
		PrintError("!\n");
		return 0;
	}
	else if (hero->equipment.length >= 3) 
	{

		SET_CYAN;
		PrintError(GetHeroName(hero));
		SET_WHITE;
		PrintError(" already has ");
		SET_RED;
		PrintError("3");
		SET_WHITE;
		PrintError(" equipments! No more!\n");
		return 0;
	}
	else 
	{
		array_add(&hero->equipment, equip);
		hero->money -= GetEquipmentPrice(equip);
		SET_CYAN;
		PrintError(GetHeroName(hero));
		SET_WHITE;
		PrintError(" bought a ");
		SET_CYAN;
		PrintError(GetEquipmentName(equip));
		SET_WHITE;
		PrintError(", spent ");
		SET_YELLOW;
		fprintf(stderr, "$%d", GetEquipmentPrice(equip));
		SET_WHITE;
		PrintError(".\n");
		return 1;
	}
}

int HeroSellEquipment(Hero* hero, int index)
{
	if (index >= 0 && index < hero->equipment.length) 
	{
		SET_CYAN;
		printf("%s", GetHeroName(hero));
		SET_WHITE;
		printf(" has sold a ");
		SET_CYAN;
		printf("%s", GetEquipmentName(GetHeroEquipmentByIndex(hero, index)));
		SET_WHITE;
		printf(", earned ");
		SET_YELLOW;
		printf("$%d", (int)(C_SELL * GetEquipmentPrice(GetHeroEquipmentByIndex(hero, index))));
		SET_WHITE;
		printf("!\n");
		hero->money += (int)(C_SELL * GetEquipmentPrice(GetHeroEquipmentByIndex(hero, index)));
		RemoveHeroEquipment(hero, index);
		return 1;
	}
	else
	{
		PrintError("Something wrong. Check again.");
		return 0;
	}
}

int HeroSynthesiEquipment(Hero* hero, int attackEquipmentIndex, int defenseEquipmentIndex)
{
	if (attackEquipmentIndex >= 0 && defenseEquipmentIndex >= 0 && attackEquipmentIndex < GetHeroEquipmentNumber(hero)
		&& defenseEquipmentIndex < GetHeroEquipmentNumber(hero) && attackEquipmentIndex != defenseEquipmentIndex)
	{
		int attackType = GetEquipmentType(GetHeroEquipmentByIndex(hero, attackEquipmentIndex));
		int defenseType = GetEquipmentType(GetHeroEquipmentByIndex(hero, defenseEquipmentIndex));
		//排除相同类型的装备		
		if (attackType == defenseType)
		{
			PrintError("No synthesizing two equipments of the same type!\n");
			return 0;
		}
		//排除合金装备
		if (attackType == alloy || defenseType == alloy)
		{
			PrintError("A Synthesis Equipment cannot be synthesized again!\n");
			return 0;
		}
		//排除第一个不是攻击，第二个不是防御的
		if (attackType != attack || defenseType != defense)
		{
			PrintError("Must be the first one is attack equipment, the second is defensive equipment!\n");
			return 0;
		}
		AttackEquipment* attackEquipmentPtr = (AttackEquipment*)(GetHeroEquipmentByIndex(hero, attackEquipmentIndex));
		DefenseEquipment* defenseEquipmentPtr = (DefenseEquipment*)(GetHeroEquipmentByIndex(hero, defenseEquipmentIndex));

	
		int needMoneyValue = (int)(0.15 * (GetEquipmentPrice(GetHeroEquipmentByIndex(hero, attackEquipmentIndex))
			+ GetEquipmentPrice(GetHeroEquipmentByIndex(hero, defenseEquipmentIndex))));
		if (GetHeroMoney(hero) >= needMoneyValue)
		{
			AlloyeEquipment* result = (AlloyeEquipment*)malloc(sizeof(AlloyeEquipment));
			if (NULL == result)
			{
				PrintError("malloc error!");
				return 0;
			}
			InitAlloyeEquipment(result, attackEquipmentPtr, defenseEquipmentPtr);
	
			SET_CYAN;
			printf("%s", GetHeroName(hero));
			SET_WHITE;
			printf(" has synthesized a ");
			SET_CYAN;
			printf("%s", GetEquipmentName((const Equipment*)attackEquipmentPtr));
			SET_WHITE;
			printf(" with a ");
			SET_CYAN;
			printf("%s", GetEquipmentName((const Equipment*)defenseEquipmentPtr));
			SET_WHITE;
			printf(" into a ");
			SET_CYAN;
			printf("%s", GetEquipmentName((const Equipment*)result));
			SET_WHITE;
			printf(". Spent ");
			SET_YELLOW;
			printf("$%d", needMoneyValue);
			SET_WHITE;
			printf(".\n");

			hero->money -= needMoneyValue;
			RemoveHeroEquipment(hero, attackEquipmentIndex);
			int newIndex = 0;
			for (int i = 0; i != hero->equipment.length; ++i)
			{
				if (strncmp(hero->equipment.data[i]->name, defenseEquipmentPtr->equipment.name, strlen(hero->equipment.data[i]->name)) == 0)
				{
					newIndex = i;
				}
			}
			RemoveHeroEquipment(hero, newIndex);
			array_add(&hero->equipment, (Equipment*const)result);
			return 1;
		}

		else 
		{
			SET_CYAN;
			PrintError(GetHeroName(hero));
			SET_WHITE;
			PrintError(" has only ");
			SET_RED;
			PrintError("$");
			fprintf(stderr, "%d", GetHeroMoney(hero));
			SET_WHITE;
			PrintError(". You need at least ");
			SET_RED;
			PrintError("$");
			fprintf(stderr, "%d", needMoneyValue);
			SET_WHITE;
			PrintError(" to synthesize a ");
			SET_CYAN;
			PrintError(GetEquipmentName((const Equipment*)attackEquipmentPtr));
			SET_WHITE;
			PrintError(" with a ");
			SET_CYAN;
			PrintError(GetEquipmentName((const Equipment*)defenseEquipmentPtr));
			SET_WHITE;
			PrintError(" ! \n");
			return 0;
		}
	}
	else 
	{
		PrintError("You are synthesize nothing! Check again!\n");
		return 0;
	}
}

int HeroAttack(Hero* me, Hero* that)
{
	int damageGiven;
	if (MYRAND < GetHeroCritChance(me))
	{
		damageGiven = Crit(me, that);
		me->money += (int)((C_RECEIVE * damageGiven) * 0.8);
		printf("CRIT!! ");
		SET_CYAN;
		printf("%s", GetHeroName(me));
		SET_WHITE;
		printf(" ATTACK %s and cause %d damage!!!\n", GetHeroName(that), damageGiven);
	}
	else 
	{
		damageGiven = NormalAttack(me, that);
		me->money += C_RECEIVE * damageGiven;
		SET_CYAN;
		printf("%s", GetHeroName(me));
		SET_WHITE;
		printf(" ATTACK %s and cause %d damage!!\n", GetHeroName(that), damageGiven);
	}
	return damageGiven;
}

int HeroRecover(Hero* hero)
{
	if (hero->money >= 200) {
		hero->money -= 200;
		hero->health += 15;
		if (hero->health > 100)
		{
			hero->health = 100;
		}
		SET_CYAN;
		printf("%s", hero->name);
		SET_WHITE;
		printf(" tries to recover and got 15HP using $200!\n");
		return 1;
	}
	else 
	{
		SET_CYAN;
		PrintError(hero->name);
		SET_WHITE;
		PrintError(" has only ");
		SET_RED;
		fprintf(stderr, "$%d", hero->money);
		SET_WHITE;
		PrintError(". Not enough to recover. Chance wasted!\n");
		return 0;
	}
}

static int RemoveHeroEquipment(Hero* hero, int index)
{
	if (index >= 0 && index < hero->equipment.length)
	{
		array_remove(&hero->equipment, index);
		return 0;
	}
	else
	{
		PrintError("REMOVE ERROR!");
	}
	return 1;
}

static int Crit(Hero* me, Hero* that)
{
	int physicalDamage = GetHeroRealPhysicalDamage(me), magicalDamage = GetHeroRealMagicalDamage(me);
	int physicalDefense = GetHeroRealPhysicalDefense(that), MagicalDefense = GetHeroRealMagicalDefense(that);
	int physicalAttack = (int)((1 - physicalDefense / (physicalDefense + C_IMMUNE)) * physicalDamage);
	int magicalAttack = (int)((1 - (double)(MagicalDefense) / (MagicalDefense + C_IMMUNE)) * magicalDamage);
	int damageGiven = DamageTaken(that, (int)(C_CRIT * (physicalAttack + magicalAttack) / 2));
	return damageGiven;
}

static int NormalAttack(Hero* me, Hero* that)
{
	int physicalDamage = GetHeroRealPhysicalDamage(me), magicalDamage = GetHeroRealMagicalDamage(me);
	int physicalDefense = GetHeroRealPhysicalDefense(that), MagicalDefense = GetHeroRealMagicalDefense(that);
	int physicalAttack = (int)((1 - (double)(physicalDefense) / (physicalDefense + C_IMMUNE)) * physicalDamage);
	int magicalAttack = (int)(((1 - (double)(MagicalDefense) / (MagicalDefense + C_IMMUNE)) * magicalDamage));
	int damageGiven = DamageTaken(that, (physicalAttack + magicalAttack) / 2);
	return damageGiven;
}

static int DamageTaken(Hero* me, int damageValue)
{
	int temp = GetHeroHealth(me);
	if (temp > damageValue) 
	{
		me->health -= damageValue;
	}
	else 
	{
		me->health = 0;
	}
	return temp - GetHeroHealth(me);
}
