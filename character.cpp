#include "character.h"
#include <iostream>
using namespace std;

// Character��Ĺ��캯������ʼ����ɫ�Ļ�������
Character::Character(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer)
    : name(name), attack(attack), HP(HP), maxHP(maxHP), defense(defense), speed(speed), hitRate(hitRate), evasionRate(evasionRate), gold(gold), isPlayer(isPlayer) {}

// ��ȡ��ɫ������
string Character::getName() const
{
    return name;
}

// ��ȡ��ɫ�Ĺ����������������ӳɺ�Ч��״̬���繥����ǿ��������
int Character::getAttack() const
{
    // ��ʼ������Ϊ�������������ϵ�ǰװ��������������
    int currentAttack = attack + (weapons.empty() ? 0 : weapons[0]->getAttack());

    // ��������Ч��״̬������������
    for (const auto& effect : effectStatus)
    {
        // ���Ч��Ϊ������ǿ�򹥻������������������
        if (effect.first == selfAttackBoost || effect.first == giveAttackWeaken)
            currentAttack *= effect.second.first; // �����ʵ���������
    }

    return currentAttack;
}

// ���ý�ɫ�Ļ���������
void Character::setAttack(int newAttack) { attack = newAttack; }

// ��ȡ��ɫ�ĵ�ǰHP��ȷ����ǰHP���������HP
int Character::getHP()
{
    if (HP > getMaxHP()) HP = getMaxHP(); // �����ǰHP�������HP��������Ϊ���HP
    return HP;
}

// �޸Ľ�ɫ��HP�����ӻ����ָ������ֵ
void Character::modifyHP(int modifyAmount)
{
    HP += modifyAmount; // ��ָ����ֵ����HP
}

// ���ý�ɫ��HP
void Character::setHP(int newHP) { HP = newHP; }

// ��ȡ��ɫ�����HP���������ߵļӳ�
int Character::getMaxHP() const
{
    // ���HPΪ����HP���ϵ�ǰװ���ķ��ߵ�HP�ӳ�
    return maxHP + (armors.empty() ? 0 : armors[0]->getHP());
}

// ���ý�ɫ�����HP
void Character::setMaxHP(int newMaxHP) { maxHP = newMaxHP; }

// ��ȡ��ɫ�ķ��������������߼ӳɺ�Ч��״̬���������ǿ��������
int Character::getDefense() const
{
    // ��ʼ������Ϊ�������������ϵ�ǰװ���ķ��߷�����
    int currentDefense = defense + (armors.empty() ? 0 : armors[0]->getDefense());

    // ��������Ч��״̬������������
    for (const auto& effect : effectStatus)
    {
        // ���Ч��Ϊ������ǿ����������������������
        if (effect.first == selfDefenseBoost || effect.first == giveDefenseWeaken)
            currentDefense *= effect.second.first; // �����ʵ���������
    }

    return currentDefense;
}

// ��ȡ��ɫ���ٶȣ����������ӳ�
int Character::getSpeed() const
{
    // �ٶ�Ϊ�����ٶȼ��ϵ�ǰװ�����������ٶȼӳ�
    return speed + (weapons.empty() ? 0 : weapons[0]->getSpeed());
}

// ��ȡ��ɫ�������ʣ����������ӳɺ�Ч��״̬����������ǿ��������
float Character::getHitRate() const
{
    // ��ʼ������Ϊ���������ʼ��ϵ�ǰװ�������������ʼӳ�
    float currentHitRate = hitRate + (weapons.empty() ? 0.0f : weapons[0]->getHitRate());

    // ��������Ч��״̬������������
    for (const auto& effect : effectStatus)
    {
        // ���Ч��Ϊ������ǿ�����������������������
        if (effect.first == selfHitRateBoost || effect.first == giveHitRateWeaken)
            currentHitRate *= effect.second.first; // �����ʵ���������
    }

    // ȷ�������ʲ��ᳬ��1
    if (currentHitRate >= 1) return 1;
    return currentHitRate;
}

