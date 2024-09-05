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
	Equipment(string name, int price);// ���캯�������ڳ�ʼ��װ�������ƺͼ۸�

	string getName() const;// ��ȡװ�������� 
	int getPrice() const;// ��ȡװ���ļ۸�  

	
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
	Weapon(string name, int price, int attack, int speed, float hitRate, string attackType);// ���캯�������ڳ�ʼ����������������
	int getAttack() const ;// ��ȡ�����Ĺ�����
	int getSpeed() const ;// ��ȡ�����Ĺ����ٶ�  
	float getHitRate() const ; // ��ȡ������������ 
	string getAttackType() const ;// ��ȡ�����Ĺ�������
	string getDescription() const ;// ��ȡ��������ϸ�����ַ���  
	void describe() const ;// ��ӡ��������ϸ����

};

class Armor : public Equipment
{
private:
	int defense;
	int HP;
	string weakness;

public:
	Armor();
	Armor(string name, int price, int defense, int HP, string weakness);// ���캯�������ڳ�ʼ�����׵���������
	int getDefense() const ;// ��ȡ���׵ķ����� 
	int getHP() const  ;// ��ȡ�����ṩ�Ķ�������ֵ
	string getWeakness() const ;// ��ȡ���׵�����
	string getDescription() const ;// ��ȡ���׵���ϸ�����ַ���
	void describe() const ;// ��ӡ���׵���ϸ����

};

#endif