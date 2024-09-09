// MUD���.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#include <iostream>
#include"battle.h"
#include"map11.h"
#include"plot.h"
#include"UI.h"
#include"Filestore.h"
#include"shop.h"
#include <windows.h>  
#include <mmsystem.h>  
#pragma comment(lib, "winmm.lib")  // ���ӵ�winmm.lib
//struct Time
//{
//    int plottime = 1;
//    int day = 1;
//};


void SetConsoleColor(int);
void shopset(Linchong &linchong);
void runDevelopmentSystem();//����ϵͳ
void pre_battle1(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2,Character* character3);
void pre_battle2(vector<Character*>&enemies, Linchong* lc, Character* character1, Character* character2);//ս��ϵͳ׼��
void change1();//Ļ��Ļ֮���ν�
void ready_save();
int change2();

void we_save();
void we_read();
void ar_save();
void ar_read();
void os_save(offensiveSkill[6]);
void os_read();
void su_save(supportSkill[11]);
void su_read();

UI ui;
Map map1;
Linchong linchong("�ֳ�", 80, 800, 800, 10, 80, 0.8, 0.1, 100, true, 100);
Linchong* lc = &linchong;
Plot plot(lc);
Time t;
Filestore files;
Shop1 shop1;
Shop2 shop2;
vector<Character*> enemies;
Character* smallen1 = new Character("����1", 40, 700, 700, 30, 90, 0.8, 0.05, 100, false);
Character* smallen2 = new Character("����2", 40, 700, 700, 30, 30, 0.8, 0.05, 100, false);
Character* bigen1 = new Character("��Ӫ", 40, 900, 900, 20, 40, 0.9, 0.1, 0, false);
Character* bigen2 = new Character("�", 40, 900, 1000, 30, 60, 0.85, 0.1, 0, false);
Character* bigen3 = new Character("½�ݺ�", 60, 1000, 1000, 40, 100, 0.85, 0.15, 0, false);
Weapon weapon1("��", 20, 30, 10, 0.1, "ն��");
Weapon weapon2("��", 20, 34, 8, 0.11, "ն��");
Weapon weapon3("��", 20, 32, 10, 0.12, "���");
Weapon weapon4("ì", 20, 30, 11, 0.14, "��ͨ");
Weapon weapon5("��ǹ", 20, 28, 12, 0.15, "��ͨ");
//
Weapon dajian("��", 50, 40, 5, 0.1, "ն��");
Weapon tiegun("����", 50, 35, 10, 0.15, "���");
Weapon cijian("�̽�", 50, 30, 15, 0.2, "��ͨ");

Weapon weapon_default("�ֳ�Ļ�ǹ", 20, 30, 10, 0.1, "��ͨ");
Weapon lcwe[3];

Armor armor1("Ƥ��", 20, 25, 100, "ն��");
Armor armor2("���Ӽ�", 20, 30, 100, "��ͨ");
Armor armor3("���", 20, 35, 120, "���");
Armor armor_default("�ֳ�Ĳ���", 15, 20, 100, "ն��");

Armor bujia("����", 50, 25, 100, "��ͨ");
Armor tiejia("����", 100, 30, 120, "���");
Armor linjia("�ۼ�", 200, 35, 150, "ն��");

Armor lcar[3];

offensiveSkill skill_1("�������������˫ն", "�������6�Σ��Լ������½�", false, true, true, 0.7, "ն��", 6, selfDefenseBoost, 0.8, 3);
offensiveSkill skill_2("ǹ������", "���幥��5�Σ��Լ������½�", false, true, true, 0.8, "��ͨ", 5, selfAttackBoost, 0.8, 3);
offensiveSkill skill_3("�Ƿ�����", "�޶�ȫ�幥��������Լ�����", true, true, true, 3.4, "���", 1, selfDamage, 0.2, 0);
offensiveSkill skill_4("����֮��", "ȫ�幥��3��", true, true, true, 0.7, "ն��", 3, none, 0, 0);
offensiveSkill skill_5("������", "���鵥�����", false, true, false, 2.2, "���", 1, giveDefenseWeaken, 0.8, 3);
offensiveSkill skill_6("��ɨǧ��", "ȫ�幥��2��", true, true, true, 1.2, "��ͨ", 2, none, 0, 0);
offensiveSkill lcofsk[6];

