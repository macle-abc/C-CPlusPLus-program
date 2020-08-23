#include "HeroWorld.h"

#define CreateAttackEquipment(valName, equipmentName, price, physicalDamage, magicalDamage) \
	AttackEquipment* valName = (AttackEquipment*)malloc(sizeof(AttackEquipment)); \
	if (valName == NULL) \
	{\
		PrintError("malloc error!");\
	}\
	InitAttackEquipment(valName, equipmentName, price, physicalDamage, magicalDamage)

#define CreateDefenseEquipment(valName, equipmentName, price, physicalDefense, magicalDefense) \
	DefenseEquipment* valName = (DefenseEquipment*)malloc(sizeof(DefenseEquipment)); \
	if (valName == NULL) \
	{\
		PrintError("malloc error!");\
	}\
	InitDefenseEquipment(valName, equipmentName, price, physicalDefense,  magicalDefense)

void InitHeroWorld(HeroWorld* heroWorld, const char* playerName, const char* enemyName)
{

	InitHero(&heroWorld->player, playerName, 800, 100, 10, 10, 10, 10);
	InitHero(&heroWorld->enemy, enemyName, 800, 100, 10, 10, 10, 10);
	heroWorld->gameNumber = 0;
	heroWorld->roundNumber = 0;
	heroWorld->score = 0;
	heroWorld->inventory = new_array(0);
	CreateAttackEquipment(knife, "Knife", 400, 20, 0);
	CreateAttackEquipment(sword, "Sword", 650, 40, 25);
	CreateAttackEquipment(poison, "Poison", 1000, 30, 50);
	CreateAttackEquipment(ak47, "AK47", 1400, 90, 10);
	CreateDefenseEquipment(vest, "Vest", 500, 30, 20);
	CreateDefenseEquipment(shield, "Shield", 800, 40, 10);
	CreateDefenseEquipment(immunity, "Immunity", 1200, 50, 50);
	CreateDefenseEquipment(mageticField, "Magnetic Field", 1500, 80, 20);
	void* arr[] = { knife, sword, poison, ak47, vest, shield, immunity, mageticField };
	for (unsigned i = 0; i != sizeof(arr) / sizeof(Equipment*); ++i)
	{
		array_add(&heroWorld->inventory, (Equipment*)arr[i]);
	}
}

void DestroyHeroWorld(HeroWorld* heroWorld)
{
	while (heroWorld->inventory.length)
	{
		void * temp = heroWorld->inventory.data[heroWorld->inventory.length - 1];
		free(temp);
		temp = NULL;
		array_remove(&heroWorld->inventory, heroWorld->inventory.length - 1);
	}
	delete_array(&heroWorld->inventory);
	DestroyHero(&heroWorld->player);
	DestroyHero(&heroWorld->enemy);
}

