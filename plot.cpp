#include "character.h" 
#include "plot.h"
#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <map>
#include <functional>
#include "map11.h"

using namespace std;

/* ���ÿ���̨��ɫ */
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}// ��ɫ����Ͷ�Ӧ��ɫ��0  ��ɫ��1 ����ɫ��2 ����ɫ��3 ����ɫ��4 ���ɫ��5 ��Ʒ��ɫ��6 ���ɫ��7 ǳ��ɫ��8 ����ɫ��9 ��ɫ��10 ��ɫ��11 ��ɫ��12 ��ɫ��13 Ʒ��ɫ��14 ��ɫ��15 ��ɫ

/* ����ָ�����ӳ����ִ�ӡ�ı� */
void Plot::PrintWithDelay(const std::string& text, int delayMs) {
    for (char ch : text) {
        cout << ch;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delayMs));
        if (isCtrlPressed) {
            delayMs = acceleratedDelayMs;  // Ctrl������ʱ����
        }
        else {
            delayMs = defaultDelayMs;      // ����ʹ��Ĭ���ӳ�
        }
    }
}

/* �̼߳������̣����Ctrl���Ƿ��� */
void Plot::KeyboardThread() {
    while (true) {
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
            isCtrlPressed = true;
        }
        else {
            isCtrlPressed = false;
        }
        this_thread::sleep_for(chrono::milliseconds(100));  // ÿ100������һ��
    }
}

/* ��ӡ�������ܣ�����Ϊ��ɫ */
void Plot::PrintIntroduce(const std::string& backgroundSentence) {
    SetConsoleColor(7);
    PrintWithDelay(backgroundSentence, defaultDelayMs);
}

/* ���캯������ʼ����ڲ��������̼����߳� */
Plot::Plot(Character* charPtr) : character(charPtr), day(1) {
    // �����̼߳���Ctrl��״̬
    keyboardThread = std::thread(&Plot::KeyboardThread, this);

    // ��ʼ��actionMap
    actionMap[1] = [this]() { handleTraining(); };
    actionMap[2] = [this]() { handleShop(); };
    actionMap[3] = [this]() { handleDock(); };
    actionMap[4] = [this]() { handleBarracks(); };

    // ��ʼ��sceneMap��ӳ�䳡��ID������ĳ�����ӡ����
    sceneMap[1] = [this]() { PrintScene1(); };
    sceneMap[2] = [this]() { PrintScene2(); };
    sceneMap[3] = [this]() { PrintScene3(); };
    sceneMap[4] = [this]() { PrintScene4(); };
    sceneMap[5] = [this]() { PrintScene5(); };
    sceneMap[6] = [this]() { PrintScene6(); };
    sceneMap[7] = [this]() { PrintScene7(); };
    sceneMap[8] = [this]() { PrintScene8(); };
    sceneMap[9] = [this]() { PrintScene9(); };
    sceneMap[10] = [this]() { PrintScene10(); };
}

/* ����������ȷ�������̰߳�ȫ�˳� */
Plot::~Plot() {
    // ȷ���߳̽���ǰ���������߳�
    if (keyboardThread.joinable()) {
        keyboardThread.detach();
    }
}

/* ��ӡ��ʾ��Ϣ����ʾ������ʾ����ʾ */
void Plot::PrintPrompt() {
    SetConsoleColor(1);
    PrintWithDelay("����Ctrl��ʱ������ʾ\n", 30);
    SetConsoleColor(6);
}

/* ��ӡ��Ϸ��Ļ������Ϊ����ɫ */
void Plot::PrintPrologue() {
    SetConsoleColor(8);
    PrintWithDelay("ǰ����Ҫ��������,������˸�̫ξ����½�ݺ�͸�̫ξ�����ݺ�����������γǡ������ڲ����˵Ĺ�ϵ��������ڳ��л��\n", 30);
    SetConsoleColor(6);
}

int placeflag; // placeflag��ʾ������־��1 ��Ƶ꣬2 ��ݣ�3 Ӫ����4 ���ϳ���5 �о���6 ��ͷ��7 ����

/* ��ӡָ������ */
void Plot::PrintScene(int scene) {
    auto it = sceneMap.find(scene);
    if (it != sceneMap.end()) {
        it->second();  // ���ö�Ӧ�����Ĵ�����
    }
    else {
        SetConsoleColor(12);
        PrintWithDelay("��Ч�ĳ�����š�\n", 30);
    }
}

