#include "equipment.h"

using namespace std;

// 默认构造函数，初始化名称为空格，价格为0
Equipment::Equipment() : name(" "), price(0) {}

// 带参数的构造函数，初始化名称和价格
Equipment::Equipment(string name, int price) : name(name), price(price) {}

// 获取名称
string Equipment::getName() const {
    return name;
}

// 获取价格
int Equipment::getPrice() const {
    return price;
}

// 设置 ifget 标志为1
void Equipment::be_get() {
    ifget = 1;
}

// 获取 ifget 标志的值
int Equipment::get_ifget() {
    return ifget;
}

// 保存 Equipment 对象到文件
void Equipment::saveToFile(ofstream& file) const {
    size_t nameLength = name.size();

    // 写入名称长度
    file.write((char*)&nameLength, sizeof(nameLength));

    // 写入名称
    file.write(name.c_str(), nameLength);

    // 写入价格
    file.write((char*)&price, sizeof(price));
}

// 从文件加载 Equipment 对象
void Equipment::loadFromFile(ifstream& file) {
    size_t nameLength;

    // 读取名称长度
    file.read((char*)&nameLength, sizeof(nameLength));

    // 读取名称
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = string(nameBuffer);
    delete[] nameBuffer;

    // 读取价格
    file.read((char*)&price, sizeof(price));
}

// 默认构造函数，初始化 Weapon 的所有属性
Weapon::Weapon() : Equipment(" ", 0), attack(0), speed(0), hitRate(0.0), attackType(" ") {}

// 带参数的构造函数，初始化 Weapon 的所有属性
Weapon::Weapon(string name, int price, int attack, int speed, float hitRate, string attackType)
    : Equipment(name, price), attack(attack), speed(speed), hitRate(hitRate), attackType(attackType) {}

// 获取攻击力
int Weapon::getAttack() const {
    return attack;
}

// 获取速度
int Weapon::getSpeed() const {
    return speed;
}

// 获取命中率
float Weapon::getHitRate() const {
    return hitRate;
}

// 获取攻击类型
string Weapon::getAttackType() const {
    return attackType;
}

// 获取武器描述
string Weapon::getDescription() const {
    return "该武器攻击加成: " + to_string(attack) +
        " 命中加成: " + to_string(hitRate) +
        " 速度加成: " + to_string(speed) +
        " 攻击方式：" + attackType;
}

// 打印武器信息
void Weapon::describe() const {
    cout << "Weapon: " << name <<
        ", Attack: " << attack <<
        ", Speed: " << speed <<
        ", Hit Rate: " << hitRate <<
        ", Attack Type: " << attackType << endl;
}

// 保存 Weapon 对象到文件
void Weapon::saveToFile(ofstream& file) const {
    Equipment::saveToFile(file);  // 保存基类的属性

    // 保存武器的属性
    file.write((char*)&attack, sizeof(attack));  // 写入攻击力
    file.write((char*)&speed, sizeof(speed));  // 写入速度
    file.write((char*)&hitRate, sizeof(hitRate));  // 写入命中率

    // 保存攻击类型 (std::string)
    size_t attackTypeLength = attackType.size();

    // 写入攻击类型长度
    file.write((char*)&attackTypeLength, sizeof(attackTypeLength));

    // 写入攻击类型字符串内容
    file.write(attackType.data(), attackTypeLength);
}

// 从文件加载 Weapon 对象
void Weapon::loadFromFile(ifstream& file) {
    Equipment::loadFromFile(file);  // 读取基类的属性

    // 读取武器的属性
    file.read((char*)&attack, sizeof(attack));  // 读取攻击力
    file.read((char*)&speed, sizeof(speed));  // 读取速度
    file.read((char*)&hitRate, sizeof(hitRate));  // 读取命中率

    // 读取攻击类型 (std::string)
    size_t attackTypeLength;

    // 读取攻击类型长度
    file.read((char*)&attackTypeLength, sizeof(attackTypeLength));

    if (file.fail()) {
        cerr << "读取攻击类型长度失败！" << endl;
        return;
    }

    attackType.resize(attackTypeLength);  // 调整字符串大小

    // 读取攻击类型字符串内容
    file.read(&attackType[0], attackTypeLength);

    if (file.fail()) {
        cerr << "读取攻击类型失败！" << endl;
        return;
    }
}

// 默认构造函数，初始化 Armor 的所有属性
Armor::Armor() : defense(0), HP(0), weakness(" ") {}

// 带参数的构造函数，初始化 Armor 的所有属性
Armor::Armor(string name, int price, int defense, int HP, string weakness)
    : Equipment(name, price), defense(defense), HP(HP), weakness(weakness) {}

// 获取防御力
int Armor::getDefense() const {
    return defense;
}

// 获取生命加成
int Armor::getHP() const {
    return HP;
}

// 获取弱点
string Armor::getWeakness() const {
    return weakness;
}

// 获取防具描述
string Armor::getDescription() const {
    return "该防具防御加成: " + to_string(defense) +
        " 最大生命加成: " + to_string(HP) +
        " 弱点：" + weakness;
}

// 打印防具信息
void Armor::describe() const {
    cout << "Armor: " << name <<
        ", Defense: " << defense <<
        ", HP Bonus: " << HP <<
        ", Weakness: " << weakness << endl;
}

// 保存 Armor 对象到文件
void Armor::saveToFile(ofstream& file) const {
    Equipment::saveToFile(file);  // 保存基类的属性

    // 保存防具的属性
    file.write((char*)&defense, sizeof(defense));  // 写入防御力
    file.write((char*)&HP, sizeof(HP));  // 写入生命加成

    // 保存弱点 (std::string)
    size_t weaknessLength = weakness.size();

    // 写入弱点长度
    file.write((char*)&weaknessLength, sizeof(weaknessLength));

    // 写入弱点字符串内容
    file.write(weakness.c_str(), weaknessLength);
}

// 从文件加载 Armor 对象
void Armor::loadFromFile(ifstream& file) {
    Equipment::loadFromFile(file);  // 读取基类的属性

    // 读取防具的属性
    file.read((char*)&defense, sizeof(defense));  // 读取防御力
    file.read((char*)&HP, sizeof(HP));  // 读取生命加成

    // 读取弱点 (std::string)
    size_t weaknessLength;

    // 读取弱点长度
    file.read((char*)&weaknessLength, sizeof(weaknessLength));

    char* weaknessBuffer = new char[weaknessLength + 1];

    // 读取弱点字符串内容
    file.read(weaknessBuffer, weaknessLength);
    weaknessBuffer[weaknessLength] = '\0';
    weakness = string(weaknessBuffer);
    delete[] weaknessBuffer;
}
