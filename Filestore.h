#ifndef FILESTORE_H
#define FILESTORE_H

#include "character.h"
#include <fstream>
#include <vector>

using namespace std;

class Filestore {
public:
    // 保存游戏进度
    static void saveGame(Linchong& character);

    // 加载游戏进度
    static bool loadGame(Linchong& character);

private:
    // 保存武器数据
    static void saveWeapons(const vector<Weapon*>& weapons, ofstream& file);

    // 加载武器数据
    static void loadWeapons(vector<Weapon*>& weapons, ifstream& file);

    // 保存护甲数据
    static void saveArmors(const vector<Armor*>& armors, ofstream& file);

    // 加载护甲数据
    static void loadArmors(vector<Armor*>& armors, ifstream& file);

    // 保存进攻技能数据
    static void saveoSkills(const vector<offensiveSkill*>& oSkills, ofstream& file);

    // 加载进攻技能数据
    static void loadoSkills(vector<offensiveSkill*>& oSkills, ifstream& file);

    // 保存支持技能数据
    static void savesSkills(const vector<supportSkill*>& sSkills, ofstream& file);

    // 加载支持技能数据
    static void loadsSkills(vector<supportSkill*>& sSkills, ifstream& file);
};

#endif // FILESTORE_H



