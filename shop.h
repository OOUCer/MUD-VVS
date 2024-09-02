#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include "character.h"
#include "equipment.h"
using namespace std;
//武器商店类
class Shop1 {
private:
	vector<unique_ptr<Weapon>> inventory; // 使用unique_ptr管理内存  
public:
	void addItem(unique_ptr<Weapon> equipment) {
		inventory.push_back(move(equipment));
	}
	void listItems() const {
		for (const auto& equipment : inventory) {
			cout << equipment->getName() << ": " << equipment->getDescription() << " Price: " << equipment->getPrice() << endl;
		}
	}
	// 尝试从商店购买物品  
	bool buyItem(Linchong& character, size_t index) {
		if (index >= inventory.size()) {
			cout << "输入有误" << endl;
			return false;
		}
		auto it = inventory.begin() + index; // 获取迭代器  
		auto& equipment = *it; // 解引用迭代器以获取对 unique_ptr 的引用  
		if (character.buyItem1(equipment.get())) { // 传递裸指针给 Character 的 buyItem 方法  
			// 如果购买成功，从商店中移除该物品  
			inventory.erase(it); // 使用迭代器来安全地移除元素  
			return true;
		}
		return false;
	}
	// 注意：移除物品后，如果玩家想要再次购买，索引可能会改变  
};
//防具商店类
class Shop2 {
private:
	vector<unique_ptr<Armor>> inventory; // 使用unique_ptr管理内存  
public:
	void addItem(unique_ptr<Armor> equipment) {
		inventory.push_back(move(equipment));
	}
	void listItems() const {
		for (const auto& equipment : inventory) {
			cout << equipment->getName() << ": " << equipment->getDescription() << " Price: " << equipment->getPrice() << endl;
		}
	}
	// 尝试从商店购买物品  
	bool buyItem(Linchong& character, size_t index) {
		if (index >= inventory.size()) {
			cout << "输入有误" << endl;
			return false;
		}
		auto it = inventory.begin() + index; // 获取迭代器  
		auto& equipment = *it; // 解引用迭代器以获取对 unique_ptr 的引用  
		if (character.buyItem2(equipment.get())) { // 传递裸指针给 Character 的 buyItem 方法  
			// 如果购买成功，从商店中移除该物品  
			inventory.erase(it); // 使用迭代器来安全地移除元素  
			return true;
		}
		return false;
	}
	// 注意：移除物品后，如果玩家想要再次购买，索引可能会改变  
};
#endif
