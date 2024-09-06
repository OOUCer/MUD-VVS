#include <iostream>
#include"Windows.h"
#include"map11.h"
using namespace std;
void Map::showmap(int placeflag)//传入地址标志int型，人物在哪，哪个地点就显示为红色。
{
    cout << "             ";
    if (placeflag == 1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "1.茶酒店" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "1.茶酒店" << endl;
    cout << "               |" << endl;
    cout << "               |" << endl;
    cout << "               |" << endl;
    if (placeflag == 2)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "2.武馆";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "2.武馆";
    cout << "-------";
    if (placeflag == 3)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "3.牢房";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "3.营房";
    cout << "----------";
    if (placeflag == 4)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "4.草料场";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "4.草料场";
    cout << "------------";
    if (placeflag == 5)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "5.市井" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
    {
        cout << "5.市井" << endl;
    }
    cout << "               |                       \\" << endl;
    cout << "               |                        \\" << endl;
    cout << "               |                         \\" << endl;
    cout << "               |                          \\" << endl;
    cout << "             ";
    if (placeflag == 6)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "6.码头";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
    {
        cout << "6.码头";
    }
    cout << "                       ";
    if (placeflag == 7)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "7.古庙" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
        cout << "7.古庙" << endl;
    return;
}
void Map::move(int placeflag)//传入地址标识（其实应该放人物里面）
{
    cout << "你来到了";
    switch (placeflag)
    {
    case 1:
        cout << "茶酒店";
        break;
    case 2:
        cout << "武馆";
        break;
    case 3:
        cout << "营房";
        break;
    case 4:
        cout << "草料场";
        break;
    case 5:
        cout << "市井";
        break;
    case 6:
        cout << "码头";
        break;
    case 7:
        cout << "古庙";
        break;
    }
}