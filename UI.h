#ifndef UI_H
#define UI_H

#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include "plot.h"

class UI
{
private:
    // 设置控制台窗口的大小
    bool SetSize(int width, int height);

    // 清除控制台中的指定行
    void ClearConsoleLines(HANDLE hConsole, SHORT s, SHORT e);

public:
    // 准备界面
    int ready();

    // 开始界面, 主菜单
    int showstart();

    // 展示菜单
    int showmenu();

    // 展示属性
    int shuxing(Linchong* lc);
};

#endif // UI_H
