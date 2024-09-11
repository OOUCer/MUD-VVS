#include "filestore.h"
#include "equipment.h"
#include "character.h"
#include "skill.h"
#include <fstream>
#include <iostream>

using namespace std;

// ������Ϸ����
void Filestore::saveGame(Linchong& character, const Time& time) {
    ofstream file("savegame.dat", ios::binary);

    if (file.is_open()) {
        // �����ɫ����
        file.write((char*)&character, sizeof(Linchong));

        // ���� Time �ṹ��
        file.write((char*)&time, sizeof(Time));

        file.close();
        cout << "��Ϸ�ѳɹ��浵��" << endl;
    }
    else {
        cerr << "�޷����ļ����б��棡" << endl;
    }
}

// ������Ϸ����
bool Filestore::loadGame(Linchong& character, Time& time) {
    ifstream file("savegame.dat", ios::binary);

    if (file.is_open()) {
        // ��ȡ��ɫ����
        file.read((char*)&character, sizeof(Linchong));

        if (file.fail()) {
            cerr << "��ȡ��ɫ����ʧ�ܣ�" << endl;
            return false;
        }

        // ��ȡ Time �ṹ��
        file.read((char*)&time, sizeof(Time));

        if (file.fail()) {
            cerr << "��ȡ Time �ṹ��ʧ�ܣ�" << endl;
            return false;
        }

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
    file.write((char*)&weaponSize, sizeof(weaponSize));  // д����������

    for (const auto& weapon : weapons) {
        weapon->saveToFile(file);  // ʹ�� Weapon ��� saveToFile ������������
    }

    // ���滤��
    size_t armorSize = armors.size();
    file.write((char*)&armorSize, sizeof(armorSize));  // д�뻤������

    for (const auto& armor : armors) {
        armor->saveToFile(file);  // ʹ�� Armor ��� saveToFile ������������
    }
}

// ���������ͻ�������
void Filestore::loadEquipment(vector<Weapon*>& weapons, vector<Armor*>& armors, ifstream& file) {
    // ������е��������ͷ��ڴ�
    for (auto weapon : weapons) {
        delete weapon;  // �ͷ�ÿһ�� Weapon ����
    }
    weapons.clear();  // �������

    // ������еĻ��ײ��ͷ��ڴ�
    for (auto armor : armors) {
        delete armor;  // �ͷ�ÿһ�� Armor ����
    }
    armors.clear();  // �������

    // ��������
    size_t weaponSize;
    file.read((char*)&weaponSize, sizeof(weaponSize));  // ��ȡ��������

    if (file.fail()) {
        cerr << "��ȡ��������ʧ�ܣ�" << endl;
        return;
    }

    for (size_t i = 0; i < weaponSize; ++i) {
        Weapon* weapon = new Weapon();  // ��̬�����ڴ�
        weapon->loadFromFile(file);  // ���ļ��ж�ȡ��������

        if (file.fail()) {
            cerr << "��ȡ��������ʧ�ܣ�" << endl;
            delete weapon;  // ���ʧ�ܣ��ͷ��ѷ�����ڴ�
            return;
        }

        weapons.push_back(weapon);  // ��������ӵ�������
    }

    // ���ػ���
    size_t armorSize;
    file.read((char*)&armorSize, sizeof(armorSize));  // ��ȡ��������

    if (file.fail()) {
        cerr << "��ȡ��������ʧ�ܣ�" << endl;
        return;
    }

    for (size_t i = 0; i < armorSize; ++i) {
        Armor* armor = new Armor();  // ��̬�����ڴ�
        armor->loadFromFile(file);  // ���ļ��ж�ȡ��������

        if (file.fail()) {
            cerr << "��ȡ��������ʧ�ܣ�" << endl;
            delete armor;  // ���ʧ�ܣ��ͷ��ѷ�����ڴ�
            return;
        }

        armors.push_back(armor);  // ��������ӵ�������
    }
}

// ���漼������
void Filestore::saveSkills(const vector<offensiveSkill*>& oSkills, const vector<supportSkill*>& sSkills, ofstream& file) {
    // �����������
    size_t oSkillSize = oSkills.size();
    file.write((char*)&oSkillSize, sizeof(oSkillSize));  // д�������������

    for (const auto& skill : oSkills) {
        skill->saveToFile(file);  // ʹ�� offensiveSkill ��� saveToFile ������������
    }

    // ����֧�ּ���
    size_t sSkillSize = sSkills.size();
    file.write((char*)&sSkillSize, sizeof(sSkillSize));  // д��֧�ּ�������

    for (const auto& skill : sSkills) {
        skill->saveToFile(file);  // ʹ�� supportSkill ��� saveToFile ������������
    }
}

// ���ؼ�������
void Filestore::loadSkills(vector<offensiveSkill*>& oSkills, vector<supportSkill*>& sSkills, ifstream& file) {
    // ���ؽ�������
    size_t oSkillSize;
    file.read((char*)&oSkillSize, sizeof(oSkillSize));  // ��ȡ������������

    oSkills.resize(oSkillSize);  // ����������С

    for (size_t i = 0; i < oSkillSize; ++i) {
        oSkills[i] = new offensiveSkill();  // ��̬�����ڴ�
        oSkills[i]->loadFromFile(file);  // ʹ�� offensiveSkill ��� loadFromFile ������������
    }

    // ����֧�ּ���
    size_t sSkillSize;
    file.read((char*)&sSkillSize, sizeof(sSkillSize));  // ��ȡ֧�ּ�������

    sSkills.resize(sSkillSize);  // ����������С

    for (size_t i = 0; i < sSkillSize; ++i) {
        sSkills[i] = new supportSkill();  // ��̬�����ڴ�
        sSkills[i]->loadFromFile(file);  // ʹ�� supportSkill ��� loadFromFile ������������
    }
}
