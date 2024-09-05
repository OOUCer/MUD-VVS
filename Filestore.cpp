/*#include "Filestore.h"
#include "character.h"
#include"equipment.h"
#include"skill.h"

void Filestore::saveGame(Linchong& character) {
    ofstream file("savegame.dat", ios::binary);
    if (file.is_open()) {
        // 保存基本属性
        file.write((char*)&character, sizeof(Linchong));

        // 保存武器
        saveWeapons(*character.getWeapons(), file);
        // 保存护甲

        saveArmors(*character.getArmors(), file);
        // 保存技能
        saveSkills(*character.getSkills(), file);

        file.close();
        cout << "游戏已成功存档！" << endl;
    }
    else {
        cerr << "无法打开文件进行保存！" << endl;
    }
}

bool Filestore::loadGame(Linchong& character) {
    ifstream file("savegame.dat", ios::binary);
    if (file.is_open()) {
        // 读取基本属性
        file.read((char*)&character, sizeof(Linchong));

        // 加载武器
        loadWeapons(*character.getWeapons(), file);
        // 加载护甲
        loadArmors(*character.getArmors(), file);
        // 加载技能
        loadSkills(*character.getSkills(), file);

        file.close();
        cout << "游戏已成功加载！" << endl;
        return true;
    }
    else {
        cerr << "无法打开文件进行读取！" << endl;
        return false;
    }
}

void Filestore::saveWeapons(const vector<Weapon*>& weapons, ofstream& file) {
    size_t size = weapons.size();
    file.write((char*)&size, sizeof(size));  // 写入武器数量

    for (const auto& weapon : weapons) {
        // 假设 Weapon 有一个适合写入文件的序列化函数
        file.write((char*)weapon, sizeof(Weapon));  // 写入每个武器的数据
    }
}

void Filestore::loadWeapons(vector<Weapon*>& weapons, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // 读取武器数量
    weapons.resize(size);

    for (auto& weapon : weapons) {
        weapon = new Weapon();  // 动态分配内存
        file.read((char*)weapon, sizeof(Weapon));  // 读取每个武器的数据
    }
}

void Filestore::saveArmors(const vector<Armor*>& armors, ofstream& file) {
    size_t size = armors.size();
    file.write((char*)&size, sizeof(size));  // 写入护甲数量

    for (const auto& armor : armors) {
        // 假设 Armor 有一个适合写入文件的序列化函数
        file.write((char*)armor, sizeof(Armor));  // 写入每个护甲的数据
    }
}

void Filestore::loadArmors(vector<Armor*>& armors, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // 读取护甲数量
    armors.resize(size);

    for (auto& armor : armors) {
        armor = new Armor();  // 动态分配内存
        file.read((char*)armor, sizeof(Armor));  // 读取每个护甲的数据
    }
}

void Filestore::saveSkills(const vector<Skill*>& skills, ofstream& file) {
    size_t size = skills.size();
    file.write((char*)&size, sizeof(size));  // 写入技能数量

    for (const auto& skill : skills) {
        // 假设 Skill 有一个适合写入文件的序列化函数
        file.write((char*)skill, sizeof(Skill));  // 写入每个技能的数据
    }
}

void Filestore::loadSkills(vector<Skill*>& skills, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // 读取技能数量
    skills.resize(size);

    for (auto& skill : skills) {
        skill = new Skill();  // 动态分配内存
        file.read((char*)skill, sizeof(Skill));  // 读取每个技能的数据
    }
}
*/