// ��ȡ��ɫ�������ʣ�����Ч��״̬����������ǿ��������
float Character::getEvasionRate() const
{
    // ��ʼ������Ϊ����������
    float currentEvasionRate = evasionRate;

    // ��������Ч��״̬������������
    for (const auto& effect : effectStatus)
    {
        // ���Ч��Ϊ������ǿ�����������������������
        if (effect.first == selfEvationBoost || effect.first == giveEvationWeaken)
            currentEvasionRate *= effect.second.first; // �����ʵ���������
    }

    // ȷ�������ʲ��ᳬ��1
    if (currentEvasionRate >= 1) return 1;
    return currentEvasionRate;
}

// ��ȡ��ɫ�Ľ����
int Character::getGold() const
{
    return gold;
}

// ���ý�ɫ�Ľ����
void Character::setGold(int newGold) { gold = newGold; }

// �жϽ�ɫ�Ƿ�����ҿ���
bool Character::isPlayerControlled() const
{
    return isPlayer;
}

// ���ý�ɫ���ж��Ƿ����
void Character::setActionAvailability(bool isAvailable)
{
    actionAvailability = isAvailable;
}

// ��ȡ��ɫ���ж�����״̬
bool Character::getActionAvailability()
{
    return actionAvailability;
}

// ���ý�ɫ�Ƿ��ܵ������㹥��
void Character::setWeaknessReceivedStatus(bool isHit)
{
    hasReceivedWeaknessHit = isHit;
}

// ��ȡ��ɫ�Ƿ��ܵ������㹥����״̬
bool Character::getWeaknessReceivedStatus()
{
    return hasReceivedWeaknessHit;
}

// ���ý�ɫ�Ƿ���е��˵�����
void Character::setHitWeakness(bool hit)
{
    hitWeakness = hit;
}

// ��ȡ��ɫ�Ƿ���е��˵������״̬
bool Character::getHitWeakness()
{
    return hitWeakness;
}

// ��ȡ��ɫ�ļ��ܵ���
int Character::getSkillPoint()
{
    return skillPoint;
}

// ���ý�ɫ�ļ��ܵ���
void Character::setSkillPoint(int point)
{
    skillPoint = point;
}

// ��ȡ��ɫ���ж�����
int Character::getActionCount()
{
    return actionCount;
}

// ���ý�ɫ���ж�����
void Character::setActionCount(int count)
{
    actionCount = count;
}

// ��ȡ��ɫ��Ԥ��״̬
bool Character::getAnticipateStatus()
{
    return isAnticipating;
}

// ���ý�ɫ��Ԥ��״̬
void Character::setAnticipateStatus(bool theStatus)
{
    isAnticipating = theStatus;
}

// ��ȡ��ɫ�Ļ���״̬
bool Character::getComatoseStatus()
{
    return isComatose.first;
}

// ��ȡ���Գ���ʱ��
int Character::getComatoseDuration()
{
    return isComatose.second;
}

// ���ý�ɫ�Ļ���״̬�ͳ���ʱ��
void Character::setComatoseStatus(bool theStatus, int duration)
{
    this->isComatose.first = theStatus;
    this->isComatose.second = duration;
}

// ��ȡ��ɫ������״̬
bool Character::getChargeStatus()
{
    return isCharged;
}

// ���ý�ɫ������״̬
void Character::setChargeStatus(bool theStatus)
{
    isCharged = theStatus;
}

// ��ȡ��ɫװ���ĵ�һ������
Weapon* Character::getFirstWeapon()
{
    return !weapons.empty() ? weapons.front() : nullptr;
}

// ��ȡ��ɫװ���ĵ�һ������
Armor* Character::getFirstArmor()
{
    return !armors.empty() ? armors.front() : nullptr;
}

// ��Ӽ���Ч����Ч������ǿ�Ⱥͳ���ʱ��
void Character::addEffect(const skillEffectType& effect, float intensity, int duration)
{
    effectStatus[effect] = make_pair(intensity, duration);
}

