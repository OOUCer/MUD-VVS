#pragma once
#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <thread>
#include <map>
#include <functional>
#include "character.h" // ���� Character �������

using namespace std;

class Plot {
private:
    bool isCtrlPressed = false;
    int defaultDelayMs = 30;
    int acceleratedDelayMs = 10;
    int day; // ��ǰ����
    Character* character; // ���ڷ��� Character ���ʵ��
    thread keyboardThread; // ���ڴ������������߳�
    map<int, function<void()>> actionMap; // �洢��ͬѡ���Ӧ�Ĵ�����
    map<int, function<void()>> sceneMap; // �洢��ͬ������Ӧ�Ĵ�����

    // �������������̺߳���
    void KeyboardThread();

    // ��ӡ���ܱ�����Ϣ
    void PrintIntroduce(const string& backgroundSentence);

    // ����������е�ѵ������
    void handleTraining();

    // �������̵��еĹ������
    void handleShop();

    // ��������ͷ���˻�����
    void handleDock();

    // ������Ӫ������Ϣ����
    void handleBarracks();

    // ��ӡ����1������
    void PrintScene1();

    // ��ӡ����2������
    void PrintScene2();

    // ��ӡ����3������
    void PrintScene3();

    // ��ӡ����4������
    void PrintScene4();

    // ��ӡ����5������
    void PrintScene5();

    // ��ӡ����6������
    void PrintScene6();

    // ��ӡ����7������
    void PrintScene7();

    // ��ӡ����8������
    void PrintScene8();

    // ��ӡ����9������
    void PrintScene9();

    // ��ӡ����10������
    void PrintScene10();



public:
    // ���캯��������һ�� Character ָ��
    Plot(Character* charPtr);

    // ��������
    ~Plot();

    // ��������ϵͳ
    void runDevelopmentSystem();

    // ��ӡ���ӳٵ��ı�
    void PrintWithDelay(const string& text, int delayMs);

    // ��ӡ��ʾ��Ϣ
    void PrintPrompt();

    // ��ӡ��Ļ
    void PrintPrologue();

    // ���ݳ�����Ŵ�ӡ��Ӧ����������
    void PrintScene(int scene); // ���²�������Ϊ int

    Plot() = default;
};

#endif // PLOT_H


