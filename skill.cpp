#include "skill.h"

using namespace std;

Skill::Skill()
{
    name = " ";
    description = " ";
    isAOE = 0;
    isOffensive = 0;
    isSelf = 0;
}

Skill::Skill(string name, string description,bool isAOE, bool isOffensive,bool isSelf) : name(name),description(description), isAOE(isAOE), isOffensive(isOffensive),isSelf(isSelf) {}

offensiveSkill::offensiveSkill()
{
    damageMultiplier = 0.0;
    attackType = " ";
    attackFrequency = 0;
    extraEffectIntensity = 0.0;
    extraEffect = none;
    extraEffectDuration = 0;
}

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
    int extraEffectDuration) : Skill(name, description,isAOE, isOffensive,isSelf),
                               //isSelf(isSelf),
                               damageMultiplier(damageMultiplier),
                               attackType(attackType),
                               attackFrequency(attackFrequency),
                               extraEffect(extraEffect),
                               extraEffectIntensity(extraEffectIntensity),
                               extraEffectDuration(extraEffectDuration) {};
                               
supportSkill::supportSkill()
{
    effect = none;
    effectIntensity = 0.0;
    duration = 0;
}

supportSkill::supportSkill(
    string name,
    string description,
    bool isAOE,
    bool isOffensive,
    bool isSelf,
    skillEffectType effect,
    float effectIntensity,
    int duration) : Skill(name,description, isAOE, isOffensive,isSelf),
                    //isSelf(isSelf),
                    effect(effect),
                    effectIntensity(effectIntensity),
                    duration(duration) {};

bool Skill::getIsAOE() const { return isAOE; }

string Skill::getName() const { return name; }

bool Skill::getIsOffensive() const { return isOffensive; }

string Skill::getDescription() const
{
    return description;
}

bool Skill::getIsSelf() const
{
    return isSelf;
}

float offensiveSkill::getDamageMultiplier() const { return damageMultiplier; }

string offensiveSkill::getAttackType() const { return attackType; }

int offensiveSkill::getAttackFrequency() const { return attackFrequency; }

skillEffectType offensiveSkill::getEffect() const { return extraEffect; }

float offensiveSkill::getEffectIntensity() const { return extraEffectIntensity; }

int offensiveSkill::getDuration() const { return extraEffectDuration; }

/*
bool offensiveSkill::getIsSelf() const
{
    return isSelf;
}*/

skillEffectType supportSkill::getEffect() const { return effect; }

float supportSkill::getEffectIntensity() const { return effectIntensity; }

int supportSkill::getDuration() const { return duration; }

//bool supportSkill::getIsSelf() const
//{
//    return isSelf;
//}

float supportSkill::getDamageMultiplier() const
{
    return 0.0f;
}

string supportSkill::getAttackType() const
{
    return string();
}

int supportSkill::getAttackFrequency() const
{
    return 0;
}