/* ��ӡѡ��˵�������ѡ���� */
int Plot::Printchange(int& t) // ����0��������һĻ������1������˵�
{
    Sleep(500);  // �ӳ�500ms
    string input;
    int flag = 0;

    std::cout << "1.��һĻ             2.����" << endl;
    cin >> input;

    if (input == "1") {
        ++t;
        flag = 0;  // ѡ����һĻ
    }
    else if (input == "2") {
        flag = 1;  // ѡ�����ѡ��
    }

    return flag;
}

/* ��ӡ��һĻ�ĳ��� */
void Plot::PrintScene1() {
    placeflag = 4;  // ���ó���Ϊ���ϳ�
    SetConsoleColor(8);
    PrintWithDelay("��һĻ��\nʮһ�³��壬�糿��ѩ���׷ɣ��ƹ�ǰ�ĺ����ɢ������ů�Ĺ�â\n", 30);

    placeflag = 1;  // ���ó���Ϊ��Ƶ�
    SetConsoleColor(7);
    PrintWithDelay("��С����", 30);

    SetConsoleColor(12);
    PrintWithDelay("��Ӫǰ���˸���Ƶꡣ����Ǯ�������������ˡ����˲�֪Ϊ�����������\n", 30);

    SetConsoleColor(7);
    PrintWithDelay("��ָ�����ϵ���", 30);

    SetConsoleColor(12);
    PrintWithDelay("��������˸�̫ξ�������ݺ�������һ����˾�����䵽���������յ�����������\n", 30);

    SetConsoleColor(7);
    PrintWithDelay("��С�����㵽�����������������ӳ������˶��ˡ�\n���ڶ���ϲ����", 30);

    SetConsoleColor(12);
    PrintWithDelay("�����޶�����û���׾죬���յö��˵��������Ǵ��콵�¡���Щ�̲����������£��ı����⡱\n", 30);

    SetConsoleColor(10);
    PrintWithDelay("�̲�+100��\n", 30);

    // ���ӽ�ɫ�Ľ������
    if (character) {
        int gold = character->getGold();
        character->setGold(gold + 100);
    }

    /*SetConsoleColor(6);
    PrintWithDelay("����ϲ�������Ƶ꣺�ṩʳ�޺���Ϣ��������ʱ����Ʒ���䡿\n", 30);*/
    SetConsoleColor(15);
}


