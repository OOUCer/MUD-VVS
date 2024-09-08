#ifndef FILESTORE_H
#define FILESTORE_H

#include <vector>
#include <fstream>
#include "equipment.h"
#include "skill.h"
#include"plot.h"

using namespace std;

class Linchong; // Forward declaration of Linchong class

class Filestore {
public:
    // 保存游戏进度
    void saveGame(Linchong& character, const Time& time);

    // 加载游戏进度
    bool loadGame(Linchong& character, Time& time);


private:
    // 保存武器和护甲数据
    void saveEquipment(const vector<Weapon*>& weapons, const vector<Armor*>& armors, ofstream& file);

    // 加载武器和护甲数据
    void loadEquipment(vector<Weapon*>& weapons, vector<Armor*>& armors, ifstream& file);

    // 保存技能数据
    void saveSkills(const vector<offensiveSkill*>& oSkills, const vector<supportSkill*>& sSkills, ofstream& file);

    // 加载技能数据
    void loadSkills(vector<offensiveSkill*>& oSkills, vector<supportSkill*>& sSkills, ifstream& file);
};

#endif // FILESTORE_H
