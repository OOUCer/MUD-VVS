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
    file.write((char*)&nameLength, sizeof(nameLength));  // д�����Ƴ���
    file.write(name.c_str(), nameLength);  // д������
    file.write((char*)&price, sizeof(price));  // д��۸�
}

void Equipment::loadFromFile(ifstream& file) {
    size_t nameLength;
    file.read((char*)&nameLength, sizeof(nameLength));  // ��ȡ���Ƴ���
    char* nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = string(nameBuffer);
    delete[] nameBuffer;

    file.read((char*)&price, sizeof(price));  // ��ȡ�۸�
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
    return "�����������ӳ�: " + to_string(attack) + " ���мӳ�: " + to_string(hitRate) + " �ٶȼӳ�: " + to_string(speed) + " ������ʽ��" + attackType;
}

void Weapon::describe() const {
    cout << "Weapon: " << name << ", Attack: " << attack << ", Speed: " << speed << ", Hit Rate: " << hitRate << ", Attack Type: " << attackType << endl;
}

void Weapon::saveToFile(ofstream& file) const {
    Equipment::saveToFile(file);  // ������������

    // ��������������
    file.write((char*)&attack, sizeof(attack));  // д�빥����
    file.write((char*)&speed, sizeof(speed));  // д���ٶ�
    file.write((char*)&hitRate, sizeof(hitRate));  // д��������

    // ���湥������ (std::string)
    size_t attackTypeLength = attackType.size();
    file.write((char*)&attackTypeLength, sizeof(attackTypeLength));  // д�빥�����ͳ���
    file.write(attackType.data(), attackTypeLength);  // д�빥�������ַ�������
}


void Weapon::loadFromFile(ifstream& file) {
    Equipment::loadFromFile(file);  // ��ȡ���������

    // ��ȡ����������
    file.read((char*)&attack, sizeof(attack));  // ��ȡ������
    file.read((char*)&speed, sizeof(speed));  // ��ȡ�ٶ�
    file.read((char*)&hitRate, sizeof(hitRate));  // ��ȡ������

    // ��ȡ�������� (std::string)
    size_t attackTypeLength;
    file.read((char*)&attackTypeLength, sizeof(attackTypeLength));  // ��ȡ�������ͳ���

    if (file.fail()) {
        cerr << "��ȡ�������ͳ���ʧ�ܣ�" << endl;
        return;
    }

    attackType.resize(attackTypeLength);  // �����ַ�����С
    file.read(&attackType[0], attackTypeLength);  // ��ȡ�ַ�������

    if (file.fail()) {
        cerr << "��ȡ��������ʧ�ܣ�" << endl;
        return;
    }
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
    return "�÷��߷����ӳ�: " + to_string(defense) + " ��������ӳ�: " + to_string(HP) + " ���㣺" + weakness;
}

void Armor::describe() const {
    cout << "Armor: " << name << ", Defense: " << defense << ", HP Bonus: " << HP << ", Weakness: " << weakness << endl;
}

void Armor::saveToFile(ofstream& file) const {
    Equipment::saveToFile(file);  // ������������
    file.write((char*)&defense, sizeof(defense));  // д�������
    file.write((char*)&HP, sizeof(HP));  // д�������ӳ�

    size_t weaknessLength = weakness.size();
    file.write((char*)&weaknessLength, sizeof(weaknessLength));  // д�����㳤��
    file.write(weakness.c_str(), weaknessLength);  // д������
}

void Armor::loadFromFile(ifstream& file) {
    Equipment::loadFromFile(file);  // ��ȡ���������
    file.read((char*)&defense, sizeof(defense));  // ��ȡ������
    file.read((char*)&HP, sizeof(HP));  // ��ȡ�����ӳ�

    size_t weaknessLength;
    file.read((char*)&weaknessLength, sizeof(weaknessLength));  // ��ȡ���㳤��
    char* weaknessBuffer = new char[weaknessLength + 1];
    file.read(weaknessBuffer, weaknessLength);
    weaknessBuffer[weaknessLength] = '\0';
    weakness = string(weaknessBuffer);
    delete[] weaknessBuffer;
}
