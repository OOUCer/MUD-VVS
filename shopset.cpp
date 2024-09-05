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


void shopset() {
	Linchong linchong(" �ֳ� ", 0, 0, 0, 0, 0, 0, 0, 999, 0, 0);
    Weapon dajian(" �� ", 50, 300, 0, 0.4, " ���� ");
	Weapon tiegun(" ���� ", 50, 200, 5, 0.6, " ��� ");
	Weapon cijian(" �̽� ", 50, 110, 10, 1, " ��ͨ ");
	Armor bujia(" ���� ", 50, 50, 100, " ��ͨ ");
	Armor tiejia(" ���� ", 100, 100, 200, " ��� ");
	Armor linjia(" �ۼ� ", 200, 200, 400, " ���� ");

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
	cout << "��������ѡ��1���������ѡ��2���˳�ѡ��0" << endl;
	while (cin >> n) {
		if (n == 0) break;
		if (n == 1) {
			shop1.listItems();
			cout << "��ѡ����Ҫ������������,�˳�ѡ��0" << endl;
			while (cin >> id) {
				// ���Թ�����Ʒ  
				if (id == 0) { 
					system("cls");
					break;
				}
				if (shop1.buyItem(linchong, id - 1)) { // ���Թ�������Ϊ0����Ʒ��Sword��  
					shop1.listItems(); // �ٴ��г���Ʒ�Բ鿴�仯  
				}
				cout << "��ѡ����Ҫ�����������ţ��˳�ѡ��0" << endl;
			}
		}
		if (n == 2) {
			shop2.listItems();
			cout << "��ѡ����Ҫ����ķ�����ţ��˳�ѡ��0" << endl;
			while (cin >> id) {
				// ���Թ�����Ʒ  
				if (id == 0) {
					system("cls");
					break;
				}
				if (shop2.buyItem(linchong, id - 1)) { // ���Թ�������Ϊ0����Ʒ��Sword��  
					shop2.listItems(); // �ٴ��г���Ʒ�Բ鿴�仯  
				}
				cout << "��ѡ����Ҫ����ķ�����ţ��˳�ѡ��0" << endl;
			}
		}

		cout << "��������ѡ��1���������ѡ��2���˳�ѡ��0" << endl;
	}

}