void SaveHeroWorld(const HeroWorld* heroWorld)
{
	char buff[101] = { 0 };
	strncpy(buff, GetHeroName(&heroWorld->player), 100);
	strncat(buff, ".txt", 100 - strlen(GetHeroName(&heroWorld->player)));
	FILE* fp = fopen(buff, "r");
	if (fp != NULL)
	{
		fclose(fp);
		printf("The hero is already archived, is it overwritten?[Y/N]\n");
		char choose = 0;
		scanf(" %c", &choose);
		if (choose == 'n' || choose == 'N')
		{
			printf("Undo!\n");
			return;
		}
		else
		{
			fp = fopen(buff, "w");
			if (fp == NULL)
			{
				PrintError("Save Error\n");
				return;
			}
			fprintf(fp, "%d %d %d\n\n", heroWorld->gameNumber, heroWorld->roundNumber, heroWorld->score);
			fputs(GetHeroName(&heroWorld->player), fp);
			fprintf(fp, " %d %d %d %d %d %d\n", heroWorld->player.health, heroWorld->player.physicalDamage,
				heroWorld->player.magicalDamage, heroWorld->player.money,
				heroWorld->player.physicalDefense, heroWorld->player.magicalDefense);
			fprintf(fp, "@[Equip]@Start\n");
			for (int i = 0; i != heroWorld->player.equipment.length; ++i)
			{
				int type = GetEquipmentType(heroWorld->player.equipment.data[i]);
				void* equipment = heroWorld->player.equipment.data[i];
				AttackEquipment* attackEquipmentPtr = (AttackEquipment*)equipment;
				DefenseEquipment* defenseEquipmentPtr = (DefenseEquipment*)equipment;
				AlloyeEquipment* alloyeEquipmetPtr = (AlloyeEquipment*)equipment;
				switch (type)
				{
				case attack:
					fprintf(fp, "$-----$\n");
					fprintf(fp, "%d %s\n", attack, attackEquipmentPtr->equipment.name);
					fprintf(fp, "%d %d %d %d\n", attackEquipmentPtr->equipment.price, attackEquipmentPtr->equipment.type,
						attackEquipmentPtr->physicalDamage, attackEquipmentPtr->magicDamage);
					break;
				case defense:
					fprintf(fp, "$-----$\n");
					fprintf(fp, "%d %s\n", defense, defenseEquipmentPtr->equipment.name);
					fprintf(fp, "%d %d %d %d\n", defenseEquipmentPtr->equipment.price, defenseEquipmentPtr->equipment.type,
						defenseEquipmentPtr->physicalDefense, defenseEquipmentPtr->magicDefense);
					break;
				case alloy:
					fprintf(fp, "$-----$\n");
					fprintf(fp, "%d %s\n", alloy, alloyeEquipmetPtr->attackEquipment.equipment.name);
					fprintf(fp, "%d %d %d %d %d %d\n", alloyeEquipmetPtr->attackEquipment.equipment.price, alloyeEquipmetPtr->attackEquipment.equipment.type,
						alloyeEquipmetPtr->attackEquipment.physicalDamage, alloyeEquipmetPtr->attackEquipment.magicDamage,
						alloyeEquipmetPtr->defenseEquipment.physicalDefense, alloyeEquipmetPtr->defenseEquipment.magicDefense);
					break;
				default:
					break;
				}
			}
			if (!heroWorld->player.equipment.length)
			{
				fprintf(fp, "%d", -1);
			}
			fprintf(fp, "@[Equip]@End\n");
			//记录敌人
			fprintf(fp, "&enemy&\n");
			fputs(GetHeroName(&heroWorld->enemy), fp);
			fprintf(fp, " %d %d %d %d %d %d\n", heroWorld->enemy.health, heroWorld->enemy.physicalDamage,
				heroWorld->enemy.magicalDamage, heroWorld->enemy.money,
				heroWorld->enemy.physicalDefense, heroWorld->enemy.magicalDefense);
			fprintf(fp, "@[Equip]@Start\n");
			for (int i = 0; i != heroWorld->enemy.equipment.length; ++i)
			{
				int type = GetEquipmentType(heroWorld->enemy.equipment.data[i]);
				void* equipment = heroWorld->enemy.equipment.data[i];
				AttackEquipment* attackEquipmentPtr = (AttackEquipment*)equipment;
				DefenseEquipment* defenseEquipmentPtr = (DefenseEquipment*)equipment;
				AlloyeEquipment* alloyeEquipmetPtr = (AlloyeEquipment*)equipment;
				switch (type)
				{
				case attack:
					fprintf(fp, "$-----$\n");
					fprintf(fp, "%d %s\n", attack, attackEquipmentPtr->equipment.name);
					fprintf(fp, "%d %d %d %d\n", attackEquipmentPtr->equipment.price, attackEquipmentPtr->equipment.type,
						attackEquipmentPtr->physicalDamage, attackEquipmentPtr->magicDamage);
					break;
				case defense:
					fprintf(fp, "$-----$\n");
					fprintf(fp, "%d %s\n", defense, defenseEquipmentPtr->equipment.name);
					fprintf(fp, "%d %d %d %d\n", defenseEquipmentPtr->equipment.price, defenseEquipmentPtr->equipment.type,
						defenseEquipmentPtr->physicalDefense, defenseEquipmentPtr->magicDefense);
					break;
				case alloy:
					fprintf(fp, "$-----$\n");
					fprintf(fp, "%d %s\n", alloy, alloyeEquipmetPtr->attackEquipment.equipment.name);
					fprintf(fp, "%d %d %d %d %d %d\n", alloyeEquipmetPtr->attackEquipment.equipment.price, alloyeEquipmetPtr->attackEquipment.equipment.type,
						alloyeEquipmetPtr->attackEquipment.physicalDamage, alloyeEquipmetPtr->attackEquipment.magicDamage,
						alloyeEquipmetPtr->defenseEquipment.physicalDefense, alloyeEquipmetPtr->defenseEquipment.magicDefense);
					break;
				default:
					break;
				}
			}
			if (!heroWorld->enemy.equipment.length)
			{
				fprintf(fp, "%d", -1);
			}
			fprintf(fp, "@[Equip]@End\n");

			fclose(fp);
			fp = NULL;
			printf("Save Ok!\n");
		}
	}
	else
	{
		fp = fopen(buff, "w");
		if (fp == NULL)
		{
			PrintError("Save Error\n");
			return;
		}
		fprintf(fp, "%d %d %d\n\n", heroWorld->gameNumber, heroWorld->roundNumber, heroWorld->score);
		fputs(GetHeroName(&heroWorld->player), fp);
		fprintf(fp, " %d %d %d %d %d %d\n", heroWorld->player.health, heroWorld->player.physicalDamage,
			heroWorld->player.magicalDamage, heroWorld->player.money,
			heroWorld->player.physicalDefense, heroWorld->player.magicalDefense);
		fprintf(fp, "@[Equip]@Start\n");
		for (int i = 0; i != heroWorld->player.equipment.length; ++i)
		{
			int type = GetEquipmentType(heroWorld->player.equipment.data[i]);
			void* equipment = heroWorld->player.equipment.data[i];
			AttackEquipment* attackEquipmentPtr = (AttackEquipment*)equipment;
			DefenseEquipment* defenseEquipmentPtr = (DefenseEquipment*)equipment;
			AlloyeEquipment* alloyeEquipmetPtr = (AlloyeEquipment*)equipment;
			switch (type)
			{
			case attack:
				fprintf(fp, "$-----$\n");
				fprintf(fp, "%d %s\n", attack, attackEquipmentPtr->equipment.name);
				fprintf(fp, "%d %d %d %d\n", attackEquipmentPtr->equipment.price, attackEquipmentPtr->equipment.type,
					attackEquipmentPtr->physicalDamage, attackEquipmentPtr->magicDamage);
				break;
			case defense:
				fprintf(fp, "$-----$\n");
				fprintf(fp, "%d %s\n", defense, defenseEquipmentPtr->equipment.name);
				fprintf(fp, "%d %d %d %d\n", defenseEquipmentPtr->equipment.price, defenseEquipmentPtr->equipment.type,
					defenseEquipmentPtr->physicalDefense, defenseEquipmentPtr->magicDefense);
				break;
			case alloy:
				fprintf(fp, "$-----$\n");
				fprintf(fp, "%d %s\n", alloy, alloyeEquipmetPtr->attackEquipment.equipment.name);
				fprintf(fp, "%d %d %d %d %d %d\n", alloyeEquipmetPtr->attackEquipment.equipment.price, alloyeEquipmetPtr->attackEquipment.equipment.type,
					alloyeEquipmetPtr->attackEquipment.physicalDamage, alloyeEquipmetPtr->attackEquipment.magicDamage,
					alloyeEquipmetPtr->defenseEquipment.physicalDefense, alloyeEquipmetPtr->defenseEquipment.magicDefense);
				break;
			default:
				break;
			}
		}
		if (!heroWorld->player.equipment.length)
		{
			fprintf(fp, "%d", -1);
		}
		fprintf(fp, "@[Equip]@End\n");
		//记录敌人
		fprintf(fp, "&enemy&\n");
		fputs(GetHeroName(&heroWorld->enemy), fp);
		fprintf(fp, " %d %d %d %d %d %d\n", heroWorld->enemy.health, heroWorld->enemy.physicalDamage,
			heroWorld->enemy.magicalDamage, heroWorld->enemy.money,
			heroWorld->enemy.physicalDefense, heroWorld->enemy.magicalDefense);
		fprintf(fp, "@[Equip]@Start\n");
		
		for (int i = 0; i != heroWorld->enemy.equipment.length; ++i)
		{
			int type = GetEquipmentType(heroWorld->enemy.equipment.data[i]);
			void* equipment = heroWorld->enemy.equipment.data[i];
			AttackEquipment* attackEquipmentPtr = (AttackEquipment*)equipment;
			DefenseEquipment* defenseEquipmentPtr = (DefenseEquipment*)equipment;
			AlloyeEquipment* alloyeEquipmetPtr = (AlloyeEquipment*)equipment;
			switch (type)
			{
			case attack:
			
				fprintf(fp, "$-----$\n");
				fprintf(fp, "%d %s\n", attack, attackEquipmentPtr->equipment.name);
				fprintf(fp, "%d %d %d %d\n", attackEquipmentPtr->equipment.price, attackEquipmentPtr->equipment.type,
					attackEquipmentPtr->physicalDamage, attackEquipmentPtr->magicDamage);
				break;
			case defense:
				fprintf(fp, "$-----$\n");
				fprintf(fp, "%d %s\n", defense, defenseEquipmentPtr->equipment.name);
				fprintf(fp, "%d %d %d %d\n", defenseEquipmentPtr->equipment.price, defenseEquipmentPtr->equipment.type,
					defenseEquipmentPtr->physicalDefense, defenseEquipmentPtr->magicDefense);
				break;
			case alloy:
			
				fprintf(fp, "$-----$\n");
				fprintf(fp, "%d %s\n", alloy, alloyeEquipmetPtr->attackEquipment.equipment.name);
				fprintf(fp, "%d %d %d %d %d %d\n", alloyeEquipmetPtr->attackEquipment.equipment.price, alloyeEquipmetPtr->attackEquipment.equipment.type,
					alloyeEquipmetPtr->attackEquipment.physicalDamage, alloyeEquipmetPtr->attackEquipment.magicDamage,
					alloyeEquipmetPtr->defenseEquipment.physicalDefense, alloyeEquipmetPtr->defenseEquipment.magicDefense);
				break;
			default:
				break;
			}
		}
		if (!heroWorld->enemy.equipment.length)
		{
			fprintf(fp, "%d", -1);
		}
		fprintf(fp, "@[Equip]@End\n");

		fclose(fp);
		fp = NULL;
		printf("Save Ok!\n");
	}
}

