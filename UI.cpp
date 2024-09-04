
#include<Windows.h>
#include<windows.h>
#include <mmsystem.h>
#include<iostream>
#include<vector>

#include"UI.h"
#pragma comment(lib, "winmm.lib") // 链接到WinMM库 

using namespace std;
void SetConsoleColor(int);
bool UI::SetSize(int width, int height)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //获取输出句柄
    SMALL_RECT wrt = { 0, 0, width - 1, height - 1 }; //设置宽高
    bool ret = SetConsoleWindowInfo(hOutput, TRUE, &wrt); // 设置窗体尺寸
    if (!ret) return false;
    COORD coord = { width, height };
    ret = SetConsoleScreenBufferSize(hOutput, coord); // 设置缓冲尺寸
    return ret;
}
void UI::ClearConsoleLines(HANDLE hConsole, SHORT s, SHORT e) {
    // 获取控制台屏幕缓冲区的信息  
    SHORT startLine = s - 1;
    SHORT endLine = e - 1;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "无法获取控制台屏幕缓冲区信息！" << std::endl;
        return;
    }
    // 计算每行需要填充的字符数（即屏幕宽度）  
    SHORT width = csbi.dwSize.X;
    // 创建一个足够大的字符数组来存储要写入的空格  
    std::vector<CHAR> spaces(width, ' ');
    // 设置写入位置为开始行的起始位置  
    COORD writePos = { 0, startLine };
    // 遍历要清除的行  
    for (SHORT line = startLine; line <= endLine; ++line) {
        DWORD written;
        // 写入空格以覆盖当前行  
        if (!WriteConsoleOutputCharacterA(hConsole, spaces.data(), static_cast<DWORD>(spaces.size()), writePos, &written)) {
            std::cerr << "无法写入控制台输出字符！" << std::endl;
            return;
        }
        // 如果需要，可以使用WriteConsoleOutputAttribute来写入属性  
        // 但在这个例子中，我们保持原有属性不变，所以不需要这样做  
        // 将写入位置移动到下一行  
        writePos.Y++;
    }
    // （可选）移动光标到屏幕底部或其他位置  
     //SetConsoleCursorPosition(hConsole, {0, csbi.dwSize.Y + e-s});  
}
int UI::showstart() {
    Plot plot;
    SetSize(100, 40);
    SetConsoleColor(4);
    cout << "****************************************************************************************************" << endl;//100
    SetConsoleColor(7);
    cout << "为保证游戏体验，请设置上面的星号在同一行。" << endl;
    cout << "游戏过程中，请勿改变窗口大小，避免影响体验。" << endl;
    cout << "输入“ENTER”继续游戏" << endl;
    cin.get();


    // 清除第二行和第三行  
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "无法获取控制台句柄！" << std::endl;
    }
    ClearConsoleLines(hConsole, 2, 4);
    for (int i = 0; i < 44; i++)
        cout << " ";
    plot.PrintWithDelay("林教头风雪山神庙", 40);
    //cout << "林教头风雪山神庙" << endl;
    cout << endl;
    //PlaySound(TEXT("C:\\FFOutput\\2301442833.wav"), NULL, SND_FILENAME | SND_ASYNC);
    
    
    for (int i = 0; i < 29; i++)
        cout << " ";
    cout << "--------------------------------------------" << endl;;
    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("天理昭昭不可诬，莫将奸恶作良图。", 500);
    //cout << "天理昭昭不可诬，莫将奸恶作良图。";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("若非风雪沽村酒，定被焚烧化朽枯。", 500);
    //cout << "若非风雪沽村酒，定被焚烧化朽枯。";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
 
    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("自谓冥中施计毒，谁知暗里有神扶。", 500);
    //cout << "自谓冥中施计毒，谁知暗里有神扶。";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    plot.PrintWithDelay("最怜万死逃生地，真是瑰奇伟丈夫。", 500);
    //cout << "最怜万死逃生地，真是瑰奇伟丈夫。";
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
    cout << "1.开始征程     2.读取存档     3.退出" << endl;
    cout << "请注意，如果未保存游戏就退出，会导致游戏进度丢失" << endl;
    int flag;
    cin >> flag;
    return flag;
}

int UI::showmenu()
{
    cout << "1.显示属性                    2.显示背包" << endl;
    cout << "3.储存游戏进度                4.返回主菜单" << endl;
    int flag;
    cin >> flag;
    return flag;
}
