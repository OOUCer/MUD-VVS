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
	int ready();//准备界面
	int showstart();//开始界面,主菜单
	int showmenu();//展示菜单
	int shuxing(Linchong* lc);//展示属性
};