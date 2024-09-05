#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <math.h>
#include <iomanip>

#include "character.h"
#include "UI.h"


class Battle
{
public:
    Battle();//��ʼ��������������ͷֲ�����

    void startBattle(Linchong *player, vector<Character *> *enemies);//ս������

    void sortBySpeed(vector<pair<int, Character*>>* sorted, Linchong* player, vector<Character*>* enemies);//��ó���˳��

    bool evaluateBattleStatus(vector<pair<int, Character *>> &theCharacters, vector<Character*>* enemies);//�������

    void manageWeaknessAndBuff(Character* theCharacter);//���������״̬

    void enemyTurn(Character *enemy, Character *player);//������˻غ�

    void playerTurn(Character *player, vector<Character *> *enemies);//������һغ�

    int takeDamage(Character *target, int damage);//�ܵ��˺�

    void normalAttack(Character *target, Character *attacker);//��ͨ����

    bool isHittingWeakness(string theWeakness, string attackType);//�ж��Ƿ񹥻�����

    bool checkHit(float evasionRate, float hitRate);//���м���

    void weaponSwitch(Character *character);//��Ҹ�������

    void useSkill(Character *user, vector<Character *> *enemies, int skillIndex);//ʹ�ü����߼�

    void userSkill_enemy(Character* player, Character* enemy, int skillIndex);//����ʹ�ü����߼�

    int getDamage(Character *attacker, Character *target, float damageMultiplier);//�����˺�

    int singleDamagePerform(Character *user, Character *enemy, int damage);//�����˺�ִ��

    void effectPerform(Character *user, Character *enemy, Skill *theSkill);//��ʽЧ��ִ��

    bool checkAndOffset(Character* character, Skill *theSkill);//���Ч��

    void manageComatoseStatus(Character *theCharacter);//�������״̬

    void describeEffect(Character* user, Character* enemy, Skill* theSkill);//��������Ч��

    void showEnemiesInformation(vector<Character*>* enemies, float hitRate);//չ�ֵ�����Ϣ

    void showWeaponInformationInBattle(Character* user);//չ��������Ϣ

    void showSkillInformationInBattle(Character* user);//չ����ʽ��Ϣ

    void showSpeedLine(vector<pair<int, Character*>> sortedCharacters);//չ���ٶ���

    void showStartInformation(Linchong* player, vector<Character*>* enemies);//ս����ʼ��Ϣ

    void showAllStatus(Character* character);//չʾ����״̬��Ч��

    void manageSkillOrder(Character* character);//�Լ���˳�����



private:
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<> dis;
    
};

#endif 