// �Ƴ�ָ���ļ���Ч��
void Character::removeEffect(const skillEffectType& effect)
{
    // ����Ч��״̬��map���ҵ�ƥ���Ч�����Ƴ�
    for (auto it = effectStatus.begin(); it != effectStatus.end(); )
    {
        if (it->first == effect)
        {
            it = effectStatus.erase(it);
            break; // �Ƴ�������ѭ��
        }
        else
        {
            ++it;
        }
    }
}

// �����������ɫ�������б�
void Character::addWeapon(Weapon* weapon)
{
    if (weapon != nullptr) // ȷ��������Ч
    {
        weapons.push_back(weapon);
        weapon->be_get(); // �����������ȡ
    }
}

// ��ӷ��ߵ���ɫ�ķ����б�
void Character::addArmor(Armor* armor)
{
    if (armor != nullptr) // ȷ��������Ч
    {
        armors.push_back(armor);
        armor->be_get(); // ��Ƿ��߱���ȡ
    }
}

// ��Ӽ��ܵ���ɫ�ļ����б�
void Character::addSkill(Skill* skill)
{
    if (skill != nullptr) // ȷ��������Ч
    {
        skills.push_back(skill);
    }
}

// ��ӹ������ܵ���ɫ�Ĺ��������б������ѧϰ��ʾ
void Character::addOffensiveSkill(offensiveSkill* skill, bool flag)
{
    if (flag)
        cout << "��ѧ���ˣ�" << skill->getName() << endl;
    if (skill != nullptr) // ȷ��������Ч
    {
        oSkills.push_back(skill);
        skill->be_get(); // ��Ǽ��ܱ���ȡ
    }
}

// ���֧Ԯ���ܵ���ɫ��֧Ԯ�����б������ѧϰ��ʾ
void Character::addSupportSkill(supportSkill* skill, bool flag)
{
    if (flag)
        cout << "��ѧ���ˣ�" << skill->getName() << endl;
    if (skill != nullptr) // ȷ��������Ч
    {
        sSkills.push_back(skill);
        skill->be_get(); // ��Ǽ��ܱ���ȡ
    }
}

// ��ȡ��ɫ��Ч��״̬������Ч��״̬��mapָ��
map<skillEffectType, pair<float, int>>* Character::getEffectStatus()
{
    return &effectStatus;
}

// ��ȡ��ɫ�������б���������������ָ��
vector<Weapon*>* Character::getWeapons()
{
    return &weapons;
}

// ��ȡ��ɫ�ķ����б����ط���������ָ��
vector<Armor*>* Character::getArmors()
{
    return &armors;
}

// ��ȡ��ɫ�ļ����б����ؼ���������ָ��
vector<Skill*>* Character::getSkills()
{
    return &skills;
}

// ��ȡ��ɫ�Ĺ��������б����ع�������������ָ��
vector<offensiveSkill*>* Character::getoSkills()
{
    return &oSkills;
}

// ��ȡ��ɫ��֧Ԯ�����б�����֧Ԯ����������ָ��
vector<supportSkill*>* Character::getsSkills()
{
    return &sSkills;
}

// Linchong ���캯�������ø��� Character �Ĺ��캯����ͬʱ��ʼ�� place
Linchong::Linchong(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer, int place)
    : Character(name, attack, HP, maxHP, defense, speed, hitRate, evasionRate, gold, isPlayer), place(place) {}

// ��ȡ��ǰ Linchong ��������ڵص�
int Linchong::getPlace() const
{
    return place;  // ���ص�ǰ�� place
}