supportSkill skill_7("������Ϣ", "�ָ������������������״̬", false, false, true, selfComatose, 1, 3);
supportSkill skill_8("���ݴ���", "�»غ��˺�����", false, false, true, selfCharge, 1, 1);
supportSkill skill_9("����ս", "ʶ�ƹ�����������������", false, false, true, selfAnticipate, 1, 1);
supportSkill skill_10("���ƴ���", "������������", false, false, true, selfAttackBoost, 1.3, 3);
supportSkill skill_11("ͭͷ����", "�����������", false, false, true, selfDefenseBoost, 1.3, 3);
supportSkill skill_12("��������", "��������������", false, false, true, selfHitRateBoost, 1.3, 3);
supportSkill skill_13("��������", "����ر�������", false, false, true, selfEvationBoost, 1.3, 3);
supportSkill skill_14("����", "���˹������½�", true, false, false, giveAttackWeaken, 0.8, 3);
supportSkill skill_15("��ɳ", "�����������½�", true, false, false, giveHitRateWeaken, 0.8, 3);
supportSkill skill_16("�ݱ�����", "����ʱ���˻���", true, false, false, giveComatose, 0.75, 3);
supportSkill skill_17("������", "ʹ���˻ر����½�", true, false, false, giveEvationWeaken, 0.7, 3);
supportSkill lcsusk[11];


