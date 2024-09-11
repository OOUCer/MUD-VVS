#ifndef SHOP_H  
#define SHOP_H  

#include <iostream>  
#include <vector>  
#include <memory>  
#include <sstream>  
#include "battle.h" 

using namespace std;

// ��ʼ���̵�����  
void shopset();

// �����̵���  
class Shop1 {
private:
    vector<unique_ptr<Weapon>> inventory; // ʹ�� unique_ptr ����ָ����� Weapon ������ڴ棬ȷ����Դ�Զ��ͷ�  

public:
    // ���̵��������  
    void addItem(unique_ptr<Weapon> equipment);

    // �г��̵��е���������  
    void listItems() const;

    // ���Դ��̵깺��ָ������������  
    // ���� true ��ʾ����ɹ���false ��ʾʧ�ܣ���������Ч���ɫ�޷�װ����  
    bool buyItem(Linchong& character, size_t index);
    // ע�⣺����󣬸���������̵�Ŀ�����Ƴ�������������ܻ�ı�  
};

// �����̵���  
class Shop2 {
private:
    vector<unique_ptr<Armor>> inventory; // ʹ�� unique_ptr ����ָ����� Armor ������ڴ棬ȷ����Դ�Զ��ͷ�  

public:
    // ���̵���ӷ���  
    void addItem(unique_ptr<Armor> equipment);

    // �г��̵��е����з���  
    void listItems() const;

    // ���Դ��̵깺��ָ�������ķ���  
    // ���� true ��ʾ����ɹ���false ��ʾʧ�ܣ���������Ч���ɫ�޷�װ����  
    bool buyItem(Linchong& character, size_t index);
    // ע�⣺����󣬸÷��߻���̵�Ŀ�����Ƴ�������������ܻ�ı�  
};

#endif // SHOP_H  
