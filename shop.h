#ifndef SHOP_H  
#define SHOP_H  

#include <iostream>  
#include <vector>  
#include <memory>  
#include <sstream>  
#include "battle.h" 

using namespace std;

void shopset();

// 武器商店类  
class Shop1 {
private:
    vector<unique_ptr<Weapon>> inventory; // 使用unique_ptr智能指针管理Weapon对象的内存，确保资源自动释放  

public:
    // 向商店添加武器  
    void addItem(unique_ptr<Weapon> equipment);

    // 列出商店中的所有武器  
    void listItems() const;

    // 尝试从商店购买指定索引的武器  
    // 返回true表示购买成功，false表示失败（如索引无效或角色无法装备）  
    bool buyItem(Linchong& character, size_t index);
    // 注意：购买后，该武器会从商店的库存中移除，因此索引可能会改变  
};

// 防具商店类  
class Shop2 {
private:
    vector<unique_ptr<Armor>> inventory; // 使用unique_ptr智能指针管理Armor对象的内存，确保资源自动释放  

public:
    // 向商店添加防具  
    void addItem(unique_ptr<Armor> equipment);

    // 列出商店中的所有防具  
    void listItems() const;

    // 尝试从商店购买指定索引的防具  
    // 返回true表示购买成功，false表示失败（如索引无效或角色无法装备）  
    bool buyItem(Linchong& character, size_t index);
    // 注意：购买后，该防具会从商店的库存中移除，因此索引可能会改变  
};

#endif // SHOP_H  
