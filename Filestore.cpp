/*#include "Filestore.h"
#include "character.h"
#include"equipment.h"
#include"skill.h"

void Filestore::saveGame(Linchong& character) {
    ofstream file("savegame.dat", ios::binary);
    if (file.is_open()) {
        // �����������
        file.write((char*)&character, sizeof(Linchong));

        // ��������
        saveWeapons(*character.getWeapons(), file);
        // ���滤��

        saveArmors(*character.getArmors(), file);
        // ���漼��
        saveSkills(*character.getSkills(), file);

        file.close();
        cout << "��Ϸ�ѳɹ��浵��" << endl;
    }
    else {
        cerr << "�޷����ļ����б��棡" << endl;
    }
}

bool Filestore::loadGame(Linchong& character) {
    ifstream file("savegame.dat", ios::binary);
    if (file.is_open()) {
        // ��ȡ��������
        file.read((char*)&character, sizeof(Linchong));

        // ��������
        loadWeapons(*character.getWeapons(), file);
        // ���ػ���
        loadArmors(*character.getArmors(), file);
        // ���ؼ���
        loadSkills(*character.getSkills(), file);

        file.close();
        cout << "��Ϸ�ѳɹ����أ�" << endl;
        return true;
    }
    else {
        cerr << "�޷����ļ����ж�ȡ��" << endl;
        return false;
    }
}

void Filestore::saveWeapons(const vector<Weapon*>& weapons, ofstream& file) {
    size_t size = weapons.size();
    file.write((char*)&size, sizeof(size));  // д����������

    for (const auto& weapon : weapons) {
        // ���� Weapon ��һ���ʺ�д���ļ������л�����
        file.write((char*)weapon, sizeof(Weapon));  // д��ÿ������������
    }
}

void Filestore::loadWeapons(vector<Weapon*>& weapons, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // ��ȡ��������
    weapons.resize(size);

    for (auto& weapon : weapons) {
        weapon = new Weapon();  // ��̬�����ڴ�
        file.read((char*)weapon, sizeof(Weapon));  // ��ȡÿ������������
    }
}

void Filestore::saveArmors(const vector<Armor*>& armors, ofstream& file) {
    size_t size = armors.size();
    file.write((char*)&size, sizeof(size));  // д�뻤������

    for (const auto& armor : armors) {
        // ���� Armor ��һ���ʺ�д���ļ������л�����
        file.write((char*)armor, sizeof(Armor));  // д��ÿ�����׵�����
    }
}

void Filestore::loadArmors(vector<Armor*>& armors, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // ��ȡ��������
    armors.resize(size);

    for (auto& armor : armors) {
        armor = new Armor();  // ��̬�����ڴ�
        file.read((char*)armor, sizeof(Armor));  // ��ȡÿ�����׵�����
    }
}

void Filestore::saveSkills(const vector<Skill*>& skills, ofstream& file) {
    size_t size = skills.size();
    file.write((char*)&size, sizeof(size));  // д�뼼������

    for (const auto& skill : skills) {
        // ���� Skill ��һ���ʺ�д���ļ������л�����
        file.write((char*)skill, sizeof(Skill));  // д��ÿ�����ܵ�����
    }
}

void Filestore::loadSkills(vector<Skill*>& skills, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // ��ȡ��������
    skills.resize(size);

    for (auto& skill : skills) {
        skill = new Skill();  // ��̬�����ڴ�
        file.read((char*)skill, sizeof(Skill));  // ��ȡÿ�����ܵ�����
    }
}
*/