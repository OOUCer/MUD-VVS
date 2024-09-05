// MUD设计.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include"battle.h"
#include"map11.h"
#include"plot.h"
#include"UI.h"
#include"shop.h"
struct Time
{
    int plottime = 1;
};
int main()
{
    //UI ui;
    //Map map;
    //Linchong linchong("林冲", 100, 100, 100, 100, 100, 100, 1000, 100, 1, 1);
    //Linchong* lc = &linchong;
    //Plot plot(lc);
    //Time t;
    //ui.ready();
    //ui.showstart();//开始界面
    //plot.PrintPrompt();//按ctrl加速
    //plot.PrintPrologue();//前情提要
    //plot.PrintScene(t.plottime);//第一幕
    //++t.plottime;
    //plot.PrintScene(t.plottime);//第二幕
    //++t.plottime;
    //plot.PrintScene(t.plottime);//第三幕
    shopset();

}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
