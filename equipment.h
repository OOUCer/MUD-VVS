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
    int ifget = 0; // 用于标记装备是否已获得

public:
    // 默认构造函数
    Equipment();

    // 带参数构造函数
    Equipment(string name, int price);

    // 获取装备名称
    string getName() const;

    // 获取装备价格
    int getPrice() const;

    // 标记装备为已获得
    void be_get();

    // 获取装备是否已获得
    int get_ifget();

    // 保存装备信息到文件（虚函数，供子类重写）
    virtual void saveToFile(ofstream& file) const;

    // 从文件加载装备信息（虚函数，供子类重写）
    virtual void loadFromFile(ifstream& file);
};

class Weapon : public Equipment {
private:
    int attack;
    int speed;
    float hitRate;
    string attackType;

public:
    // 默认构造函数
    Weapon();

    // 带参数构造函数
    Weapon(string name, int price, int attack, int speed, float hitRate, string attackType);

    // 获取武器的攻击力
    int getAttack() const;

    // 获取武器的速度
    int getSpeed() const;

    // 获取武器的命中率
    float getHitRate() const;

    // 获取武器的攻击类型
    string getAttackType() const;

    // 获取武器的描述信息
    string getDescription() const;

    // 输出武器的描述信息
    void describe() const;

    // 保存武器信息到文件
    void saveToFile(ofstream& file) const override;

    // 从文件加载武器信息
    void loadFromFile(ifstream& file) override;
};

class Armor : public Equipment {
private:
    int defense;
    int HP;
    string weakness;

public:
    // 默认构造函数
    Armor();

    // 带参数构造函数
    Armor(string name, int price, int defense, int HP, string weakness);

    // 获取护甲的防御值
    int getDefense() const;

    // 获取护甲的生命值
    int getHP() const;

    // 获取护甲的弱点
    string getWeakness() const;

    // 获取护甲的描述信息
    string getDescription() const;

    // 输出护甲的描述信息
    void describe() const;

    // 保存护甲信息到文件
    void saveToFile(ofstream& file) const override;

    // 从文件加载护甲信息
    void loadFromFile(ifstream& file) override;
};

#endif // EQUIPMENT_H
