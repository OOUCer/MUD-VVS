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
    // ���ÿ���̨���ڵĴ�С
    bool SetSize(int width, int height);

    // �������̨�е�ָ����
    void ClearConsoleLines(HANDLE hConsole, SHORT s, SHORT e);

public:
    // ׼������
    int ready();

    // ��ʼ����, ���˵�
    int showstart();

    // չʾ�˵�
    int showmenu();

    // չʾ����
    int shuxing(Linchong* lc);
};

#endif // UI_H
