// MUD���.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#include <iostream>
#include"battle.h"
#include"map11.h"
#include"plot.h"
#include"UI.h"
#include"Filestore.h"
#include"shop.h"

struct Time
{
    int plottime = 1;
};


void shopset(Linchong &linchong);
void change1();//Ļ��Ļ֮���ν�
int change2();


UI ui;
Map map1;
Linchong linchong("�ֳ�", 100, 100, 100, 100, 100, 100, 1000, 100, 1, 1);
Linchong* lc = &linchong;
Plot plot(lc);
Time t;
Filestore files;
int main()
{


   // ui.ready();
    //ui.showstart();//��ʼ����
   // plot.PrintPrompt();//��ctrl����
   // plot.PrintPrologue();//ǰ����Ҫ
    //plot.PrintScene(t.plottime);//��һĻ

    change1();
    shopset(linchong);
    change1();
    plot.PrintScene(3);

}
 void change1() {
    int f = plot.Printchange(t.plottime);
    int f_func = 0;
    if (f)
    {
        f_func = change2();
        if (f_func == 1)
        {

        }
        if (f_func == 4)
        {
            change1();
        }
    }
    else
        return;
}
 int change2()
 {
     int f= ui.showmenu();
     int f_func = 0;
    
     if (f == 1)//��ʾ����
     {
         ui.shuxing(lc);
         change2();
     }
     if (f == 2)//��ʾ����
     {

         change2();
     }
     if (f == 3)//�浵
     {
         files.saveGame(linchong);
         change2();
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
