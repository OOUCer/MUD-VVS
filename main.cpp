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
vector<Character*> enemies;
Character* character1 = new Character("�ν�", 40, 1000, 1000, 40, 40, 0.8, 0.1, 0, false);
Character* character2 = new Character("³����", 40, 2000, 1000, 40, 40, 0.8, 0.1, 0, false);
   
Weapon weapon1("��", 20, 30, 10, 0.1, "ն��");
Weapon weapon2("��", 20, 30, 10, 0.1, "ն��");
Weapon weapon3("��", 20, 30, 10, 0.1, "���");
Weapon weapon4("ì", 20, 30, 10, 0.1, "��ͨ");
Weapon weapon5("ǹ", 20, 30, 10, 0.1, "��ͨ");

Armor armor1("����1", 20, 30, 100, "ն��");
Armor armor2("����2", 20, 30, 100, "��ͨ");
Armor armor3("����3", 20, 30, 100, "���");

offensiveSkill skill_1("�������������˫ն", "�������6�Σ��Լ������½�", false, true, true, 0.7, "ն��", 6, selfDefenseBoost, 0.8, 3);
offensiveSkill skill_2("���񳯷�", "���幥��5�Σ��Լ������½�", false, true, true, 0.8, "��ͨ", 5, selfAttackBoost, 0.8, 3);
offensiveSkill skill_3("����֮ս", "�޶�ȫ�幥��������Լ�����", true, true, true, 3.4, "���", 1, selfDamage, 0.2, 0);
offensiveSkill skill_4("���б���", "ȫ�幥��3��", true, true, true, 0.7, "ն��", 3, none, 0, 0);
offensiveSkill skill_5("������", "���鵥�����", false, true, false, 2.2, "���", 1, giveDefenseWeaken, 0.8, 3);
offensiveSkill skill_6("��ɨǧ��", "ȫ�幥��2��", true, true, true, 1.2, "��ͨ", 2, none, 0, 0);

supportSkill skill_7("˯��", "�ָ������������������״̬", false, false, true, selfComatose, 1, 3);
supportSkill skill_8("����", "�»غ��˺�����", false, false, true, selfCharge, 1, 1);
supportSkill skill_9("����", "ʶ�ƹ�����������������", false, false, true, selfAnticipate, 1, 1);
supportSkill skill_10("����", "������������", false, false, true, selfAttackBoost, 1.3, 3);
supportSkill skill_11("����", "�����������", false, false, true, selfDefenseBoost, 1.3, 3);
supportSkill skill_12("ӥ��", "��������������", false, false, true, selfHitRateBoost, 1.3, 3);
supportSkill skill_13("����", "����ر�������", false, false, true, selfEvationBoost, 1.3, 3);
supportSkill skill_14("����", "���˹������½�", true, false, false, giveAttackWeaken, 0.8, 3);
supportSkill skill_15("��ɳ", "�����������½�", true, false, false, giveHitRateWeaken, 0.8, 3);
supportSkill skill_16("ҡ����", "����ʱ���˻���", true, false, false, giveComatose, 0.75, 3);
supportSkill skill_17("���Ũ��", "ʹ���˻ر����½�", true, false, false, giveEvationWeaken, 0.7, 3);

    
int main(){
    //����ս��ϵͳ________________
    //pre_battle(enemies,  lc, character1,character2);



   // ui.ready();
    //ui.showstart();//��ʼ����
   // plot.PrintPrompt();//��ctrl����
   // plot.PrintPrologue();//ǰ����Ҫ
    //plot.PrintScene(t.plottime);//��һĻ


    change1();
    shopset(linchong);
    change1();
    plot.PrintScene(3);

    return 0;

}
void pre_battle(vector<Character*>&enemies, Linchong*lc, Character*character1, Character*character2)
{
    enemies.push_back(character1);
    enemies.push_back(character2);
    lc->addOffensiveSkill(&skill_1);
    lc->addOffensiveSkill(&skill_2);
    lc->addOffensiveSkill(&skill_3);
    lc->addOffensiveSkill(&skill_4);
    lc->addOffensiveSkill(&skill_5);
    lc->addOffensiveSkill(&skill_6);

    lc->addSupportSkill(&skill_7);
    lc->addSupportSkill(&skill_8);
    lc->addSupportSkill(&skill_9);
    lc->addSupportSkill(&skill_10);
    lc->addSupportSkill(&skill_11);
    lc->addSupportSkill(&skill_12);
    lc->addSupportSkill(&skill_13);
    lc->addSupportSkill(&skill_14);
    lc->addSupportSkill(&skill_15);
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
