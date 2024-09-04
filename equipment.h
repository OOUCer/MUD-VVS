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
	Equipment(string name, int price);

	string getName() const;
	int getPrice() const;

	//virtual string getDescription() const =0;
	//virtual void describe() const =0;
	//virtual string getAttackType() const=0;
	//virtual string getWeakness() const=0;
	//virtual int getAttack() const=0;
	//virtual int getSpeed() const=0;
	//virtual float getHitRate() const=0;
	//virtual int getDefense() const=0;
	//virtual int getHP() const=0;
	
};

class Weapon : public Equipment
{
private:
	int attack;
	int speed;
	float hitRate;
	string attackType;

public:
	Weapon(string name, int price, int attack, int speed, float hitRate, string attackType);
	int getAttack() const ;
	int getSpeed() const ;
	float getHitRate() const ;
	string getAttackType() const ;
	string getDescription() const ;
	void describe() const ;


	//virtual string getWeakness() const;
	//virtual int getDefense() const;
	//virtual int getHP() const;
};

class Armor : public Equipment
{
private:
	int defense;
	int HP;
	string weakness;

public:
	Armor(string name, int price, int defense, int HP, string weakness);
	int getDefense() const ;
	int getHP() const  ;
	string getWeakness() const ;
	string getDescription() const ;
	void describe() const ;


	//virtual int getAttack() const;
	//virtual int getSpeed() const;
	//virtual float getHitRate() const;
	//virtual string getAttackType() const;
};

#endif