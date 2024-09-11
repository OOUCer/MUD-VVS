#include<iostream>
#include"shop.h"

using namespace std;

// �����Ʒ���̵�
void Shop1::addItem(unique_ptr<Weapon> equipment) {
    inventory.push_back(move(equipment));
}

// �г��̵��е���Ʒ��ֻ�г�ǰ������Ʒ��
void Shop1::listItems() const {
    size_t count = 1;

    for (const auto& equipment : inventory) {
        if (count >= 4) {
            break; // ֻ�г�ǰ����
        }

        cout << "��ţ�" << count << " " << equipment->getName()
            << ": " << equipment->getDescription()
            << " �۸�: " << equipment->getPrice() << endl;

        ++count;
    }
}

// ���Դ��̵깺����Ʒ
bool Shop1::buyItem(Linchong& character, size_t index) {
    if (index >= inventory.size()) {
        cout << "��������" << endl;
        return false;
    }

    auto it = inventory.begin() + index; // ��ȡ������
    auto& equipment = *it; // �����õ������Ի�ȡ�� unique_ptr ������

    if (character.buyItem1(equipment.get())) { // ������ָ��� Character �� buyItem ����
        return true;
    }

    return false;
}

// �����Ʒ���̵�
void Shop2::addItem(unique_ptr<Armor> equipment) {
    inventory.push_back(move(equipment));
}

// �г��̵��е���Ʒ��ֻ�г�ǰ������Ʒ��
void Shop2::listItems() const {
    size_t count = 1;

    for (const auto& equipment : inventory) {
        if (count >= 4) {
            break; // ֻ�г�ǰ����
        }

        cout << "��ţ�" << count << " " << equipment->getName()
            << ": " << equipment->getDescription()
            << " �۸�: " << equipment->getPrice() << endl;

        ++count;
    }
}

// ���Դ��̵깺����Ʒ
bool Shop2::buyItem(Linchong& character, size_t index) {
    if (index >= inventory.size()) {
        cout << "��������" << endl;
        return false;
    }

    auto it = inventory.begin() + index; // ��ȡ������
    auto& equipment = *it; // �����õ������Ի�ȡ�� unique_ptr ������

    if (character.buyItem2(equipment.get())) { // ������ָ��� Character �� buyItem ����
        return true;
    }

    return false;
}
