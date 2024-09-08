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


void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}// ��ɫ����Ͷ�Ӧ��ɫ��0  ��ɫ��1����ɫ��2 ����ɫ3������ɫ��4  ���ɫ�� 5 ��Ʒ��ɫ�� 6  ���ɫ ��7ǳ��ɫ��8 ����ɫ��9 ��ɫ�� 10��ɫ�� 11 ��ɫ��12 ��ɫ ��13 Ʒ��ɫ�� 14 ��ɫ��15  ��ɫ

void Plot::PrintWithDelay(const std::string& text, int delayMs) {
    for (char ch : text) {
        cout << ch;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delayMs));
        if (isCtrlPressed) {
            delayMs = acceleratedDelayMs;
        }
        else {
            delayMs = defaultDelayMs;
        }
    }
}

void Plot::KeyboardThread() {
    while (true) {
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
            isCtrlPressed = true;
        }
        else {
            isCtrlPressed = false;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Plot::PrintIntroduce(const std::string& backgroundSentence) {
    SetConsoleColor(7);
    PrintWithDelay(backgroundSentence, defaultDelayMs);
}

Plot::Plot(Character* charPtr) : character(charPtr), day(1) {
    // �����̼߳���Ctrl��״̬
    keyboardThread = std::thread(&Plot::KeyboardThread, this);

    // ��ʼ�� actionMap
    actionMap[1] = [this]() { handleTraining(); };
    actionMap[2] = [this]() { handleShop(); };
    actionMap[3] = [this]() { handleDock(); };
    actionMap[4] = [this]() { handleBarracks(); };
    // ��ʼ�� sceneMap
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

Plot::~Plot() {
    // ȷ���߳̽���ǰ���������߳�
    if (keyboardThread.joinable()) {
        keyboardThread.detach();
    }
}

void Plot::PrintPrompt() {
    SetConsoleColor(1);
    PrintWithDelay("����Ctrl��ʱ������ʾ\n", 30);
    SetConsoleColor(6);
}

void Plot::PrintPrologue() {
    SetConsoleColor(8);
    PrintWithDelay("ǰ����Ҫ��������,������˸�̫ξ����½�ݺ�͸�̫ξ�����ݺ�����������γǡ������ڲ����˵Ĺ�ϵ��������ڳ��л��\n", 30);
    SetConsoleColor(6);
}
int placeflag; //placeflag= 1 ��Ƶ� 2 ��� 3 Ӫ�� 4 ���ϳ� 5 �о� 6 ��ͷ 7 ���� 
void Plot::PrintScene(int scene) {
    auto it = sceneMap.find(scene);
    if (it != sceneMap.end()) {
        it->second(); // ���ö�Ӧ�����Ĵ�����
    }
    else {
        SetConsoleColor(12);
        PrintWithDelay("��Ч�ĳ�����š�\n", 30);
    }
}

int Plot::Printchange(int& t)//����0��������һĻ������1������˵�
{
    Sleep(500);
    string input;
    int flag=0;
    std::cout << "1.��һĻ             2.����" << endl;
    cin>> input; 

    if (input=="1") {
        ++t;
        flag = 0;
    }
    else if(input=="2") {
        flag = 1;
    }

    return flag;
}

void Plot::PrintScene1() {
    placeflag = 4;
    SetConsoleColor(8);
    PrintWithDelay("��һĻ��\nʮһ�³��壬�糿��ѩ���׷ɣ��ƹ�ǰ�ĺ����ɢ������ů�Ĺ�â\n", 30);
    placeflag = 1;
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
    PrintWithDelay("�����޶�����û���׾죬���յö��˵��������Ǵ��콵�¡���\n", 30);
    SetConsoleColor(10);
    PrintWithDelay("�̲�+100��\n", 30);
    if (character) {
        int gold = character->getGold();
        character->setGold(gold + 100);
    }
    /*SetConsoleColor(6);
    PrintWithDelay("����ϲ�������Ƶ꣺�ṩʳ�޺���Ϣ��������ʱ����Ʒ���䡿\n", 30);*/
    SetConsoleColor(15);
}


void Plot::PrintScene2() {
    SetConsoleColor(8);
    PrintWithDelay("�ڶ�Ļ��\nʮһ�³��������磬����̹ǣ��ֵ��ϵ�ѩ���ȵ�����\n", 30);
    placeflag = 1;
    SetConsoleColor(7);
    PrintWithDelay("�������Ƶꡣ\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("��С����æ����", 30);
    SetConsoleColor(12);
    PrintWithDelay("��ȴ���и����������ˣ������������Ӫ������˰��վơ�����ֻ���Ӧ�������������������ϣ��ô�Ҫ�������������������һ�������������Ӫ�����\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("�����ˣ��󾪵���", 30);
    SetConsoleColor(12);
    PrintWithDelay("������ʮ�������½�ݺ����ü���Ҳ�������ﺦ�ң���Ҫײ���ң�ֻ��������Ϊ�࣡��\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("��С������", 30);
    SetConsoleColor(12);
    PrintWithDelay("��ֻҪ��������ˡ����ˣ���������ĵ�ͼ���������¡���\n", 30);
    SetConsoleColor(6);
    Map map2;
    cout << endl;
    cout << endl;
    cout << endl;
    Sleep(1000);
    cout << endl;
    cout << "���롰ENTER���򿪵�ͼ"<<endl;
    getchar();
    cin.get();
    map2.showmap(1);
    SetConsoleColor(7);
    PrintWithDelay("��С������", 30);
    SetConsoleColor(12);
    PrintWithDelay("�����ͼ�ϱ��ɫ�ģ����Ƕ���Ŀǰ���ڵĵط�����\n��������С�˵Ĳ�ƹ���������Ϣ�ظ���������㶫����ȥ��ݿ�������������ѧϰ���ܡ�ȥ��ͷ����׬Ǯ����\n", 30);
    SetConsoleColor(7);

}

void Plot::PrintScene3() {
    SetConsoleColor(8);
    PrintWithDelay("����Ļ:\n��������С����̸ʱ��һλ�׷�ͯ�յ��������˽�����������һ���������ơ�\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("�Ƿ񻨷�20�̲���һ������\n", 30);
    cout << "1.��          2.��" << endl;
    int flag;
    cin >> flag;
    if (flag == 1)
    {
        PrintWithDelay("�����������ֹǣ��ֿ��˿����񣬴󾪵���\n", 30);
        SetConsoleColor(12);
        PrintWithDelay("��λС�ֵܣ�������,Ҳ����ʮһ��ʮ�ģ�����Ѫ��֮�֣���ʱ�򶫶��У����ֱؽ⡣��\n", 30);
        SetConsoleColor(10);
        cout << "�̲� - 20" << endl;
        SetConsoleColor(7);
        if (character) {
            int gold = character->getGold();
            character->setGold(gold - 20);
        }
    }
    else
    {
        SetConsoleColor(7);
        PrintWithDelay("��û�����λ���ߣ�����ȴһ�ѽ����������������ֹǣ��ֿ��˿����񣬴󾪵���\n", 30);
        SetConsoleColor(12);
        PrintWithDelay("��λС�ֵܣ�������,Ҳ����ʮһ��ʮ�ģ�����Ѫ��֮�֣���ʱ�򶫶��У����ֱؽ⡣��\n", 30);
        SetConsoleColor(7);
        //PrintWithDelay("��û�����λ���ߣ�����ȴһ�ѽ����������������ֹǣ��ֿ��˿����񣬴󾪵�������λС�ֵܣ�������Ҳ����ʮһ��ʮ�ģ�����Ѫ��֮�֣���ʱ�򶫶��У����ֱؽ⡣��\n", 30);
    }
    PrintWithDelay("���л���ߣ�ȴ�������ᡣֻ��������С���ֽ�̸����󣬱��뿪�˲�Ƶ�\n", 30);
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
    SetConsoleColor(8);
    PrintWithDelay("����Ļ��\nʮһ��ʮ�����磬��Ӫ������������������ڿռ����ɢ������������Ϣ����Ӫ���ڿ���ľ����\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("��Ӫ̧��ͷ����Ŀ�����ࣺ", 30);
    SetConsoleColor(12);
    PrintWithDelay("���˼䶫����ʮ�����������ݳ�����Щ����Ǯȡ�١������̧����ȥ�����Ͼ����������á���\n", 30);
  /*  SetConsoleColor(6);
    PrintWithDelay("����ϲ��������ϳ��������Ų��ϣ���������������Ʒ����\n", 30);*/
    SetConsoleColor(7);
}

void Plot::PrintScene5() {
    placeflag = 4;
    SetConsoleColor(8); // ��ɫ
    PrintWithDelay("����Ļ��\n��Ͳһͬ���������⡣�ƿ���ʱ��ľͷ������΢��֨ѽ�������ڲ����˲ݡ�\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("��ߵ��Ͼ���ǰ����������Ͼ��Ը��㿴�ܲݶѺ���ʰ�������˵����\n", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("�����衢���ӡ��롢�����������㡣��\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("�Ͼ�ָ���Ϲҵ�һ�����«˵����", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("��������Ƴ�ʱ��ֻ���ݳ���Ͷ����·ȥ����������о�����\n", 30);
    placeflag = 5;
    SetConsoleColor(7); // ��ɫ
    //PrintWithDelay("����+1����«+1��\n", 30);
    //SetConsoleColor(6);
}

void Plot::PrintScene6() {
    SetConsoleColor(8); // ��ɫ
    placeflag = 4;
    PrintWithDelay("����Ļ��\n���������Щ�����������¯��Ļ��潥���������濴�ǲ���ʱ�����±�˷�紵����ҡ��ö���\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("�㣺", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("��Ҫ�����о�����ƣ���\n", 30);
    //placeflag = 5;
    SetConsoleColor(7);
}

void Plot::PrintScene7() {
    SetConsoleColor(8); // ��ɫ
    placeflag = 7;
    PrintWithDelay("����Ļ��\n�в��ϰ����·������һ������\n�������У����ּ��������������棬��Χ�����ӳ�ճ��������յ���ס�\n������һ����׼������ս����\n", 30);
    //SetConsoleColor(6);
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

void Plot::PrintScene11()
{
    SetConsoleColor(7); // ��ɫ
    placeflag = 5;
    PrintWithDelay("��ң�", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("���������䣬����������Ȩ���ӷ硣��", 30);
    SetConsoleColor(10); // ��ɫ
    PrintWithDelay("�����һ����ţ�⣬��һ���Ⱦƣ�����ԡ�\n", 30);
    SetConsoleColor(10); // ��ɫ
    PrintWithDelay("״̬����\n", 30);
    SetConsoleColor(7);
}
void Plot::PrintScene8() {
    placeflag = 4;
    SetConsoleColor(8); // ��ɫ
    PrintWithDelay("�ڰ�Ļ��\n��ص��ݳ���ֻ����������Ѿ������صĻ�ѩѹ����ѩ���ڿ��з׷ɣ�������һ�С�\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("�㣺", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("��ȥ����Ը�һ����\n", 30);
    placeflag = 7;
    SetConsoleColor(7);
}

void Plot::PrintScene9() {
    SetConsoleColor(8); // ��ɫ
    PrintWithDelay("�ھ�Ļ��\n������Ϣʱ����Ȼ���������ϳ������\n����ʰ���׼������������档���ڴ�ʱ��������ǰ���������ٵĽŲ����͵����Ի���\n������������ʱ��һ���ǲ��һ����½�ݺ�һ���Ǹ�����\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("������һ�󾪻ţ�����������", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("����������㣡�����ǵ��˲�������׼���������������ˣ���\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("�����ʯͷ�޿���ͦ�Ż�ǹ,���һ������\n", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("����������ȥ����\n", 30);
    SetConsoleColor(10); // ��ɫ
    PrintWithDelay("����ս����\n", 30);
    SetConsoleColor(7);
}

void Plot::PrintScene10() {
    system("cls");
    SetConsoleColor(8); // ��ɫ
    //PrintWithDelay("\n�������������裬�������𽵷׷ס�\n������Ұ�ѷ�·�����ǧɽ�����ۡ�\n�����磬��Ǭ�����������������ء�\n�����µ��������ݷ���ƽ����š�", 30);
    for (int i = 0; i < 29; i++)
        cout << " ";
    cout << "--------------------------------------------" << endl;;
    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("�������������裬�������𽵷׷ס�", 500);
    //cout << "�������Ѳ����ܣ�Ī���������ͼ��";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("������Ұ�ѷ�·�����ǧɽ�����ۡ�", 500);
    //cout << "���Ƿ�ѩ����ƣ��������ջ���ݡ�";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("�����磬��Ǭ�����������������ء�", 500);
    //cout << "��νڤ��ʩ�ƶ���˭֪�����������";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("�����µ��������ݷ���ƽ����š�", 500);
    //cout << "�������������أ����ǹ���ΰ�ɷ�";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
    SetConsoleColor(7);
}




int Plot::handleTraining() {
    if (character) {
        int gold = character->getGold();
        int attack = character->getAttack();
        int currentHP = character->getHP();
        int maxHP = character->getMaxHP();

        //// ��������Ƿ��㹻
        //if (currentHP < 20) {  // ����ѵ����Ҫ����20������
        //    SetConsoleColor(12);
        //    PrintWithDelay("����������㣬�޷�����ѵ����\n", 30);
        //    SetConsoleColor(7);
        //    return;
        //}

        //// ����ѵ����ص��߼�
        //// ��������ֵ
        //character->modifyHP(-20);  // ѵ������ 20 ������
       // character->setGold(gold - 10);  // ѵ������ 10 ��

        SetConsoleColor(8);
        PrintWithDelay("�������ϰ����������˷���\n", 30);
        SetConsoleColor(7);
        PrintWithDelay("������", 30);
        SetConsoleColor(12);
        PrintWithDelay("����ӭ������ݣ�����������ͨ��ѵ�����ǿ��ļ��ܣ��������ս�����������ǵ�ѵ���������ӹ����������������Լ�һЩ���⼼�ܡ���\n", 30);
        PrintWithDelay("����ע�⣬ѵ������������������������������㣬���޷�����ѵ����ѵ�����������ָ������������һ���֡���\n\n", 30);
        SetConsoleColor(7);
        PrintWithDelay("�Ƿ񻨷�10�̲�����ѵ��\n", 30);
        cout << "1.��           2.��" << endl;
        int flag;
        cin >> flag;
        if (flag == 1)
        {
            if (gold < 10)
            {
                PrintWithDelay("�̲����㣬��ȥ��ͷ׬Ǯ������\n", 30);
                return 0;
            }
            else
            {
                PrintWithDelay("���ڹ��ڽ�����ǿ��ѵ�����о��Լ��������õ�������������\n", 30);
                character->setAttack(1);//�޸�5->1��5̫���ˡ�
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    SetConsoleColor(7);
}



void Plot::handleShop() {
    int gold = character->getGold();
    SetConsoleColor(8); // ��ɫ
    PrintWithDelay("�̵��ڵƻ�ͨ���������ϰ����˸��������Ͳ���Ʒ��\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("������", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("����ӭ���٣��͹٣�����ҪЩʲô����\n", 30);
    SetConsoleColor(7); // ��ɫ

}

void Plot::handleDock() {
    int gold = character->getGold();
    SetConsoleColor(8); // ��ɫ
    PrintWithDelay("����ͷ���㿴��������ѻ���һ�𣬹�����æµ�ذ����š�\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("��ͷ���ˣ�", 30);
    SetConsoleColor(12); // ��ɫ
    PrintWithDelay("���͹٣���û����Ȥ��æ�˻�����æ�Ļ�����׬ЩǮ����\n", 30);
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay("��ͬ���ˣ��������˻������С�\n", 30);
    SetConsoleColor(10); // ��ɫ
    PrintWithDelay("Ǯ��+50\n", 30);
    character->setGold(gold + 50);
    SetConsoleColor(7);
}

int Plot::handleBarracks() {
    if (character) {
        bool running = true;
        while (running) {
            int currentHP = character->getHP(); // ��ȡ��ǰHP
            int maxHP = character->getMaxHP(); // ��ȡ���HP
            int gold = character->getGold(); // ��ȡ��ǰ���

            // ��ʾ�˵�
            SetConsoleColor(8); // ��ɫ
            PrintWithDelay("��ص�Ӫ�����е���һЩƣ������Ҳ�ջ��˲��١�\n", 30);
            SetConsoleColor(7); // ��ɫ
            PrintWithDelay("��ѡ������Ҫ�Ĳ�����\n", 30);
            SetConsoleColor(10); // ��ɫ
           // PrintWithDelay("1. ��Ϣһ��\n", 30);
            PrintWithDelay("1. �鿴�˵�", 30);
            cout << "        ";
            PrintWithDelay("2. �뿪\n", 30);
            SetConsoleColor(7); // ��ɫ
            //PrintWithDelay("������ѡ�1-3����", 30);

            int choice;
            cin >> choice;
            return choice;
            //switch (choice) {
            //case 1:
            //    // ��Ϣ����
            //    SetConsoleColor(8); // ��ɫ
            //    PrintWithDelay("�������Ϣһ�£�Ϊ����������ս��׼����\n", 30);
            //    SetConsoleColor(10); // ��ɫ
            //    PrintWithDelay("�������ֵ+10�� ����ֵ+50�����������������ֵ��\n", 30);
            //    character->setMaxHP(maxHP + 10);
            //    character->modifyHP(50);

            //    // ȷ����ǰHP���������HP
            //    if (character->getHP() > character->getMaxHP()) {
            //        character->setHP(character->getMaxHP());
            //    }
            //    break;

            //case 2:
            //    // �鿴��ǰ״̬
            //    SetConsoleColor(8); // ��ɫ
            //    PrintWithDelay("��ǰ״̬���£�\n", 30);
            //    SetConsoleColor(7); // ��ɫ
            //    PrintWithDelay("����ֵ��", 30);
            //    cout << character->getHP() << "/" << character->getMaxHP() << "\n";
            //    PrintWithDelay("��ң�", 30);
            //    cout << character->getGold() << "\n";
            //    SetConsoleColor(6); // ��ɫ
            //    PrintWithDelay("����������ز˵�...", 30);
            //    cin.ignore(); // �ȴ��û�����
            //    cin.get();
            //    break;

            //case 3:
            //    // �������˵�
            //    running = false;
            //    break;

            //default:
            //    // ��Чѡ��
            //    SetConsoleColor(12); // ��ɫ
            //    PrintWithDelay("��Чѡ�������ѡ��\n", 30);
            //    SetConsoleColor(6); // ��ɫ
            //    break;
            //}
        }
    }
}