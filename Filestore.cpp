#include "filestore.h"
#include "equipment.h"
#include"character.h"
#include "skill.h"
#include <fstream>
#include <iostream>

using namespace std;

// 保存游戏进度
void Filestore::saveGame(Linchong& character) {
    ofstream file("savegame.dat", ios::binary);
    if (file.is_open()) {
        // 保存角色基本属性
        file.write((char*)&character, sizeof(Linchong));

        // 保存武器、护甲、技能
        saveEquipment(*character.getWeapons(), *character.getArmors(), file);
        saveSkills(*character.getoSkills(), *character.getsSkills(), file);

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
        // 读取角色基本属性
        file.read((char*)&character, sizeof(Linchong));

        // 加载武器、护甲、技能
        loadEquipment(*character.getWeapons(), *character.getArmors(), file);
        loadSkills(*character.getoSkills(), *character.getsSkills(), file);

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
    file.write((char*)&weaponSize, sizeof(weaponSize));
    for (const auto& weapon : weapons) {
        weapon->saveToFile(file);  // 使用 Weapon 类的 saveToFile 方法保存数据
    }

    // 保存护甲
    size_t armorSize = armors.size();
    file.write((char*)&armorSize, sizeof(armorSize));
    for (const auto& armor : armors) {
        armor->saveToFile(file);  // 使用 Armor 类的 saveToFile 方法保存数据
    }
}

// 加载武器和护甲数据
void Filestore::loadEquipment(vector<Weapon*>& weapons, vector<Armor*>& armors, ifstream& file) {
    // 加载武器
    size_t weaponSize;
    file.read((char*)&weaponSize, sizeof(weaponSize));
    weapons.resize(weaponSize);
    for (size_t i = 0; i < weaponSize; ++i) {
        weapons[i] = new Weapon();
        weapons[i]->loadFromFile(file);  // 使用 Weapon 类的 loadFromFile 方法加载数据
    }

    // 加载护甲
    size_t armorSize;
    file.read((char*)&armorSize, sizeof(armorSize));
    armors.resize(armorSize);
    for (size_t i = 0; i < armorSize; ++i) {
        armors[i] = new Armor();
        armors[i]->loadFromFile(file);  // 使用 Armor 类的 loadFromFile 方法加载数据
    }
}

// 保存技能数据
void Filestore::saveSkills(const vector<offensiveSkill*>& oSkills, const vector<supportSkill*>& sSkills, ofstream& file) {
    // 保存进攻技能
    size_t oSkillSize = oSkills.size();
    file.write((char*)&oSkillSize, sizeof(oSkillSize));
    for (const auto& skill : oSkills) {
        skill->saveToFile(file);  // 使用 offensiveSkill 类的 saveToFile 方法保存数据
    }

    // 保存支持技能
    size_t sSkillSize = sSkills.size();
    file.write((char*)&sSkillSize, sizeof(sSkillSize));
    for (const auto& skill : sSkills) {
        skill->saveToFile(file);  // 使用 supportSkill 类的 saveToFile 方法保存数据
    }
}

// 加载技能数据
void Filestore::loadSkills(vector<offensiveSkill*>& oSkills, vector<supportSkill*>& sSkills, ifstream& file) {
    // 加载进攻技能
    size_t oSkillSize;
    file.read((char*)&oSkillSize, sizeof(oSkillSize));
    oSkills.resize(oSkillSize);
    for (size_t i = 0; i < oSkillSize; ++i) {
        oSkills[i] = new offensiveSkill();
        oSkills[i]->loadFromFile(file);  // 使用 offensiveSkill 类的 loadFromFile 方法加载数据
    }

    // 加载支持技能
    size_t sSkillSize;
    file.read((char*)&sSkillSize, sizeof(sSkillSize));
    sSkills.resize(sSkillSize);
    for (size_t i = 0; i < sSkillSize; ++i) {
        sSkills[i] = new supportSkill();
        sSkills[i]->loadFromFile(file);  // 使用 supportSkill 类的 loadFromFile 方法加载数据
    }
}
