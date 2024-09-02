
#include<Windows.h>
#include<iostream>
#include<vector>
#include"plot.h"
#include"UI.h"
#pragma comment(lib, "winmm.lib") // ���ӵ�WinMM�� 
using namespace std;
void SetConsoleColor(int);
bool UI::SetSize(int width, int height)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ������
    SMALL_RECT wrt = { 0, 0, width - 1, height - 1 }; //���ÿ��
    bool ret = SetConsoleWindowInfo(hOutput, TRUE, &wrt); // ���ô���ߴ�
    if (!ret) return false;
    COORD coord = { width, height };
    ret = SetConsoleScreenBufferSize(hOutput, coord); // ���û���ߴ�
    return ret;
}
void UI::ClearConsoleLines(HANDLE hConsole, SHORT s, SHORT e) {
    // ��ȡ����̨��Ļ����������Ϣ  
    SHORT startLine = s - 1;
    SHORT endLine = e - 1;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "�޷���ȡ����̨��Ļ��������Ϣ��" << std::endl;
        return;
    }
    // ����ÿ����Ҫ�����ַ���������Ļ��ȣ�  
    SHORT width = csbi.dwSize.X;
    // ����һ���㹻����ַ��������洢Ҫд��Ŀո�  
    std::vector<CHAR> spaces(width, ' ');
    // ����д��λ��Ϊ��ʼ�е���ʼλ��  
    COORD writePos = { 0, startLine };
    // ����Ҫ�������  
    for (SHORT line = startLine; line <= endLine; ++line) {
        DWORD written;
        // д��ո��Ը��ǵ�ǰ��  
        if (!WriteConsoleOutputCharacterA(hConsole, spaces.data(), static_cast<DWORD>(spaces.size()), writePos, &written)) {
            std::cerr << "�޷�д�����̨����ַ���" << std::endl;
            return;
        }
        // �����Ҫ������ʹ��WriteConsoleOutputAttribute��д������  
        // ������������У����Ǳ���ԭ�����Բ��䣬���Բ���Ҫ������  
        // ��д��λ���ƶ�����һ��  
        writePos.Y++;
    }
    // ����ѡ���ƶ���굽��Ļ�ײ�������λ��  
     //SetConsoleCursorPosition(hConsole, {0, csbi.dwSize.Y + e-s});  
}
void UI::show() {
    Plot plot;
    SetSize(100, 40);
    SetConsoleColor(4);
    cout << "****************************************************************************************************" << endl;//100
    SetConsoleColor(7);
    cout << "Ϊ��֤��Ϸ���飬������������Ǻ���ͬһ�С�" << endl;
    cout << "��Ϸ�����У�����ı䴰�ڴ�С������Ӱ�����顣" << endl;
    cout << "���롰ENTER��������Ϸ" << endl;
    cin.get();
    // ����ڶ��к͵�����  
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "�޷���ȡ����̨�����" << std::endl;
    }
    ClearConsoleLines(hConsole, 2, 4);
    for (int i = 0; i < 44; i++)
        cout << " ";
    plot.PrintWithDelay("�ֽ�ͷ��ѩɽ����", 40);
    //cout << "�ֽ�ͷ��ѩɽ����" << endl;
    cout << endl;
    //PlaySound(TEXT("C:\\Users\\smtur\\Downloads\\2301442833.MP3"), NULL, SND_FILENAME | SND_ASYNC);
    for (int i = 0; i < 29; i++)
        cout << " ";
    cout << "--------------------------------------------" << endl;;
    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("�������Ѳ����ܣ�Ī���������ͼ��", 1000);
    //cout << "�������Ѳ����ܣ�Ī���������ͼ��";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
    Sleep(1000);
    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("���Ƿ�ѩ����ƣ��������ջ���ݡ�", 1000);
    //cout << "���Ƿ�ѩ����ƣ��������ջ���ݡ�";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
    Sleep(1000);
    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("��νڤ��ʩ�ƶ���˭֪�����������", 1000);
    //cout << "��νڤ��ʩ�ƶ���˭֪�����������";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
    Sleep(1000);
    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("�������������أ����ǹ���ΰ�ɷ�", 1000);
    //cout << "�������������أ����ǹ���ΰ�ɷ�";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
    cout << endl;
    Sleep(1000);
    cout << "1.��ʼ����     2.��ȡ�浵     3.�˳�" << endl;
    cout << "��ע�⣬���δ������Ϸ���˳����ᵼ����Ϸ���ȶ�ʧ" << endl;
    int flag;
    cin >> flag;
}
