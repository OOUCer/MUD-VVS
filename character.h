#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <iostream>
#include <map>


#include "equipment.h"
#include "skill.h"

using namespace std;
class Character
{
protected:
    string name;
    int attack;
    int HP;
    int maxHP;
    int defense;
    int speed;
    float hitRate;
    float evasionRate;
    int gold;
    bool actionAvailability = true;
    bool hasReceivedWeaknessHit = false;
    bool hitWeakness = false;
    bool isPlayer;

    pair<bool, int> isComatose{ false,0 };
    bool isCharged = false;
    bool isAnticipating = false;
    int skillPoint = 3;
    int actionCount = 0;

    vector<Weapon*> weapons;
    vector<Armor*> armors;
    vector<supportSkill*> sSkills;
    vector<offensiveSkill*> oSkills;
    vector<Skill*> skills;//���ã������ã���ɾ��
    map<skillEffectType, pair<float, int>> effectStatus;//�Զ���ʼ��Ϊ��

public:
    // ���캯�������ڳ�ʼ����ɫ�Ļ�������  
    Character(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer);

    // ��ȡ��ɫ����  
    string getName() const;

    // ��ȡ��ɫ�Ĺ�����  
    int getAttack() const;

    void setAttack(int newAttack);

    // ��ȡ��ɫ�ĵ�ǰ����ֵ  
    int getHP();

    // �޸Ľ�ɫ������ֵ  
    void modifyHP(int modifyAmount);


    void setHP(int newHP);

    // ��ȡ��ɫ���������ֵ  
    int getMaxHP() const;

    void setMaxHP(int newMaxHP);

    // ��ȡ��ɫ�ķ�����  
    int getDefense() const;

    // ��ȡ��ɫ���ٶ�  
    int getSpeed() const;

    // ��ȡ��ɫ��������  
    float getHitRate() const;

    // ��ȡ��ɫ��������  
    float getEvasionRate() const;

    // ��ȡ��ɫӵ�еĽ������  
    int getGold() const;

    void setGold(int newGold);

    // �жϽ�ɫ�Ƿ�Ϊ��ҿ���  
    bool isPlayerControlled() const;

    // ���ý�ɫ���ж��Ƿ����  
    void setActionAvailability(bool isAvailable);

    // ��ȡ��ɫ���ж��Ƿ����  
    bool getActionAvailability();

    // ���ý�ɫ�Ƿ��ܵ����㹥��  
    void setWeaknessReceivedStatus(bool isHit);

    // ��ȡ��ɫ�Ƿ��ܵ����㹥��  
    bool getWeaknessReceivedStatus();

    // ���ý�ɫ�Ƿ��������  
    void setHitWeakness(bool hit);

    // ��ȡ��ɫ�Ƿ��������  
    bool getHitWeakness();

    // ��ȡ��ɫ�ļ��ܵ���  
    int getSkillPoint();

    // ���ý�ɫ�ļ��ܵ���  
    void setSkillPoint(int point);

    // ��ȡ��ɫ���ж�����  
    int getActionCount();

    // ���ý�ɫ���ж�����  
    void setActionCount(int count);

    // ��ȡ��ɫ�Ƿ���Ԥ��״̬  
    bool getAnticipateStatus();

    // ���ý�ɫ�Ƿ���Ԥ��״̬  
    void setAnticipateStatus(bool theStatus);

    // ��ȡ��ɫ�Ƿ��ڻ���״̬  
    bool getComatoseStatus();

    // ��ȡ��ɫ���Եĳ���ʱ��  
    int getComatoseDuration();

    // ���ý�ɫ�Ƿ��ڻ���״̬�Լ����Եĳ���ʱ��  
    void setComatoseStatus(bool theStatus, int duration);

    // ��ȡ��ɫ�Ƿ��ڳ���״̬  
    bool getChargeStatus();

    // ���ý�ɫ�Ƿ��ڳ���״̬  
    void setChargeStatus(bool theStatus);

    // ��ȡ��ɫ�ĵ�һ������������еĻ���  
    Weapon* getFirstWeapon();

    // ��ȡ��ɫ�ĵ�һ�׻��ף�����еĻ���  
    Armor* getFirstArmor();

    // ����ɫ���һ��Ч��  
    void addEffect(const skillEffectType& effect, float intensity, int duration);

    // �Ƴ���ɫ���ϵ�һ��Ч��  
    void removeEffect(const skillEffectType& effect);

    // ����ɫ���һ������  
    void addWeapon(Weapon* weapon);

    // ����ɫ���һ�׻���  
    void addArmor(Armor* armor);

    // ����ɫ���һ������  
    void addSkill(Skill* skill);

    // ��ȡ��ɫ��ǰ������Ч��״̬  
    map<skillEffectType, pair<float, int>>* getEffectStatus();

    // ��ȡ��ɫ��������������ָ����������ʽ��  
    vector<Weapon*>* getWeapons();

    // ��ȡ��ɫ�����л��ף���ָ����������ʽ��  
    vector<Armor*>* getArmors();

    // ��ȡ��ɫ�����м��ܣ���ָ����������ʽ�� 
    vector<Skill*> *getSkills();
    vector<offensiveSkill*>* getoSkills();
    vector<supportSkill*>* getsSkills();
};

class Linchong : public Character
{
protected:
    int place;

public:
    // ���캯�����̳���Character�࣬�����λ������  
    Linchong(const string& name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer, int place);

    // ��ȡ��ɫ����λ��  
    int getPlace() const;

    // �ı��ɫ��λ�ã�����ʵ����������Ϸ�߼���  
    void changePlace();

    // ��ӡ��ɫӵ�е���������  
    void printWeapons() const;

    // ��ӡ��ɫӵ�е����л���  
    void printArmors() const;

    // ���Թ���һ������������ʵ����������Ϸ�߼��������Ƿ��㹻�ȣ�  
    bool buyItem1(Weapon* equipment);

    // ���Թ���һ�׻��ף�����ʵ����������Ϸ�߼��������Ƿ��㹻�ȣ�  
    bool buyItem2(Armor* equipment);
};


#endif // CHARACTER_H