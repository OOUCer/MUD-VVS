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





void SetConsoleColor(int);
void shopset(Linchong &linchong);
void runDevelopmentSystem();//����ϵͳ
void pre_battle(vector<Character*>&enemies, Linchong* lc, Character* character1, Character* character2);//ս��ϵͳ׼��
void change1();//Ļ��Ļ֮���ν�
int change2();


    UI ui;
    Map map1;
    Linchong linchong("�ֳ�", 80, 1000, 800, 10, 80, 0.8, 0.1, 100, true, 100);
    Linchong* lc = &linchong;
    Plot plot(lc);
    Time t;
    Filestore files;
    Shop1 shop1;
    Shop2 shop2;
    vector<Character*> enemies;
    Character* character1 = new Character("����1", 40, 100, 100, 10, 10, 0.8, 0.1, 100, false);
    Character* character2 = new Character("����2", 40, 100, 100, 10, 10, 0.8, 0.1, 100, false);

    Weapon weapon1("��", 20, 30, 10, 0.1, "ն��");
    Weapon weapon2("��", 20, 30, 10, 0.1, "ն��");
    Weapon weapon3("��", 20, 30, 10, 0.1, "���");
    Weapon weapon4("ì", 20, 30, 10, 0.1, "��ͨ");
    Weapon weapon5("ǹ", 20, 30, 10, 0.1, "��ͨ");

    Armor armor1("����1", 20, 30, 100, "ն��");
    Armor armor2("����2", 20, 30, 100, "��ͨ");
    Armor armor3("����3", 20, 30, 100, "���");

    offensiveSkill skill_1("���⽣Ӱ", "�������6�Σ��Լ������½�", false, true, true, 0.7, "ն��", 6, selfDefenseBoost, 0.8, 3);
    offensiveSkill skill_2("ǹ������", "���幥��5�Σ��Լ������½�", false, true, true, 0.8, "��ͨ", 5, selfAttackBoost, 0.8, 3);
    offensiveSkill skill_3("�Ƿ�����", "�޶�ȫ�幥��������Լ�����", true, true, true, 3.4, "���", 1, selfDamage, 0.2, 0);
    //offensiveSkill skill_4("���б���", "ȫ�幥��3��", true, true, true, 0.7, "ն��", 3, none, 0, 0);
    //offensiveSkill skill_5("������", "���鵥�����", false, true, false, 2.2, "���", 1, giveDefenseWeaken, 0.8, 3);
    offensiveSkill skill_6("��ɨǧ��", "ȫ�幥��2��", true, true, true, 1.2, "��ͨ", 2, none, 0, 0);

    supportSkill skill_7("������Ϣ", "�ָ������������������״̬", false, false, true, selfComatose, 1, 3);
    supportSkill skill_8("���ݴ���", "�»غ��˺�����", false, false, true, selfCharge, 1, 1);
    supportSkill skill_9("����ս", "ʶ�ƹ�����������������", false, false, true, selfAnticipate, 1, 1);
    supportSkill skill_10("���ƴ���", "������������", false, false, true, selfAttackBoost, 1.3, 3);
    supportSkill skill_11("ͭͷ����", "�����������", false, false, true, selfDefenseBoost, 1.3, 3);
    supportSkill skill_12("��������", "��������������", false, false, true, selfHitRateBoost, 1.3, 3);
    supportSkill skill_13("��������", "����ر�������", false, false, true, selfEvationBoost, 1.3, 3);
    //supportSkill skill_14("����", "���˹������½�", true, false, false, giveAttackWeaken, 0.8, 3);
    //supportSkill skill_15("��ɳ", "�����������½�", true, false, false, giveHitRateWeaken, 0.8, 3);
    supportSkill skill_16("�ݱ�����", "����ʱ���˻���", true, false, false, giveComatose, 0.75, 3);
    supportSkill skill_17("������", "ʹ���˻ر����½�", true, false, false, giveEvationWeaken, 0.7, 3);










int main(){
    //����ս��ϵͳ________________
    //pre_battle(enemies,  lc, character1,character2);



   // ui.ready();
    //ui.showstart();//��ʼ����
   // plot.PrintPrompt();//��ctrl����
   // plot.PrintPrologue();//ǰ����Ҫ
    //plot.PrintScene(t.plottime);//��һĻ


    //change1();
    //shopset(linchong);
    //change1();
    plot.PrintScene(2);

    return 0;

}