int main(){
    //����ս��ϵͳ________________
    //pre_battle(enemies,  lc, character1,character2);
    int flag;  
    //PlaySound(TEXT("309764634.wav"), NULL, SND_FILENAME | SND_ASYNC);
    PlaySound(TEXT("309764634.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    //lc->buyItem11(&weapon_default);
    //lc->buyItem22(&armor_default);
    // ����������������������  
    //����ʹ����SND_ASYNC���������ֻ��ں�̨����  
    // ��������ó���ȴ�ֱ���û��رգ�����ʹ�����´���  
    lc->addWeapon(&weapon_default);
    lc->addArmor(&armor_default);
    lc->addOffensiveSkill(&skill_4, false);
    lc->addOffensiveSkill(&skill_5, false);
    lc->addOffensiveSkill(&skill_6, false);

    ui.ready();
    flag=ui.showstart();//��ʼ����
    if (flag == 2)
    {
        cout << "���ڼ���" << endl;
        ready_save();
        we_read();
        ar_read();
        os_read();
        su_read();
        lc->loadFromFile("linchong.txt", lc);
        t=plot.loadTimeFromFile("time1.txt");
    }
    else if (flag == 3)
    {
        cout << "�����˳�" << endl;
        exit(1);
    }
    //��������Ϸ����Ϊ�ֳ�����Ĭ������������ʽ

    while(t.plottime<=10)
    {
        switch (t.plottime)
        {
        case 1:
            plot.PrintPrompt();//��ctrl����
            plot.PrintPrologue();//ǰ����Ҫ
            plot.PrintScene(t.plottime);//��һĻ
            change1();
            break;
        case 2:
            plot.PrintScene(t.plottime);//�ڶ�Ļ
            
            change1(); 
            break;
        case 3:
            if (t.day == 0)
            {
                plot.PrintScene(t.plottime);//3
            }
            runDevelopmentSystem();//����
            change1();
            break;
        case 4:
            plot.PrintScene(t.plottime);//4
            change1(); 
            break;
        case 5:
            plot.PrintScene(t.plottime);//5
            change1(); 
            break;
        case 6:
            plot.PrintScene(t.plottime);//6
            map1.showmap(lc->getPlace());
            lc->changePlace(t.plottime);
            change1(); 
            break;
        case 7:
            plot.PrintScene(t.plottime);
            pre_battle2(enemies, lc, smallen1, smallen2);
            plot.PrintScene11();
            lc->setHP(lc->getMaxHP());
            change1(); 
            break;
        case 8:
            plot.PrintScene(t.plottime);//8
            change1(); 
            break;
        case 9:
            plot.PrintScene(t.plottime);//9
            pre_battle1(enemies, lc, bigen1, bigen2, bigen3);
            change1(); break;
        case 10:
            plot.PrintScene(t.plottime);//10
            ++t.plottime;
            break;
        default:
            break;
        }
    }
    cout << "��Ϸ����" << endl;
    //MSG msg;
    //while (GetMessage(&msg, NULL, 0, 0)) {
    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg);
    //}
    return 0;

}

void runDevelopmentSystem() {
    while (t.day <= 8) { // �޸�Ϊday <= 8��ȷ��8�������ϵͳ
        SetConsoleColor(7);
        cout << "������ʮһ��";
        switch (t.day)
        {
        case 1:cout << "���� (���������ʽ:" <<skill_1.getName()<< ")" << endl<<endl; break;
        case 2:cout << "���� (���������ʽ:" << skill_2.getName() << " "<<skill_8.getName()<<")"<<endl<<endl; break;
        case 3:cout << "���� (���������ʽ:" << skill_3.getName() << " " << skill_10.getName() << ")" << endl<<endl; break;
        case 4:cout << "���� (���������ʽ:" << skill_13.getName() << " " << skill_15.getName() << ")" << endl<<endl; break;
        case 5:cout << "ʮ�� (���������ʽ:" << skill_7.getName() << " " << skill_16.getName() << ")" << endl<<endl; break;
        case 6:cout << "ʮһ (���������ʽ:" << skill_11.getName() << " " << skill_17.getName() << ")" << endl<<endl; break;
        case 7:cout << "ʮ�� (���������ʽ:" << skill_9.getName() << " " << skill_14.getName() << ")" << endl<<endl; break;
        case 8:cout << "ʮ�� (���������ʽ:" << skill_12.getName()  << ")" << endl<<endl; break;
        default:
            break;
        }
        map1.showmap(lc->getPlace());
        lc->changePlace(t.plottime);
        switch (lc->getPlace())//1��Ƶ꣬2��ݣ�3Ӫ��4���ϳ�5�о���6��ͷ��7����
        {
        case 1:
            shopset(linchong); ++t.day; break;
        case 2:
            if (plot.handleTraining())
            {
                switch (t.day)
                {
                case 1:
                    lc->addOffensiveSkill(&skill_1, true); break;
                case 2:
                    lc->addOffensiveSkill(&skill_2, true); lc->addSupportSkill(&skill_8,true); break;
                case 3:
                    lc->addOffensiveSkill(&skill_3, true); lc->addSupportSkill(&skill_10,true); break;
                case 4:
                    lc->addSupportSkill(&skill_13,true); lc->addSupportSkill(&skill_15,true);break;
                case 5:
                    lc->addSupportSkill(&skill_7,true); lc->addSupportSkill(&skill_16,true); break;
                case 6:
                    lc->addSupportSkill(&skill_11,true);lc->addSupportSkill(&skill_17,true); break;
                case 7:
                    lc->addSupportSkill(&skill_9,true); lc->addSupportSkill(&skill_14,true);break;
                case 8:
                    lc->addSupportSkill(&skill_12,true);break;
                default:
                    break;
                }
            }
            ; ++t.day; break;
        case 3:
            if (plot.handleBarracks() == 1)
            {
                change2();
            }
            break;
        case 6:
            plot.handleDock(); ++t.day; break;
        default:
            break;
        }
        //plot.PrintWithDelay("����������ı�ţ�\n��ѡ�1.��ݣ�����������\n2.�̵꣨�ƣ�ţ�⣬����ǹ��������³��������ȣ���־�Ľ䵶��\n3.��ͷ���˻�׬Ǯ,Ǯ�������������̵��е������ͷ��ߣ�\n4.Ӫ��������������\n", 30);
        
    }
}

void pre_battle1(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2, Character* character3)
{
    enemies.clear();
    enemies.push_back(character1);
    enemies.push_back(character2);
    enemies.push_back(character3);

    character1->addWeapon(&weapon1);//ն��
    character1->addArmor(&armor2);//��ͨ
    character1->addOffensiveSkill(&skill_1,false);
    character1->addOffensiveSkill(&skill_4, false);
    character1->addSupportSkill(&skill_11,false);
    character1->addSupportSkill(&skill_8,false);

    character2->addWeapon(&weapon5);//��ͨ
    character2->addArmor(&armor3);//���
    character2->addOffensiveSkill(&skill_6,false);
    character2->addOffensiveSkill(&skill_2, false);
    character2->addSupportSkill(&skill_10,false);
    character2->addSupportSkill(&skill_17,false);

    character3->addWeapon(&weapon3);//���
    character3->addArmor(&armor1);//ն��
    character3->addOffensiveSkill(&skill_3,false);
    character3->addOffensiveSkill(&skill_5, false);
    character3->addSupportSkill(&skill_9,false);
    character3->addSupportSkill(&skill_7,false);
    Battle battle_1;
    battle_1.startBattle(lc, &enemies);
    delete character1;
    delete character2;
    delete character3;
}

void pre_battle2(vector<Character*>&enemies, Linchong*lc, Character*character1, Character*character2)
{
    
    enemies.push_back(character1);
    enemies.push_back(character2);
 

    character1->addWeapon(&weapon1);
    character1->addArmor(&armor3);
    character1->addOffensiveSkill(&skill_4,false);
    character1->addSupportSkill(&skill_8,false);
    character1->addSupportSkill(&skill_12,false);

    character2->addWeapon(&weapon5);
    character2->addArmor(&armor1);
    character2->addOffensiveSkill(&skill_6,false);
    character2->addSupportSkill(&skill_10,false);
    Battle battle_1;
    battle_1.startBattle(lc, &enemies);
    delete character1;
    delete character2;
}

 void change1() {
    int f = plot.Printchange(t.plottime);
    int f_func = 0;
    if (f)
    {
        f_func = change2();

        if (f_func == 4)
        {
            change1();
        }
    }
    else
        return;
}

 void ready_save()
 {
     lcwe[0] = dajian;
     
     lcwe[1] = tiegun;
     
     lcwe[2] = cijian;
     
     

     lcar[0] = bujia;
     
     lcar[1] = tiejia;
     
     lcar[2] = linjia;

     lcofsk[0] = skill_1;
     
     lcofsk[1] = skill_2;
     
     lcofsk[2] = skill_3;
     
     lcofsk[3] = skill_4;
     
     lcofsk[4] = skill_5;
     
     lcofsk[5] = skill_6;

     lcsusk[0] = skill_7;
     
     lcsusk[1] = skill_8;
     
     lcsusk[2] = skill_9;
     
     lcsusk[3] = skill_10;
     
     lcsusk[4] = skill_11;
     
     lcsusk[5] = skill_12;
     
     lcsusk[6] = skill_13;
     
     lcsusk[7] = skill_14;
     
     lcsusk[8] = skill_15;
     
     lcsusk[9] = skill_16;
     
     lcsusk[10] = skill_17;
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
         linchong.printWeapons();
         linchong.printArmors();
         change2();
     }
     if (f == 3)//�浵
     {
         ready_save();
         we_save();
         ar_save();
         os_save(lcofsk);
         su_save(lcsusk);
         //lc->loadFromFile("linchong.txt",lc);
         lc->saveToFile("linchong.txt");
         plot.saveTimeToFile("time1.txt", t);
         change2();
     }
     if (f == 4)
        return f;
  }
 void we_save()
 {
     std::ofstream outfile("weapon.txt", std::ios::out | std::ios::binary);
     if (!outfile) {
         std::cerr << "�޷����ļ���" << std::endl;
         return ;
     }
     //cout << a[0].get_ifget();
     // д�����鵽�ļ�  
     int x[3];

     for (int i = 0; i < 3; i++)
     {
         x[i] = lcwe[i].get_ifget();
         // �ر��ļ�  
     }
     outfile.write(reinterpret_cast<char*>(x), 5 * sizeof(int));
     outfile.close();

     std::cout << "�����ѱ��浽�ļ���" << std::endl;
 }
 void we_read()
 {
     int size = 3;

     // ʹ��vector���洢��ȡ�����ݣ���Ϊ��̬�����С�ڱ���ʱȷ��  
     std::vector<int> readArray(size);

     // ���ļ����ڶ�ȡ  
     std::ifstream infile("weapon.txt", std::ios::in | std::ios::binary);
     if (!infile) {
         std::cerr << "�޷����ļ���" << std::endl;
         return ;
     }

     // ��ȡ���ݵ�vector  
     infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

     // �ر��ļ�  
     infile.close();
     int i = 0;
     for (i = 0; i < size; i++)
     {
         if (readArray[i])
         {
             lc->addWeapon(&lcwe[i]); lcwe[i].be_get();
         }
     }
     
 }
 void ar_save()
 {
     std::ofstream outfile("Armor.txt", std::ios::out | std::ios::binary);
     if (!outfile) {
         std::cerr << "�޷����ļ���" << std::endl;
         return;
     }

     // д�����鵽�ļ�  int x[5];
     int x[3];
     for (int i = 0; i < 3; i++)
     {
         x[i] = lcar[i].get_ifget();
         // �ر��ļ�  
     }
     outfile.write(reinterpret_cast<char*>(x), 3 * sizeof(int));
     

     // �ر��ļ�  
     outfile.close();
     std::cout << "�����ѱ��浽�ļ���" << std::endl;
 }
 void ar_read()
 {
     int size = 3;

     // ʹ��vector���洢��ȡ�����ݣ���Ϊ��̬�����С�ڱ���ʱȷ��  
     std::vector<int> readArray(size);

     // ���ļ����ڶ�ȡ  
     std::ifstream infile("Armor.txt", std::ios::in | std::ios::binary);
     if (!infile) {
         std::cerr << "�޷����ļ���" << std::endl;
         return;
     }

     // ��ȡ���ݵ�vector  
     infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

     // �ر��ļ�  
     infile.close();
     int i = 0;
     for (i = 0; i < size; i++)
     {
         if (readArray[i])
             lc->addArmor(&lcar[i]);
     }

 }

 void os_save(offensiveSkill c[6])
 {
     std::ofstream outfile("offensiveSkill.txt", std::ios::out | std::ios::binary);
     if (!outfile) {
         std::cerr << "�޷����ļ���" << std::endl;
         return;
     }

     // д�����鵽�ļ�  
     int x[6];

     for (int i = 0; i < 6; i++)
     {
         x[i] = c[i].get_ifget();
         // �ر��ļ�  
     }
     outfile.write(reinterpret_cast<char*>(x), 6 * sizeof(int));
     

     // �ر��ļ�  
     outfile.close();

     std::cout << "���������ѱ��浽�ļ���" << std::endl;
 }
 void os_read()
 {
     int size = 6;

     // ʹ��vector���洢��ȡ�����ݣ���Ϊ��̬�����С�ڱ���ʱȷ��  
     std::vector<int> readArray(size);

     // ���ļ����ڶ�ȡ  
     std::ifstream infile("offensiveSkill.txt", std::ios::in | std::ios::binary);
     if (!infile) {
         std::cerr << "�޷����ļ���" << std::endl;
         return;
     }

     // ��ȡ���ݵ�vector  
     infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

     // �ر��ļ�  
     infile.close();
     int i = 0;
     for (i = 0; i < size; i++)
     {
         if (readArray[i])
             lc->addOffensiveSkill(&lcofsk[i],true);
     }

 }

 void su_save(supportSkill d[10])
 {
     std::ofstream outfile("supportSkill.txt", std::ios::out | std::ios::binary);
     if (!outfile) {
         std::cerr << "�޷����ļ���" << std::endl;
         return;
     }

     // д�����鵽�ļ�  
     int x[10];

     for (int i = 0; i < 10; i++)
     {
         x[i] = d[i].get_ifget();
         // �ر��ļ�  
     }
     outfile.write(reinterpret_cast<char*>(x), 10 * sizeof(int));

     // �ر��ļ�  
     outfile.close();

     std::cout << "���������ѱ��浽�ļ���" << std::endl;
 }
 void su_read()
 {
     int size = 10;

     // ʹ��vector���洢��ȡ�����ݣ���Ϊ��̬�����С�ڱ���ʱȷ��  
     std::vector<int> readArray(size);

     // ���ļ����ڶ�ȡ  
     std::ifstream infile("supportSkill.txt", std::ios::in | std::ios::binary);
     if (!infile) {
         std::cerr << "�޷����ļ���" << std::endl;
         return;
     }

     // ��ȡ���ݵ�vector  
     infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

     // �ر��ļ�  
     infile.close();
     int i = 0;
     for (i = 0; i < size; i++)
     {
         if (readArray[i])
             lc->addSupportSkill(&lcsusk[i],true);
     }

 }

 void shopset(Linchong& linchong) {

     Weapon dajian("��", 50, 40, 5, 0.1, "ն��");
     Weapon tiegun("����", 50, 35, 10, 0.15, "���");
     Weapon cijian("�̽�", 50, 30, 15, 0.2, "��ͨ");
     Armor bujia("����", 50, 25, 100, "��ͨ");
     Armor tiejia("����", 100, 30, 120, "���");
     Armor linjia("�ۼ�", 200, 35, 150, "ն��");


     shop1.addItem(make_unique<Weapon>(dajian));
     shop1.addItem(make_unique<Weapon>(tiegun));
     shop1.addItem(make_unique<Weapon>(cijian));
     shop2.addItem(make_unique<Armor>(bujia));
     shop2.addItem(make_unique<Armor>(tiejia));
     shop2.addItem(make_unique<Armor>(linjia));

     int n;
     int id;
     plot.PrintWithDelay("��С��������һ�ߣ���һ�ƣ����������ʲô����\n", 30);
     cout << "0.�˳�          1.����           2.����" << endl;
     while (cin >> n) {
         if (n == 0) {
             plot.PrintWithDelay("��С���������ϣ��������ߣ���\n", 30);
             break;
         }
         if (n == 1) {
             shop1.listItems();
             cout << "��ѡ����Ҫ������������,�˳�ѡ��0" << endl;
             while (cin >> id) {
                 // ���Թ�����Ʒ  
                 if (id == 0) {
                     break;
                 }
                 if (shop1.buyItem(linchong, id - 1)) { // ���Թ�������Ϊ0����Ʒ��Sword��  
                     shop1.listItems(); // �ٴ��г���Ʒ�Բ鿴�仯  
                 }
                 cout << "��ѡ����Ҫ�����������ţ��˳�ѡ��0" << endl;
             }
         }
         if (n == 2) {
             shop2.listItems();
             cout << "��ѡ����Ҫ����ķ�����ţ��˳�ѡ��0" << endl;
             while (cin >> id) {
                 // ���Թ�����Ʒ  
                 if (id == 0) {
                     break;
                 }
                 if (shop2.buyItem(linchong, id - 1)) { // ���Թ�������Ϊ0����Ʒ��Sword��  
                     shop2.listItems(); // �ٴ��г���Ʒ�Բ鿴�仯  
                 }
                 cout << "��ѡ����Ҫ����ķ�����ţ��˳�ѡ��0" << endl;
             }
         }
         cout << "0.�˳�          1.����           2.����" << endl;
     }

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
