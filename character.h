#ifndef CHARACTER_H
#define CHARACTER_H

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
    bool actionAvailability = true;
    bool hasReceivedWeaknessHit = false;
    bool hitWeakness = false;
    bool isPlayer;

    pair<bool, int> isComatose{ false,0 };
    bool isCharged = false;
    bool isAnticipating = false;
    int skillPoint = 3;
    int actionCount = 0;

    vector<Weapon*> weapons;
    vector<Armor*> armors;
    vector<supportSkill*> sSkills;
    vector<offensiveSkill*> oSkills;
    vector<Skill*> skills;//无用，测试用，勿删除
    map<skillEffectType, pair<float, int>> effectStatus;//自动初始化为空

public:
    // 构造函数，用于初始化角色的基础属性  
    Character(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer);

    // 获取角色名称  
    string getName() const;

    // 获取角色的攻击力  
    int getAttack() const;

    void setAttack(int newAttack);

    // 获取角色的当前生命值  
    int getHP();

    // 修改角色的生命值  
    void modifyHP(int modifyAmount);


    void setHP(int newHP);

    // 获取角色的最大生命值  
    int getMaxHP() const;

    void setMaxHP(int newMaxHP);

    // 获取角色的防御力  
    int getDefense() const;

    // 获取角色的速度  
    int getSpeed() const;

    // 获取角色的命中率  
    float getHitRate() const;

    // 获取角色的闪避率  
    float getEvasionRate() const;

    // 获取角色拥有的金币数量  
    int getGold() const;

    void setGold(int newGold);

    // 判断角色是否为玩家控制  
    bool isPlayerControlled() const;

    // 设置角色的行动是否可用  
    void setActionAvailability(bool isAvailable);

    // 获取角色的行动是否可用  
    bool getActionAvailability();

    // 设置角色是否受到弱点攻击  
    void setWeaknessReceivedStatus(bool isHit);

    // 获取角色是否受到弱点攻击  
    bool getWeaknessReceivedStatus();

    // 设置角色是否击中弱点  
    void setHitWeakness(bool hit);

    // 获取角色是否击中弱点  
    bool getHitWeakness();

    // 获取角色的技能点数  
    int getSkillPoint();

    // 设置角色的技能点数  
    void setSkillPoint(int point);

    // 获取角色的行动次数  
    int getActionCount();

    // 设置角色的行动次数  
    void setActionCount(int count);

    // 获取角色是否处于预判状态  
    bool getAnticipateStatus();

    // 设置角色是否处于预判状态  
    void setAnticipateStatus(bool theStatus);

    // 获取角色是否处于昏迷状态  
    bool getComatoseStatus();

    // 获取角色昏迷的持续时间  
    int getComatoseDuration();

    // 设置角色是否处于昏迷状态以及昏迷的持续时间  
    void setComatoseStatus(bool theStatus, int duration);

    // 获取角色是否处于充能状态  
    bool getChargeStatus();

    // 设置角色是否处于充能状态  
    void setChargeStatus(bool theStatus);

    // 获取角色的第一把武器（如果有的话）  
    Weapon* getFirstWeapon();

    // 获取角色的第一套护甲（如果有的话）  
    Armor* getFirstArmor();

    // 给角色添加一个效果  
    void addEffect(const skillEffectType& effect, float intensity, int duration);

    // 移除角色身上的一个效果  
    void removeEffect(const skillEffectType& effect);

    // 给角色添加一把武器  
    void addWeapon(Weapon* weapon);

    // 给角色添加一套护甲  
    void addArmor(Armor* armor);

    // 给角色添加一个技能  
    void addSkill(Skill* skill);

    // 获取角色当前的所有效果状态  
    map<skillEffectType, pair<float, int>>* getEffectStatus();

    // 获取角色的所有武器（以指针向量的形式）  
    vector<Weapon*>* getWeapons();

    // 获取角色的所有护甲（以指针向量的形式）  
    vector<Armor*>* getArmors();

    // 获取角色的所有技能（以指针向量的形式） 
    vector<Skill*> *getSkills();
    vector<offensiveSkill*>* getoSkills();
    vector<supportSkill*>* getsSkills();
};

class Linchong : public Character
{
protected:
    int place;

public:
    // 构造函数，继承自Character类，并添加位置属性  
    Linchong(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer, int place);

    // 获取角色所在位置  
    int getPlace() const;

    // 改变角色的位置（具体实现依赖于游戏逻辑）  
    void changePlace();

    // 打印角色拥有的所有武器  
    void printWeapons() const;

    // 打印角色拥有的所有护甲  
    void printArmors() const;

    // 尝试购买一件武器（具体实现依赖于游戏逻辑，如金币是否足够等）  
    bool buyItem1(Weapon* equipment);

    // 尝试购买一套护甲（具体实现依赖于游戏逻辑，如金币是否足够等）  
    bool buyItem2(Armor* equipment);
};


#endif // CHARACTER_H