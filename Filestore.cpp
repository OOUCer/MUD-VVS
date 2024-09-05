#include "filestore.h"
#include "equipment.h"
#include "skill.h"

// ������Ϸ����
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
        saveoSkills(*character.getoSkills(), file);
        savesSkills(*character.getsSkills(), file);

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
        // ��ȡ��������
        file.read((char*)&character, sizeof(Linchong));

        // ��������
        loadWeapons(*character.getWeapons(), file);

        // ���ػ���
        loadArmors(*character.getArmors(), file);

        // ���ؼ���
        loadoSkills(*character.getoSkills(), file);
        loadsSkills(*character.getsSkills(), file);

        file.close();
        cout << "��Ϸ�ѳɹ����أ�" << endl;
        return true;
    }
    else {
        cerr << "�޷����ļ����ж�ȡ��" << endl;
        return false;
    }
}

// ������������
void Filestore::saveWeapons(const vector<Weapon*>& weapons, ofstream& file) {
    size_t size = weapons.size();
    file.write((char*)&size, sizeof(size));  // д����������

    for (const auto& weapon : weapons) {
        file.write((char*)weapon, sizeof(Weapon));  // ���� Weapon �������л�����
    }
}

// ������������
void Filestore::loadWeapons(vector<Weapon*>& weapons, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // ��ȡ��������
    weapons.resize(size);

    for (auto& weapon : weapons) {
        weapon = new Weapon();  // ���� Weapon ����Ĭ�Ϲ��캯��
        file.read((char*)weapon, sizeof(Weapon));  // ��ȡÿ������������
    }
}

// ���滤������
void Filestore::saveArmors(const vector<Armor*>& armors, ofstream& file) {
    size_t size = armors.size();
    file.write((char*)&size, sizeof(size));  // д�뻤������

    for (const auto& armor : armors) {
        file.write((char*)armor, sizeof(Armor));  // ���� Armor �������л�����
    }
}

// ���ػ�������
void Filestore::loadArmors(vector<Armor*>& armors, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // ��ȡ��������
    armors.resize(size);

    for (auto& armor : armors) {
        armor = new Armor();  // ���� Armor ����Ĭ�Ϲ��캯��
        file.read((char*)armor, sizeof(Armor));  // ��ȡÿ�����׵�����
    }
}

// ���������������
void Filestore::saveoSkills(const vector<offensiveSkill*>& oSkills, ofstream& file) {
    size_t size = oSkills.size();
    file.write((char*)&size, sizeof(size));  // д�������������

    for (const auto& skill : oSkills) {
        file.write((char*)skill, sizeof(offensiveSkill));  // д��ÿ���������ܵ�����
    }
}

// ���ؽ�����������
void Filestore::loadoSkills(vector<offensiveSkill*>& oSkills, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // ��ȡ������������
    oSkills.resize(size);

    for (auto& skill : oSkills) {
        skill = new offensiveSkill();  // ���� offensiveSkill ����Ĭ�Ϲ��캯��
        file.read((char*)skill, sizeof(offensiveSkill));  // ��ȡÿ���������ܵ�����
    }
}

// ����֧�ּ�������
void Filestore::savesSkills(const vector<supportSkill*>& sSkills, ofstream& file) {
    size_t size = sSkills.size();
    file.write((char*)&size, sizeof(size));  // д��֧�ּ�������

    for (const auto& skill : sSkills) {
        file.write((char*)skill, sizeof(supportSkill));  // д��ÿ��֧�ּ��ܵ�����
    }
}

// ����֧�ּ�������
void Filestore::loadsSkills(vector<supportSkill*>& sSkills, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // ��ȡ֧�ּ�������
    sSkills.resize(size);

    for (auto& skill : sSkills) {
        skill = new supportSkill();  // ���� supportSkill ����Ĭ�Ϲ��캯��
        file.read((char*)skill, sizeof(supportSkill));  // ��ȡÿ��֧�ּ��ܵ�����
    }
}
