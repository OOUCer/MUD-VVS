#include "filestore.h"
#include "equipment.h"
#include "character.h"
#include "skill.h"
#include <fstream>
#include <iostream>

using namespace std;

// 保存游戏进度
void Filestore::saveGame(Linchong& character, const Time& time) {
    ofstream file("savegame.dat", ios::binary);

    if (file.is_open()) {
        // 保存角色数据
        file.write((char*)&character, sizeof(Linchong));

        // 保存 Time 结构体
        file.write((char*)&time, sizeof(Time));

        file.close();
        cout << "游戏已成功存档！" << endl;
    }
    else {
        cerr << "无法打开文件进行保存！" << endl;
    }
}

// 加载游戏进度
bool Filestore::loadGame(Linchong& character, Time& time) {
    ifstream file("savegame.dat", ios::binary);

    if (file.is_open()) {
        // 读取角色数据
        file.read((char*)&character, sizeof(Linchong));

        if (file.fail()) {
            cerr << "读取角色数据失败！" << endl;
            return false;
        }

        // 读取 Time 结构体
        file.read((char*)&time, sizeof(Time));

        if (file.fail()) {
            cerr << "读取 Time 结构体失败！" << endl;
            return false;
        }

        file.close();
        cout << "游戏已成功加载！" << endl;
        return true;
    }
    else {
        cerr << "无法打开文件进行读取！" << endl;
        return false;
    }
}

// 保存武器和护甲数据
void Filestore::saveEquipment(const vector<Weapon*>& weapons, const vector<Armor*>& armors, ofstream& file) {
    // 保存武器
    size_t weaponSize = weapons.size();
    file.write((char*)&weaponSize, sizeof(weaponSize));  // 写入武器数量

    for (const auto& weapon : weapons) {
        weapon->saveToFile(file);  // 使用 Weapon 类的 saveToFile 方法保存数据
    }

    // 保存护甲
    size_t armorSize = armors.size();
    file.write((char*)&armorSize, sizeof(armorSize));  // 写入护甲数量

    for (const auto& armor : armors) {
        armor->saveToFile(file);  // 使用 Armor 类的 saveToFile 方法保存数据
    }
}

// 加载武器和护甲数据
void Filestore::loadEquipment(vector<Weapon*>& weapons, vector<Armor*>& armors, ifstream& file) {
    // 清空现有的武器并释放内存
    for (auto weapon : weapons) {
        delete weapon;  // 释放每一个 Weapon 对象
    }
    weapons.clear();  // 清空向量

    // 清空现有的护甲并释放内存
    for (auto armor : armors) {
        delete armor;  // 释放每一个 Armor 对象
    }
    armors.clear();  // 清空向量

    // 加载武器
    size_t weaponSize;
    file.read((char*)&weaponSize, sizeof(weaponSize));  // 读取武器数量

    if (file.fail()) {
        cerr << "读取武器数量失败！" << endl;
        return;
    }

    for (size_t i = 0; i < weaponSize; ++i) {
        Weapon* weapon = new Weapon();  // 动态分配内存
        weapon->loadFromFile(file);  // 从文件中读取武器数据

        if (file.fail()) {
            cerr << "读取武器数据失败！" << endl;
            delete weapon;  // 如果失败，释放已分配的内存
            return;
        }

        weapons.push_back(weapon);  // 将武器添加到向量中
    }

    // 加载护甲
    size_t armorSize;
    file.read((char*)&armorSize, sizeof(armorSize));  // 读取护甲数量

    if (file.fail()) {
        cerr << "读取护甲数量失败！" << endl;
        return;
    }

    for (size_t i = 0; i < armorSize; ++i) {
        Armor* armor = new Armor();  // 动态分配内存
        armor->loadFromFile(file);  // 从文件中读取护甲数据

        if (file.fail()) {
            cerr << "读取护甲数据失败！" << endl;
            delete armor;  // 如果失败，释放已分配的内存
            return;
        }

        armors.push_back(armor);  // 将护甲添加到向量中
    }
}

// 保存技能数据
void Filestore::saveSkills(const vector<offensiveSkill*>& oSkills, const vector<supportSkill*>& sSkills, ofstream& file) {
    // 保存进攻技能
    size_t oSkillSize = oSkills.size();
    file.write((char*)&oSkillSize, sizeof(oSkillSize));  // 写入进攻技能数量

    for (const auto& skill : oSkills) {
        skill->saveToFile(file);  // 使用 offensiveSkill 类的 saveToFile 方法保存数据
    }

    // 保存支持技能
    size_t sSkillSize = sSkills.size();
    file.write((char*)&sSkillSize, sizeof(sSkillSize));  // 写入支持技能数量

    for (const auto& skill : sSkills) {
        skill->saveToFile(file);  // 使用 supportSkill 类的 saveToFile 方法保存数据
    }
}

// 加载技能数据
void Filestore::loadSkills(vector<offensiveSkill*>& oSkills, vector<supportSkill*>& sSkills, ifstream& file) {
    // 加载进攻技能
    size_t oSkillSize;
    file.read((char*)&oSkillSize, sizeof(oSkillSize));  // 读取进攻技能数量

    oSkills.resize(oSkillSize);  // 调整向量大小

    for (size_t i = 0; i < oSkillSize; ++i) {
        oSkills[i] = new offensiveSkill();  // 动态分配内存
        oSkills[i]->loadFromFile(file);  // 使用 offensiveSkill 类的 loadFromFile 方法加载数据
    }

    // 加载支持技能
    size_t sSkillSize;
    file.read((char*)&sSkillSize, sizeof(sSkillSize));  // 读取支持技能数量

    sSkills.resize(sSkillSize);  // 调整向量大小

    for (size_t i = 0; i < sSkillSize; ++i) {
        sSkills[i] = new supportSkill();  // 动态分配内存
        sSkills[i]->loadFromFile(file);  // 使用 supportSkill 类的 loadFromFile 方法加载数据
    }
}
