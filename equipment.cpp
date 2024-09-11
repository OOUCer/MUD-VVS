#include "equipment.h"

using namespace std;

// Ĭ�Ϲ��캯������ʼ������Ϊ�ո񣬼۸�Ϊ0
Equipment::Equipment() : name(" "), price(0) {}

// �������Ĺ��캯������ʼ�����ƺͼ۸�
Equipment::Equipment(string name, int price) : name(name), price(price) {}

// ��ȡ����
string Equipment::getName() const {
    return name;
}

// ��ȡ�۸�
int Equipment::getPrice() const {
    return price;
}

// ���� ifget ��־Ϊ1
void Equipment::be_get() {
    ifget = 1;
}

// ��ȡ ifget ��־��ֵ
int Equipment::get_ifget() {
    return ifget;
}

// ���� Equipment �����ļ�
void Equipment::saveToFile(ofstream& file) const {
    size_t nameLength = name.size();

    // д�����Ƴ���
    file.write((char*)&nameLength, sizeof(nameLength));

    // д������
    file.write(name.c_str(), nameLength);

    // д��۸�
    file.write((char*)&price, sizeof(price));
}

// ���ļ����� Equipment ����
void Equipment::loadFromFile(ifstream& file) {
    size_t nameLength;

    // ��ȡ���Ƴ���
    file.read((char*)&nameLength, sizeof(nameLength));

    // ��ȡ����
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = string(nameBuffer);
    delete[] nameBuffer;

    // ��ȡ�۸�
    file.read((char*)&price, sizeof(price));
}

// Ĭ�Ϲ��캯������ʼ�� Weapon ����������
Weapon::Weapon() : Equipment(" ", 0), attack(0), speed(0), hitRate(0.0), attackType(" ") {}

// �������Ĺ��캯������ʼ�� Weapon ����������
Weapon::Weapon(string name, int price, int attack, int speed, float hitRate, string attackType)
    : Equipment(name, price), attack(attack), speed(speed), hitRate(hitRate), attackType(attackType) {}

// ��ȡ������
int Weapon::getAttack() const {
    return attack;
}

// ��ȡ�ٶ�
int Weapon::getSpeed() const {
    return speed;
}

// ��ȡ������
float Weapon::getHitRate() const {
    return hitRate;
}

// ��ȡ��������
string Weapon::getAttackType() const {
    return attackType;
}

// ��ȡ��������
string Weapon::getDescription() const {
    return "�����������ӳ�: " + to_string(attack) +
        " ���мӳ�: " + to_string(hitRate) +
        " �ٶȼӳ�: " + to_string(speed) +
        " ������ʽ��" + attackType;
}

// ��ӡ������Ϣ
void Weapon::describe() const {
    cout << "Weapon: " << name <<
        ", Attack: " << attack <<
        ", Speed: " << speed <<
        ", Hit Rate: " << hitRate <<
        ", Attack Type: " << attackType << endl;
}

// ���� Weapon �����ļ�
void Weapon::saveToFile(ofstream& file) const {
    Equipment::saveToFile(file);  // ������������

    // ��������������
    file.write((char*)&attack, sizeof(attack));  // д�빥����
    file.write((char*)&speed, sizeof(speed));  // д���ٶ�
    file.write((char*)&hitRate, sizeof(hitRate));  // д��������

    // ���湥������ (std::string)
    size_t attackTypeLength = attackType.size();

    // д�빥�����ͳ���
    file.write((char*)&attackTypeLength, sizeof(attackTypeLength));

    // д�빥�������ַ�������
    file.write(attackType.data(), attackTypeLength);
}

// ���ļ����� Weapon ����
void Weapon::loadFromFile(ifstream& file) {
    Equipment::loadFromFile(file);  // ��ȡ���������

    // ��ȡ����������
    file.read((char*)&attack, sizeof(attack));  // ��ȡ������
    file.read((char*)&speed, sizeof(speed));  // ��ȡ�ٶ�
    file.read((char*)&hitRate, sizeof(hitRate));  // ��ȡ������

    // ��ȡ�������� (std::string)
    size_t attackTypeLength;

    // ��ȡ�������ͳ���
    file.read((char*)&attackTypeLength, sizeof(attackTypeLength));

    if (file.fail()) {
        cerr << "��ȡ�������ͳ���ʧ�ܣ�" << endl;
        return;
    }

    attackType.resize(attackTypeLength);  // �����ַ�����С

    // ��ȡ���������ַ�������
    file.read(&attackType[0], attackTypeLength);

    if (file.fail()) {
        cerr << "��ȡ��������ʧ�ܣ�" << endl;
        return;
    }
}

// Ĭ�Ϲ��캯������ʼ�� Armor ����������
Armor::Armor() : defense(0), HP(0), weakness(" ") {}

// �������Ĺ��캯������ʼ�� Armor ����������
Armor::Armor(string name, int price, int defense, int HP, string weakness)
    : Equipment(name, price), defense(defense), HP(HP), weakness(weakness) {}

// ��ȡ������
int Armor::getDefense() const {
    return defense;
}

// ��ȡ�����ӳ�
int Armor::getHP() const {
    return HP;
}

// ��ȡ����
string Armor::getWeakness() const {
    return weakness;
}

// ��ȡ��������
string Armor::getDescription() const {
    return "�÷��߷����ӳ�: " + to_string(defense) +
        " ��������ӳ�: " + to_string(HP) +
        " ���㣺" + weakness;
}

// ��ӡ������Ϣ
void Armor::describe() const {
    cout << "Armor: " << name <<
        ", Defense: " << defense <<
        ", HP Bonus: " << HP <<
        ", Weakness: " << weakness << endl;
}

// ���� Armor �����ļ�
void Armor::saveToFile(ofstream& file) const {
    Equipment::saveToFile(file);  // ������������

    // ������ߵ�����
    file.write((char*)&defense, sizeof(defense));  // д�������
    file.write((char*)&HP, sizeof(HP));  // д�������ӳ�

    // �������� (std::string)
    size_t weaknessLength = weakness.size();

    // д�����㳤��
    file.write((char*)&weaknessLength, sizeof(weaknessLength));

    // д�������ַ�������
    file.write(weakness.c_str(), weaknessLength);
}

// ���ļ����� Armor ����
void Armor::loadFromFile(ifstream& file) {
    Equipment::loadFromFile(file);  // ��ȡ���������

    // ��ȡ���ߵ�����
    file.read((char*)&defense, sizeof(defense));  // ��ȡ������
    file.read((char*)&HP, sizeof(HP));  // ��ȡ�����ӳ�

    // ��ȡ���� (std::string)
    size_t weaknessLength;

    // ��ȡ���㳤��
    file.read((char*)&weaknessLength, sizeof(weaknessLength));

    char* weaknessBuffer = new char[weaknessLength + 1];

    // ��ȡ�����ַ�������
    file.read(weaknessBuffer, weaknessLength);
    weaknessBuffer[weaknessLength] = '\0';
    weakness = string(weaknessBuffer);
    delete[] weaknessBuffer;
}