void Plot::PrintScene2() {
    // ���ÿ���̨��ɫΪ��ɫ
    SetConsoleColor(8);
    // ��ӡ�ڶ�Ļ�ĳ������������ӳ���ʾ
    PrintWithDelay("�ڶ�Ļ��\nʮһ�³��������磬����̹ǣ��ֵ��ϵ�ѩ���ȵ�����\n", 30);
    placeflag = 1;  // ���ó������Ϊ1
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    PrintWithDelay("�������Ƶꡣ\n", 30);
    // ��ӡ��С���ĶԻ�
    SetConsoleColor(7);
    PrintWithDelay("��С����æ����", 30);
    SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
    PrintWithDelay("��ȴ���и����������ˣ������������Ӫ������˰��վơ�����ֻ���Ӧ�������������������ϣ��ô�Ҫ�������������������һ�������������Ӫ�����\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    PrintWithDelay("�����ˣ��󾪵���", 30);
    SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
    PrintWithDelay("������ʮ�������½�ݺ����ü���Ҳ�������ﺦ�ң���Ҫײ���ң�ֻ��������Ϊ�࣡��\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    PrintWithDelay("��С������", 30);
    SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
    PrintWithDelay("��ֻҪ��������ˡ����ˣ���������ĵ�ͼ���������¡���\n", 30);
    // ���ÿ���̨��ɫΪ��ɫ
    SetConsoleColor(6);
    Map map2;
    cout << endl;
    cout << endl;
    cout << endl;
    Sleep(1000); // ��ͣ1��
    cout << endl;
    cout << "���롰ENTER���򿪵�ͼ" << endl;
    getchar(); // �ȴ��û�����
    cin.get();
    map2.showmap(1); // ��ʾ��ͼ
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    PrintWithDelay("��С������", 30);
    SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
    PrintWithDelay("�����ͼ�ϱ��ɫ�ģ����Ƕ���Ŀǰ���ڵĵط�����\n��������С�˵Ĳ�ƹ���������Ϣ�ظ���������㶫����ȥ��ݿ�������������ѧϰ���ܡ�ȥ��ͷ����׬Ǯ����\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
}

void Plot::PrintScene3() {
    // ���ÿ���̨��ɫΪ��ɫ
    SetConsoleColor(8);
    // ��ӡ����Ļ�ĳ������������ӳ���ʾ
    PrintWithDelay("����Ļ:\n��������С����̸ʱ��һλ�׷�ͯ�յ��������˽�����������һ���������ơ�\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    PrintWithDelay("�Ƿ񻨷�20�̲���һ������\n", 30);
    cout << "1.��          2.��" << endl;
    int flag;
    cin >> flag; // ��ȡ�û�����
    if (flag == 1) {
        // ����û�ѡ���ǡ�������ʾ�������
        PrintWithDelay("�����������ֹǣ��ֿ��˿����񣬴󾪵���\n", 30);
        SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
        PrintWithDelay("��λС�ֵܣ�������,Ҳ����ʮһ��ʮ�ģ�����Ѫ��֮�֣���ʱ�򶫶��У����ֱؽ⡣��\n", 30);
        SetConsoleColor(10); // ���ÿ���̨��ɫΪ��ɫ
        cout << "�̲� - 20" << endl;
        // �ָ�����̨��ɫΪ��ɫ
        SetConsoleColor(7);
        if (character) {
            int gold = character->getGold(); // ��ȡ��ǰ�������
            character->setGold(gold - 20); // ����20���
        }
    }
    else {
        // ����û�ѡ�񡰷񡱣�����Ȼ��ʾ�������
        SetConsoleColor(7);
        PrintWithDelay("��û�����λ���ߣ�����ȴһ�ѽ����������������ֹǣ��ֿ��˿����񣬴󾪵���\n", 30);
        SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
        PrintWithDelay("��λС�ֵܣ�������,Ҳ����ʮһ��ʮ�ģ�����Ѫ��֮�֣���ʱ�򶫶��У����ֱؽ⡣��\n", 30);
        // �ָ�����̨��ɫΪ��ɫ
        SetConsoleColor(7);
        // ���ô��룺Ϊ�������ܵ���չ׼��
        // PrintWithDelay("��û�����λ���ߣ�����ȴһ�ѽ����������������ֹǣ��ֿ��˿����񣬴󾪵�������λС�ֵܣ�������Ҳ����ʮһ��ʮ�ģ�����Ѫ��֮�֣���ʱ�򶫶��У����ֱؽ⡣��\n", 30);
    }
    // ��ӡ�뿪��Ƶ������
    PrintWithDelay("���л���ߣ�ȴ�������ᡣֻ��������С���ֽ�̸����󣬱��뿪�˲�Ƶ�\n", 30);
    // ���ô��룺Ϊ�������ܵ���չ׼��
    /*placeflag = 5;
    PrintWithDelay("�̵꣺", 30);
    SetConsoleColor(12);
    PrintWithDelay("������~~�͹�Ҫ��Щʲô����\n", 30);
    PrintWithDelay("����ϲ������о����о����и����̵꣬���Թ��������Ʒ��������װ������\n", 30);*/
    // ѡ�񲿷�
    // ��ʼ���������ϵͳ
    //runDevelopmentSystem();
}

void Plot::PrintScene4() {
    // ���ÿ���̨��ɫΪ��ɫ
    SetConsoleColor(8);
    // ��ӡ����Ļ�ĳ������������ӳ���ʾ
    PrintWithDelay("����Ļ��\nʮһ��ʮ�����磬��Ӫ������������������ڿռ����ɢ������������Ϣ����Ӫ���ڿ���ľ����\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    PrintWithDelay("��Ӫ̧��ͷ����Ŀ�����ࣺ", 30);
    SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
    PrintWithDelay("���˼䶫����ʮ�����������ݳ�����Щ����Ǯȡ�١������̧����ȥ�����Ͼ����������á���\n", 30);
    // ���ô��룺Ϊ�������ܵ���չ׼��
    /*SetConsoleColor(6);
    PrintWithDelay("����ϲ��������ϳ��������Ų��ϣ���������������Ʒ����\n", 30);*/
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
}

void Plot::PrintScene5() {
    placeflag = 4; // ���ó������Ϊ4
    // ���ÿ���̨��ɫΪ��ɫ
    SetConsoleColor(8);
    // ��ӡ����Ļ�ĳ������������ӳ���ʾ
    PrintWithDelay("����Ļ��\n��Ͳһͬ���������⡣�ƿ���ʱ��ľͷ������΢��֨ѽ�������ڲ����˲ݡ�\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    PrintWithDelay("��ߵ��Ͼ���ǰ����������Ͼ��Ը��㿴�ܲݶѺ���ʰ�������˵����\n", 30);
    SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
    PrintWithDelay("�����衢���ӡ��롢�����������㡣��\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    PrintWithDelay("�Ͼ�ָ���Ϲҵ�һ�����«˵����", 30);
    SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
    PrintWithDelay("��������Ƴ�ʱ��ֻ���ݳ���Ͷ����·ȥ����������о�����\n", 30);
    placeflag = 5; // ���ó������Ϊ5
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    // ���ô��룺Ϊ�������ܵ���չ׼��
    //PrintWithDelay("����+1����«+1��\n", 30);
    //SetConsoleColor(6);
}

void Plot::PrintScene6() {
    // ���ÿ���̨��ɫΪ��ɫ
    SetConsoleColor(8);
    placeflag = 4; // ���ó������Ϊ4
    // ��ӡ����Ļ�ĳ������������ӳ���ʾ
    PrintWithDelay("����Ļ��\n���������Щ�����������¯��Ļ��潥���������濴�ǲ���ʱ�����±�˷�紵����ҡ��ö���\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    PrintWithDelay("�㣺", 30);
    SetConsoleColor(12); // ���ÿ���̨��ɫΪ��ɫ
    PrintWithDelay("��Ҫ�����о�����ƣ���\n", 30);
    // ���ô��룺Ϊ�������ܵ���չ׼��
    //placeflag = 5;
    //SetConsoleColor(7);
}

void Plot::PrintScene7() {
    // ���ÿ���̨��ɫΪ��ɫ
    SetConsoleColor(8);
    placeflag = 7; // ���ó������Ϊ7
    // ��ӡ����Ļ�ĳ������������ӳ���ʾ
    PrintWithDelay("����Ļ��\n�в��ϰ����·������һ������\n�������У����ּ��������������棬��Χ�����ӳ�ճ��������յ���ס�\n������һ����׼������ս����\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
    // ���ô��룺Ϊ�������ܵ���չ׼��
    //PrintWithDelay("����ϲ������������ѳ�������Ҳ��������Σ�մӶ�����ս������\n", 30);
    //SetConsoleColor(7); // ��ɫ
    //placeflag = 5;
    //PrintWithDelay("��ң�", 30);
    //SetConsoleColor(12); // ��ɫ
    //PrintWithDelay("���������䣬����������Ȩ���ӷ硣��", 30);
    //SetConsoleColor(10); // ��ɫ
    //PrintWithDelay("�����һ����ţ�⣬��һ���Ⱦƣ�����ԡ�\n", 30);
    //SetConsoleColor(10); // ��ɫ
    //PrintWithDelay("״̬����\n", 30);
    //SetConsoleColor(6);
}


void Plot::PrintScene11() {
    SetConsoleColor(7); // ��ɫ
    placeflag = 5; // ���ó������Ϊ5
    // ��ӡ��ҵĶԻ�
    PrintWithDelay("��ң�", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("���������䣬����������Ȩ���ӷ硣��", 30);
    SetConsoleColor(10); // ��ɫ
    // ��ӡ�ṩ��ʳ�����Ʒ
    PrintWithDelay("�����һ����ţ�⣬��һ���Ⱦƣ�����ԡ�\n", 30);
    SetConsoleColor(10); // ��ɫ
    // ��ӡ״̬�ָ���ʾ
    PrintWithDelay("״̬����\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
}

void Plot::PrintScene8() {
    placeflag = 4; // ���ó������Ϊ4
    SetConsoleColor(8); // ��ɫ
    // ��ӡ�ڰ�Ļ�ĳ�������
    PrintWithDelay("�ڰ�Ļ��\n��ص��ݳ���ֻ����������Ѿ������صĻ�ѩѹ����ѩ���ڿ��з׷ɣ�������һ�С�\n", 30);
    SetConsoleColor(7); // ��ɫ
    // ��ӡ��ɫ�ĶԻ�
    PrintWithDelay("�㣺", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("��ȥ����Ը�һ����\n", 30);
    placeflag = 7; // ���ó������Ϊ7
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
}

void Plot::PrintScene9() {
    SetConsoleColor(8); // ��ɫ
    // ��ӡ�ھ�Ļ�ĳ�������
    PrintWithDelay("�ھ�Ļ��\n������Ϣʱ����Ȼ���������ϳ������\n����ʰ���׼������������档���ڴ�ʱ��������ǰ���������ٵĽŲ����͵����Ի���\n������������ʱ��һ���ǲ��һ����½�ݺ�һ���Ǹ�����\n", 30);
    SetConsoleColor(7); // ��ɫ
    // ��ӡ��ɫ�ĶԻ�
    PrintWithDelay("������һ�󾪻ţ���������", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("����������㣡�����ǵ��˲�������׼���������������ˣ���\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("�����ʯͷ�޿���ͦ�Ż�ǹ, ���һ����", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("����������ȥ����\n", 30);
    SetConsoleColor(10); // ��ɫ
    // ��ӡ����ս������ʾ
    PrintWithDelay("����ս����\n", 30);
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
}

void Plot::PrintScene10() {
    system("cls"); // ����
    SetConsoleColor(7); // ��ɫ
    // ��ӡʫ��ĸ�ʽ
    for (int i = 0; i < 29; i++)
        cout << " ";
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("�������������裬�������𽵷׷ס�", 500);
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("������Ұ�ѷ�·�����ǧɽ�����ۡ�", 500);
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("�����磬��Ǭ�����������������ء�", 500);
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("�����µ��������ݷ���ƽ����š�", 500);
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
}

int Plot::handleTraining() {
    if (character) {
        int gold = character->getGold(); // ��ȡ�������
        int attack = character->getAttack(); // ��ȡ������
        int currentHP = character->getHP(); // ��ȡ��ǰ����
        int maxHP = character->getMaxHP(); // ��ȡ�������

        // ѵ��ǰ�ļ�飨Ŀǰ��ע�͵���
        // if (currentHP < 20) { // ����ѵ����Ҫ����20������
        //     SetConsoleColor(12);
        //     PrintWithDelay("����������㣬�޷�����ѵ����\n", 30);
        //     SetConsoleColor(7);
        //     return;
        // }

        // ����ѵ����ص��߼���Ŀǰ��ע�͵���
        // character->modifyHP(-20);  // ѵ������20������
        // character->setGold(gold - 10);  // ѵ������10���

        SetConsoleColor(8); // ��ɫ
        PrintWithDelay("�������ϰ����������˷���\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("������", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("����ӭ������ݣ�����������ͨ��ѵ����������������ü��ܣ�����ս����������\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�Ƿ񻨷�10�̲�����ѵ��\n", 30);
        SetConsoleColor(10); // ��ɫ
        cout << "1.��           2.��" << endl;
        SetConsoleColor(7); // ��ɫ
        int flag;
        cin >> flag; // ��ȡ�û�ѡ��
        while (flag != 1 && flag != 2) {
            cout << "�����������������" << endl;
            SetConsoleColor(10); // ��ɫ
            cout << "1.��              2.��" << endl;
            SetConsoleColor(7); // ��ɫ
            cin >> flag; // ���»�ȡ�û�ѡ��
        }
        if (flag == 1) {
            if (gold < 10) {
                PrintWithDelay("�̲����㣬��ȥ��ͷ׬Ǯ������\n", 30);
                return 0; // ����0��ʾδ�ܽ���ѵ��
            }
            else {
                PrintWithDelay("���ڹ��ڽ�����ǿ��ѵ�����о��Լ��������õ�������������\n", 30);
                return 1; // ����1��ʾѵ���ɹ�
            }
        }
        else if (flag == 2) {
            PrintWithDelay("���뿪����ݡ�\n", 30);
            return 0; // ����0��ʾδ����ѵ��
        }
    }
    // �ָ�����̨��ɫΪ��ɫ
    SetConsoleColor(7);
}


void Plot::handleShop() {
    int gold = character->getGold(); // ��ȡ��ǰ���

    SetConsoleColor(8); // ��ɫ
    // ��ӡ�̵��ڵ�����
    PrintWithDelay("�̵��ڵƻ�ͨ���������ϰ����˸��������Ͳ���Ʒ��\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("������", 30);
    SetConsoleColor(12); // ��ɫ
    // ��ӡ�����ĶԻ�
    PrintWithDelay("����ӭ���٣��͹٣�����ҪЩʲô����\n", 30);
    SetConsoleColor(7); // �ָ�Ϊ��ɫ
}

void Plot::handleDock() {
    int gold = character->getGold(); // ��ȡ��ǰ���

    SetConsoleColor(8); // ��ɫ
    // ��ӡ��ͷ������
    PrintWithDelay("����ͷ���㿴��������ѻ���һ�𣬹�����æµ�ذ����š�\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("��ͷ���ˣ�", 30);
    SetConsoleColor(12); // ��ɫ
    // ��ӡ��ͷ���˵ĶԻ�
    PrintWithDelay("���͹٣���û����Ȥ��æ�˻�����æ�Ļ�����׬ЩǮ����\n", 30);
    SetConsoleColor(10); // ��ɫ
    // ��ӡѡ��
    cout << "1.��              2.��" << endl;
    SetConsoleColor(7); // �ָ�Ϊ��ɫ
    int f = 0;
    cin >> f; // ��ȡ�û�����
    while (f != 1 && f != 2) {
        // ���������ʾ
        cout << "�����������������" << endl;
        SetConsoleColor(10); // ��ɫ
        cout << "1.��              2.��" << endl;
        SetConsoleColor(7); // �ָ�Ϊ��ɫ
        cin >> f; // ���»�ȡ�û�����
    }
    if (f == 1) {
        // �û�ͬ�����
        PrintWithDelay("��ͬ���ˣ��������˻������С�\n", 30);
        SetConsoleColor(10); // ��ɫ
        PrintWithDelay("Ǯ��+50\n", 30);
        character->setGold(gold + 50); // ���ӽ��
        SetConsoleColor(7); // �ָ�Ϊ��ɫ
    }
    else if (f == 2) {
        // �û�ѡ���뿪
        PrintWithDelay("���뿪����ͷ��\n", 30);
        return;
    }
}

int Plot::handleBarracks() {
    if (character) {
        bool running = true;
        while (running) {
            int currentHP = character->getHP(); // ��ȡ��ǰHP
            int maxHP = character->getMaxHP(); // ��ȡ���HP
            int gold = character->getGold(); // ��ȡ��ǰ���

            SetConsoleColor(8); // ��ɫ
            // ��ӡӪ��������
            PrintWithDelay("��ص�Ӫ�����е���һЩƣ������Ҳ�ջ��˲��١�\n", 30);
            SetConsoleColor(7); // ��ɫ
            PrintWithDelay("��ѡ������Ҫ�Ĳ�����\n", 30);
            SetConsoleColor(10); // ��ɫ
            // ��ӡ����ѡ��
            PrintWithDelay("1. �鿴�˵�", 30);
            cout << "        ";
            PrintWithDelay("2. �뿪\n", 30);
            SetConsoleColor(7); // �ָ�Ϊ��ɫ

            int choice;
            cin >> choice; // ��ȡ�û�ѡ��
            return choice; // �����û�ѡ��Ĳ���
        }
    }
    return 0; // ����0��ʾû��ѡ���κβ���
}

void Plot::saveTimeToFile(const string& filename, const Time& time) {
    ofstream outFile(filename); // ���ļ�����д����
    if (outFile.is_open()) {
        // ��ʱ������д���ļ�
        outFile << time.plottime << "\n";
        outFile << time.day << "\n";
    }
    outFile.close(); // �ر��ļ�
    cout << "�����Ѵ���" << endl; // ��ӡ����ɹ���ʾ
}

Time Plot::loadTimeFromFile(const string& filename) {
    ifstream inFile(filename); // ���ļ����ж�����
    Time time;
    if (inFile.is_open()) {
        // ���ļ��ж�ȡʱ������
        inFile >> time.plottime;
        inFile >> time.day;
    }
    inFile.close(); // �ر��ļ�
    return time; // ���ض�ȡ��ʱ������
}