void LoadHeroWorld(HeroWorld* heroWorld)
{
	char buff[101] = { 0 };
	strncpy(buff, GetHeroName(&heroWorld->player), 100);
	strncat(buff, ".txt", 100 - strlen(GetHeroName(&heroWorld->player)));
	FILE* fp = fopen(buff, "r");
	if (fp == NULL)
	{
		PrintError("Load Error\n");
		return;
	}
	fscanf(fp, "%d %d %d", &heroWorld->gameNumber, &heroWorld->roundNumber, &heroWorld->score);
	fgets(buff, 80, fp);
	fgets(buff, 80, fp);

	fscanf(fp, "%s %d %d %d %d %d %d", heroWorld->player.name, &heroWorld->player.health, &heroWorld->player.physicalDamage,
		&heroWorld->player.magicalDamage, &heroWorld->player.money,
		&heroWorld->player.physicalDefense, &heroWorld->player.magicalDefense);

	fgets(buff, 80, fp);
	fgets(buff, 80, fp);

		//开始装备
	AttackEquipment* attackEquipment = NULL; 
	DefenseEquipment* defenseEquipment = NULL; 
	AlloyeEquipment* alloyeEquipment = NULL; 
	int type = -1;
	while (1)
	{	
		fscanf(fp, "%s", buff);
		if (strncmp(buff, "@[Equip]@End", 80) == 0)
			break;
		fscanf(fp, "%d", &type);
		switch (type)
		{
		case attack:
			attackEquipment = (AttackEquipment*)malloc(sizeof(AttackEquipment));
			InitAttackEquipment(attackEquipment, "", 0, 0, 0);
			fscanf(fp, "%s", attackEquipment->equipment.name);
			fscanf(fp, "%d %d %d %d", &attackEquipment->equipment.price, &attackEquipment->equipment.type,
				&attackEquipment->physicalDamage, &attackEquipment->magicDamage);

			array_add(&heroWorld->player.equipment, attackEquipment);
			break;
		case defense:
			defenseEquipment = (DefenseEquipment*)malloc(sizeof(DefenseEquipment));
			InitDefenseEquipment(defenseEquipment, "", 0, 0, 0);
			fscanf(fp, "%s", defenseEquipment->equipment.name);
			fscanf(fp, "%d %d %d %d", &defenseEquipment->equipment.price, &defenseEquipment->equipment.type,
				&defenseEquipment->physicalDefense, &defenseEquipment->magicDefense);

			array_add(&heroWorld->player.equipment, defenseEquipment);
			break;
		case alloy:
			alloyeEquipment = (AlloyeEquipment*)malloc(sizeof(AlloyeEquipment));
			AttackEquipment tempa;
			InitAttackEquipment(&tempa, "", 0, 0, 0);
			DefenseEquipment tempd;
			InitDefenseEquipment(&tempd, "", 0, 0, 0);
			InitAlloyeEquipment(alloyeEquipment, &tempa, &tempd);
			fscanf(fp, "%s", alloyeEquipment->attackEquipment.equipment.name);
			fscanf(fp, "%d %d %d %d %d %d\n", &alloyeEquipment->attackEquipment.equipment.price, &alloyeEquipment->attackEquipment.equipment.type,
				&alloyeEquipment->attackEquipment.physicalDamage, &alloyeEquipment->attackEquipment.magicDamage,
				&alloyeEquipment->defenseEquipment.physicalDefense, &alloyeEquipment->defenseEquipment.magicDefense);
			array_add(&heroWorld->player.equipment, alloyeEquipment);
			break;
		default:
			break;
		}
		if (type == -1)
			break;
		else
			continue;
	}
	fgets(buff, 80, fp);
	//读取敌人

	fgets(buff, 80, fp);

	fscanf(fp, "%s %d %d %d %d %d %d", heroWorld->enemy.name, &heroWorld->enemy.health, &heroWorld->enemy.physicalDamage,
		&heroWorld->enemy.magicalDamage, &heroWorld->enemy.money,
		&heroWorld->enemy.physicalDefense, &heroWorld->enemy.magicalDefense);

	fgets(buff, 80, fp);
	fgets(buff, 80, fp);

		//开始装备
	AttackEquipment* attackEquipmentEnemy = NULL; 
	DefenseEquipment* defenseEquipmentEnemy = NULL; 
	AlloyeEquipment* alloyeEquipmentEnemy = NULL; 
	int typeEnemy = -1;
	while (1)
	{

		fscanf(fp, "%s", buff);	
		if (strncmp(buff, "@[Equip]@End", 80) == 0)
			break;
//		fgets(buff, 80, fp);
		fscanf(fp, "%d", &typeEnemy);
		switch (typeEnemy)
		{
		case attack:
			attackEquipmentEnemy = (AttackEquipment*)malloc(sizeof(AttackEquipment));
			InitAttackEquipment(attackEquipmentEnemy, "", 0, 0, 0);
			fscanf(fp, "%s", attackEquipmentEnemy->equipment.name);
			fscanf(fp, "%d %d %d %d", &attackEquipmentEnemy->equipment.price, &attackEquipmentEnemy->equipment.type,
				&attackEquipmentEnemy->physicalDamage, &attackEquipmentEnemy->magicDamage);

			array_add(&heroWorld->enemy.equipment, attackEquipmentEnemy);
			break;
		case defense:
			defenseEquipmentEnemy = (DefenseEquipment*)malloc(sizeof(DefenseEquipment));
			InitDefenseEquipment(defenseEquipmentEnemy, "", 0, 0, 0);
			fscanf(fp, "%s", defenseEquipmentEnemy->equipment.name);
			fscanf(fp, "%d %d %d %d", &defenseEquipmentEnemy->equipment.price, &defenseEquipmentEnemy->equipment.type,
				&defenseEquipmentEnemy->physicalDefense, &defenseEquipmentEnemy->magicDefense);

			array_add(&heroWorld->enemy.equipment, defenseEquipmentEnemy);
			break;
		case alloy:
			alloyeEquipmentEnemy = (AlloyeEquipment*)malloc(sizeof(AlloyeEquipment));
			InitAlloyeEquipment(alloyeEquipmentEnemy, attackEquipmentEnemy, defenseEquipmentEnemy);
			fscanf(fp, "%s", alloyeEquipmentEnemy->attackEquipment.equipment.name);
			fscanf(fp, "%d %d %d %d %d %d\n", &alloyeEquipmentEnemy->attackEquipment.equipment.price, &alloyeEquipmentEnemy->attackEquipment.equipment.type,
				&alloyeEquipmentEnemy->attackEquipment.physicalDamage, &alloyeEquipmentEnemy->attackEquipment.magicDamage,
				&alloyeEquipmentEnemy->defenseEquipment.physicalDefense, &alloyeEquipmentEnemy->defenseEquipment.magicDefense);
			array_add(&heroWorld->enemy.equipment, alloyeEquipmentEnemy);
			break;
		default:
			break;
		}
		if (typeEnemy == -1)
			break;
		else
			continue;
	}
	fgets(buff, 80, fp);
//	fprintf(fp, "@[Equip]@End\n");

	fclose(fp);
	fp = NULL;
	printf("Load Success!");
	Sleep(1000);
}

