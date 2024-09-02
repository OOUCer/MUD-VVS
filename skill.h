//#ifndef SKILL_H
//#define SKILL_H

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
public:
    Skill(string name, bool isAOE, bool isOffensive);

    bool getIsAOE() const;

    string getName() const;

    bool getIsOffensive() const;

    virtual bool getIsSelf() const = 0;

    virtual float getDamageMultiplier() const = 0;

    virtual string getAttackType() const = 0;

    virtual int getAttackFrequency() const = 0;

    virtual skillEffectType getEffect() const = 0;

    virtual float getEffectIntensity() const = 0;

    virtual int getDuration() const = 0;

    
};

class offensiveSkill : public Skill
{
protected:
    float damageMultiplier;      // 伤害倍率
    string attackType;             // 用于确定当前装备武器是否可以使用该招式
    int attackFrequency;         // 连击次数
    skillEffectType extraEffect; // 附加效果
    float extraEffectIntensity;  // 实例：攻击x1.5 昏睡概率0.5
    int extraEffectDuration;

public:
    offensiveSkill(
        string name,
        bool isAOE,
        bool isOffensive,
        float damageMultiplier,
        string attackType,
        int attackFrequency,
        skillEffectType extraEffect,
        float extraEffectIntensity,
        int extraEffectDuration);

    float getDamageMultiplier() const;

    string getAttackType() const;

    int getAttackFrequency() const;

    skillEffectType getEffect() const;

    float getEffectIntensity() const;

    int getDuration() const;

    virtual bool getIsSelf() const;
};

class supportSkill : public Skill
{
protected:
    skillEffectType effect;
    float effectIntensity;
    int duration;
    bool isSelf;

public:
    supportSkill(
        string name,
        bool isAOE,
        bool isOffensive,
        bool isSelf,
        skillEffectType effect,
        float effectIntensity,
        int duration);
        

    skillEffectType getEffect() const;

    float getEffectIntensity() const;

    int getDuration() const;

    bool getIsSelf() const;

    virtual float getDamageMultiplier() const;

    virtual string getAttackType() const;

    virtual int getAttackFrequency() const;
};

//#endif