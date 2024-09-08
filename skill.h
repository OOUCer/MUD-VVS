#ifndef SKILL_H
#define SKILL_H

#include <iostream>
#include <fstream> // for file operations
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
    int ifget=0;
public:
    Skill();
    Skill(string name, string description, bool isAOE, bool isOffensive, bool isSelf);

    bool getIsAOE() const;
    string getName() const;
    bool getIsOffensive() const;
    string getDescription() const;
    bool getIsSelf() const;
    void be_get();
    int get_ifget();
    virtual float getDamageMultiplier() const = 0;
    virtual string getAttackType() const = 0;
    virtual int getAttackFrequency() const = 0;
    virtual skillEffectType getEffect() const = 0;
    virtual float getEffectIntensity() const = 0;
    virtual int getDuration() const = 0;

    virtual void saveToFile(ofstream& file) const;
    virtual void loadFromFile(ifstream& file);
};

class offensiveSkill : public Skill
{
protected:
    float damageMultiplier;
    string attackType;
    int attackFrequency;
    skillEffectType extraEffect;
    float extraEffectIntensity;
    int extraEffectDuration;

public:
    offensiveSkill();
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
        int extraEffectDuration);

    float getDamageMultiplier() const;
    string getAttackType() const;
    int getAttackFrequency() const;
    skillEffectType getEffect() const;
    float getEffectIntensity() const;
    int getDuration() const;

    void saveToFile(ofstream& file) const override;
    void loadFromFile(ifstream& file) override;
};

class supportSkill : public Skill
{
protected:
    skillEffectType effect;
    float effectIntensity;
    int duration;

public:
    supportSkill();
    supportSkill(
        string name,
        string description,
        bool isAOE,
        bool isOffensive,
        bool isSelf,
        skillEffectType effect,
        float effectIntensity,
        int duration);

    skillEffectType getEffect() const;
    float getEffectIntensity() const;
    int getDuration() const;

    float getDamageMultiplier() const override;
    string getAttackType() const override;
    int getAttackFrequency() const override;

    void saveToFile(ofstream& file) const override;
    void loadFromFile(ifstream& file) override;
};

#endif // SKILL_H
