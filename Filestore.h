#ifndef FILESTORE_H
#define FILESTORE_H

#include <vector>
#include <fstream>
#include "equipment.h"
#include "skill.h"

using namespace std;

class Linchong; // Forward declaration of Linchong class

class Filestore {
public:
    // ������Ϸ����
    void saveGame(Linchong& character);

    // ������Ϸ����
    bool loadGame(Linchong& character);

private:
    // ���������ͻ�������
    void saveEquipment(const vector<Weapon*>& weapons, const vector<Armor*>& armors, ofstream& file);

    // ���������ͻ�������
    void loadEquipment(vector<Weapon*>& weapons, vector<Armor*>& armors, ifstream& file);

    // ���漼������
    void saveSkills(const vector<offensiveSkill*>& oSkills, const vector<supportSkill*>& sSkills, ofstream& file);

    // ���ؼ�������
    void loadSkills(vector<offensiveSkill*>& oSkills, vector<supportSkill*>& sSkills, ifstream& file);
};

#endif // FILESTORE_H
