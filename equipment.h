#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Equipment {
protected:
    string name;
    int price;
    int ifget = 0; // ���ڱ��װ���Ƿ��ѻ��

public:
    // Ĭ�Ϲ��캯��
    Equipment();

    // ���������캯��
    Equipment(string name, int price);

    // ��ȡװ������
    string getName() const;

    // ��ȡװ���۸�
    int getPrice() const;

    // ���װ��Ϊ�ѻ��
    void be_get();

    // ��ȡװ���Ƿ��ѻ��
    int get_ifget();

    // ����װ����Ϣ���ļ����麯������������д��
    virtual void saveToFile(ofstream& file) const;

    // ���ļ�����װ����Ϣ���麯������������д��
    virtual void loadFromFile(ifstream& file);
};

class Weapon : public Equipment {
private:
    int attack;
    int speed;
    float hitRate;
    string attackType;

public:
    // Ĭ�Ϲ��캯��
    Weapon();

    // ���������캯��
    Weapon(string name, int price, int attack, int speed, float hitRate, string attackType);

    // ��ȡ�����Ĺ�����
    int getAttack() const;

    // ��ȡ�������ٶ�
    int getSpeed() const;

    // ��ȡ������������
    float getHitRate() const;

    // ��ȡ�����Ĺ�������
    string getAttackType() const;

    // ��ȡ������������Ϣ
    string getDescription() const;

    // ���������������Ϣ
    void describe() const;

    // ����������Ϣ���ļ�
    void saveToFile(ofstream& file) const override;

    // ���ļ�����������Ϣ
    void loadFromFile(ifstream& file) override;
};

class Armor : public Equipment {
private:
    int defense;
    int HP;
    string weakness;

public:
    // Ĭ�Ϲ��캯��
    Armor();

    // ���������캯��
    Armor(string name, int price, int defense, int HP, string weakness);

    // ��ȡ���׵ķ���ֵ
    int getDefense() const;

    // ��ȡ���׵�����ֵ
    int getHP() const;

    // ��ȡ���׵�����
    string getWeakness() const;

    // ��ȡ���׵�������Ϣ
    string getDescription() const;

    // ������׵�������Ϣ
    void describe() const;

    // ���滤����Ϣ���ļ�
    void saveToFile(ofstream& file) const override;

    // ���ļ����ػ�����Ϣ
    void loadFromFile(ifstream& file) override;
};

#endif // EQUIPMENT_H
