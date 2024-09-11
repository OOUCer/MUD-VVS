#include "skill.h"

// Skill���Ĭ�Ϲ��캯��
Skill::Skill()
    : name(" "), description(" "), isAOE(false), isOffensive(false), isSelf(false) {}

// Skill��Ĳ��������캯��
Skill::Skill(string name, string description, bool isAOE, bool isOffensive, bool isSelf)
    : name(name), description(description), isAOE(isAOE), isOffensive(isOffensive), isSelf(isSelf) {}

// ��ȡ�����Ƿ�ΪAOE
bool Skill::getIsAOE() const { return isAOE; }

// ��ȡ��������
string Skill::getName() const { return name; }

// ��ȡ�����Ƿ�Ϊ�����Լ���
bool Skill::getIsOffensive() const { return isOffensive; }

// ��ȡ��������
string Skill::getDescription() const { return description; }

// ��ȡ�����Ƿ��������Լ�
bool Skill::getIsSelf() const { return isSelf; }

// ���ü��ܱ���ȡ��״̬
void Skill::be_get() {
    ifget = 1;
}

// ��ȡ�����Ƿ񱻻�ȡ��״̬
int Skill::get_ifget() {
    return ifget;
}

// ��Skill���󱣴浽�ļ�
void Skill::saveToFile(ofstream& file) const {
    // д�����Ƴ���
    size_t nameLength = name.size();
    file.write((char*)&nameLength, sizeof(nameLength));

    // д������
    file.write(name.c_str(), nameLength);

    // д����������
    size_t descriptionLength = description.size();
    file.write((char*)&descriptionLength, sizeof(descriptionLength));

    // д������
    file.write(description.c_str(), descriptionLength);

    // д���Ƿ���AOE
    file.write((char*)&isAOE, sizeof(isAOE));

    // д���Ƿ��ǽ�������
    file.write((char*)&isOffensive, sizeof(isOffensive));

    // д���Ƿ��������Լ�
    file.write((char*)&isSelf, sizeof(isSelf));
}

// ���ļ�����Skill����
void Skill::loadFromFile(ifstream& file) {
    // ��ȡ���Ƴ���
    size_t nameLength;
    file.read((char*)&nameLength, sizeof(nameLength));

    // ��ȡ����
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = string(nameBuffer);
    delete[] nameBuffer;

    // ��ȡ��������
    size_t descriptionLength;
    file.read((char*)&descriptionLength, sizeof(descriptionLength));

    // ��ȡ����
    char* descriptionBuffer = new char[descriptionLength + 1];
    file.read(descriptionBuffer, descriptionLength);
    descriptionBuffer[descriptionLength] = '\0';
    description = string(descriptionBuffer);
    delete[] descriptionBuffer;

    // ��ȡ�Ƿ���AOE
    file.read((char*)&isAOE, sizeof(isAOE));

    // ��ȡ�Ƿ��ǽ�������
    file.read((char*)&isOffensive, sizeof(isOffensive));

    // ��ȡ�Ƿ��������Լ�
    file.read((char*)&isSelf, sizeof(isSelf));
}

// offensiveSkill���Ĭ�Ϲ��캯��
offensiveSkill::offensiveSkill()
    : damageMultiplier(0.0), attackType(" "), attackFrequency(0), extraEffect(none), extraEffectIntensity(0.0), extraEffectDuration(0) {}

// offensiveSkill��Ĳ��������캯��
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

// ��ȡ�˺�����
float offensiveSkill::getDamageMultiplier() const { return damageMultiplier; }

// ��ȡ��������
string offensiveSkill::getAttackType() const { return attackType; }

// ��ȡ����Ƶ��
int offensiveSkill::getAttackFrequency() const { return attackFrequency; }

// ��ȡ����Ч��
skillEffectType offensiveSkill::getEffect() const { return extraEffect; }

// ��ȡЧ��ǿ��
float offensiveSkill::getEffectIntensity() const { return extraEffectIntensity; }

// ��ȡЧ������ʱ��
int offensiveSkill::getDuration() const { return extraEffectDuration; }

