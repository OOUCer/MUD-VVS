#ifndef SKILL_H
#define SKILL_H

#include <iostream>
#include <vector>
#include "skillEffectType.h"

using namespace std;


class Skill
{
protected:
    string name;      // 招式名称
    bool isAOE;       // 是否是范围效果
    bool isOffensive; // 是否是进攻类招式
    string description;//招式描述
    bool isSelf;//是否作用自己
public:
    Skill(string name, string description, bool isAOE, bool isOffensive, bool isSelf);

    bool getIsAOE() const;//返回是否范围效果

    string getName() const;//返回名字

    bool getIsOffensive() const;//返回是否进攻招式

    string getDescription() const;//返回描述

    bool getIsSelf() const ;//返回是否作用自己

    virtual float getDamageMultiplier() const =0;//返回伤害倍率

    virtual string getAttackType() const = 0;//返回攻击类型

    virtual int getAttackFrequency() const = 0;//返回攻击频率

    virtual skillEffectType getEffect() const = 0;//返回效果

    virtual float getEffectIntensity() const = 0;//返回效果强度

    virtual int getDuration() const = 0;//返回效果持续时间

    


};

class offensiveSkill : public Skill
{
protected:
    float damageMultiplier;      // 伤害倍率
    string attackType;             // 用于确定当前装备武器是否可以使用该招式
    int attackFrequency;         // 连击次数
    skillEffectType extraEffect; // 附加效果
    float extraEffectIntensity;  // 实例：攻击x1.5 昏睡概率0.5
    int extraEffectDuration;//附加效果持续时间
    

public:
    offensiveSkill(
        string name,
        string description,
        bool isAOE,
        bool isOffensive,
        bool isSelf,
        float damageMultiplier,
        string attackType,
        int attackFrequency,
        skillEffectType extraEffect,
        float extraEffectIntensity,
        int extraEffectDuration);//构造

    float getDamageMultiplier() const;//返回伤害倍率

    string getAttackType() const;//返回攻击类型

    int getAttackFrequency() const;//返回攻击频率

    skillEffectType getEffect() const;//返回效果

    float getEffectIntensity() const;//返回效果强度

    int getDuration() const;//返回持续时间

    //返回是否作用自己
};

class supportSkill : public Skill
{
protected:
    skillEffectType effect;
    float effectIntensity;
    int duration;
 

public:
    supportSkill(
        string name,
        string description,
        bool isAOE,
        bool isOffensive,
        bool isSelf,
        skillEffectType effect,
        float effectIntensity,
        int duration);//构造
        

    skillEffectType getEffect() const;//返回招式效果

    float getEffectIntensity() const;//返回效果强度

    int getDuration() const;//返回持续时间

   //返回是否作用自己

    virtual float getDamageMultiplier() const;//返回伤害倍率

    virtual string getAttackType() const;//返回攻击类型

    virtual int getAttackFrequency() const;//返回攻击频率
};

#endif