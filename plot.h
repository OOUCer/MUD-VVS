#pragma once
#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <thread>
#include <map>
#include <functional>
#include "character.h" // 包含 Character 类的声明

using namespace std;

// 时间结构体，包含剧情时间和天数
struct Time
{
    int plottime = 1; // 剧情时间
    int day = 1; // 天数
};

// 剧情类，处理游戏中的剧情和场景
class Plot {
private:
    bool isCtrlPressed = false; // 是否按下Ctrl键
    int defaultDelayMs = 30; // 默认延迟时间（毫秒）
    int acceleratedDelayMs = -2; // 加速的延迟时间
    int day; // 当前天数
    Character* character; // 指向 Character 类的指针
    thread keyboardThread; // 处理键盘输入的线程
    map<int, function<void()>> actionMap; // 存储不同选项对应的处理函数
    map<int, function<void()>> sceneMap; // 存储不同场景对应的处理函数

    // 处理键盘输入的线程函数
    void KeyboardThread();

    // 打印介绍背景信息
    void PrintIntroduce(const string& backgroundSentence);

    // 打印场景1的描述
    void PrintScene1();

    // 打印场景2的描述
    void PrintScene2();

    // 打印场景3的描述
    void PrintScene3();

    // 打印场景4的描述
    void PrintScene4();

    // 打印场景5的描述
    void PrintScene5();

    // 打印场景6的描述
    void PrintScene6();

    // 打印场景7的描述
    void PrintScene7();

    // 打印场景8的描述
    void PrintScene8();

    // 打印场景9的描述
    void PrintScene9();

    // 打印场景10的描述
    void PrintScene10();

public:
    // 构造函数，接受一个 Character 指针，用于初始化剧情中的角色
    Plot(Character* charPtr);

    // 析构函数，销毁对象时调用，负责清理资源
    ~Plot();

    // 打印场景11的描述
    void PrintScene11();

    // 处理在武馆中的训练操作
    int handleTraining();

    // 处理在商店中的购买操作
    void handleShop();

    // 处理在码头的运货操作
    void handleDock();

    // 处理在营房的休息操作
    int handleBarracks();

    // 将时间保存到文件
    void saveTimeToFile(const string& filename, const Time& time);

    // 从文件加载时间
    Time loadTimeFromFile(const string& filename);

    // 打印带延迟的文本，delayMs为延迟的毫秒数
    void PrintWithDelay(const string& text, int delayMs);

    // 打印提示信息
    void PrintPrompt();

    // 打印序幕
    void PrintPrologue();

    // 根据场景编号打印对应场景的描述
    void PrintScene(int scene);

    // 默认构造函数
    Plot() = default;

    // 打印过场，传入时间参数，返回0表示进入下一幕，返回1表示进入菜单
    int Printchange(int& timeFlag);
};

#endif // PLOT_H
