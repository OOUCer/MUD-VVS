#include "skill.h"

using namespace std;

Skill::Skill(string name, bool isAOE, bool isOffensive) : name(name), isAOE(isAOE), isOffensive(isOffensive) {}

offensiveSkill::offensiveSkill(
    string name,
    bool isAOE,
    bool isOffensive,
    float damageMultiplier,
    string attackType,
    int attackFrequency,
    skillEffectType extraEffect,
    float extraEffectIntensity,
    int extraEffectDuration) : Skill(name, isAOE, isOffensive),
                               damageMultiplier(damageMultiplier),
                               attackType(attackType),
                               attackFrequency(attackFrequency),
                               extraEffect(extraEffect),
                               extraEffectIntensity(extraEffectIntensity),
                               extraEffectDuration(extraEffectDuration) {};
                               
supportSkill::supportSkill(
    string name,
    bool isAOE,
    bool isOffensive,
    bool isSelf,
    skillEffectType effect,
    float effectIntensity,
    int duration) : Skill(name, isAOE, isOffensive),
                    isSelf(isSelf),
                    effect(effect),
                    effectIntensity(effectIntensity),
                    duration(duration) {};

bool Skill::getIsAOE() const { return isAOE; }

string Skill::getName() const { return name; }

bool Skill::getIsOffensive() const { return isOffensive; }

float offensiveSkill::getDamageMultiplier() const { return damageMultiplier; }

string offensiveSkill::getAttackType() const { return attackType; }

int offensiveSkill::getAttackFrequency() const { return attackFrequency; }

skillEffectType offensiveSkill::getEffect() const { return extraEffect; }

float offensiveSkill::getEffectIntensity() const { return extraEffectIntensity; }

int offensiveSkill::getDuration() const { return extraEffectDuration; }

bool offensiveSkill::getIsSelf() const
{
    return false;
}

skillEffectType supportSkill::getEffect() const { return effect; }

float supportSkill::getEffectIntensity() const { return effectIntensity; }

int supportSkill::getDuration() const { return duration; }

bool supportSkill::getIsSelf() const
{
    return isSelf;
}

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
