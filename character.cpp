#include "character.h"
#include <iostream>
using namespace std;

Character::Character(const string &name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer)
    : name(name), attack(attack), HP(HP), maxHP(maxHP), defense(defense), speed(speed), hitRate(hitRate), evasionRate(evasionRate), gold(gold), isPlayer(isPlayer) {}

string Character::getName() const
{
    return name;
}

int Character::getAttack() const
{
    int currentAttack = attack + (weapons.empty() ? 0 : weapons[0]->getAttack());
    for (const auto &effect : effectStatus)
    {
        if (effect.first == selfAttackBoost || effect.first == giveAttackWeaken)
            currentAttack *= effect.second.first;
    }
    return currentAttack;
}

int Character::getHP() 
{
    if (HP > getMaxHP())HP =getMaxHP() ;
    return HP;
}

void Character::modifyHP(int modifyAmount)
{
    HP += modifyAmount;
}

int Character::getMaxHP() const
{
    return maxHP + (armors.empty() ? 0 : armors[0]->getHP());
}

int Character::getDefense() const
{
    int currentDefense = defense + (armors.empty() ? 0 : armors[0]->getDefense());
    for (const auto &effect : effectStatus)
    {
        if (effect.first == selfDefenseBoost || effect.first == giveDefenseWeaken)
            currentDefense *= effect.second.first;
    }
    return currentDefense;
}

int Character::getSpeed() const
{
    return speed + (weapons.empty() ? 0 : weapons[0]->getSpeed());
}

float Character::getHitRate() const
{
    float currentHitRate = hitRate + (weapons.empty() ? 0.0f : weapons[0]->getHitRate());
    for (const auto &effect : effectStatus)
    {
        if (effect.first == selfHitRateBoost || effect.first == giveHitRateWeaken)
            currentHitRate *= effect.second.first;
    }
    if (currentHitRate >= 1) return 1;
    return currentHitRate;
}

float Character::getEvasionRate() const
{
    float currentEvasionRate = evasionRate;
    for (const auto &effect : effectStatus)
    {
        if (effect.first == selfEvationBoost || effect.first == giveEvationWeaken)
            currentEvasionRate *= effect.second.first;
    }
    if (currentEvasionRate >= 1) return 1;
    return currentEvasionRate;
}

int Character::getGold() const
{
    return gold;
}

bool Character::isPlayerControlled() const
{
    return isPlayer;
}

void Character::setActionAvailability(bool isAvailable)
{
    actionAvailability = isAvailable;
}

bool Character::getActionAvailability()
{
    return actionAvailability;
}

void Character::setWeaknessReceivedStatus(bool isHit)
{
    hasReceivedWeaknessHit = isHit;
}

bool Character::getWeaknessReceivedStatus()
{
    return hasReceivedWeaknessHit;
}

void Character::setHitWeakness(bool hit)
{
    hitWeakness = hit;
}

bool Character::getHitWeakness()
{
    return hitWeakness;
}

int Character::getSkillPoint()
{
    return skillPoint;
}

void Character::setSkillPoint(int point)
{
    skillPoint = point;
}

int Character::getActionCount()
{
    return actionCount;
}

void Character::setActionCount(int count)
{
    actionCount = count;
}

bool Character::getAnticipateStatus()
{
    return isAnticipating;
}

void Character::setAnticipateStatus(bool theStatus)
{
    isAnticipating = theStatus;
}

bool Character::getComatoseStatus()
{
    return isComatose.first;
}

int Character::getComatoseDuration()
{
    return isComatose.second;
}

void Character::setComatoseStatus(bool theStatus, int duration)
{
    this->isComatose.first = theStatus;
    this->isComatose.second = duration;
}

bool Character::getChargeStatus()
{
    return isCharged;
}

void Character::setChargeStatus(bool theStatus)
{
    isCharged = theStatus;
}

Weapon* Character::getFirstWeapon()
{
    return !weapons.empty() ? weapons.front() : nullptr;
}

Armor* Character::getFirstArmor()
{
    return !armors.empty() ? armors.front() : nullptr;
}

vector<Skill*>* Character::getSkills()
{
    return &skills;
}

void Character::addEffect(const skillEffectType &effect, float intensity, int duration)
{
    effectStatus[effect] = make_pair(intensity, duration);
}

void Character::removeEffect(const skillEffectType& effect)
{
    for (auto it = effectStatus.begin(); it != effectStatus.end(); )
    {
        if (it->first == effect)
        {
            it = effectStatus.erase(it);   
            break;   
        }
        else
        {
            ++it; 
        }
    } 
}

void Character::addWeapon(Weapon* weapon)
{
    if (weapon != nullptr)
    {
        weapons.push_back(weapon);
    }
}

void Character::addArmor(Armor* armor)
{
    if (armor != nullptr)
    {
        armors.push_back(armor);
    }
}

void Character::addSkill(Skill* skill)
{
    if (skill != nullptr)
    {
        skills.push_back(skill);
    }
}

map<skillEffectType, pair<float, int>>* Character::getEffectStatus()
{
    return &effectStatus;
}

vector<Weapon*>* Character::getWeapons()
{
    return &weapons;
}

vector<Armor*>* Character::getArmors()
{
    return &armors;
}



Linchong::Linchong(const string &name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer, int place)
    : Character(name, attack, HP, maxHP, defense, speed, hitRate, evasionRate, gold, isPlayer), place(place) {}


int Linchong::getPlace() const
{
    return place;
}

void Linchong::changePlace()
{
    cout << "你要去哪：" << endl;
    int placeflag;
    cin >> placeflag;
    cout << "你来到了";
    place = placeflag;
    switch (place)
    {
    case 1:
        cout << "茶酒店";
        break;
    case 2:
        cout << "武馆";
        break;
    case 3:
        cout << "营房";
        break;
    case 4:
        cout << "草料场";
        break;
    case 5:
        cout << "茶酒店";
        break;
    case 6:
        cout << "市井";
        break;
    case 7:
        cout << "古庙";
        break;
    }// Implement the logic to change the place of the character.
}

void Linchong::printWeapons() const
{
    for (const auto &weapon : weapons)
    {
        cout << weapon->getName() << ": " << weapon->getDescription() << endl;
    }
}

void Linchong::printArmors() const
{
    for (const auto &armor : armors)
    {
        cout << armor->getName() << ": " << armor->getDescription() << endl;
    }
}

bool Linchong::buyItem1(Weapon *equipment)
{
    if (equipment->getPrice() <= gold)
    {
        gold -= equipment->getPrice();
        cout << "购买成功！你现在还有 " << gold << " 块钱" << endl;
        weapons.push_back(equipment);
        return true;
    }
    else
    {
        cout << "钱不够！你需要" << equipment->getPrice() << "块钱，但是你只有" << gold << "块钱." << endl;
        return false;
    }
}

bool Linchong::buyItem2(Armor *equipment)
{
    if (equipment->getPrice() <= gold)
    {
        gold -= equipment->getPrice();
        cout << "购买成功！你现在还有 " << gold << " 块钱" << endl;
        armors.push_back(equipment);
        return true;
    }
    else
    {
        cout << "钱不够！你需要" << equipment->getPrice() << "块钱，但是你只有" << gold << "块钱." << endl;
        return false;
    }
}