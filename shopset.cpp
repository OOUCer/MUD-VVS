#include<iostream>
#include"shop.h"

using namespace std;

// 添加物品到商店
void Shop1::addItem(unique_ptr<Weapon> equipment) {
    inventory.push_back(move(equipment));
}

// 列出商店中的物品（只列出前三个物品）
void Shop1::listItems() const {
    size_t count = 1;

    for (const auto& equipment : inventory) {
        if (count >= 4) {
            break; // 只列出前三个
        }

        cout << "序号：" << count << " " << equipment->getName()
            << ": " << equipment->getDescription()
            << " 价格: " << equipment->getPrice() << endl;

        ++count;
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

// 添加物品到商店
void Shop2::addItem(unique_ptr<Armor> equipment) {
    inventory.push_back(move(equipment));
}

// 列出商店中的物品（只列出前三个物品）
void Shop2::listItems() const {
    size_t count = 1;

    for (const auto& equipment : inventory) {
        if (count >= 4) {
            break; // 只列出前三个
        }

        cout << "序号：" << count << " " << equipment->getName()
            << ": " << equipment->getDescription()
            << " 价格: " << equipment->getPrice() << endl;

        ++count;
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
