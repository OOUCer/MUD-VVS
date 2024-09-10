#include "character.h"
#include <iostream>
using namespace std;

Character::Character(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer)
    : name(name), attack(attack), HP(HP), maxHP(maxHP), defense(defense), speed(speed), hitRate(hitRate), evasionRate(evasionRate), gold(gold), isPlayer(isPlayer) {}

string Character::getName() const
{
    return name;
}

int Character::getAttack() const
{
    int currentAttack = attack + (weapons.empty() ? 0 : weapons[0]->getAttack());
    for (const auto& effect : effectStatus)
    {
        if (effect.first == selfAttackBoost || effect.first == giveAttackWeaken)
            currentAttack *= effect.second.first;
    }
    return currentAttack;
}

void Character::setAttack(int newAttack) { attack = newAttack; }

int Character::getHP()
{
    if (HP > getMaxHP())HP = getMaxHP();
    return HP;
}

void Character::modifyHP(int modifyAmount)
{
    HP += modifyAmount;
}

void Character::setHP(int newHP) { HP = newHP; }

int Character::getMaxHP() const
{
    return maxHP + (armors.empty() ? 0 : armors[0]->getHP());
}

void Character::setMaxHP(int newMaxHP) { maxHP = newMaxHP; }

int Character::getDefense() const
{
    int currentDefense = defense + (armors.empty() ? 0 : armors[0]->getDefense());
    for (const auto& effect : effectStatus)
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
    for (const auto& effect : effectStatus)
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
    for (const auto& effect : effectStatus)
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

void Character::setGold(int newGold) { gold = newGold; }
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


void Character::addEffect(const skillEffectType& effect, float intensity, int duration)
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
        weapon->be_get();
    }
}

void Character::addArmor(Armor* armor)
{
    if (armor != nullptr)
    {
        armors.push_back(armor);
        armor->be_get();
    }
}

void Character::addSkill(Skill* skill)
{
    if (skill != nullptr)
    {
        skills.push_back(skill);
    }
}

void Character::addOffensiveSkill(offensiveSkill* skill,bool flag)
{
    if(flag) 
        cout << "你学会了：" << skill->getName() << endl;
    if (skill != nullptr)
    {
        oSkills.push_back(skill);
        skill->be_get();
    }
}

void Character::addSupportSkill(supportSkill* skill,bool flag){
    if(flag)
        cout << "你学会了：" << skill->getName() << endl;
    if (skill != nullptr)
    {
        sSkills.push_back(skill);
        skill->be_get();
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

vector<Skill*>* Character::getSkills()
{
    return &skills;
}

vector<offensiveSkill*>* Character::getoSkills()
{
    return &oSkills;
}

vector<supportSkill*>* Character::getsSkills()
{
    return &sSkills;
}




Linchong::Linchong(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer, int place)
    : Character(name, attack, HP, maxHP, defense, speed, hitRate, evasionRate, gold, isPlayer), place(place) {}


int Linchong::getPlace() const
{
    return place;
}

void Linchong::changePlace(int t)
{
    cout << endl;
    cout << "你要去哪：" << endl;
    int placeflag;
    cin >> placeflag;
    if (t == 6)
    {
        if (placeflag != 5)
        {
            cout << "这里可没有酒喝" << endl;
            changePlace(t);
        }
    }
    else if (t <= 4)
    {
        if (placeflag == 4 || placeflag == 5 || placeflag == 7)
        {
            cout << "此地点暂未开放，请重新选择" << endl;
            changePlace(t);
        }
        else
        {
            cout << endl;
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
                cout << "市井";
                break;
            case 6:
                cout << "码头";
                break;
            case 7:
                cout << "古庙";
                break;
            }
            cout << endl;
        }
    
    }
    else
    {
        cout << endl;
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
            cout << "市井";
            break;
        case 6:
            cout << "码头";
            break;
        case 7:
            cout << "古庙";
            break;
        }
        cout << endl;
    }
   // Implement the logic to change the place of the character.
}

void Linchong::printWeapons() const
{
    for (const auto& weapon : weapons)
    {
        cout << weapon->getName() << ": " << weapon->getDescription() << endl;
    }
}

void Linchong::printArmors() const
{
    for (const auto& armor : armors)
    {
        cout << armor->getName() << ": " << armor->getDescription() << endl;
    }
}

bool Linchong::buyItem1(Weapon* equipment)
{
    for (const auto& weapon : weapons)
    {
        if (weapon->getName() == equipment->getName()) {
            cout << "你已经买过了，不需要再次购买哦！" << endl;
            return false;
        };
    }

    if (equipment->getPrice() <= gold)
    {
        gold -= equipment->getPrice();
        cout << "购买成功！你现在还有 " << gold << " 盘缠。" << endl;
        weapons.push_back(equipment);
        return true;
    }
    else
    {
        cout << "盘缠不足！你需要" << equipment->getPrice() << " ，但是你只有" << gold << "盘缠。" << endl;
        return false;
    }
}

bool Linchong::buyItem2(Armor* equipment)
{
    for (const auto& armor : armors)
    {
        if (armor->getName() == equipment->getName()) {
            cout << "你已经买过了，不需要再次购买哦！" << endl;
            return false;
        };
    }

    if (equipment->getPrice() <= gold)
    {
        gold -= equipment->getPrice();
        cout << "购买成功！你现在还有 " << gold << " 盘缠。" << endl;
        armors.push_back(equipment);
        return true;
    }
    else
    {
        cout << "盘缠不足！你需要" << equipment->getPrice() << " ，但是你只有" << gold << "盘缠。" << endl;
        return false;
    }
}

bool Linchong::buyItem11(Weapon* equipment)
{
    weapons.push_back(equipment); 
    return true;
}

bool Linchong::buyItem22(Armor* equipment)
{
    armors.push_back(equipment);
    return true;
}
void Linchong::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << getName() << "\n";
        outFile << getAttack() << "\n";
        outFile << HP << "\n";
        outFile << getMaxHP() << "\n";
        outFile << getDefense() << "\n";
        outFile << getSpeed() << "\n";
        outFile << getHitRate() << "\n";
        outFile << getEvasionRate() << "\n";
        outFile << getGold() << "\n";
        //outFile << getIsPlayer() << "\n";
        outFile << getPlace() << "\n";
    }

    outFile.close();
}

void Linchong::loadFromFile(const string& filename,Linchong *lc) {
    ifstream inFile(filename);
    string name;
    int attack1, HP1, maxHP1, defense1, speed1, gold1, place1;
    float hitRate1, evasionRate1;
    bool isPlayer;

    if (inFile.is_open()) {
        getline(inFile, name);
        inFile >> attack1;
        inFile >> HP1;
        inFile >> maxHP1;
        inFile >> defense1;
        inFile >> speed1;
        inFile >> hitRate1;
        inFile >> evasionRate1;
        inFile >> gold1;
        //inFile >> isPlayer;
        inFile >> place1;
    }
    inFile.close();
    //lc->setAttack(80);
    lc->setGold(gold1);
    //lc->setHP(HP1);
    //lc->setMaxHP(maxHP1);
    lc->setplace(place1);
    // Return a new Linchong object with the loaded values
    
}

void Linchong::setplace(int a)
{
    place = a;
    return ;
}