int GetHeroWorldGameNumber(const HeroWorld* heroWorld)
{
	return heroWorld->gameNumber;
}

int GetHeroWorldRoundNumber(const HeroWorld* heroWorld)
{
	return heroWorld->roundNumber;
}

int GetHeroWorldScore(const HeroWorld* heroWorld)
{
	return heroWorld->score;
}

Equipment* GetHeroWorldInventory(const HeroWorld* heroWorld, int index)
{
	if (index >= 0 && index < heroWorld->inventory.length)
	{
		return heroWorld->inventory.data[index];
	}
	else
	{
		return NULL;
	}
}

void PrintHeroWorldInventory(const HeroWorld* heroWorld)
{
	printf(
		"┌─────────────────────────────────────┐ \n"
		"│         ***  INVENTORY  ***         │ \n"
		"├────┬────────────────────┬───────────┤ \n"
		"│ No │ Equipment          │ Price     │ \n");
	int j = 0;
	for (int i = 0; i != heroWorld->inventory.length; ++i, ++j)
	{
		printf("│ %-3d", j);
		printf("│ %19s│ ", GetEquipmentName(heroWorld->inventory.data[i]));
		if (GetEquipmentPrice(heroWorld->inventory.data[i]) <= GetHeroMoney(&heroWorld->player))
		{
			SET_GREEN;
		}
		else
		{
			SET_RED;
		}
		printf("$%4d", GetEquipmentPrice(heroWorld->inventory.data[i]));
		SET_WHITE;
		printf("     │ \n");
	}
	printf("└────┴────────────────────┴───────────┘ \n\n");
}

