#include "character.h"
#include <iostream>
using namespace std;

// Character类的构造函数，初始化角色的基本属性
Character::Character(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer)
    : name(name), attack(attack), HP(HP), maxHP(maxHP), defense(defense), speed(speed), hitRate(hitRate), evasionRate(evasionRate), gold(gold), isPlayer(isPlayer) {}

// 获取角色的名字
string Character::getName() const
{
    return name;
}

// 获取角色的攻击力，包含武器加成和效果状态（如攻击增强或削弱）
int Character::getAttack() const
{
    // 初始攻击力为基础攻击力加上当前装备的武器攻击力
    int currentAttack = attack + (weapons.empty() ? 0 : weapons[0]->getAttack());

    // 遍历所有效果状态，调整攻击力
    for (const auto& effect : effectStatus)
    {
        // 如果效果为攻击增强或攻击削弱，则调整攻击力
        if (effect.first == selfAttackBoost || effect.first == giveAttackWeaken)
            currentAttack *= effect.second.first; // 按倍率调整攻击力
    }

    return currentAttack;
}

// 设置角色的基础攻击力
void Character::setAttack(int newAttack) { attack = newAttack; }

// 获取角色的当前HP，确保当前HP不超过最大HP
int Character::getHP()
{
    if (HP > getMaxHP()) HP = getMaxHP(); // 如果当前HP大于最大HP，则将其设为最大HP
    return HP;
}

// 修改角色的HP，增加或减少指定的数值
void Character::modifyHP(int modifyAmount)
{
    HP += modifyAmount; // 按指定数值调整HP
}

// 设置角色的HP
void Character::setHP(int newHP) { HP = newHP; }

// 获取角色的最大HP，包括防具的加成
int Character::getMaxHP() const
{
    // 最大HP为基础HP加上当前装备的防具的HP加成
    return maxHP + (armors.empty() ? 0 : armors[0]->getHP());
}

// 设置角色的最大HP
void Character::setMaxHP(int newMaxHP) { maxHP = newMaxHP; }

// 获取角色的防御力，包含防具加成和效果状态（如防御增强或削弱）
int Character::getDefense() const
{
    // 初始防御力为基础防御力加上当前装备的防具防御力
    int currentDefense = defense + (armors.empty() ? 0 : armors[0]->getDefense());

    // 遍历所有效果状态，调整防御力
    for (const auto& effect : effectStatus)
    {
        // 如果效果为防御增强或防御削弱，则调整防御力
        if (effect.first == selfDefenseBoost || effect.first == giveDefenseWeaken)
            currentDefense *= effect.second.first; // 按倍率调整防御力
    }

    return currentDefense;
}

// 获取角色的速度，包含武器加成
int Character::getSpeed() const
{
    // 速度为基础速度加上当前装备的武器的速度加成
    return speed + (weapons.empty() ? 0 : weapons[0]->getSpeed());
}

// 获取角色的命中率，包含武器加成和效果状态（如命中增强或削弱）
float Character::getHitRate() const
{
    // 初始命中率为基础命中率加上当前装备的武器命中率加成
    float currentHitRate = hitRate + (weapons.empty() ? 0.0f : weapons[0]->getHitRate());

    // 遍历所有效果状态，调整命中率
    for (const auto& effect : effectStatus)
    {
        // 如果效果为命中增强或命中削弱，则调整命中率
        if (effect.first == selfHitRateBoost || effect.first == giveHitRateWeaken)
            currentHitRate *= effect.second.first; // 按倍率调整命中率
    }

    // 确保命中率不会超过1
    if (currentHitRate >= 1) return 1;
    return currentHitRate;
}

// 获取角色的闪避率，包含效果状态（如闪避增强或削弱）
float Character::getEvasionRate() const
{
    // 初始闪避率为基础闪避率
    float currentEvasionRate = evasionRate;

    // 遍历所有效果状态，调整闪避率
    for (const auto& effect : effectStatus)
    {
        // 如果效果为闪避增强或闪避削弱，则调整闪避率
        if (effect.first == selfEvationBoost || effect.first == giveEvationWeaken)
            currentEvasionRate *= effect.second.first; // 按倍率调整闪避率
    }

    // 确保闪避率不会超过1
    if (currentEvasionRate >= 1) return 1;
    return currentEvasionRate;
}

