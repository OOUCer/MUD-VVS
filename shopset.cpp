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
// 尝试从商店购买物品  
bool Shop1::buyItem(Linchong& character, size_t index) {
	if (index >= inventory.size()) {
		cout << "输入有误" << endl;
		return false;
	}
	auto it = inventory.begin() + index; // 获取迭代器  
	auto& equipment = *it; // 解引用迭代器以获取对 unique_ptr 的引用  
	if (character.buyItem1(equipment.get())) { // 传递裸指针给 Character 的 buyItem 方法  
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
// 尝试从商店购买物品  
bool Shop2::buyItem(Linchong& character, size_t index) {
	if (index >= inventory.size()) {
		cout << "输入有误" << endl;
		return false;
	}
	auto it = inventory.begin() + index; // 获取迭代器  
	auto& equipment = *it; // 解引用迭代器以获取对 unique_ptr 的引用  
	if (character.buyItem2(equipment.get())) { // 传递裸指针给 Character 的 buyItem 方法  
		return true;
	}
	return false;
}


