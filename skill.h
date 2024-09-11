#ifndef SKILL_H
#define SKILL_H

#include <iostream>
#include <fstream> // 用于文件操作
#include <vector>
#include "skillEffectType.h"

using namespace std;

class Skill {
protected:
    string name;      // 招式名称
    bool isAOE;       // 是否是范围效果
    bool isOffensive; // 是否是进攻类招式
    string description; // 招式描述
    bool isSelf;      // 是否作用自己
    int ifget = 0;    // 是否获得

public:
    // 默认构造函数
    Skill();

    // 带参数的构造函数
    Skill(string name, string description, bool isAOE, bool isOffensive, bool isSelf);

    // 获取是否是范围效果
    bool getIsAOE() const;

    // 获取招式名称
    string getName() const;

    // 获取是否是进攻类招式
    bool getIsOffensive() const;

    // 获取招式描述
    string getDescription() const;

    // 获取是否作用自己
    bool getIsSelf() const;

    // 设置为已获得
    void be_get();

    // 获取是否已获得
    int get_ifget();

    // 获取伤害倍数（纯虚函数）
    virtual float getDamageMultiplier() const = 0;

    // 获取攻击类型（纯虚函数）
    virtual string getAttackType() const = 0;

    // 获取攻击频率（纯虚函数）
    virtual int getAttackFrequency() const = 0;

    // 获取技能效果（纯虚函数）
    virtual skillEffectType getEffect() const = 0;

    // 获取效果强度（纯虚函数）
    virtual float getEffectIntensity() const = 0;

    // 获取持续时间（纯虚函数）
    virtual int getDuration() const = 0;

    // 将技能数据保存到文件
    virtual void saveToFile(ofstream& file) const;

    // 从文件加载技能数据
    virtual void loadFromFile(ifstream& file);
};

class offensiveSkill : public Skill {
protected:
    float damageMultiplier;        // 伤害倍数
    string attackType;             // 攻击类型
    int attackFrequency;           // 攻击频率
    skillEffectType extraEffect;   // 额外效果
    float extraEffectIntensity;    // 额外效果强度
    int extraEffectDuration;       // 额外效果持续时间

public:
    // 默认构造函数
    offensiveSkill();

    // 带参数的构造函数
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

    // 获取伤害倍数
    float getDamageMultiplier() const;

    // 获取攻击类型
    string getAttackType() const;

    // 获取攻击频率
    int getAttackFrequency() const;

    // 获取技能效果
    skillEffectType getEffect() const;

    // 获取效果强度
    float getEffectIntensity() const;

    // 获取效果持续时间
    int getDuration() const;

    // 将技能数据保存到文件
    void saveToFile(ofstream& file) const override;

    // 从文件加载技能数据
    void loadFromFile(ifstream& file) override;
};

class supportSkill : public Skill {
protected:
    skillEffectType effect;         // 技能效果
    float effectIntensity;          // 效果强度
    int duration;                   // 持续时间

public:
    // 默认构造函数
    supportSkill();

    // 带参数的构造函数
    supportSkill(
        string name,
        string description,
        bool isAOE,
        bool isOffensive,
        bool isSelf,
        skillEffectType effect,
        float effectIntensity,
        int duration);

    // 获取技能效果
    skillEffectType getEffect() const;

    // 获取效果强度
    float getEffectIntensity() const;

    // 获取效果持续时间
    int getDuration() const;

    // 获取伤害倍数（纯虚函数实现）
    float getDamageMultiplier() const override;

    // 获取攻击类型（纯虚函数实现）
    string getAttackType() const override;

    // 获取攻击频率（纯虚函数实现）
    int getAttackFrequency() const override;

    // 将技能数据保存到文件
    void saveToFile(ofstream& file) const override;

    // 从文件加载技能数据
    void loadFromFile(ifstream& file) override;
};

#endif // SKILL_H