// �ı� Linchong ��λ�ã���������� t ����λ��ѡ��
void Linchong::changePlace(int t)
{
    cout << endl;
    cout << "��Ҫȥ�ģ�" << endl;  // ��ʾ�û�ѡ��ص�
    int placeflag;
    cin >> placeflag;  // ��ȡ�û�����ĵص���

    // ��� t == 6, ǿ���û�ѡ�� 5 �ŵص�
    if (t == 6)
    {
        if (placeflag != 5)
        {
            cout << "�����û�оƺ�" << endl;
            changePlace(t);  // �����ǵص� 5������ѡ��
        }
    }
    // ��� t <= 4�������û�ѡ��ĵص�
    else if (t <= 4)
    {
        if (placeflag == 4 || placeflag == 5 || placeflag == 7)
        {
            cout << "�˵ص���δ���ţ�������ѡ��" << endl;  // ĳЩ�ص���ʱδ����
            changePlace(t);  // ����ѡ��ص�
        }
        else
        {
            cout << endl;
            cout << "��������";  // �ɹ����ĵص�
            place = placeflag;  // ���� Linchong �ĵص�
            // ���� place ��ֵ��ӡ��Ӧ�ĵص�����
            switch (place)
            {
            case 1:
                cout << "��Ƶ�";
                break;
            case 2:
                cout << "���";
                break;
            case 3:
                cout << "Ӫ��";
                break;
            case 4:
                cout << "���ϳ�";
                break;
            case 5:
                cout << "�о�";
                break;
            case 6:
                cout << "��ͷ";
                break;
            case 7:
                cout << "����";
                break;
            }
            cout << endl;
        }
    }
    // ��� t > 4������ѡ������ص�
    else
    {
        cout << endl;
        cout << "��������";
        place = placeflag;  // ���µص�Ϊ�û�ѡ���ֵ
        // ���� place ��ֵ��ӡ��Ӧ�ĵص�����
        switch (place)
        {
        case 1:
            cout << "��Ƶ�";
            break;
        case 2:
            cout << "���";
            break;
        case 3:
            cout << "Ӫ��";
            break;
        case 4:
            cout << "���ϳ�";
            break;
        case 5:
            cout << "�о�";
            break;
        case 6:
            cout << "��ͷ";
            break;
        case 7:
            cout << "����";
            break;
        }
        cout << endl;
    }
    // ���ĵص���߼�ʵ�ֽ���
}

// ��ӡ Linchong ��ǰӵ�е�������Ϣ
void Linchong::printWeapons() const
{
    for (const auto& weapon : weapons)  // ���������б�
    {
        cout << weapon->getName() << ": " << weapon->getDescription() << endl;  // ������������ƺ�����
    }
}

// ��ӡ Linchong ��ǰӵ�еķ�����Ϣ
void Linchong::printArmors() const
{
    for (const auto& armor : armors)  // ���������б�
    {
        cout << armor->getName() << ": " << armor->getDescription() << endl;  // ������ߵ����ƺ�����
    }
}

// ���������������Ƿ�ɹ�
bool Linchong::buyItem1(Weapon* equipment)
{
    // ����Ƿ���ӵ�и�����
    for (const auto& weapon : weapons)
    {
        if (weapon->getName() == equipment->getName()) {
            cout << "���Ѿ�����ˣ�����Ҫ�ٴι���Ŷ��" << endl;  // ����Ѿ�ӵ�и����������ٹ���
            return false;
        };
    }

    // ����Ƿ����㹻�Ľ�Ǯ��������
    if (equipment->getPrice() <= gold)
    {
        gold -= equipment->getPrice();  // �۳���Ӧ�Ľ�Ǯ
        cout << "����ɹ��������ڻ��� " << gold << " �̲���" << endl;
        weapons.push_back(equipment);  // ���������������б�
        return true;
    }
    else
    {
        cout << "�̲����㣡����Ҫ" << equipment->getPrice() << " ��������ֻ��" << gold << "�̲���" << endl;  // ��Ǯ���㣬�޷�����
        return false;
    }
}

// ������ߣ������Ƿ�ɹ�
bool Linchong::buyItem2(Armor* equipment)
{
    // ����Ƿ���ӵ�и÷���
    for (const auto& armor : armors)
    {
        if (armor->getName() == equipment->getName()) {
            cout << "���Ѿ�����ˣ�����Ҫ�ٴι���Ŷ��" << endl;  // ����Ѿ�ӵ�и÷��ߣ����ٹ���
            return false;
        };
    }

    // ����Ƿ����㹻�Ľ�Ǯ�������
    if (equipment->getPrice() <= gold)
    {
        gold -= equipment->getPrice();  // �۳���Ӧ�Ľ�Ǯ
        cout << "����ɹ��������ڻ��� " << gold << " �̲���" << endl;
        armors.push_back(equipment);  // �����߼�������б�
        return true;
    }
    else
    {
        cout << "�̲����㣡����Ҫ" << equipment->getPrice() << " ��������ֻ��" << gold << "�̲���" << endl;  // ��Ǯ���㣬�޷�����
        return false;
    }
}

