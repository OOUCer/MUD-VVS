#include<iostream>
#include"shop.h"



void Shop1::addItem(unique_ptr<Weapon> equipment) {
	inventory.push_back(move(equipment));
}
void Shop1::listItems() const { // ֻ�г�ǰ������Ʒ  
	size_t count = 0;
	for (const auto& equipment : inventory) {
		if (count >= 3) break; // ֻ�г�ǰ����  
		cout << equipment->getName() << ": " << equipment->getDescription() << " �۸�: " << equipment->getPrice() << endl;
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

void Shop2::addItem(unique_ptr<Armor> equipment) {
	inventory.push_back(move(equipment));
}
void Shop2::listItems() const { // ֻ�г�ǰ������Ʒ  
	size_t count = 0;
	for (const auto& equipment : inventory) {
		if (count >= 3) break; // ֻ�г�ǰ����  
		cout << equipment->getName() << ": " << equipment->getDescription() << " �۸�: " << equipment->getPrice() << endl;
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


