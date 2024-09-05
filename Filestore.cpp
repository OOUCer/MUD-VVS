#include "filestore.h"
#include "equipment.h"
#include "skill.h"

// 保存游戏进度
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
        saveoSkills(*character.getoSkills(), file);
        savesSkills(*character.getsSkills(), file);

        file.close();
        cout << "游戏已成功存档！" << endl;
    }
    else {
        cerr << "无法打开文件进行保存！" << endl;
    }
}

// 加载游戏进度
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
        loadoSkills(*character.getoSkills(), file);
        loadsSkills(*character.getsSkills(), file);

        file.close();
        cout << "游戏已成功加载！" << endl;
        return true;
    }
    else {
        cerr << "无法打开文件进行读取！" << endl;
        return false;
    }
}

// 保存武器数据
void Filestore::saveWeapons(const vector<Weapon*>& weapons, ofstream& file) {
    size_t size = weapons.size();
    file.write((char*)&size, sizeof(size));  // 写入武器数量

    for (const auto& weapon : weapons) {
        file.write((char*)weapon, sizeof(Weapon));  // 假设 Weapon 类有序列化功能
    }
}

// 加载武器数据
void Filestore::loadWeapons(vector<Weapon*>& weapons, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // 读取武器数量
    weapons.resize(size);

    for (auto& weapon : weapons) {
        weapon = new Weapon();  // 假设 Weapon 类有默认构造函数
        file.read((char*)weapon, sizeof(Weapon));  // 读取每个武器的数据
    }
}

// 保存护甲数据
void Filestore::saveArmors(const vector<Armor*>& armors, ofstream& file) {
    size_t size = armors.size();
    file.write((char*)&size, sizeof(size));  // 写入护甲数量

    for (const auto& armor : armors) {
        file.write((char*)armor, sizeof(Armor));  // 假设 Armor 类有序列化功能
    }
}

// 加载护甲数据
void Filestore::loadArmors(vector<Armor*>& armors, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // 读取护甲数量
    armors.resize(size);

    for (auto& armor : armors) {
        armor = new Armor();  // 假设 Armor 类有默认构造函数
        file.read((char*)armor, sizeof(Armor));  // 读取每个护甲的数据
    }
}

// 保存进攻技能数据
void Filestore::saveoSkills(const vector<offensiveSkill*>& oSkills, ofstream& file) {
    size_t size = oSkills.size();
    file.write((char*)&size, sizeof(size));  // 写入进攻技能数量

    for (const auto& skill : oSkills) {
        file.write((char*)skill, sizeof(offensiveSkill));  // 写入每个进攻技能的数据
    }
}

// 加载进攻技能数据
void Filestore::loadoSkills(vector<offensiveSkill*>& oSkills, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // 读取进攻技能数量
    oSkills.resize(size);

    for (auto& skill : oSkills) {
        skill = new offensiveSkill();  // 假设 offensiveSkill 类有默认构造函数
        file.read((char*)skill, sizeof(offensiveSkill));  // 读取每个进攻技能的数据
    }
}

// 保存支持技能数据
void Filestore::savesSkills(const vector<supportSkill*>& sSkills, ofstream& file) {
    size_t size = sSkills.size();
    file.write((char*)&size, sizeof(size));  // 写入支持技能数量

    for (const auto& skill : sSkills) {
        file.write((char*)skill, sizeof(supportSkill));  // 写入每个支持技能的数据
    }
}

// 加载支持技能数据
void Filestore::loadsSkills(vector<supportSkill*>& sSkills, ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size));  // 读取支持技能数量
    sSkills.resize(size);

    for (auto& skill : sSkills) {
        skill = new supportSkill();  // 假设 supportSkill 类有默认构造函数
        file.read((char*)skill, sizeof(supportSkill));  // 读取每个支持技能的数据
    }
}
