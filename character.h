//#ifndef CHARACTER_H
//#define CHARACTER_H

#include <string>
#include <vector>
#include <iostream>
#include <map>


#include "equipment.h"
#include "skill.h"

using namespace std;


class Character
{
protected:
    string name;
    int attack;
    int HP;
    int maxHP;
    int defense;
    int speed;
    float hitRate;
    float evasionRate;
    int gold;
    bool actionAvailability=true;
    bool hasReceivedWeaknessHit=false;
    bool hitWeakness = false;
    bool isPlayer;
    

    pair<bool, int> isComatose{ false,0 };
    bool isCharged=false;                 
    bool isAnticipating=false;            

    vector<Weapon *> weapons;
    vector<Armor *> armors;
    vector<Skill*> skills;
    map<skillEffectType, pair<float, int>> effectStatus;//自动初始化为空

public:
    Character(const string &name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer);

    string getName() const;

    //virtual int getPlace() const = 0;//Character类不能有虚函数，抽象类无法实例化

    int getAttack() const;

    int getHP() ;

    void modifyHP(int modifyAmount);

    int getMaxHP() const;

    int getDefense() const;

    int getSpeed() const;

    float getHitRate() const;

    float getEvasionRate() const;

    int getGold() const;

    bool isPlayerControlled() const;

    void setActionAvailability(bool isAvailable);

    bool getActionAvailability();

    void setWeaknessReceivedStatus(bool isHit);

    bool getWeaknessReceivedStatus();

    void setHitWeakness(bool hit);

    bool getHitWeakness();

    bool getAnticipateStatus();

    void setAnticipateStatus(bool theStatus);

    bool getComatoseStatus();

    int getComatoseDuration();

    void setComatoseStatus(bool theStatus, int duration);

    bool getChargeStatus();

    void setChargeStatus(bool theStatus);

    Weapon* getFirstWeapon();

    Armor* getFirstArmor();

    void addEffect(const skillEffectType &effect, float intensity, int duration);
    
    void removeEffect(const skillEffectType& effect);

    void addWeapon(Weapon* weapon);

    void addArmor(Armor* armor);

    void addSkill(Skill* skill);

    map<skillEffectType, pair<float, int>>* getEffectStatus();

    vector<Weapon*>* getWeapons();

    vector<Armor*>* getArmors();

    vector<Skill*>* getSkills();


    
};

class Linchong : public Character
{
protected:
    int place;

public:
    Linchong(const string &name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer, int place);

    int getPlace() const;

    void changePlace();

    void printWeapons() const;

    void printArmors() const;

    bool buyItem1(Weapon *equipment);
    bool buyItem2(Armor *equipment);
};

//#endif // CHARACTER_H