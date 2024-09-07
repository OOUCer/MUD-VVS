
#include<Windows.h>
#include<windows.h>
#include <mmsystem.h>
#include<iostream>
#include<vector>
#include"character.h"
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
int UI::ready()
{
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
    ClearConsoleLines(hConsole, 2, 5);
    for (int i = 0; i < 44; i++)
        cout << " ";
    plot.PrintWithDelay("�ֽ�ͷ��ѩɽ����", 40);
    //cout << "�ֽ�ͷ��ѩɽ����" << endl;
    cout << endl;
    //PlaySound(TEXT("C:\\FFOutput\\2301442833.wav"), NULL, SND_FILENAME | SND_ASYNC);


    for (int i = 0; i < 29; i++)
        cout << " ";
    cout << "--------------------------------------------" << endl;;
    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("�������Ѳ����ܣ�Ī���������ͼ��", 500);
    //cout << "�������Ѳ����ܣ�Ī���������ͼ��";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("���Ƿ�ѩ����ƣ��������ջ���ݡ�", 500);
    //cout << "���Ƿ�ѩ����ƣ��������ջ���ݡ�";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("��νڤ��ʩ�ƶ���˭֪�����������", 500);
    //cout << "��νڤ��ʩ�ƶ���˭֪�����������";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("�������������أ����ǹ���ΰ�ɷ�", 500);
    //cout << "�������������أ����ǹ���ΰ�ɷ�";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
    return 0;
}
int UI::showstart() {
    Plot plot;
    
    cout << "1.��ʼ����     2.��ȡ�浵     3.�˳�" << endl;
    cout << "��ע�⣬���δ������Ϸ���˳����ᵼ����Ϸ���ȶ�ʧ" << endl;
    int flag;
    cin >> flag;
    if (flag > 3 || flag < 1)
        flag=showstart();
    return flag;
}

int UI::showmenu()
{
    cout << "1.��ʾ����                    2.��ʾ����" << endl;
    cout << "3.������Ϸ����                4.������һ��" << endl;
    cout << "5.�˳���Ϸ" << endl;
    int flag;
    cin >> flag;
    if (flag == 5)
    {
        cout << "�����˳�";
        exit(EXIT_SUCCESS);
    }
    return flag;
}

int UI::shuxing(Linchong* lc)
{
    cout << "���ƣ� " << lc->getName();
    for (int i = 0; i < 15; i++)
        cout << " ";
    cout << "�Ƹ��� " << lc->getGold() << endl;


    cout << "��������� " << lc->getMaxHP();
    for (int i = 0; i < 15; i++)
        cout << " ";
    cout << "��ǰ������ " << lc->getHP()<<endl;
   
    
    cout << "������ " << lc->getAttack();
    for (int i = 0; i < 15; i++)
        cout << " ";
    cout << "������ " << lc->getDefense()<<endl;


    cout << "���ܣ� " << lc->getEvasionRate();
    for (int i = 0; i < 15; i++)
        cout << " ";
    cout << "���У� " << lc->getHitRate()<<endl;

    
    cout << "�ٶȣ� " << lc->getSpeed() << endl;
    return 0;
}
