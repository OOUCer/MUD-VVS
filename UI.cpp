#include <Windows.h>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <vector>
#include "character.h"
#include "UI.h"

#pragma comment(lib, "winmm.lib") // 链接到WinMM库 

using namespace std;

// 设置控制台颜色
void SetConsoleColor(int color);

// 设置控制台窗口大小
bool UI::SetSize(int width, int height)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); // 获取输出句柄

    SMALL_RECT wrt = { 0, 0, width - 1, height - 1 }; // 设置宽高

    bool ret = SetConsoleWindowInfo(hOutput, TRUE, &wrt); // 设置窗体尺寸
    if (!ret) {
        return false;
    }

    COORD coord = { width, height };
    ret = SetConsoleScreenBufferSize(hOutput, coord); // 设置缓冲尺寸

    return ret;
}

// 清除控制台的指定行
void UI::ClearConsoleLines(HANDLE hConsole, SHORT s, SHORT e)
{
    SHORT startLine = s - 1; // 起始行
    SHORT endLine = e - 1; // 结束行

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "无法获取控制台屏幕缓冲区信息！" << std::endl;
        return;
    }

    SHORT width = csbi.dwSize.X; // 屏幕宽度

    std::vector<CHAR> spaces(width, ' '); // 创建空格字符数组

    COORD writePos = { 0, startLine }; // 写入位置初始化

    for (SHORT line = startLine; line <= endLine; ++line) {
        DWORD written;
        if (!WriteConsoleOutputCharacterA(hConsole, spaces.data(), static_cast<DWORD>(spaces.size()), writePos, &written)) {
            std::cerr << "无法写入控制台输出字符！" << std::endl;
            return;
        }
        writePos.Y++; // 移动到下一行
    }
}

// 准备界面
int UI::ready()
{
    Plot plot;

    SetSize(100, 40); // 设置控制台大小
    SetConsoleColor(4); // 设置颜色
    cout << "***************************************************************************************************" << endl; // 打印星号
    SetConsoleColor(7); // 恢复默认颜色
    Sleep(500);

    cout << "为保证游戏体验，请设置上面的星号在同一行。" << endl;
    cout << "游戏过程中，请勿改变窗口大小，避免影响体验。" << endl;
    cout << "按“ENTER”继续游戏" << endl;
    cin.get();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "无法获取控制台句柄！" << std::endl;
    }

    ClearConsoleLines(hConsole, 1, 5); // 清除指定行

    for (int i = 0; i < 44; i++) {
        cout << " "; // 打印空格
    }

    plot.PrintWithDelay("林教头风雪山神庙", 40); // 打印文字
    cout << endl;

    for (int i = 0; i < 29; i++) {
        cout << " ";
    }

    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < 36; i++) {
        cout << " ";
    }

    plot.PrintWithDelay("天理昭昭不可诬，莫将奸恶作良图。", 500); // 打印文字
    cout << endl;

    for (int i = 0; i < 36; i++) {
        cout << " ";
    }

    plot.PrintWithDelay("若非风雪沽村酒，定被焚烧化朽枯。", 500); // 打印文字
    cout << endl;

    for (int i = 0; i < 36; i++) {
        cout << " ";
    }

    plot.PrintWithDelay("自谓冥中施计毒，谁知暗里有神扶。", 500); // 打印文字
    cout << endl;

    for (int i = 0; i < 36; i++) {
        cout << " ";
    }

    plot.PrintWithDelay("最怜万死逃生地，真是瑰奇伟丈夫。", 500); // 打印文字
    cout << endl;

    return 0;
}

// 显示开始菜单并获取用户选择
int UI::showstart()
{
    Plot plot;

    cout << "1.开始征程     2.读取存档     3.退出" << endl;
    cout << "请注意，如果未保存游戏就退出，会导致游戏进度丢失" << endl;

    int flag;
    cin >> flag;

    if (flag > 3 || flag < 1) {
        flag = showstart(); // 重新显示菜单
    }

    return flag;
}

// 显示菜单并获取用户选择
int UI::showmenu()
{
    cout << endl;
    cout << "1.显示属性                    2.显示背包" << endl;
    cout << "3.储存游戏进度                4.返回上一级" << endl;
    cout << "5.退出游戏" << endl;

    int flag;
    cin >> flag;

    if (flag == 5) {
        cout << "正在退出";
        exit(EXIT_SUCCESS); // 退出程序
    }

    return flag;
}

// 显示角色属性
int UI::shuxing(Linchong* lc)
{
    cout << "名称： " << lc->getName();

    for (int i = 0; i < 15; i++) {
        cout << " ";
    }

    cout << "盘缠： " << lc->getGold() << endl;

    cout << "最大生命： " << lc->getMaxHP();

    for (int i = 0; i < 15; i++) {
        cout << " ";
    }

    cout << "当前生命： " << lc->getHP() << endl;

    cout << "攻击： " << lc->getAttack();

    for (int i = 0; i < 15; i++) {
        cout << " ";
    }

    cout << "防御： " << lc->getDefense() << endl;

    cout << "闪避： " << lc->getEvasionRate();

    for (int i = 0; i < 15; i++) {
        cout << " ";
    }

    cout << "命中： " << lc->getHitRate() << endl;

    cout << "速度： " << lc->getSpeed() << endl;

    return 0;
}
