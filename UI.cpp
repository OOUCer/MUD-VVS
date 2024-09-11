#include <Windows.h>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <vector>
#include "character.h"
#include "UI.h"

#pragma comment(lib, "winmm.lib") // ���ӵ�WinMM�� 

using namespace std;

// ���ÿ���̨��ɫ
void SetConsoleColor(int color);

// ���ÿ���̨���ڴ�С
bool UI::SetSize(int width, int height)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ������

    SMALL_RECT wrt = { 0, 0, width - 1, height - 1 }; // ���ÿ��

    bool ret = SetConsoleWindowInfo(hOutput, TRUE, &wrt); // ���ô���ߴ�
    if (!ret) {
        return false;
    }

    COORD coord = { width, height };
    ret = SetConsoleScreenBufferSize(hOutput, coord); // ���û���ߴ�

    return ret;
}

// �������̨��ָ����
void UI::ClearConsoleLines(HANDLE hConsole, SHORT s, SHORT e)
{
    SHORT startLine = s - 1; // ��ʼ��
    SHORT endLine = e - 1; // ������

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "�޷���ȡ����̨��Ļ��������Ϣ��" << std::endl;
        return;
    }

    SHORT width = csbi.dwSize.X; // ��Ļ���

    std::vector<CHAR> spaces(width, ' '); // �����ո��ַ�����

    COORD writePos = { 0, startLine }; // д��λ�ó�ʼ��

    for (SHORT line = startLine; line <= endLine; ++line) {
        DWORD written;
        if (!WriteConsoleOutputCharacterA(hConsole, spaces.data(), static_cast<DWORD>(spaces.size()), writePos, &written)) {
            std::cerr << "�޷�д�����̨����ַ���" << std::endl;
            return;
        }
        writePos.Y++; // �ƶ�����һ��
    }
}

// ׼������
int UI::ready()
{
    Plot plot;

    SetSize(100, 40); // ���ÿ���̨��С
    SetConsoleColor(4); // ������ɫ
    cout << "***************************************************************************************************" << endl; // ��ӡ�Ǻ�
    SetConsoleColor(7); // �ָ�Ĭ����ɫ
    Sleep(500);

    cout << "Ϊ��֤��Ϸ���飬������������Ǻ���ͬһ�С�" << endl;
    cout << "��Ϸ�����У�����ı䴰�ڴ�С������Ӱ�����顣" << endl;
    cout << "����ENTER��������Ϸ" << endl;
    cin.get();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨���
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "�޷���ȡ����̨�����" << std::endl;
    }

    ClearConsoleLines(hConsole, 1, 5); // ���ָ����

    for (int i = 0; i < 44; i++) {
        cout << " "; // ��ӡ�ո�
    }

    plot.PrintWithDelay("�ֽ�ͷ��ѩɽ����", 40); // ��ӡ����
    cout << endl;

    for (int i = 0; i < 29; i++) {
        cout << " ";
    }

    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < 36; i++) {
        cout << " ";
    }

    plot.PrintWithDelay("�������Ѳ����ܣ�Ī���������ͼ��", 500); // ��ӡ����
    cout << endl;

    for (int i = 0; i < 36; i++) {
        cout << " ";
    }

    plot.PrintWithDelay("���Ƿ�ѩ����ƣ��������ջ���ݡ�", 500); // ��ӡ����
    cout << endl;

    for (int i = 0; i < 36; i++) {
        cout << " ";
    }

    plot.PrintWithDelay("��νڤ��ʩ�ƶ���˭֪�����������", 500); // ��ӡ����
    cout << endl;

    for (int i = 0; i < 36; i++) {
        cout << " ";
    }

    plot.PrintWithDelay("�������������أ����ǹ���ΰ�ɷ�", 500); // ��ӡ����
    cout << endl;

    return 0;
}

// ��ʾ��ʼ�˵�����ȡ�û�ѡ��
int UI::showstart()
{
    Plot plot;

    cout << "1.��ʼ����     2.��ȡ�浵     3.�˳�" << endl;
    cout << "��ע�⣬���δ������Ϸ���˳����ᵼ����Ϸ���ȶ�ʧ" << endl;

    int flag;
    cin >> flag;

    if (flag > 3 || flag < 1) {
        flag = showstart(); // ������ʾ�˵�
    }

    return flag;
}

// ��ʾ�˵�����ȡ�û�ѡ��
int UI::showmenu()
{
    cout << endl;
    cout << "1.��ʾ����                    2.��ʾ����" << endl;
    cout << "3.������Ϸ����                4.������һ��" << endl;
    cout << "5.�˳���Ϸ" << endl;

    int flag;
    cin >> flag;

    if (flag == 5) {
        cout << "�����˳�";
        exit(EXIT_SUCCESS); // �˳�����
    }

    return flag;
}

// ��ʾ��ɫ����
int UI::shuxing(Linchong* lc)
{
    cout << "���ƣ� " << lc->getName();

    for (int i = 0; i < 15; i++) {
        cout << " ";
    }

    cout << "�̲��� " << lc->getGold() << endl;

    cout << "��������� " << lc->getMaxHP();

    for (int i = 0; i < 15; i++) {
        cout << " ";
    }

    cout << "��ǰ������ " << lc->getHP() << endl;

    cout << "������ " << lc->getAttack();

    for (int i = 0; i < 15; i++) {
        cout << " ";
    }

    cout << "������ " << lc->getDefense() << endl;

    cout << "���ܣ� " << lc->getEvasionRate();

    for (int i = 0; i < 15; i++) {
        cout << " ";
    }

    cout << "���У� " << lc->getHitRate() << endl;

    cout << "�ٶȣ� " << lc->getSpeed() << endl;

    return 0;
}
