#include "skill.h"

Skill::Skill() : name(" "), description(" "), isAOE(false), isOffensive(false), isSelf(false) {}

Skill::Skill(string name, string description, bool isAOE, bool isOffensive, bool isSelf)
    : name(name), description(description), isAOE(isAOE), isOffensive(isOffensive), isSelf(isSelf) {}

bool Skill::getIsAOE() const { return isAOE; }
string Skill::getName() const { return name; }
bool Skill::getIsOffensive() const { return isOffensive; }
string Skill::getDescription() const { return description; }
bool Skill::getIsSelf() const { return isSelf; }

void Skill::saveToFile(ofstream& file) const {
    size_t nameLength = name.size();
    file.write((char*)&nameLength, sizeof(nameLength));  // 写入名称长度
    file.write(name.c_str(), nameLength);  // 写入名称

    size_t descriptionLength = description.size();
    file.write((char*)&descriptionLength, sizeof(descriptionLength));  // 写入描述长度
    file.write(description.c_str(), descriptionLength);  // 写入描述

    file.write((char*)&isAOE, sizeof(isAOE));  // 写入是否是AOE
    file.write((char*)&isOffensive, sizeof(isOffensive));  // 写入是否是进攻技能
    file.write((char*)&isSelf, sizeof(isSelf));  // 写入是否作用于自己
}

void Skill::loadFromFile(ifstream& file) {
    size_t nameLength;
    file.read((char*)&nameLength, sizeof(nameLength));  // 读取名称长度
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = string(nameBuffer);
    delete[] nameBuffer;

    size_t descriptionLength;
    file.read((char*)&descriptionLength, sizeof(descriptionLength));  // 读取描述长度
    char* descriptionBuffer = new char[descriptionLength + 1];
    file.read(descriptionBuffer, descriptionLength);
    descriptionBuffer[descriptionLength] = '\0';
    description = string(descriptionBuffer);
    delete[] descriptionBuffer;

    file.read((char*)&isAOE, sizeof(isAOE));  // 读取是否是AOE
    file.read((char*)&isOffensive, sizeof(isOffensive));  // 读取是否是进攻技能
    file.read((char*)&isSelf, sizeof(isSelf));  // 读取是否作用于自己
}

offensiveSkill::offensiveSkill() : damageMultiplier(0.0), attackType(" "), attackFrequency(0), extraEffect(none), extraEffectIntensity(0.0), extraEffectDuration(0) {}

offensiveSkill::offensiveSkill(
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
    int extraEffectDuration)
    : Skill(name, description, isAOE, isOffensive, isSelf),
    damageMultiplier(damageMultiplier),
    attackType(attackType),
    attackFrequency(attackFrequency),
    extraEffect(extraEffect),
    extraEffectIntensity(extraEffectIntensity),
    extraEffectDuration(extraEffectDuration) {}

float offensiveSkill::getDamageMultiplier() const { return damageMultiplier; }
string offensiveSkill::getAttackType() const { return attackType; }
int offensiveSkill::getAttackFrequency() const { return attackFrequency; }
skillEffectType offensiveSkill::getEffect() const { return extraEffect; }
float offensiveSkill::getEffectIntensity() const { return extraEffectIntensity; }
int offensiveSkill::getDuration() const { return extraEffectDuration; }

void offensiveSkill::saveToFile(ofstream& file) const {
    Skill::saveToFile(file);  // 保存基类成员

    file.write((char*)&damageMultiplier, sizeof(damageMultiplier));  // 保存伤害倍率

    size_t attackTypeLength = attackType.size();
    file.write((char*)&attackTypeLength, sizeof(attackTypeLength));  // 保存攻击类型长度
    file.write(attackType.c_str(), attackTypeLength);  // 保存攻击类型

    file.write((char*)&attackFrequency, sizeof(attackFrequency));  // 保存攻击频率
    file.write((char*)&extraEffect, sizeof(extraEffect));  // 保存附加效果
    file.write((char*)&extraEffectIntensity, sizeof(extraEffectIntensity));  // 保存效果强度
    file.write((char*)&extraEffectDuration, sizeof(extraEffectDuration));  // 保存持续时间
}

void offensiveSkill::loadFromFile(ifstream& file) {
    Skill::loadFromFile(file);  // 加载基类成员

    file.read((char*)&damageMultiplier, sizeof(damageMultiplier));  // 加载伤害倍率

    size_t attackTypeLength;
    file.read((char*)&attackTypeLength, sizeof(attackTypeLength));  // 加载攻击类型长度
    char* attackTypeBuffer = new char[attackTypeLength + 1];
    file.read(attackTypeBuffer, attackTypeLength);
    attackTypeBuffer[attackTypeLength] = '\0';
    attackType = string(attackTypeBuffer);
    delete[] attackTypeBuffer;

    file.read((char*)&attackFrequency, sizeof(attackFrequency));  // 加载攻击频率
    file.read((char*)&extraEffect, sizeof(extraEffect));  // 加载附加效果
    file.read((char*)&extraEffectIntensity, sizeof(extraEffectIntensity));  // 加载效果强度
    file.read((char*)&extraEffectDuration, sizeof(extraEffectDuration));  // 加载持续时间
}

supportSkill::supportSkill() : effect(none), effectIntensity(0.0), duration(0) {}

supportSkill::supportSkill(
    string name,
    string description,
    bool isAOE,
    bool isOffensive,
    bool isSelf,
    skillEffectType effect,
    float effectIntensity,
    int duration)
    : Skill(name, description, isAOE, isOffensive, isSelf),
    effect(effect),
    effectIntensity(effectIntensity),
    duration(duration) {}

skillEffectType supportSkill::getEffect() const { return effect; }
float supportSkill::getEffectIntensity() const { return effectIntensity; }
int supportSkill::getDuration() const { return duration; }

float supportSkill::getDamageMultiplier() const { return 0.0f; }
string supportSkill::getAttackType() const { return ""; }
int supportSkill::getAttackFrequency() const { return 0; }

void supportSkill::saveToFile(ofstream& file) const {
    Skill::saveToFile(file);  // 保存基类成员

    file.write((char*)&effect, sizeof(effect));  // 保存效果
    file.write((char*)&effectIntensity, sizeof(effectIntensity));  // 保存效果强度
    file.write((char*)&duration, sizeof(duration));  // 保存持续时间
}

void supportSkill::loadFromFile(ifstream& file) {
    Skill::loadFromFile(file);  // 加载基类成员

    file.read((char*)&effect, sizeof(effect));  // 加载效果
    file.read((char*)&effectIntensity, sizeof(effectIntensity));  // 加载效果强度
    file.read((char*)&duration, sizeof(duration));  // 加载持续时间
}