// ��offensiveSkill���󱣴浽�ļ�
void offensiveSkill::saveToFile(ofstream& file) const {
    Skill::saveToFile(file);  // ��������Ա

    // �����˺�����
    file.write((char*)&damageMultiplier, sizeof(damageMultiplier));

    // ���湥�����ͳ���
    size_t attackTypeLength = attackType.size();
    file.write((char*)&attackTypeLength, sizeof(attackTypeLength));

    // ���湥������
    file.write(attackType.c_str(), attackTypeLength);

    // ���湥��Ƶ��
    file.write((char*)&attackFrequency, sizeof(attackFrequency));

    // ���渽��Ч��
    file.write((char*)&extraEffect, sizeof(extraEffect));

    // ����Ч��ǿ��
    file.write((char*)&extraEffectIntensity, sizeof(extraEffectIntensity));

    // ����Ч������ʱ��
    file.write((char*)&extraEffectDuration, sizeof(extraEffectDuration));
}

// ���ļ�����offensiveSkill����
void offensiveSkill::loadFromFile(ifstream& file) {
    Skill::loadFromFile(file);  // ���ػ����Ա

    // �����˺�����
    file.read((char*)&damageMultiplier, sizeof(damageMultiplier));

    // ���ع������ͳ���
    size_t attackTypeLength;
    file.read((char*)&attackTypeLength, sizeof(attackTypeLength));

    // ���ع�������
    char* attackTypeBuffer = new char[attackTypeLength + 1];
    file.read(attackTypeBuffer, attackTypeLength);
    attackTypeBuffer[attackTypeLength] = '\0';
    attackType = string(attackTypeBuffer);
    delete[] attackTypeBuffer;

    // ���ع���Ƶ��
    file.read((char*)&attackFrequency, sizeof(attackFrequency));

    // ���ظ���Ч��
    file.read((char*)&extraEffect, sizeof(extraEffect));

    // ����Ч��ǿ��
    file.read((char*)&extraEffectIntensity, sizeof(extraEffectIntensity));

    // ����Ч������ʱ��
    file.read((char*)&extraEffectDuration, sizeof(extraEffectDuration));
}

// supportSkill���Ĭ�Ϲ��캯��
supportSkill::supportSkill()
    : effect(none), effectIntensity(0.0), duration(0) {}

// supportSkill��Ĳ��������캯��
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

// ��ȡЧ��
skillEffectType supportSkill::getEffect() const { return effect; }

// ��ȡЧ��ǿ��
float supportSkill::getEffectIntensity() const { return effectIntensity; }

// ��ȡЧ������ʱ��
int supportSkill::getDuration() const { return duration; }

// ��ȡ�˺����ʣ�֧�ּ���û���˺����ʣ�
float supportSkill::getDamageMultiplier() const { return 0.0f; }

// ��ȡ�������ͣ�֧�ּ���û�й������ͣ�
string supportSkill::getAttackType() const { return ""; }

// ��ȡ����Ƶ�ʣ�֧�ּ���û�й���Ƶ�ʣ�
int supportSkill::getAttackFrequency() const { return 0; }

// ��supportSkill���󱣴浽�ļ�
void supportSkill::saveToFile(ofstream& file) const {
    Skill::saveToFile(file);  // ��������Ա

    // ����Ч��
    file.write((char*)&effect, sizeof(effect));

    // ����Ч��ǿ��
    file.write((char*)&effectIntensity, sizeof(effectIntensity));

    // ����Ч������ʱ��
    file.write((char*)&duration, sizeof(duration));
}

// ���ļ�����supportSkill����
void supportSkill::loadFromFile(ifstream& file) {
    Skill::loadFromFile(file);  // ���ػ����Ա

    // ����Ч��
    file.read((char*)&effect, sizeof(effect));

    // ����Ч��ǿ��
    file.read((char*)&effectIntensity, sizeof(effectIntensity));

    // ����Ч������ʱ��
    file.read((char*)&duration, sizeof(duration));
}
