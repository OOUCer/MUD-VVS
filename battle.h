//#ifndef BATTLE_H
//#define BATTLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <math.h>


#include "character.h"



using namespace std;

class Battle
{
public:
    Battle();

    ~Battle();

    void startBattle(Linchong *player, vector<Character *> *enemies);

    void sortBySpeed(vector<pair<int, Character*>>* sorted, Linchong* player, vector<Character*>* enemies);

    bool evaluateBattleStatus(vector<pair<int, Character *>> &theCharacters);

    void manageWeaknessAndBuff(Character* theCharacter);

    void enemyTurn(Character *enemy, Character *player);

    void playerTurn(Character *player, vector<Character *> *enemies);

    int takeDamage(Character *target, int damage);

    void normalAttack(Character *target, Character *attacker);

    bool isHittingWeakness(string theWeakness, string attackType);

    bool checkHit(float evasionRate, float hitRate);

    void weaponSwitch(Character *character);

    void useSkill(Character *user, vector<Character *> *enemies, int skillIndex);

    int getDamage(Character *attacker, Character *target, float damageMultiplier);

    int singleDamagePerform(Character *user, Character *enemy, int damage);

    void effectPerform(Character *user, Character *enemy, Skill *theSkill);

    bool checkAndOffset(Character* character, Skill *theSkill);

    void manageComatoseStatus(Character *theCharacter);

    void describeEffect(Character* user, Character* enemy, Skill* theSkill);

    void showEnemiesInformation(vector<Character*>* enemies);

    void showWeaponInformationInBattle(Character* user);

    void showSkillInformationInBattle(Character* user);

    void showSpeedLine(vector<pair<int, Character*>> sortedCharacters);

    void showStartInformation(Linchong* player, vector<Character*>* enemies);

    void showAllStatus(Character* character);

    void endBattle();

private:
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<> dis;
};

//#endif 