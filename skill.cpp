#include "skill.h"

Skill::Skill() : name(" "), description(" "), isAOE(false), isOffensive(false), isSelf(false) {}

Skill::Skill(string name, string description, bool isAOE, bool isOffensive, bool isSelf)
    : name(name), description(description), isAOE(isAOE), isOffensive(isOffensive), isSelf(isSelf) {}

bool Skill::getIsAOE() const { return isAOE; }
string Skill::getName() const { return name; }
bool Skill::getIsOffensive() const { return isOffensive; }
string Skill::getDescription() const { return description; }
bool Skill::getIsSelf() const { return isSelf; }

void Skill::be_get()
{
    ifget = 1;
}

int Skill::get_ifget()
{
    return ifget;
}

void Skill::saveToFile(ofstream& file) const {
    size_t nameLength = name.size();
    file.write((char*)&nameLength, sizeof(nameLength));  // д�����Ƴ���
    file.write(name.c_str(), nameLength);  // д������

    size_t descriptionLength = description.size();
    file.write((char*)&descriptionLength, sizeof(descriptionLength));  // д����������
    file.write(description.c_str(), descriptionLength);  // д������

    file.write((char*)&isAOE, sizeof(isAOE));  // д���Ƿ���AOE
    file.write((char*)&isOffensive, sizeof(isOffensive));  // д���Ƿ��ǽ�������
    file.write((char*)&isSelf, sizeof(isSelf));  // д���Ƿ��������Լ�
}

void Skill::loadFromFile(ifstream& file) {
    size_t nameLength;
    file.read((char*)&nameLength, sizeof(nameLength));  // ��ȡ���Ƴ���
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = string(nameBuffer);
    delete[] nameBuffer;

    size_t descriptionLength;
    file.read((char*)&descriptionLength, sizeof(descriptionLength));  // ��ȡ��������
    char* descriptionBuffer = new char[descriptionLength + 1];
    file.read(descriptionBuffer, descriptionLength);
    descriptionBuffer[descriptionLength] = '\0';
    description = string(descriptionBuffer);
    delete[] descriptionBuffer;

    file.read((char*)&isAOE, sizeof(isAOE));  // ��ȡ�Ƿ���AOE
    file.read((char*)&isOffensive, sizeof(isOffensive));  // ��ȡ�Ƿ��ǽ�������
    file.read((char*)&isSelf, sizeof(isSelf));  // ��ȡ�Ƿ��������Լ�
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
    Skill::saveToFile(file);  // ��������Ա

    file.write((char*)&damageMultiplier, sizeof(damageMultiplier));  // �����˺�����

    size_t attackTypeLength = attackType.size();
    file.write((char*)&attackTypeLength, sizeof(attackTypeLength));  // ���湥�����ͳ���
    file.write(attackType.c_str(), attackTypeLength);  // ���湥������

    file.write((char*)&attackFrequency, sizeof(attackFrequency));  // ���湥��Ƶ��
    file.write((char*)&extraEffect, sizeof(extraEffect));  // ���渽��Ч��
    file.write((char*)&extraEffectIntensity, sizeof(extraEffectIntensity));  // ����Ч��ǿ��
    file.write((char*)&extraEffectDuration, sizeof(extraEffectDuration));  // �������ʱ��
}

void offensiveSkill::loadFromFile(ifstream& file) {
    Skill::loadFromFile(file);  // ���ػ����Ա

    file.read((char*)&damageMultiplier, sizeof(damageMultiplier));  // �����˺�����

    size_t attackTypeLength;
    file.read((char*)&attackTypeLength, sizeof(attackTypeLength));  // ���ع������ͳ���
    char* attackTypeBuffer = new char[attackTypeLength + 1];
    file.read(attackTypeBuffer, attackTypeLength);
    attackTypeBuffer[attackTypeLength] = '\0';
    attackType = string(attackTypeBuffer);
    delete[] attackTypeBuffer;

    file.read((char*)&attackFrequency, sizeof(attackFrequency));  // ���ع���Ƶ��
    file.read((char*)&extraEffect, sizeof(extraEffect));  // ���ظ���Ч��
    file.read((char*)&extraEffectIntensity, sizeof(extraEffectIntensity));  // ����Ч��ǿ��
    file.read((char*)&extraEffectDuration, sizeof(extraEffectDuration));  // ���س���ʱ��
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
    Skill::saveToFile(file);  // ��������Ա

    file.write((char*)&effect, sizeof(effect));  // ����Ч��
    file.write((char*)&effectIntensity, sizeof(effectIntensity));  // ����Ч��ǿ��
    file.write((char*)&duration, sizeof(duration));  // �������ʱ��
}

void supportSkill::loadFromFile(ifstream& file) {
    Skill::loadFromFile(file);  // ���ػ����Ա

    file.read((char*)&effect, sizeof(effect));  // ����Ч��
    file.read((char*)&effectIntensity, sizeof(effectIntensity));  // ����Ч��ǿ��
    file.read((char*)&duration, sizeof(duration));  // ���س���ʱ��
}
