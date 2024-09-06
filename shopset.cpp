#include<iostream>
#include"shop.h"



void Shop1::addItem(unique_ptr<Weapon> equipment) {
	inventory.push_back(move(equipment));
}
void Shop1::listItems() const {
	for (const auto& equipment : inventory) {
		cout << equipment->getName() << ": " << equipment->getDescription() << " Price: " << equipment->getPrice() << endl;
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

void Shop2::addItem(unique_ptr<Armor> equipment) {
	inventory.push_back(move(equipment));
}
void Shop2::listItems() const {
	for (const auto& equipment : inventory) {
		cout << equipment->getName() << ": " << equipment->getDescription() << " Price: " << equipment->getPrice() << endl;
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


