#include "equipment.h"

using namespace std;

Equipment::Equipment(string name, int price) : name(name), price(price) {}

string Equipment::getName() const { return name; }

int Equipment::getPrice() const { return price; }

//void Equipment::describe() const
//{
//	cout << "Name: " << name << ", Price: " << price << endl;
//}

Weapon::Weapon(string name, int price, int attack, int speed, float hitRate, string attackType)
	: Equipment(name, price), attack(attack), speed(speed), hitRate(hitRate), attackType(attackType) {}

int Weapon::getAttack() const { return attack; }

int Weapon::getSpeed() const { return speed; }

float Weapon::getHitRate() const { return hitRate; }

string Weapon::getAttackType() const { return attackType; }

string Weapon::getDescription() const
{
	return "该武器攻击加成: " + to_string(attack) + " 命中加成: " + to_string(hitRate) + " 速度加成: " + to_string(speed) + " 攻击方式：" + attackType;
}

void Weapon::describe() const
{
	cout << "Weapon: " << name << ", Attack: " << attack << ", Speed: " << speed << ", Hit Rate: " << hitRate << ", Attack string: " << attackType << endl;
}

Armor::Armor(string name, int price, int defense, int HP, string weakness)
	: Equipment(name, price), defense(defense), HP(HP), weakness(weakness) {}

int Armor::getDefense() const { return defense; }

int Armor::getHP() const { return HP; }

string Armor::getWeakness() const { return weakness; }

string Armor::getDescription() const
{
	return "该防具防御加成: " + to_string(defense) + " 最大生命加成: " + to_string(HP) + " 弱点：" + weakness;
}

void Armor::describe() const
{
	cout << "Armor: " << name << ", Defense: " << defense << ", HP Bonus: " << HP << ", Weakness: " << weakness << endl;
}





