#ifndef SKILL_H
#define SKILL_H

#include <iostream>
#include <vector>
#include "skillEffectType.h"

using namespace std;


class Skill
{
protected:
    string name;      // ��ʽ����
    bool isAOE;       // �Ƿ��Ƿ�ΧЧ��
    bool isOffensive; // �Ƿ��ǽ�������ʽ
    string description;//��ʽ����
    bool isSelf;//�Ƿ������Լ�
public:
    Skill();
    Skill(string name, string description, bool isAOE, bool isOffensive, bool isSelf);

    bool getIsAOE() const;//�����Ƿ�ΧЧ��

    string getName() const;//��������

    bool getIsOffensive() const;//�����Ƿ������ʽ

    string getDescription() const;//��������

    bool getIsSelf() const ;//�����Ƿ������Լ�

    virtual float getDamageMultiplier() const =0;//�����˺�����

    virtual string getAttackType() const = 0;//���ع�������

    virtual int getAttackFrequency() const = 0;//���ع���Ƶ��

    virtual skillEffectType getEffect() const = 0;//����Ч��

    virtual float getEffectIntensity() const = 0;//����Ч��ǿ��

    virtual int getDuration() const = 0;//����Ч������ʱ��

    


};

class offensiveSkill : public Skill
{
protected:
    float damageMultiplier;      // �˺�����
    string attackType;             // ����ȷ����ǰװ�������Ƿ����ʹ�ø���ʽ
    int attackFrequency;         // ��������
    skillEffectType extraEffect; // ����Ч��
    float extraEffectIntensity;  // ʵ��������x1.5 ��˯����0.5
    int extraEffectDuration;//����Ч������ʱ��
    

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
        int extraEffectDuration);//����

    float getDamageMultiplier() const;//�����˺�����

    string getAttackType() const;//���ع�������

    int getAttackFrequency() const;//���ع���Ƶ��

    skillEffectType getEffect() const;//����Ч��

    float getEffectIntensity() const;//����Ч��ǿ��

    int getDuration() const;//���س���ʱ��

    //�����Ƿ������Լ�
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
        int duration);//����
        

    skillEffectType getEffect() const;//������ʽЧ��

    float getEffectIntensity() const;//����Ч��ǿ��

    int getDuration() const;//���س���ʱ��

   //�����Ƿ������Լ�

    virtual float getDamageMultiplier() const;//�����˺�����

    virtual string getAttackType() const;//���ع�������

    virtual int getAttackFrequency() const;//���ع���Ƶ��
};

#endif