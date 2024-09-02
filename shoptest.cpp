#include <string>
#include <vector>
#include <iostream>
#include "character.h"
#include "equipment.h "
#include "shop.h"

int main() {


	Linchong linchong("林冲", 0, 0, 0, 0, 0, 0, 0, 999, 0, 0);

	Weapon dajian("大剑", 50, 300, 0, 0.4, slash);
	Weapon tiegun("铁棍", 50, 200, 5, 0.6, strike);
	Weapon cijian("刺剑", 50, 110, 10, 1, pierce);

	Armor bujia("布甲", 50, 50, 100, pierce);
	Armor tiejia("铁甲", 100, 100, 200, strike);
	Armor linjia("鳞甲", 200, 200, 400, slash);

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
				if (id == 0)break;
				if (shop1.buyItem(linchong, id-1)) { // 尝试购买索引为0的物品（Sword）  
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
				if (id == 0)break;
				if (shop2.buyItem(linchong, id-1)) { // 尝试购买索引为0的物品（Sword）  
					shop2.listItems(); // 再次列出物品以查看变化  
				}
				cout << "请选择你要购买的防具序号，退出选择0" << endl;
			}
		}

		cout << "购买武器选择1，购买防具选择2，退出选择0" << endl;
	}
	
	cout << "展示：" << endl;
	linchong.printArmors();
	linchong.printWeapons();
}