void runDevelopmentSystem() {
    int day = 1;
    while (day <= 8) { // �޸�Ϊday <= 8��ȷ��8�������ϵͳ
        SetConsoleColor(1);
        cout << "������ʮһ��";
        switch (day)
        {
        case 1:cout << "����" << endl; break;
        case 2:cout << "����" << endl; break;
        case 3:cout << "����" << endl; break;
        case 4:cout << "����" << endl; break;
        case 5:cout << "ʮ��" << endl; break;
        case 6:cout << "ʮһ" << endl; break;
        case 7:cout << "ʮ��" << endl; break;
        case 8:cout << "ʮ��" << endl; break;
        default:
            break;
        }
        map1.showmap(lc->getPlace());
        lc->changePlace();
        plot.PrintWithDelay("����������ı�ţ�\n��ѡ�1.��ݣ�����������\n2.�̵꣨�ƣ�ţ�⣬����ǹ��������³��������ȣ���־�Ľ䵶��\n3.��ͷ���˻�׬Ǯ,Ǯ�������������̵��е������ͷ��ߣ�\n4.Ӫ��������������\n", 30);
        
    }
}




void pre_battle(vector<Character*>&enemies, Linchong*lc, Character*character1, Character*character2)
{
    enemies.push_back(character1);
    enemies.push_back(character2);
    lc->addOffensiveSkill(&skill_1);
    lc->addOffensiveSkill(&skill_2);
    lc->addOffensiveSkill(&skill_3);
    //lc->addOffensiveSkill(&skill_4);
    //lc->addOffensiveSkill(&skill_5);
    lc->addOffensiveSkill(&skill_6);

    lc->addSupportSkill(&skill_7);
    lc->addSupportSkill(&skill_8);
    lc->addSupportSkill(&skill_9);
    lc->addSupportSkill(&skill_10);
    lc->addSupportSkill(&skill_11);
    lc->addSupportSkill(&skill_12);
    lc->addSupportSkill(&skill_13);
    //lc->addSupportSkill(&skill_14);
    //lc->addSupportSkill(&skill_15);
    lc->addSupportSkill(&skill_16);
    lc->addSupportSkill(&skill_17);

    lc->addArmor(&armor3);
    lc->addWeapon(&weapon4);
    lc->addWeapon(&weapon2);
    lc->addWeapon(&weapon3);

    character1->addWeapon(&weapon1);
    character1->addArmor(&armor1);
    character1->addOffensiveSkill(&skill_1);
    character1->addSupportSkill(&skill_8);

    character2->addWeapon(&weapon5);
    character2->addArmor(&armor2);
    character2->addOffensiveSkill(&skill_6);
    character2->addSupportSkill(&skill_10);
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
         linchong.printWeapons();
         linchong.printArmors();
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
 void shopset(Linchong& linchong) {

     Weapon dajian(" �� ", 50, 300, 0, 0.4, " ���� ");
     Weapon tiegun(" ���� ", 50, 200, 5, 0.6, " ��� ");
     Weapon cijian(" �̽� ", 50, 110, 10, 1, " ��ͨ ");
     Armor bujia(" ���� ", 50, 50, 100, " ��ͨ ");
     Armor tiejia(" ���� ", 100, 100, 200, " ��� ");
     Armor linjia(" �ۼ� ", 200, 200, 400, " ���� ");


     shop1.addItem(make_unique<Weapon>(dajian));
     shop1.addItem(make_unique<Weapon>(tiegun));
     shop1.addItem(make_unique<Weapon>(cijian));
     shop2.addItem(make_unique<Armor>(bujia));
     shop2.addItem(make_unique<Armor>(tiejia));
     shop2.addItem(make_unique<Armor>(linjia));

     int n;
     int id;
     cout << "��������ѡ��1���������ѡ��2���˳�ѡ��0" << endl;
     while (cin >> n) {
         if (n == 0) break;
         if (n == 1) {
             shop1.listItems();
             cout << "��ѡ����Ҫ������������,�˳�ѡ��0" << endl;
             while (cin >> id) {
                 // ���Թ�����Ʒ  
                 if (id == 0) {
                     system("cls");
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
                     system("cls");
                     break;
                 }
                 if (shop2.buyItem(linchong, id - 1)) { // ���Թ�������Ϊ0����Ʒ��Sword��  
                     shop2.listItems(); // �ٴ��г���Ʒ�Բ鿴�仯  
                 }
                 cout << "��ѡ����Ҫ����ķ�����ţ��˳�ѡ��0" << endl;
             }
         }

         cout << "��������ѡ��1���������ѡ��2���˳�ѡ��0" << endl;
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
