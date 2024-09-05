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


void shopset(Linchong& linchong) {
	
    Weapon dajian(" 大剑 ", 50, 300, 0, 0.4, " 砍击 ");
	Weapon tiegun(" 铁棍 ", 50, 200, 5, 0.6, " 打击 ");
	Weapon cijian(" 刺剑 ", 50, 110, 10, 1, " 贯通 ");
	Armor bujia(" 布甲 ", 50, 50, 100, " 贯通 ");
	Armor tiejia(" 铁甲 ", 100, 100, 200, " 打击 ");
	Armor linjia(" 鳞甲 ", 200, 200, 400, " 砍击 ");

	Shop1 shop1;
	Shop2 shop2;
	shop1.addItem(make_unique<Weapon>(dajian));
	shop1.addItem(make_unique<Weapon>(tiegun));
	shop1.addItem(make_unique<Weapon>(cijian));
	shop2.addItem(make_unique<Armor>(bujia));
	shop2.addItem(make_unique<Armor>(tiejia));
	shop2.addItem(make_unique<Armor>(linjia));

	int n;
	int id;
	cout << "购买武器选择1，购买防具选择2，退出选择0" << endl;
	while (cin >> n) {
		if (n == 0) break;
		if (n == 1) {
			shop1.listItems();
			cout << "请选择你要购买的武器序号,退出选择0" << endl;
			while (cin >> id) {
				// 尝试购买物品  
				if (id == 0) { 
					system("cls");
					break;
				}
				if (shop1.buyItem(linchong, id - 1)) { // 尝试购买索引为0的物品（Sword）  
					shop1.listItems(); // 再次列出物品以查看变化  
				}
				cout << "请选择你要购买的武器序号，退出选择0" << endl;
			}
		}
		if (n == 2) {
			shop2.listItems();
			cout << "请选择你要购买的防具序号，退出选择0" << endl;
			while (cin >> id) {
				// 尝试购买物品  
				if (id == 0) {
					system("cls");
					break;
				}
				if (shop2.buyItem(linchong, id - 1)) { // 尝试购买索引为0的物品（Sword）  
					shop2.listItems(); // 再次列出物品以查看变化  
				}
				cout << "请选择你要购买的防具序号，退出选择0" << endl;
			}
		}

		cout << "购买武器选择1，购买防具选择2，退出选择0" << endl;
	}

	cout << " 展示： " << endl;
	linchong.printWeapons();
	linchong.printArmors();
}
