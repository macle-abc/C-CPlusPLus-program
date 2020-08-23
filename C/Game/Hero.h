#ifndef HERO_H_
#define HERO_H_

#include "AlloyEquipment.h"
#define type Equipment*
#include "array.h"

//英雄结构
typedef struct Hero
{
	char name[81];
	int health;
	int physicalDamage;
	int magicalDamage;
	int money;
	int physicalDefense;
	int magicalDefense;
	array equipment;
}Hero;


/**初始化英雄
 *

 * 用于初始化英雄

 * @param [in] 
	hero		英雄结构地址
	name		英雄名
	money		金钱
	health		健康值
	physicalDamage	物理攻击
	magicalDamage	魔法攻击
	physicalDefense	物理防御
	magicalDefense	魔法防御

 * @param [out] 
	空

 * @return 
	空

 * @note   

*/
void InitHero(Hero* hero,
	const char* name, int money, int health,
	int physicalDamage, int magicalDamage,
	int physicalDefense, int magicalDefense);

/**重新建立英雄

 *

 * 重新建立英雄信息

 * @param [in]
	hero		英雄结构
	name		新的名字
	money		金钱
	reset_equip	是否重建装备
	equip		重建装备的地址结构

 * @param [out] 
	空

 * @return 
	空

 * @note   

*/
void ResetHero(Hero* hero, const char* name, int money,	int reset_equip, Equipment* equip);
void DestroyHero(Hero* hero);

const char* GetHeroName(const Hero* hero);
int GetHeroHealth(const Hero* hero);
int GetHeroPhysicalDamage(const Hero* hero);
int GetHeroMagicalDamage(const Hero* hero);
int GetHeroPhysicalDefense(const Hero* hero);
int GetHeroMagicalDefense(const Hero* hero);
int GetHeroEquipmentNumber(const Hero* hero); 
int GetHeroMoney(const Hero* hero);
Equipment* GetHeroEquipmentByIndex(const Hero* hero, int index);
int GetHeroRealPhysicalDamage(const Hero* hero);
int GetHeroRealMagicalDamage(const Hero* hero);
int GetHeroRealPhysicalDefense(const Hero* hero);
int GetHeroRealMagicalDefense(const Hero* hero);
double GetHeroCritChance(const Hero* hero);

//判断英雄是否存活
int HeroIsAlive(const Hero* hero);

void PrintHeroInfo(const Hero* hero);

int HeroBuyEquipment(Hero* hero, Equipment* equip);

int HeroSellEquipment(Hero* hero, int index);


/**合成新装备

 *

 * 根据攻击装备和防御装备合成

 * @param [in] 
	hero					英雄结构
	attackEquipmentIndex	攻击装备下标
	defenseEquipmentIndex	防御装备下标


 * @param [out]
	int

 * @return 
	成功返回1，失败返回0

 * @note   
	两个下标必须严格对应装备类型

*/
int HeroSynthesiEquipment(Hero* hero, int attackEquipmentIndex, int defenseEquipmentIndex);


int HeroAttack(Hero* me, Hero* that);
int HeroRecover(Hero* hero);

#endif