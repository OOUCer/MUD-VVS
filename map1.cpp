#include <iostream>
#include"Windows.h"
#include"map11.h"
using namespace std;
void Map::showmap(int placeflag)//�����ַ��־int�ͣ��������ģ��ĸ��ص����ʾΪ��ɫ��
{
    cout << "             ";
    if (placeflag == 1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "1.��Ƶ�" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "1.��Ƶ�" << endl;
    cout << "               |" << endl;
    cout << "               |" << endl;
    cout << "               |" << endl;
    if (placeflag == 2)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "2.���";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "2.���";
    cout << "-------";
    if (placeflag == 3)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "3.�η�";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "3.Ӫ��";
    cout << "----------";
    if (placeflag == 4)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "4.���ϳ�";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "4.���ϳ�";
    cout << "------------";
    if (placeflag == 5)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "5.�о�" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
    {
        cout << "5.�о�" << endl;
    }
    cout << "               |                       \\" << endl;
    cout << "               |                        \\" << endl;
    cout << "               |                         \\" << endl;
    cout << "               |                          \\" << endl;
    cout << "             ";
    if (placeflag == 6)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "6.��ͷ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
    {
        cout << "6.��ͷ";
    }
    cout << "                       ";
    if (placeflag == 7)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "7.����" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "7.����" << endl;
    return;
}
void Map::move(int placeflag)//�����ַ��ʶ����ʵӦ�÷��������棩
{
    cout << "��������";
    switch (placeflag)
    {
    case 1:
        cout << "��Ƶ�";
        break;
    case 2:
        cout << "���";
        break;
    case 3:
        cout << "Ӫ��";
        break;
    case 4:
        cout << "���ϳ�";
        break;
    case 5:
        cout << "�о�";
        break;
    case 6:
        cout << "��ͷ";
        break;
    case 7:
        cout << "����";
        break;
    }
}