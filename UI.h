#pragma once
#include<Windows.h>
#include<iostream>
#include<vector>
class UI
{
private:
	bool SetSize(int width, int height);
	void ClearConsoleLines(HANDLE hConsole, SHORT s, SHORT e);
public:
	void show();
};