// 获取角色的金币数
int Character::getGold() const
{
    return gold;
}

// 设置角色的金币数
void Character::setGold(int newGold) { gold = newGold; }

// 判断角色是否是玩家控制
bool Character::isPlayerControlled() const
{
    return isPlayer;
}

// 设置角色的行动是否可用
void Character::setActionAvailability(bool isAvailable)
{
    actionAvailability = isAvailable;
}

// 获取角色的行动可用状态
bool Character::getActionAvailability()
{
    return actionAvailability;
}

// 设置角色是否受到了弱点攻击
void Character::setWeaknessReceivedStatus(bool isHit)
{
    hasReceivedWeaknessHit = isHit;
}

// 获取角色是否受到了弱点攻击的状态
bool Character::getWeaknessReceivedStatus()
{
    return hasReceivedWeaknessHit;
}

// 设置角色是否击中敌人的弱点
void Character::setHitWeakness(bool hit)
{
    hitWeakness = hit;
}

// 获取角色是否击中敌人的弱点的状态
bool Character::getHitWeakness()
{
    return hitWeakness;
}

// 获取角色的技能点数
int Character::getSkillPoint()
{
    return skillPoint;
}

// 设置角色的技能点数
void Character::setSkillPoint(int point)
{
    skillPoint = point;
}

// 获取角色的行动次数
int Character::getActionCount()
{
    return actionCount;
}

// 设置角色的行动次数
void Character::setActionCount(int count)
{
    actionCount = count;
}

// 获取角色的预测状态
bool Character::getAnticipateStatus()
{
    return isAnticipating;
}

// 设置角色的预测状态
void Character::setAnticipateStatus(bool theStatus)
{
    isAnticipating = theStatus;
}

// 获取角色的昏迷状态
bool Character::getComatoseStatus()
{
    return isComatose.first;
}

// 获取昏迷持续时间
int Character::getComatoseDuration()
{
    return isComatose.second;
}

// 设置角色的昏迷状态和持续时间
void Character::setComatoseStatus(bool theStatus, int duration)
{
    this->isComatose.first = theStatus;
    this->isComatose.second = duration;
}

// 获取角色的蓄力状态
bool Character::getChargeStatus()
{
    return isCharged;
}

// 设置角色的蓄力状态
void Character::setChargeStatus(bool theStatus)
{
    isCharged = theStatus;
}

// 获取角色装备的第一件武器
Weapon* Character::getFirstWeapon()
{
    return !weapons.empty() ? weapons.front() : nullptr;
}

// 获取角色装备的第一件防具
Armor* Character::getFirstArmor()
{
    return !armors.empty() ? armors.front() : nullptr;
}

// 添加技能效果，效果包括强度和持续时间
void Character::addEffect(const skillEffectType& effect, float intensity, int duration)
{
    effectStatus[effect] = make_pair(intensity, duration);
}

// 移除指定的技能效果
void Character::removeEffect(const skillEffectType& effect)
{
    // 遍历效果状态的map，找到匹配的效果并移除
    for (auto it = effectStatus.begin(); it != effectStatus.end(); )
    {
        if (it->first == effect)
        {
            it = effectStatus.erase(it);
            break; // 移除后跳出循环
        }
        else
        {
            ++it;
        }
    }
}

// 添加武器到角色的武器列表
void Character::addWeapon(Weapon* weapon)
{
    if (weapon != nullptr) // 确保武器有效
    {
        weapons.push_back(weapon);
        weapon->be_get(); // 标记武器被获取
    }
}

// 添加防具到角色的防具列表
void Character::addArmor(Armor* armor)
{
    if (armor != nullptr) // 确保防具有效
    {
        armors.push_back(armor);
        armor->be_get(); // 标记防具被获取
    }
}

// 添加技能到角色的技能列表
void Character::addSkill(Skill* skill)
{
    if (skill != nullptr) // 确保技能有效
    {
        skills.push_back(skill);
    }
}

// 添加攻击技能到角色的攻击技能列表，并输出学习提示
void Character::addOffensiveSkill(offensiveSkill* skill, bool flag)
{
    if (flag)
        cout << "你学会了：" << skill->getName() << endl;
    if (skill != nullptr) // 确保技能有效
    {
        oSkills.push_back(skill);
        skill->be_get(); // 标记技能被获取
    }
}

