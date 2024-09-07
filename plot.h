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
    int acceleratedDelayMs = -2;
    int day; // ��ǰ����
    Character* character; // ���ڷ��� Character ���ʵ��
    thread keyboardThread; // ���ڴ������������߳�
    map<int, function<void()>> actionMap; // �洢��ͬѡ���Ӧ�Ĵ�����
    map<int, function<void()>> sceneMap; // �洢��ͬ������Ӧ�Ĵ�����

    // �������������̺߳���
    void KeyboardThread();

    // ��ӡ���ܱ�����Ϣ
    void PrintIntroduce(const string& backgroundSentence);



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
    //void runDevelopmentSystem();

    void PrintScene11();
        // ����������е�ѵ������
    int handleTraining();

    // �������̵��еĹ������
    void handleShop();

    // ��������ͷ���˻�����
    void handleDock();

    // ������Ӫ������Ϣ����
    int handleBarracks();

    // ��ӡ���ӳٵ��ı�
    void PrintWithDelay(const string& text, int delayMs);

    // ��ӡ��ʾ��Ϣ
    void PrintPrompt();

    // ��ӡ��Ļ
    void PrintPrologue();

    // ���ݳ�����Ŵ�ӡ��Ӧ����������
    void PrintScene(int scene); // ���²�������Ϊ int

    //Ĭ�Ϲ��캯��
    Plot() = default;

    //��ӡ����
    int Printchange(int&);//����0��������һĻ������1������˵�������ʱ��
};

#endif // PLOT_H


