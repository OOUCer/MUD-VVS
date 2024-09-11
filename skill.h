#ifndef SKILL_H
#define SKILL_H

#include <iostream>
#include <fstream> // �����ļ�����
#include <vector>
#include "skillEffectType.h"

using namespace std;

class Skill {
protected:
    string name;      // ��ʽ����
    bool isAOE;       // �Ƿ��Ƿ�ΧЧ��
    bool isOffensive; // �Ƿ��ǽ�������ʽ
    string description; // ��ʽ����
    bool isSelf;      // �Ƿ������Լ�
    int ifget = 0;    // �Ƿ���

public:
    // Ĭ�Ϲ��캯��
    Skill();

    // �������Ĺ��캯��
    Skill(string name, string description, bool isAOE, bool isOffensive, bool isSelf);

    // ��ȡ�Ƿ��Ƿ�ΧЧ��
    bool getIsAOE() const;

    // ��ȡ��ʽ����
    string getName() const;

    // ��ȡ�Ƿ��ǽ�������ʽ
    bool getIsOffensive() const;

    // ��ȡ��ʽ����
    string getDescription() const;

    // ��ȡ�Ƿ������Լ�
    bool getIsSelf() const;

    // ����Ϊ�ѻ��
    void be_get();

    // ��ȡ�Ƿ��ѻ��
    int get_ifget();

    // ��ȡ�˺����������麯����
    virtual float getDamageMultiplier() const = 0;

    // ��ȡ�������ͣ����麯����
    virtual string getAttackType() const = 0;

    // ��ȡ����Ƶ�ʣ����麯����
    virtual int getAttackFrequency() const = 0;

    // ��ȡ����Ч�������麯����
    virtual skillEffectType getEffect() const = 0;

    // ��ȡЧ��ǿ�ȣ����麯����
    virtual float getEffectIntensity() const = 0;

    // ��ȡ����ʱ�䣨���麯����
    virtual int getDuration() const = 0;

    // ���������ݱ��浽�ļ�
    virtual void saveToFile(ofstream& file) const;

    // ���ļ����ؼ�������
    virtual void loadFromFile(ifstream& file);
};

class offensiveSkill : public Skill {
protected:
    float damageMultiplier;        // �˺�����
    string attackType;             // ��������
    int attackFrequency;           // ����Ƶ��
    skillEffectType extraEffect;   // ����Ч��
    float extraEffectIntensity;    // ����Ч��ǿ��
    int extraEffectDuration;       // ����Ч������ʱ��

public:
    // Ĭ�Ϲ��캯��
    offensiveSkill();

    // �������Ĺ��캯��
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

    // ��ȡ�˺�����
    float getDamageMultiplier() const;

    // ��ȡ��������
    string getAttackType() const;

    // ��ȡ����Ƶ��
    int getAttackFrequency() const;

    // ��ȡ����Ч��
    skillEffectType getEffect() const;

    // ��ȡЧ��ǿ��
    float getEffectIntensity() const;

    // ��ȡЧ������ʱ��
    int getDuration() const;

    // ���������ݱ��浽�ļ�
    void saveToFile(ofstream& file) const override;

    // ���ļ����ؼ�������
    void loadFromFile(ifstream& file) override;
};

class supportSkill : public Skill {
protected:
    skillEffectType effect;         // ����Ч��
    float effectIntensity;          // Ч��ǿ��
    int duration;                   // ����ʱ��

public:
    // Ĭ�Ϲ��캯��
    supportSkill();

    // �������Ĺ��캯��
    supportSkill(
        string name,
        string description,
        bool isAOE,
        bool isOffensive,
        bool isSelf,
        skillEffectType effect,
        float effectIntensity,
        int duration);

    // ��ȡ����Ч��
    skillEffectType getEffect() const;

    // ��ȡЧ��ǿ��
    float getEffectIntensity() const;

    // ��ȡЧ������ʱ��
    int getDuration() const;

    // ��ȡ�˺����������麯��ʵ�֣�
    float getDamageMultiplier() const override;

    // ��ȡ�������ͣ����麯��ʵ�֣�
    string getAttackType() const override;

    // ��ȡ����Ƶ�ʣ����麯��ʵ�֣�
    int getAttackFrequency() const override;

    // ���������ݱ��浽�ļ�
    void saveToFile(ofstream& file) const override;

    // ���ļ����ؼ�������
    void loadFromFile(ifstream& file) override;
};

#endif // SKILL_H
