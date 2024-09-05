#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <iostream>


using namespace std;


class Equipment
{
protected:
	string name;
	int price;

public:
	Equipment();
	Equipment(string name, int price);// 构造函数，用于初始化装备的名称和价格

	string getName() const;// 获取装备的名称 
	int getPrice() const;// 获取装备的价格  

	
};

class Weapon : public Equipment
{
private:
	int attack;
	int speed;
	float hitRate;
	string attackType;

public:
	Weapon();
	Weapon(string name, int price, int attack, int speed, float hitRate, string attackType);// 构造函数，用于初始化武器的所有属性
	int getAttack() const ;// 获取武器的攻击力
	int getSpeed() const ;// 获取武器的攻击速度  
	float getHitRate() const ; // 获取武器的命中率 
	string getAttackType() const ;// 获取武器的攻击类型
	string getDescription() const ;// 获取武器的详细描述字符串  
	void describe() const ;// 打印武器的详细描述

};

class Armor : public Equipment
{
private:
	int defense;
	int HP;
	string weakness;

public:
	Armor();
	Armor(string name, int price, int defense, int HP, string weakness);// 构造函数，用于初始化护甲的所有属性
	int getDefense() const ;// 获取护甲的防御力 
	int getHP() const  ;// 获取护甲提供的额外生命值
	string getWeakness() const ;// 获取护甲的弱点
	string getDescription() const ;// 获取护甲的详细描述字符串
	void describe() const ;// 打印护甲的详细描述

};

#endif