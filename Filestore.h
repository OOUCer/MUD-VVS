#ifndef FILESTORE_H
#define FILESTORE_H

#include "character.h"
#include <fstream>
#include <vector>

using namespace std;

class Filestore {
public:
    // ������Ϸ����
    static void saveGame(Linchong& character);

    // ������Ϸ����
    static bool loadGame(Linchong& character);

private:
    // ������������
    static void saveWeapons(const vector<Weapon*>& weapons, ofstream& file);

    // ������������
    static void loadWeapons(vector<Weapon*>& weapons, ifstream& file);

    // ���滤������
    static void saveArmors(const vector<Armor*>& armors, ofstream& file);

    // ���ػ�������
    static void loadArmors(vector<Armor*>& armors, ifstream& file);

    // ���������������
    static void saveoSkills(const vector<offensiveSkill*>& oSkills, ofstream& file);

    // ���ؽ�����������
    static void loadoSkills(vector<offensiveSkill*>& oSkills, ifstream& file);

    // ����֧�ּ�������
    static void savesSkills(const vector<supportSkill*>& sSkills, ofstream& file);

    // ����֧�ּ�������
    static void loadsSkills(vector<supportSkill*>& sSkills, ifstream& file);
};

#endif // FILESTORE_H