// 添加支援技能到角色的支援技能列表，并输出学习提示
void Character::addSupportSkill(supportSkill* skill, bool flag)
{
    if (flag)
        cout << "你学会了：" << skill->getName() << endl;
    if (skill != nullptr) // 确保技能有效
    {
        sSkills.push_back(skill);
        skill->be_get(); // 标记技能被获取
    }
}

// 获取角色的效果状态，返回效果状态的map指针
map<skillEffectType, pair<float, int>>* Character::getEffectStatus()
{
    return &effectStatus;
}

// 获取角色的武器列表，返回武器向量的指针
vector<Weapon*>* Character::getWeapons()
{
    return &weapons;
}

// 获取角色的防具列表，返回防具向量的指针
vector<Armor*>* Character::getArmors()
{
    return &armors;
}

// 获取角色的技能列表，返回技能向量的指针
vector<Skill*>* Character::getSkills()
{
    return &skills;
}

// 获取角色的攻击技能列表，返回攻击技能向量的指针
vector<offensiveSkill*>* Character::getoSkills()
{
    return &oSkills;
}

// 获取角色的支援技能列表，返回支援技能向量的指针
vector<supportSkill*>* Character::getsSkills()
{
    return &sSkills;
}

// Linchong 构造函数，调用父类 Character 的构造函数，同时初始化 place
Linchong::Linchong(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer, int place)
    : Character(name, attack, HP, maxHP, defense, speed, hitRate, evasionRate, gold, isPlayer), place(place) {}

// 获取当前 Linchong 对象的所在地点
int Linchong::getPlace() const
{
    return place;  // 返回当前的 place
}