void PrintHeroWorldFinal(HeroWorld* heroWorld)
{
	system("cls");
	SET_CYAN;
	printf("%s\n\n", GetHeroName(&heroWorld->player));
	SET_WHITE;
	printf("You have played %d games.\n\n", heroWorld->gameNumber);
	printf("Your final score: ");
	SET_GREEN;
	printf("%d", heroWorld->score);
	SET_WHITE;
	printf("\nPress [ ANY KEY ] to go back to main menu.\n\n");
}

int HeroWorldRoundLoop(HeroWorld* heroWorld)
{
	while (1)
	{
		heroWorld->roundNumber++;
		system("cls");	// Clear screen.
		PrintXY(43, 0, "★★★ Game ");
		printf("%d * Round %d ★★★", heroWorld->gameNumber, heroWorld->roundNumber);
		PrintXY(74, 0, "Score: ");
		printf("%d\n", heroWorld->score);
		PrintHeroInfo(&heroWorld->player);
		printf("\n");
		PrintHeroInfo(&heroWorld->enemy);
		printf("\n");
		int damage = 0;
		int isOk = 0;

		while (1)
		{
			printf("Round %d: ", heroWorld->roundNumber);
			printf("It's your turn. [ A ] Attack, [ R ] Recover, [ B ] Buy, [ S ] Sell. [ Y ] Synthesize. [Space] Save.\n\n");
			char action = _getch();
			if (action == ' ')
			{
				SaveHeroWorld(heroWorld);
				continue;
			}
			else if (action == 'a' || action == 'A') 
			{
				damage = HeroAttack(&heroWorld->player, &heroWorld->enemy);
				heroWorld->score += damage;
				break;
			}
			else if (action == 'r' || action == 'R') 
			{
				isOk =	HeroRecover(&heroWorld->player);
				break;
			}
			else if (action == 'b' || action == 'B') 
			{
				PrintHeroWorldInventory(heroWorld);
				printf("You have ");
				SET_GREEN;
				printf("$%d", GetHeroMoney(&heroWorld->player));
				SET_WHITE;
				printf(". Enter the number of the equipment you want to buy and hit [ ENTER ].\n");
				int buy = 0;
			
				while (scanf("%d", &buy) != 1 || buy < 0 || buy >= heroWorld->inventory.length)
				{
					while (getchar() != '\n')
					{
					
					}
					SET_RED;
					printf("Illeagle input!");
					SET_WHITE;
					printf("You have ");
					SET_GREEN;
					printf("$%d", GetHeroMoney(&heroWorld->player));
					SET_WHITE;
					printf(". Enter the number of the equipment you want to buy and hit [ ENTER ].\n");
				}
				printf("\n");
				if (HeroBuyEquipment(&heroWorld->player, GetHeroWorldInventory(heroWorld, buy)))
				{
					break;
				}
				else 
				{
					continue;
				}
			}
	
			else if (action == 'y' || action == 'Y') 
			{
				if (GetHeroEquipmentNumber(&heroWorld->player) >= 2)
				{
					printf("Which two equipments do you want to synthesize? Enter two numbers(First Attack Equipment, Then Defense Equipment), separated by a space.\n");
					int syn1 = 0, syn2 = 0;
					scanf("%d%d", &syn1, &syn2);
					HeroSynthesiEquipment(&heroWorld->player, syn1, syn2);
					break;
				}
				else 
				{
					SET_RED;
					printf("Failed! ");
					SET_WHITE;
					printf("You need at least 2 equipments to synthesize!\n");
					continue;
				}
			}
			else if (action == 's' || action == 'S') 
			{
				if (GetHeroEquipmentNumber(&heroWorld->player))
				{
					printf("What do you want to sell? Enter a number of your equipment.\n");
					int sell = -1;
					scanf("%d", &sell);
					if (sell == -1)
					{
						while (getchar() != '\n')
						{

						}
					}
					HeroSellEquipment(&heroWorld->player, sell);
					break;
				}
				else
				{
					SET_RED;
					printf("Failed! ");
					SET_WHITE;
					printf("You don't have any equipment to sell!\n");
					continue;
				}
			}
			else 
			{
				continue;
			}
		}
		heroWorld->score += 100;
		Sleep(500);

		if (!HeroIsAlive(&heroWorld->enemy))
		{ 
			SET_GREEN;
			printf("\nYou win!\n");
			SET_WHITE;
			return 1;
		}

		while (1)
		{
			if (GetHeroHealth(&heroWorld->enemy) < 40)
			{
				if (MYRAND < 0.7 &&  GetHeroMoney(&heroWorld->enemy) >= 200)
				{
					HeroRecover(&heroWorld->enemy);
				}
				else 
				{
					HeroAttack(&heroWorld->enemy, &heroWorld->player);
				}
				break;
			}
			else
			{
				damage = HeroAttack(&heroWorld->enemy, &heroWorld->player);
				break;
			}
			
		}	
		Sleep(500);


		if (!HeroIsAlive(&heroWorld->player))
		{
			system("color 4F");
			for (int i = 0; i < 5; i++)
			{
				Sleep(75);
				system("color F");
				Sleep(75);
				system("color 4F");
			}
			Sleep(800);
			system("color");
			SET_YELLOW;
			printf("\nYou die!\n");
			SET_WHITE;
			return 0;
		}
		printf("\nPress [ ANY KEY ] to continue the next round...\n");
		_getch();
		Sleep(1000);
	}
}