// ֱ�ӽ� Weapon ������������б������κζ�����
bool Linchong::buyItem11(Weapon* equipment)
{
    weapons.push_back(equipment);  // ���������������б�
    return true;  // �����ɹ������� true
}

// ֱ�ӽ� Armor �����������б������κζ�����
bool Linchong::buyItem22(Armor* equipment)
{
    armors.push_back(equipment);  // �����߼�������б�
    return true;  // �����ɹ������� true
}

// �� Linchong ��������Ա��浽ָ���ļ���
void Linchong::saveToFile(const string& filename) const {
    ofstream outFile(filename);  // ���ļ�����д��
    if (outFile.is_open()) {
        outFile << getName() << "\n";  // �����ɫ����
        outFile << getAttack() << "\n";  // ���湥����
        outFile << HP << "\n";  // ���浱ǰ HP
        outFile << getMaxHP() << "\n";  // ������� HP
        outFile << getDefense() << "\n";  // ���������
        outFile << getSpeed() << "\n";  // �����ٶ�
        outFile << getHitRate() << "\n";  // ����������
        outFile << getEvasionRate() << "\n";  // ����������
        outFile << getGold() << "\n";  // ����������
        //outFile << getIsPlayer() << "\n";  // �����Ҫ�����Ƿ�����ҽ�ɫ������ȡ��ע��
        outFile << getPlace() << "\n";  // ���浱ǰ���ڵص�
    }
    outFile.close();  // �ر��ļ�
}

// ���ļ��м��� Linchong ���������
void Linchong::loadFromFile(const string& filename, Linchong* lc) {
    ifstream inFile(filename);  // ���ļ����ж�ȡ
    string name;  // ��ɫ����
    int attack1, HP1, maxHP1, defense1, speed1, gold1, place1;  // ��������
    float hitRate1, evasionRate1;  // �����ʺ�������
    bool isPlayer;  // �Ƿ�Ϊ��ҽ�ɫ�������Ҫ��

    if (inFile.is_open()) {
        getline(inFile, name);  // ��ȡ��ɫ����
        inFile >> attack1;  // ��ȡ������
        inFile >> HP1;  // ��ȡ��ǰ HP
        inFile >> maxHP1;  // ��ȡ��� HP
        inFile >> defense1;  // ��ȡ������
        inFile >> speed1;  // ��ȡ�ٶ�
        inFile >> hitRate1;  // ��ȡ������
        inFile >> evasionRate1;  // ��ȡ������
        inFile >> gold1;  // ��ȡ�������
        //inFile >> isPlayer;  // �����Ҫ��ȡ�Ƿ�����ҽ�ɫ������ȡ��ע��
        inFile >> place1;  // ��ȡ��ǰ�ص�
    }
    inFile.close();  // �ر��ļ�

    // ����ȡ�������Ը�ֵ�� lc ����
    lc->setGold(gold1);  // ���ý������
    lc->setplace(place1);  // ���õ�ǰ�ص�
    //lc->setAttack(attack1);  // �����Ҫ���ù�����������ȡ��ע��
    //lc->setHP(HP1);  // �����Ҫ���� HP������ȡ��ע��
    //lc->setMaxHP(maxHP1);  // �����Ҫ������� HP������ȡ��ע��
    //lc->setIsPlayer(isPlayer);  // �����Ҫ�����Ƿ�����ҽ�ɫ������ȡ��ע��
}

// ���� Linchong ����ĵ�ǰ�ص�
void Linchong::setplace(int a)
{
    place = a;  // ���� place ֵ
    return;  // ���践���κ�ֵ
}
