#include "filestore.h"
#include "equipment.h"
#include"character.h"
#include "skill.h"
#include <fstream>
#include <iostream>

using namespace std;

// ������Ϸ����
void Filestore::saveGame(Linchong& character) {
    ofstream file("savegame.dat", ios::binary);
    if (file.is_open()) {
        // �����ɫ��������
        file.write((char*)&character, sizeof(Linchong));

        // �������������ס�����
        saveEquipment(*character.getWeapons(), *character.getArmors(), file);
        saveSkills(*character.getoSkills(), *character.getsSkills(), file);

        file.close();
        cout << "��Ϸ�ѳɹ��浵��" << endl;
    }
    else {
        cerr << "�޷����ļ����б��棡" << endl;
    }
}

// ������Ϸ����
bool Filestore::loadGame(Linchong& character) {
    ifstream file("savegame.dat", ios::binary);
    if (file.is_open()) {
        // ��ȡ��ɫ��������
        file.read((char*)&character, sizeof(Linchong));

        // �������������ס�����
        loadEquipment(*character.getWeapons(), *character.getArmors(), file);
        loadSkills(*character.getoSkills(), *character.getsSkills(), file);

        file.close();
        cout << "��Ϸ�ѳɹ����أ�" << endl;
        return true;
    }
    else {
        cerr << "�޷����ļ����ж�ȡ��" << endl;
        return false;
    }
}

// ���������ͻ�������
void Filestore::saveEquipment(const vector<Weapon*>& weapons, const vector<Armor*>& armors, ofstream& file) {
    // ��������
    size_t weaponSize = weapons.size();
    file.write((char*)&weaponSize, sizeof(weaponSize));
    for (const auto& weapon : weapons) {
        weapon->saveToFile(file);  // ʹ�� Weapon ��� saveToFile ������������
    }

    // ���滤��
    size_t armorSize = armors.size();
    file.write((char*)&armorSize, sizeof(armorSize));
    for (const auto& armor : armors) {
        armor->saveToFile(file);  // ʹ�� Armor ��� saveToFile ������������
    }
}

// ���������ͻ�������
void Filestore::loadEquipment(vector<Weapon*>& weapons, vector<Armor*>& armors, ifstream& file) {
    // ��������
    size_t weaponSize;
    file.read((char*)&weaponSize, sizeof(weaponSize));
    weapons.resize(weaponSize);
    for (size_t i = 0; i < weaponSize; ++i) {
        weapons[i] = new Weapon();
        weapons[i]->loadFromFile(file);  // ʹ�� Weapon ��� loadFromFile ������������
    }

    // ���ػ���
    size_t armorSize;
    file.read((char*)&armorSize, sizeof(armorSize));
    armors.resize(armorSize);
    for (size_t i = 0; i < armorSize; ++i) {
        armors[i] = new Armor();
        armors[i]->loadFromFile(file);  // ʹ�� Armor ��� loadFromFile ������������
    }
}

// ���漼������
void Filestore::saveSkills(const vector<offensiveSkill*>& oSkills, const vector<supportSkill*>& sSkills, ofstream& file) {
    // �����������
    size_t oSkillSize = oSkills.size();
    file.write((char*)&oSkillSize, sizeof(oSkillSize));
    for (const auto& skill : oSkills) {
        skill->saveToFile(file);  // ʹ�� offensiveSkill ��� saveToFile ������������
    }

    // ����֧�ּ���
    size_t sSkillSize = sSkills.size();
    file.write((char*)&sSkillSize, sizeof(sSkillSize));
    for (const auto& skill : sSkills) {
        skill->saveToFile(file);  // ʹ�� supportSkill ��� saveToFile ������������
    }
}

// ���ؼ�������
void Filestore::loadSkills(vector<offensiveSkill*>& oSkills, vector<supportSkill*>& sSkills, ifstream& file) {
    // ���ؽ�������
    size_t oSkillSize;
    file.read((char*)&oSkillSize, sizeof(oSkillSize));
    oSkills.resize(oSkillSize);
    for (size_t i = 0; i < oSkillSize; ++i) {
        oSkills[i] = new offensiveSkill();
        oSkills[i]->loadFromFile(file);  // ʹ�� offensiveSkill ��� loadFromFile ������������
    }

    // ����֧�ּ���
    size_t sSkillSize;
    file.read((char*)&sSkillSize, sizeof(sSkillSize));
    sSkills.resize(sSkillSize);
    for (size_t i = 0; i < sSkillSize; ++i) {
        sSkills[i] = new supportSkill();
        sSkills[i]->loadFromFile(file);  // ʹ�� supportSkill ��� loadFromFile ������������
    }
}