void HeroWorldGameLoop(HeroWorld* heroWorld)
{
	int status = 0;
	while (1)
	{
		heroWorld->roundNumber = 0;
		heroWorld->gameNumber++;
		for (int i = 3; i >= 1; i--)
		{
			system("cls");
			PrintXY(0, 10, "              Okay, ");
			SET_CYAN;
			printf("%s", GetHeroName(&heroWorld->player));
			SET_WHITE;
			printf(", get ready.\n\n");
			printf("              GAME %d%s%d%s\n", heroWorld->gameNumber, " will start in ", i, " seconds.");
			Sleep(1000);
		}
		status = HeroWorldRoundLoop(heroWorld);
		if (status)
		{
			printf("ANOTHER GAME? (Y/N)\n");
			char another = _getch();
			printf("%c", another);
			if (another == 'n' || another == 'N')
			{
				break;
			}
			else 
			{
				int playerMoney = GetHeroMoney(&heroWorld->player);
				int newMoney = 0;
				if (playerMoney < 300)
				{
					newMoney = 800;
				}
				else
				{ 
					newMoney = playerMoney + 500;
				}
				ResetHero(&heroWorld->player, GetHeroName(&heroWorld->player), newMoney, 0, NULL);
				extern const char* enemyNameArr[5];
				ResetHero(&heroWorld->enemy, enemyNameArr[(int)(5 * MYRAND)], 800 + 200 * heroWorld->gameNumber, 1, 
					GetHeroWorldInventory(heroWorld, heroWorld->gameNumber % heroWorld->inventory.length));
				continue;
			}
		}
		else
		{
			printf("Press [ ANY KEY ] to see your score.\n");
			_getch();
			system("color F");
			break;
		}
	}	
	heroWorld->score += 200 * GetHeroWorldGameNumber(heroWorld);
	PrintHeroWorldFinal(heroWorld);
	DestroyHeroWorld(heroWorld);
	_getch();
	PrintBye();
}
