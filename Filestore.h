#ifndef FILESTORE_H
#define FILESTORE_H

#include <fstream>
#include "character.h"
#include"equipment.h"
#include"skill.h"


using namespace std;

class Filestore {
public:
    static void saveGame(Linchong& character);  // 存档函数
    static bool loadGame(Linchong& character);  // 读档函数

private:
    static void saveWeapons(const vector<Weapon*>& weapons, ofstream& file);  // 保存武器
    static void loadWeapons(vector<Weapon*>& weapons, ifstream& file);  // 加载武器

    static void saveArmors(const vector<Armor*>& armors, ofstream& file);     // 保存护甲
    static void loadArmors(vector<Armor*>& armors, ifstream& file);     // 加载护甲

    static void saveSkills(const vector<Skill*>& skills, ofstream& file);     // 保存技能
    static void loadSkills(vector<Skill*>& skills, ifstream& file);     // 加载技能
};

#endif // FILESTORE_H
