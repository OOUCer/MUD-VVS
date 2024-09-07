#include "equipment.h"

using namespace std;

Equipment::Equipment() : name(" "), price(0) {}

Equipment::Equipment(string name, int price) : name(name), price(price) {}

string Equipment::getName() const {
    return name;
}

int Equipment::getPrice() const {
    return price;
}

void Equipment::saveToFile(ofstream& file) const {
    size_t nameLength = name.size();
    file.write((char*)&nameLength, sizeof(nameLength));  // 写入名称长度
    file.write(name.c_str(), nameLength);  // 写入名称
    file.write((char*)&price, sizeof(price));  // 写入价格
}

void Equipment::loadFromFile(ifstream& file) {
    size_t nameLength;
    file.read((char*)&nameLength, sizeof(nameLength));  // 读取名称长度
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = string(nameBuffer);
    delete[] nameBuffer;

    file.read((char*)&price, sizeof(price));  // 读取价格
}

Weapon::Weapon() : attack(0), speed(0), hitRate(0.0), attackType(" ") {}

Weapon::Weapon(string name, int price, int attack, int speed, float hitRate, string attackType)
    : Equipment(name, price), attack(attack), speed(speed), hitRate(hitRate), attackType(attackType) {}

int Weapon::getAttack() const {
    return attack;
}

int Weapon::getSpeed() const {
    return speed;
}

float Weapon::getHitRate() const {
    return hitRate;
}

string Weapon::getAttackType() const {
    return attackType;
}

string Weapon::getDescription() const {
    return "该武器攻击加成: " + to_string(attack) + " 命中加成: " + to_string(hitRate) + " 速度加成: " + to_string(speed) + " 攻击方式：" + attackType;
}

void Weapon::describe() const {
    cout << "Weapon: " << name << ", Attack: " << attack << ", Speed: " << speed << ", Hit Rate: " << hitRate << ", Attack Type: " << attackType << endl;
}

void Weapon::saveToFile(ofstream& file) const {
    Equipment::saveToFile(file);  // 保存基类的属性
    file.write((char*)&attack, sizeof(attack));  // 写入攻击力
    file.write((char*)&speed, sizeof(speed));  // 写入速度
    file.write((char*)&hitRate, sizeof(hitRate));  // 写入命中率

    size_t attackTypeLength = attackType.size();
    file.write((char*)&attackTypeLength, sizeof(attackTypeLength));  // 写入攻击类型长度
    file.write(attackType.c_str(), attackTypeLength);  // 写入攻击类型
}

void Weapon::loadFromFile(ifstream& file) {
    Equipment::loadFromFile(file);  // 读取基类的属性
    file.read((char*)&attack, sizeof(attack));  // 读取攻击力
    file.read((char*)&speed, sizeof(speed));  // 读取速度
    file.read((char*)&hitRate, sizeof(hitRate));  // 读取命中率

    size_t attackTypeLength;
    file.read((char*)&attackTypeLength, sizeof(attackTypeLength));  // 读取攻击类型长度
    char* attackTypeBuffer = new char[attackTypeLength + 1];
    file.read(attackTypeBuffer, attackTypeLength);
    attackTypeBuffer[attackTypeLength] = '\0';
    attackType = string(attackTypeBuffer);
    delete[] attackTypeBuffer;
}

Armor::Armor() : defense(0), HP(0), weakness(" ") {}

Armor::Armor(string name, int price, int defense, int HP, string weakness)
    : Equipment(name, price), defense(defense), HP(HP), weakness(weakness) {}

int Armor::getDefense() const {
    return defense;
}

int Armor::getHP() const {
    return HP;
}

string Armor::getWeakness() const {
    return weakness;
}

string Armor::getDescription() const {
    return "该防具防御加成: " + to_string(defense) + " 最大生命加成: " + to_string(HP) + " 弱点：" + weakness;
}

void Armor::describe() const {
    cout << "Armor: " << name << ", Defense: " << defense << ", HP Bonus: " << HP << ", Weakness: " << weakness << endl;
}

void Armor::saveToFile(ofstream& file) const {
    Equipment::saveToFile(file);  // 保存基类的属性
    file.write((char*)&defense, sizeof(defense));  // 写入防御力
    file.write((char*)&HP, sizeof(HP));  // 写入生命加成

    size_t weaknessLength = weakness.size();
    file.write((char*)&weaknessLength, sizeof(weaknessLength));  // 写入弱点长度
    file.write(weakness.c_str(), weaknessLength);  // 写入弱点
}

void Armor::loadFromFile(ifstream& file) {
    Equipment::loadFromFile(file);  // 读取基类的属性
    file.read((char*)&defense, sizeof(defense));  // 读取防御力
    file.read((char*)&HP, sizeof(HP));  // 读取生命加成

    size_t weaknessLength;
    file.read((char*)&weaknessLength, sizeof(weaknessLength));  // 读取弱点长度
    char* weaknessBuffer = new char[weaknessLength + 1];
    file.read(weaknessBuffer, weaknessLength);
    weaknessBuffer[weaknessLength] = '\0';
    weakness = string(weaknessBuffer);
    delete[] weaknessBuffer;
}
