// MUD���.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#include <iostream>
#include"battle.h"
#include"map11.h"
#include"plot.h"
#include"UI.h"
#include"shop.h"
#include"Filestore.h"
struct Time
{
    int plottime = 1;
};
int main()
{
    //UI ui;
    //Map map;
    //Linchong linchong("�ֳ�", 100, 100, 100, 100, 100, 100, 1000, 100, 1, 1);
    //Linchong* lc = &linchong;
    //Plot plot(lc);
    //Time t;
    //ui.ready();
    //ui.showstart();//��ʼ����
    //plot.PrintPrompt();//��ctrl����
    //plot.PrintPrologue();//ǰ����Ҫ
    //plot.PrintScene(t.plottime);//��һĻ
    //++t.plottime;
    //plot.PrintScene(t.plottime);//�ڶ�Ļ
    //++t.plottime;
    //plot.PrintScene(t.plottime);//����Ļ
    shopset();

     }
     if (f == 3)//�浵
     {
         files.saveGame(linchong);
     }
     if (f == 4)
        return f;
  }
// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�
// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
