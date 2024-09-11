#include "skill.h"

// Skill类的默认构造函数
Skill::Skill()
    : name(" "), description(" "), isAOE(false), isOffensive(false), isSelf(false) {}

// Skill类的参数化构造函数
Skill::Skill(string name, string description, bool isAOE, bool isOffensive, bool isSelf)
    : name(name), description(description), isAOE(isAOE), isOffensive(isOffensive), isSelf(isSelf) {}

// 获取技能是否为AOE
bool Skill::getIsAOE() const { return isAOE; }

// 获取技能名称
string Skill::getName() const { return name; }

// 获取技能是否为进攻性技能
bool Skill::getIsOffensive() const { return isOffensive; }

// 获取技能描述
string Skill::getDescription() const { return description; }

// 获取技能是否作用于自己
bool Skill::getIsSelf() const { return isSelf; }

// 设置技能被获取的状态
void Skill::be_get() {
    ifget = 1;
}

// 获取技能是否被获取的状态
int Skill::get_ifget() {
    return ifget;
}

// 将Skill对象保存到文件
void Skill::saveToFile(ofstream& file) const {
    // 写入名称长度
    size_t nameLength = name.size();
    file.write((char*)&nameLength, sizeof(nameLength));

    // 写入名称
    file.write(name.c_str(), nameLength);

    // 写入描述长度
    size_t descriptionLength = description.size();
    file.write((char*)&descriptionLength, sizeof(descriptionLength));

    // 写入描述
    file.write(description.c_str(), descriptionLength);

    // 写入是否是AOE
    file.write((char*)&isAOE, sizeof(isAOE));

    // 写入是否是进攻技能
    file.write((char*)&isOffensive, sizeof(isOffensive));

    // 写入是否作用于自己
    file.write((char*)&isSelf, sizeof(isSelf));
}

// 从文件加载Skill对象
void Skill::loadFromFile(ifstream& file) {
    // 读取名称长度
    size_t nameLength;
    file.read((char*)&nameLength, sizeof(nameLength));

    // 读取名称
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = string(nameBuffer);
    delete[] nameBuffer;

    // 读取描述长度
    size_t descriptionLength;
    file.read((char*)&descriptionLength, sizeof(descriptionLength));

    // 读取描述
    char* descriptionBuffer = new char[descriptionLength + 1];
    file.read(descriptionBuffer, descriptionLength);
    descriptionBuffer[descriptionLength] = '\0';
    description = string(descriptionBuffer);
    delete[] descriptionBuffer;

    // 读取是否是AOE
    file.read((char*)&isAOE, sizeof(isAOE));

    // 读取是否是进攻技能
    file.read((char*)&isOffensive, sizeof(isOffensive));

    // 读取是否作用于自己
    file.read((char*)&isSelf, sizeof(isSelf));
}

// offensiveSkill类的默认构造函数
offensiveSkill::offensiveSkill()
    : damageMultiplier(0.0), attackType(" "), attackFrequency(0), extraEffect(none), extraEffectIntensity(0.0), extraEffectDuration(0) {}

// offensiveSkill类的参数化构造函数
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

// 获取伤害倍率
float offensiveSkill::getDamageMultiplier() const { return damageMultiplier; }

// 获取攻击类型
string offensiveSkill::getAttackType() const { return attackType; }

// 获取攻击频率
int offensiveSkill::getAttackFrequency() const { return attackFrequency; }

// 获取附加效果
skillEffectType offensiveSkill::getEffect() const { return extraEffect; }

// 获取效果强度
float offensiveSkill::getEffectIntensity() const { return extraEffectIntensity; }

// 获取效果持续时间
int offensiveSkill::getDuration() const { return extraEffectDuration; }

// 将offensiveSkill对象保存到文件
void offensiveSkill::saveToFile(ofstream& file) const {
    Skill::saveToFile(file);  // 保存基类成员

    // 保存伤害倍率
    file.write((char*)&damageMultiplier, sizeof(damageMultiplier));

    // 保存攻击类型长度
    size_t attackTypeLength = attackType.size();
    file.write((char*)&attackTypeLength, sizeof(attackTypeLength));

    // 保存攻击类型
    file.write(attackType.c_str(), attackTypeLength);

    // 保存攻击频率
    file.write((char*)&attackFrequency, sizeof(attackFrequency));

    // 保存附加效果
    file.write((char*)&extraEffect, sizeof(extraEffect));

    // 保存效果强度
    file.write((char*)&extraEffectIntensity, sizeof(extraEffectIntensity));

    // 保存效果持续时间
    file.write((char*)&extraEffectDuration, sizeof(extraEffectDuration));
}

// 从文件加载offensiveSkill对象
void offensiveSkill::loadFromFile(ifstream& file) {
    Skill::loadFromFile(file);  // 加载基类成员

    // 加载伤害倍率
    file.read((char*)&damageMultiplier, sizeof(damageMultiplier));

    // 加载攻击类型长度
    size_t attackTypeLength;
    file.read((char*)&attackTypeLength, sizeof(attackTypeLength));

    // 加载攻击类型
    char* attackTypeBuffer = new char[attackTypeLength + 1];
    file.read(attackTypeBuffer, attackTypeLength);
    attackTypeBuffer[attackTypeLength] = '\0';
    attackType = string(attackTypeBuffer);
    delete[] attackTypeBuffer;

    // 加载攻击频率
    file.read((char*)&attackFrequency, sizeof(attackFrequency));

    // 加载附加效果
    file.read((char*)&extraEffect, sizeof(extraEffect));

    // 加载效果强度
    file.read((char*)&extraEffectIntensity, sizeof(extraEffectIntensity));

    // 加载效果持续时间
    file.read((char*)&extraEffectDuration, sizeof(extraEffectDuration));
}

// supportSkill类的默认构造函数
supportSkill::supportSkill()
    : effect(none), effectIntensity(0.0), duration(0) {}

// supportSkill类的参数化构造函数
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

// 获取效果
skillEffectType supportSkill::getEffect() const { return effect; }

// 获取效果强度
float supportSkill::getEffectIntensity() const { return effectIntensity; }

// 获取效果持续时间
int supportSkill::getDuration() const { return duration; }

// 获取伤害倍率（支持技能没有伤害倍率）
float supportSkill::getDamageMultiplier() const { return 0.0f; }

// 获取攻击类型（支持技能没有攻击类型）
string supportSkill::getAttackType() const { return ""; }

// 获取攻击频率（支持技能没有攻击频率）
int supportSkill::getAttackFrequency() const { return 0; }

// 将supportSkill对象保存到文件
void supportSkill::saveToFile(ofstream& file) const {
    Skill::saveToFile(file);  // 保存基类成员

    // 保存效果
    file.write((char*)&effect, sizeof(effect));

    // 保存效果强度
    file.write((char*)&effectIntensity, sizeof(effectIntensity));

    // 保存效果持续时间
    file.write((char*)&duration, sizeof(duration));
}

// 从文件加载supportSkill对象
void supportSkill::loadFromFile(ifstream& file) {
    Skill::loadFromFile(file);  // 加载基类成员

    // 加载效果
    file.read((char*)&effect, sizeof(effect));

    // 加载效果强度
    file.read((char*)&effectIntensity, sizeof(effectIntensity));

    // 加载效果持续时间
    file.read((char*)&duration, sizeof(duration));
}
