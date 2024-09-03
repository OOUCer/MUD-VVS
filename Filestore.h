#ifndef FILESTORE_H
#define FILESTORE_H

#include <fstream>
#include "character.h"
#include"equipment.h"
#include"skill.h"


using namespace std;

class Filestore {
public:
    static void saveGame(Linchong& character);  // �浵����
    static bool loadGame(Linchong& character);  // ��������

private:
    static void saveWeapons(const vector<Weapon*>& weapons, ofstream& file);  // ��������
    static void loadWeapons(vector<Weapon*>& weapons, ifstream& file);  // ��������

    static void saveArmors(const vector<Armor*>& armors, ofstream& file);     // ���滤��
    static void loadArmors(vector<Armor*>& armors, ifstream& file);     // ���ػ���

    static void saveSkills(const vector<Skill*>& skills, ofstream& file);     // ���漼��
    static void loadSkills(vector<Skill*>& skills, ifstream& file);     // ���ؼ���
};

#endif // FILESTORE_H
