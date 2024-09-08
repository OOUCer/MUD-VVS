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
    int ifget = 0;
public:
    Equipment();
    Equipment(string name, int price);

    string getName() const;
    int getPrice() const;
    void be_get();
    int get_ifget();
    virtual void saveToFile(ofstream& file) const;
    virtual void loadFromFile(ifstream& file);
};

class Weapon : public Equipment {
private:
    int attack;
    int speed;
    float hitRate;
    string attackType;

public:
    Weapon();
    Weapon(string name, int price, int attack, int speed, float hitRate, string attackType);

    int getAttack() const;
    int getSpeed() const;
    float getHitRate() const;
    string getAttackType() const;

    string getDescription() const;
    void describe() const;
    
    void saveToFile(ofstream& file) const override;
    void loadFromFile(ifstream& file) override;
};

class Armor : public Equipment {
private:
    int defense;
    int HP;
    string weakness;

public:
    Armor();
    Armor(string name, int price, int defense, int HP, string weakness);

    int getDefense() const;
    int getHP() const;
    string getWeakness() const;

    string getDescription() const;
    void describe() const;

    void saveToFile(ofstream& file) const override;
    void loadFromFile(ifstream& file) override;
};

#endif // EQUIPMENT_H
