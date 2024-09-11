#pragma once
#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <thread>
#include <map>
#include <functional>
#include "character.h" // ���� Character �������

using namespace std;

// ʱ��ṹ�壬��������ʱ�������
struct Time
{
    int plottime = 1; // ����ʱ��
    int day = 1; // ����
};

// �����࣬������Ϸ�еľ���ͳ���
class Plot {
private:
    bool isCtrlPressed = false; // �Ƿ���Ctrl��
    int defaultDelayMs = 30; // Ĭ���ӳ�ʱ�䣨���룩
    int acceleratedDelayMs = -2; // ���ٵ��ӳ�ʱ��
    int day; // ��ǰ����
    Character* character; // ָ�� Character ���ָ��
    thread keyboardThread; // �������������߳�
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
    // ���캯��������һ�� Character ָ�룬���ڳ�ʼ�������еĽ�ɫ
    Plot(Character* charPtr);

    // �������������ٶ���ʱ���ã�����������Դ
    ~Plot();

    // ��ӡ����11������
    void PrintScene11();

    // ����������е�ѵ������
    int handleTraining();

    // �������̵��еĹ������
    void handleShop();

    // ��������ͷ���˻�����
    void handleDock();

    // ������Ӫ������Ϣ����
    int handleBarracks();

    // ��ʱ�䱣�浽�ļ�
    void saveTimeToFile(const string& filename, const Time& time);

    // ���ļ�����ʱ��
    Time loadTimeFromFile(const string& filename);

    // ��ӡ���ӳٵ��ı���delayMsΪ�ӳٵĺ�����
    void PrintWithDelay(const string& text, int delayMs);

    // ��ӡ��ʾ��Ϣ
    void PrintPrompt();

    // ��ӡ��Ļ
    void PrintPrologue();

    // ���ݳ�����Ŵ�ӡ��Ӧ����������
    void PrintScene(int scene);

    // Ĭ�Ϲ��캯��
    Plot() = default;

    // ��ӡ����������ʱ�����������0��ʾ������һĻ������1��ʾ����˵�
    int Printchange(int& timeFlag);
};

#endif // PLOT_H
