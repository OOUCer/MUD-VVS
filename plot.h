#pragma once
#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <thread>
#include <map>
#include <functional>
#include "character.h" // 包含 Character 类的声明

using namespace std;

class Plot {
private:
    bool isCtrlPressed = false;
    int defaultDelayMs = 30;
    int acceleratedDelayMs = -2;
    int day; // 当前天数
    Character* character; // 用于访问 Character 类的实例
    thread keyboardThread; // 用于处理键盘输入的线程
    map<int, function<void()>> actionMap; // 存储不同选项对应的处理函数
    map<int, function<void()>> sceneMap; // 存储不同场景对应的处理函数

    // 处理键盘输入的线程函数
    void KeyboardThread();

    // 打印介绍背景信息
    void PrintIntroduce(const string& backgroundSentence);

    // 处理在武馆中的训练操作
    void handleTraining();

    // 处理在商店中的购买操作
    void handleShop();

    // 处理在码头的运货操作
    void handleDock();

    // 处理在营房的休息操作
    void handleBarracks();

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
    // 构造函数，接受一个 Character 指针
    Plot(Character* charPtr);

    // 析构函数
    ~Plot();

    // 运行养成系统
    void runDevelopmentSystem();

    // 打印带延迟的文本
    void PrintWithDelay(const string& text, int delayMs);

    // 打印提示信息
    void PrintPrompt();

    // 打印序幕
    void PrintPrologue();

    // 根据场景编号打印对应场景的描述
    void PrintScene(int scene); // 更新参数类型为 int

    Plot() = default;
};

#endif // PLOT_H


