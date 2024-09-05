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
    Battle();//初始化随机数生成器和分布对象

    void startBattle(Linchong *player, vector<Character *> *enemies);//战斗启动

    void sortBySpeed(vector<pair<int, Character*>>* sorted, Linchong* player, vector<Character*>* enemies);//获得出手顺序

    bool evaluateBattleStatus(vector<pair<int, Character *>> &theCharacters, vector<Character*>* enemies,int flag);//监控死亡

    void manageWeaknessAndBuff(Character* theCharacter);//管理弱点和状态

    void enemyTurn(Character *enemy, Character *player);//管理敌人回合

    void playerTurn(Character *player, vector<Character *> *enemies);//管理玩家回合

    int takeDamage(Character *target, int damage);//受到伤害

    void normalAttack(Character *target, Character *attacker);//普通攻击

    bool isHittingWeakness(string theWeakness, string attackType);//判断是否攻击弱点

    bool checkHit(float evasionRate, float hitRate);//命中鉴定

    void weaponSwitch(Character *character);//玩家更换武器

    void useSkill(Character *user, vector<Character *> *enemies, int skillIndex);//使用技能逻辑

    void userSkill_enemy(Character* player, Character* enemy, int skillIndex);//敌人使用技能逻辑

    int getDamage(Character *attacker, Character *target, float damageMultiplier);//计算伤害

    int singleDamagePerform(Character *user, Character *enemy, int damage);//单次伤害执行

    void effectPerform(Character *user, Character *enemy, Skill *theSkill);//招式效果执行

    bool checkAndOffset(Character* character, Skill *theSkill);//监控效果

    void manageComatoseStatus(Character *theCharacter);//管理昏迷状态

    void describeEffect(Character* user, Character* enemy, Skill* theSkill);//描述技能效果

    void showEnemiesInformation(vector<Character*>* enemies, float hitRate);//展现敌人信息

    void showWeaponInformationInBattle(Character* user);//展现武器信息

    void showSkillInformationInBattle(Character* user);//展现招式信息

    void showSpeedLine(vector<pair<int, Character*>> sortedCharacters);//展现速度线

    void showStartInformation(Linchong* player, vector<Character*>* enemies);//战斗开始信息

    void showAllStatus(Character* character);//展示所有状态和效果

    void manageSkillOrder(Character* character);//对技能顺序分类

    void prepareSkill(Character* character);

private:
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<> dis;
    
};

#endif 