#pragma once
#include<Windows.h>
#include<iostream>
#include<vector>
#include"plot.h"
class UI
{
private:
	bool SetSize(int width, int height);
	void ClearConsoleLines(HANDLE hConsole, SHORT s, SHORT e);
public:
	int showstart();//��ʼչʾ
	int showmenu();//չʾ�˵�
};