// 改变 Linchong 的位置，根据输入的 t 进行位置选择
void Linchong::changePlace(int t)
{
    cout << endl;
    cout << "你要去哪：" << endl;  // 提示用户选择地点
    int placeflag;
    cin >> placeflag;  // 读取用户输入的地点编号

    // 如果 t == 6, 强制用户选择 5 号地点
    if (t == 6)
    {
        if (placeflag != 5)
        {
            cout << "这里可没有酒喝" << endl;
            changePlace(t);  // 若不是地点 5，重新选择
        }
    }
    // 如果 t <= 4，限制用户选择的地点
    else if (t <= 4)
    {
        if (placeflag == 4 || placeflag == 5 || placeflag == 7)
        {
            cout << "此地点暂未开放，请重新选择" << endl;  // 某些地点暂时未开放
            changePlace(t);  // 重新选择地点
        }
        else
        {
            cout << endl;
            cout << "你来到了";  // 成功更改地点
            place = placeflag;  // 更新 Linchong 的地点
            // 根据 place 的值打印对应的地点名称
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
    // 如果 t > 4，允许选择任意地点
    else
    {
        cout << endl;
        cout << "你来到了";
        place = placeflag;  // 更新地点为用户选择的值
        // 根据 place 的值打印对应的地点名称
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
    // 更改地点的逻辑实现结束
}

// 打印 Linchong 当前拥有的武器信息
void Linchong::printWeapons() const
{
    for (const auto& weapon : weapons)  // 遍历武器列表
    {
        cout << weapon->getName() << ": " << weapon->getDescription() << endl;  // 输出武器的名称和描述
    }
}

// 打印 Linchong 当前拥有的防具信息
void Linchong::printArmors() const
{
    for (const auto& armor : armors)  // 遍历防具列表
    {
        cout << armor->getName() << ": " << armor->getDescription() << endl;  // 输出防具的名称和描述
    }
}

// 购买武器，返回是否成功
bool Linchong::buyItem1(Weapon* equipment)
{
    // 检查是否已拥有该武器
    for (const auto& weapon : weapons)
    {
        if (weapon->getName() == equipment->getName()) {
            cout << "你已经买过了，不需要再次购买哦！" << endl;  // 如果已经拥有该武器，则不再购买
            return false;
        };
    }

    // 检查是否有足够的金钱购买武器
    if (equipment->getPrice() <= gold)
    {
        gold -= equipment->getPrice();  // 扣除对应的金钱
        cout << "购买成功！你现在还有 " << gold << " 盘缠。" << endl;
        weapons.push_back(equipment);  // 将武器加入武器列表
        return true;
    }
    else
    {
        cout << "盘缠不足！你需要" << equipment->getPrice() << " ，但是你只有" << gold << "盘缠。" << endl;  // 金钱不足，无法购买
        return false;
    }
}

// 购买防具，返回是否成功
bool Linchong::buyItem2(Armor* equipment)
{
    // 检查是否已拥有该防具
    for (const auto& armor : armors)
    {
        if (armor->getName() == equipment->getName()) {
            cout << "你已经买过了，不需要再次购买哦！" << endl;  // 如果已经拥有该防具，则不再购买
            return false;
        };
    }

    // 检查是否有足够的金钱购买防具
    if (equipment->getPrice() <= gold)
    {
        gold -= equipment->getPrice();  // 扣除对应的金钱
        cout << "购买成功！你现在还有 " << gold << " 盘缠。" << endl;
        armors.push_back(equipment);  // 将防具加入防具列表
        return true;
    }
    else
    {
        cout << "盘缠不足！你需要" << equipment->getPrice() << " ，但是你只有" << gold << "盘缠。" << endl;  // 金钱不足，无法购买
        return false;
    }
}

// 直接将 Weapon 对象加入武器列表，无需任何额外检查
bool Linchong::buyItem11(Weapon* equipment)
{
    weapons.push_back(equipment);  // 将武器加入武器列表
    return true;  // 操作成功，返回 true
}

// 直接将 Armor 对象加入防具列表，无需任何额外检查
bool Linchong::buyItem22(Armor* equipment)
{
    armors.push_back(equipment);  // 将防具加入防具列表
    return true;  // 操作成功，返回 true
}

// 将 Linchong 对象的属性保存到指定文件中
void Linchong::saveToFile(const string& filename) const {
    ofstream outFile(filename);  // 打开文件进行写入
    if (outFile.is_open()) {
        outFile << getName() << "\n";  // 保存角色名称
        outFile << getAttack() << "\n";  // 保存攻击力
        outFile << HP << "\n";  // 保存当前 HP
        outFile << getMaxHP() << "\n";  // 保存最大 HP
        outFile << getDefense() << "\n";  // 保存防御力
        outFile << getSpeed() << "\n";  // 保存速度
        outFile << getHitRate() << "\n";  // 保存命中率
        outFile << getEvasionRate() << "\n";  // 保存闪避率
        outFile << getGold() << "\n";  // 保存金币数量
        //outFile << getIsPlayer() << "\n";  // 如果需要保存是否是玩家角色，可以取消注释
        outFile << getPlace() << "\n";  // 保存当前所在地点
    }
    outFile.close();  // 关闭文件
}

// 从文件中加载 Linchong 对象的属性
void Linchong::loadFromFile(const string& filename, Linchong* lc) {
    ifstream inFile(filename);  // 打开文件进行读取
    string name;  // 角色名称
    int attack1, HP1, maxHP1, defense1, speed1, gold1, place1;  // 各项属性
    float hitRate1, evasionRate1;  // 命中率和闪避率
    bool isPlayer;  // 是否为玩家角色（如果需要）

    if (inFile.is_open()) {
        getline(inFile, name);  // 读取角色名称
        inFile >> attack1;  // 读取攻击力
        inFile >> HP1;  // 读取当前 HP
        inFile >> maxHP1;  // 读取最大 HP
        inFile >> defense1;  // 读取防御力
        inFile >> speed1;  // 读取速度
        inFile >> hitRate1;  // 读取命中率
        inFile >> evasionRate1;  // 读取闪避率
        inFile >> gold1;  // 读取金币数量
        //inFile >> isPlayer;  // 如果需要读取是否是玩家角色，可以取消注释
        inFile >> place1;  // 读取当前地点
    }
    inFile.close();  // 关闭文件

    // 将读取到的属性赋值给 lc 对象
    lc->setGold(gold1);  // 设置金币数量
    lc->setplace(place1);  // 设置当前地点
    //lc->setAttack(attack1);  // 如果需要设置攻击力，可以取消注释
    //lc->setHP(HP1);  // 如果需要设置 HP，可以取消注释
    //lc->setMaxHP(maxHP1);  // 如果需要设置最大 HP，可以取消注释
    //lc->setIsPlayer(isPlayer);  // 如果需要设置是否是玩家角色，可以取消注释
}

// 设置 Linchong 对象的当前地点
void Linchong::setplace(int a)
{
    place = a;  // 更新 place 值
    return;  // 无需返回任何值
}
