#include "plot.h"
#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}//�ı����������ɫ
void Plot::PrintWithDelay(const std::string& text, int delayMs) {
    for (char ch : text) {
        cout << ch;
        cout.flush(); // ȷ���ַ��������
        this_thread::sleep_for(chrono::milliseconds(delayMs));
        if (isCtrlPressed) {
            delayMs = acceleratedDelayMs; // Ctrl������ʱ������ʾ
        }
        else {
            delayMs = defaultDelayMs; // Ctrl��δ����ʱ������ʾ�ٶ�
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
    SetConsoleColor(7); // ��ɫ
    PrintWithDelay(backgroundSentence, defaultDelayMs);
}
Plot::Plot() {
    // �����̼߳���Ctrl��״̬
    keyboardThread = thread(&Plot::KeyboardThread, this);
}
Plot::~Plot() {
    // ȷ���߳̽���ǰ���������߳�
    if (keyboardThread.joinable()) {
        keyboardThread.detach();
    }
}
void Plot::PrintPrompt() {
    SetConsoleColor(1); // ��ɫ
    PrintWithDelay("����Cter��ʱ������ʾ\n", 30);
    SetConsoleColor(6);
}
void Plot::PrintPrologue() {
    SetConsoleColor(8); // ��ɫ
    PrintWithDelay("ǰ����Ҫ��������˸�̫ξ������������γǺ����ڲ����˵Ĺ�ϵ��������ڳ��л��\n", 30);
    SetConsoleColor(6);
}
int placeflag;
//placeflag= 1 ��Ƶ�    2 ���  3 Ӫ��  4 ���ϳ�  5 �о�  6 ��ͷ  7 ����
void Plot::PrintScene(int& scene) {
    int now_day = 1;
    switch (scene) {
    case 1:
        placeflag = 4;
        SetConsoleColor(8); // ��ɫ
        PrintWithDelay("��һĻ��\n����߳�Ӫ������Χ�Ŀ��������ʪ��ѩ���׷ɣ��·�Ϊ�������һ�������̺���ݳ���ѩѹ�ü���̱��Զ����ɽ���������������ɼ����������类��Ⱦ����������ɫ�������ڱ�ѩ���ǵ�С·�ϣ����·�������֨��֨������������Ȼ������ǰ����һ��С��Ƶ꣬�ƹ�ǰ�ĺ�����ں�����ҡҷ���ˣ�ɢ������ů�Ĺ�â��\n", 30);
        placeflag = 1;
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("��С����", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("��Ӫǰ���˸���Ƶꡣ����Ǯ�������������ˡ����˲�֪Ϊ�����������\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�ֳ�ָ�����ϵ���", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("��������˸�̫ξ�������ݺ�������һ����˾�����䵽��������ҹ������ã�δ֪�ú���Ρ�������յ�����������\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("��С�������ֳ嵽�����������������ӳ������˶��ˡ�\n���ڶ���ϲ����", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("������޶�����û���׾죬���յö��˵��������Ǵ��콵�¡���\n", 30);
        SetConsoleColor(10); // ��ɫ
        PrintWithDelay("�̲�+100���ް�+1��\n", 30);
        SetConsoleColor(6);
        break;
    case 2:
        SetConsoleColor(8); // ��ɫ
        PrintWithDelay("�ڶ�Ļ��\n���յĺ�����Ű���ֵ��ϵ�ѩ���ȵ����������������Ŵ̹ǵĺ��䡣\n", 30);
        placeflag = 1;
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�ֳ������Ƶ꣬˵����", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("��С���磬���պ���������\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("��С����æ����", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("������������С��ȴ����ҪѰ���ˣ���ЩҪ����˵����\n", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("��ȴ���и��������������ˣ������������Ӫ������˰��վơ�������ų�����̫ξ����������������ֻ�������Ӧ�������������������ϣ��ô�Ҫ�������������������һ�������������Ӫ������ֳ�һ�ؾƣ�����ɢ�ˡ�\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�ֳ����ˣ��󾪵���", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("������ʮ�������½�ݺ����ü���Ҳ�������ﺦ�ң���Ҫײ���ң�ֻ��������Ϊ�࣡��\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("��С������", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("��ֻҪ��������ˡ��������ȥ�����̵�����������Ʒ����\n", 30);
        SetConsoleColor(6);
        break;
    case 3:
        SetConsoleColor(8); // ��ɫ
        PrintWithDelay("����Ļ:\n���߳���Ƶ꣬����ѩ���ϣ����µĻ�ѩ��ѹ��һ����������㼣���ֵ�����������磬�ֱߵ�С������ǰ���ź�ɫ�ĵ����������˺����ҹ���̵��ľ�ų����ţ�����͸����͵ĵƹ⣬��ƵĹ�â��ѩ����Ͷ�³�����Ӱ�ӡ�\n", 30);
        SetConsoleColor(7); // ��ɫ
        placeflag = 5;
        PrintWithDelay("�̵꣺", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("������~~�͹�Ҫ��Щʲô����\n", 30);
        // ѡ�񲿷�
        while (now_day != 9) {
            SetConsoleColor(1); // ��ɫ
            cout << "���������ɵĵ�" << now_day++ << "��,";
            PrintWithDelay("����������ı�ţ�\n��ѡ�1.��ݣ�����������\n2.�̵꣨�ƣ�ţ�⣬����ǹ��������³��������ȣ���־�Ľ䵶��\n3.��ͷ���˻�׬Ǯ��\n4.Ӫ������������ֵ��\n", 30);
            int choice;
            cin >> choice; // ����ʹ�� scanf ����ȡ�û�������
            switch (choice) {
            case 1: // ���
                placeflag = 2;
                SetConsoleColor(8); // ��ɫ
                PrintWithDelay("�������ϰ����������˷������������㣬������к��㡣\n", 30);
                SetConsoleColor(7); // ��ɫ
                PrintWithDelay("������", 30);
                SetConsoleColor(12); // ��ɫ
                PrintWithDelay("����ӭ�������������ѵ�������������ս����������\n", 30);
                SetConsoleColor(7); // ��ɫ
                PrintWithDelay("���ڹ��ڽ�����ǿ��ѵ�����о��Լ��������õ�������������\n", 30);
                SetConsoleColor(10); // ��ɫ
                PrintWithDelay("����+10��Ǯ��-40��\n", 30);//attack+10,gold-40
                SetConsoleColor(6);
                break;
            case 2: // �̵�
                placeflag = 5;
                SetConsoleColor(8); // ��ɫ
                PrintWithDelay("�̵��ڵƻ�ͨ���������ϰ����˸��������Ͳ���Ʒ�����������ӭ���㣬�����˵��ڵĻ�Ʒ��\n", 30);
                SetConsoleColor(7); // ��ɫ
                PrintWithDelay("������", 30);
                SetConsoleColor(12); // ��ɫ
                PrintWithDelay("����ӭ���٣��͹٣������и�ʽ������������װ��������ҪЩʲô����\n", 30);
                SetConsoleColor(7); // ��ɫ
                PrintWithDelay("����ϸ��ѡ��һЩ�����ͷ��ߣ�׼��Ӧ�Կ��ܵ�Σ�ա�\n", 30);
                SetConsoleColor(10); // ��ɫ
                PrintWithDelay("����װ��+1��Ǯ��-50��\n", 30);//weapons+1,gold-50
                SetConsoleColor(6);
                break;
            case 3: // ��ͷ
                placeflag = 6;
                SetConsoleColor(8); // ��ɫ
                PrintWithDelay("����ͷ���㿴��������ѻ���һ�𣬹�����æµ�ذ����š�\n", 30);
                SetConsoleColor(7); // ��ɫ
                PrintWithDelay("��ͷ���ˣ�", 30);
                SetConsoleColor(12); // ��ɫ
                PrintWithDelay("���͹٣���û����Ȥ��æ�˻���������Ҫ������Ͷ�������æ�Ļ�����׬ЩǮ����\n", 30);
                SetConsoleColor(7); // ��ɫ
                PrintWithDelay("��ͬ���ˣ��������˻������С�����һ�죬��æµ�ذ��˻����Ȼ���ۣ��������Լ�������Ҳ�е������⡣\n", 30);
                SetConsoleColor(10); // ��ɫ
                PrintWithDelay("Ǯ��+50\n", 30);//gold+50
                SetConsoleColor(6);
                break;
            case 4: // Ӫ��
                placeflag = 3;
                SetConsoleColor(8); // ��ɫ
                PrintWithDelay("��ص�Ӫ�����е���һЩƣ������Ҳ�ջ��˲��١����յ�����͸��Ӫ                         ���Ĵ��������������������һ˿��ů��\n", 30);
                SetConsoleColor(7); // ��ɫ          nb
                PrintWithDelay("�������Ϣһ�£�Ϊ����������ս��׼����\n", 30);
                SetConsoleColor(10); // ��ɫ
                PrintWithDelay("�������ֵ+10�� ����ֵ+50�����������������ֵ��\n", 30);//maxHP+10,HP+50(������maxHP)
                SetConsoleColor(6);
                break;
            default:
                SetConsoleColor(12); // ��ɫ
                PrintWithDelay("��Ч��ѡ����������Ч�ı�š�\n", 30);
                now_day--;
                SetConsoleColor(1);
                break;
            }
        }
    case 4:
        SetConsoleColor(8); // ��ɫ
        PrintWithDelay("����Ļ��\n���߽������������ڿռ��������������ʯ�壬ɢ������������Ϣ��ǽ�������ż���սͼ��ս�ģ��͵��µĹ�Ӱ��ǽ��ҡҷ��ӳ����һ�������ϵ�ս�����󡣹�Ӫ���ڿ���ľ�������ϰڷ��ż������ص��˲��ͱ�ī��΢���ĵƹ��£�ֽҳ�ϵ������Ե���Ϊ������\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("��Ӫ̧��ͷ����Ŀ�����ࣺ", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("�������������ʱ����������Ƥ������̧�ٵ��㡣�˼䶫����ʮ�����������ݳ���ÿ�µ����ɲ����ϵģ���Щ����Ǯȡ�١�ԭ��һ���Ͼ����ܡ������̧����ȥ�����Ͼ����������á���������Ѱ�����̲�����ɺͲ��ȥ���ｻ���\n", 30);
        SetConsoleColor(6);
        break;
    case 5:
        placeflag = 4;
        SetConsoleColor(8); // ��ɫ
        PrintWithDelay("����Ļ��\n��Ͳһͬ���������⣬����·�����ǽ���ϲ��������ƣ��Եó¾ɶ��ֲڡ����ȳ��ص�ľ����Ϳ��һ��¾ɵ����ᣬ�ƿ���ʱ��ľͷ������΢��֨ѽ�������ڲ����˲ݷ����ݶ����øɲݺ�ľ���ɵģ�ɢ����һ��Ũ�ҵĲ��㡣\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("��ߵ��Ͼ���ǰ����������һ˿��ʽ��", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("����Ӫ������ֳ�������������ÿ��ء���ɼ��㽻���\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�Ͼ�����Կ�ף������ֳ壬�Ը�����", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("�����������й�˾��ǡ��⼸�Ѳݣ�һ�ѶѶ�����Ŀ����\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�Ͼ�������˶����������ֳ嵽�����ϡ��Ͼ���ʰ�������˵����", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("�����衢���ӡ��롢�����������㡣��\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�Ͼ�ָ���Ϲ�һ�����«˵����", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("��������Ƴ�ʱ��ֻ���ݳ���Ͷ����·ȥ����������о�����\n", 30);
        placeflag = 5;
        SetConsoleColor(10); // ��ɫ
        PrintWithDelay("����+1����«+1��\n", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("������~~�͹�Ҫ��Щʲô����\n", 30);
        SetConsoleColor(6);
        break;
    case 6:
        SetConsoleColor(8); // ��ɫ
        placeflag = 4;
        PrintWithDelay("����Ļ��\n��������Щ�����������¯��Ļ��潥������¯�߶��ż���ֲڵĲ�̿��ľ�񷢳���ž�����졣�ݱ���һ�Ѳ�̿���ü����������ڵ�¯����濴�ǲ���ʱ������������ˣ��ֱ�˷�紵����ҡ��ö���\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�ֳ壺", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("��Ҫ�����о�����ƣ���\n", 30);
        placeflag = 5;
        SetConsoleColor(6);
        break;
    case 7:
        SetConsoleColor(8); // ��ɫ
        placeflag = 7;
        PrintWithDelay("����Ļ��\n�в��ϰ����·������һ�����������ʯשǽ�ڰ߲�������������ʯ����ҡҡ��׹��\n������һ�أ�����һ���˼ҡ���ס�ſ�ʱ������Ϲ���һ�Ѳ��㣬���ҡҷ��¶��������������\n���������̤��ѩ�أ����·�����֨��֨�����졣�������У������ּ���С͵�������棬��Χ�����ҡҷ������ӳ�ճ��������յ���ס�\n������һ����׼������ս����\n", 30);
        SetConsoleColor(7); // ��ɫ
        placeflag = 5;
        PrintWithDelay("��ң�", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("���������䣬����������Ȩ���ӷ硣�������һ����ţ�⣬��һ���Ⱦƣ����ֳ�ԡ���\n", 30);
        SetConsoleColor(10); // ��ɫ
        PrintWithDelay("����+20������ƻظ�����30�㣬ţ��ظ�����40�㡣\n", 30);
        SetConsoleColor(6);
        break;
    case 8:
        placeflag = 4;
        SetConsoleColor(8); // ��ɫ
        PrintWithDelay("�ڰ�Ļ��\n��ص��ݳ���ֻ����������Ѿ������صĻ�ѩѹ����ѩ���ڿ��з׷ɣ�������һ�С�\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�ֳ壺", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("��ȥ����Ը�һ����\n", 30);
        placeflag = 7;
        SetConsoleColor(6);
        break;
    case 9:
        SetConsoleColor(8); // ��ɫ
        PrintWithDelay("�ھ�Ļ��\n  �����ڲݳ������ӣ�ҹɫ�У����ӳ�ճ����ܺڰ������������ȵ������ڿ��������������������Ŵ̱ǵ��ս�ζ��\n���ս����е�ǹ��׼������������档���ڴ�ʱ��������ǰ���������ٵĽŲ����͵����Ի���\n�㿿�������ϣ������赲�ŵ��ƿ����ŷ�͸��΢���Ĺ��ߣ�ӳ���������ʵ���Ӱ��\n������������ʱ��һ���ǲ��һ����½�ݺ�һ���Ǹ�����\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�ֳ�����һ�󾪻ţ�����������", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("����������ֳ壡�����ǵ��˲�������׼���������������ˣ���\n", 30);
        SetConsoleColor(7); // ��ɫ
        PrintWithDelay("�����ʯͷ�޿���ͦ�Ż�ǹ��һ��ק�����ţ����һ������\n", 30);
        SetConsoleColor(12); // ��ɫ
        PrintWithDelay("����������ȥ����\n", 30);
        SetConsoleColor(10); // ��ɫ
        PrintWithDelay("����ս����\n", 30);
        SetConsoleColor(6);
        break;
    case 10:
        SetConsoleColor(8); // ��ɫ
        PrintWithDelay("��ʮĻ��\n�������������裬�������𽵷׷ס�������Ұ�ѷ�·�����ǧɽ�����ۡ�\n�����磬��Ǭ�����������������ء������µ��������ݷ���ƽ����š�", 30);
        SetConsoleColor(6);
        break;
    }
}
/*
����Ϊmain.cpp
#include <iostream>
#include "plot.h"
using namespace std;
int main() {
    Plot plot;
    plot.PrintPrompt();
    plot.PrintPrologue();
    for (int i = 1; i <= 10; ++i) {
        cout << "\n��Enter���������� " << i << " Ļ...";
        cin.get(); // �ȴ��û����»س���
        // ��ӡ��ǰĻ
        plot.PrintScene(i);
        if (i > 9) {
            cout << "\n��Enter���˳�...";
        }
    }
    return 0;
}
*/