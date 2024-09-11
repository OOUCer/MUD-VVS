// MUD���.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
#include <iostream>
#include "battle.h"      // ����ս��ϵͳ��ص�ͷ�ļ�
#include "map11.h"       // ������ͼ��ص�ͷ�ļ�
#include "plot.h"        // ����������ص�ͷ�ļ�
#include "UI.h"          // �����û�������ص�ͷ�ļ�
#include "Filestore.h"   // �����ļ��洢��ص�ͷ�ļ�
#include "shop.h"        // �����̵���ص�ͷ�ļ�
#include <windows.h>  
#include <mmsystem.h>  
#pragma comment(lib, "winmm.lib")  // ���ӵ� winmm.lib�����ڲ�����Ч

// ��������
void SetConsoleColor(int);
void shopset(Linchong& linchong);
void runDevelopmentSystem(); // ����ϵͳ
void pre_battle1(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2, Character* character3);
void pre_battle2(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2); // ս��ϵͳ׼��
void change1(); // Ļ��Ļ֮���ν�
void ready_save(); // ׼��������Ϸ
int change2(); // �ı���Ϸ״̬

void we_save(); // ��������
void we_read(); // ��ȡ����
void ar_save(); // ���滤��
void ar_read(); // ��ȡ����
void os_save(offensiveSkill[6]); // �����������
void os_read(); // ��ȡ��������
void su_save(supportSkill[11]); // ����֧Ԯ����
void su_read(); // ��ȡ֧Ԯ����

// ȫ�ֶ���ͱ�����ʼ��
UI ui;                      // �û��������
Map map1;                   // ��ͼ����
Linchong linchong("�ֳ�", 80, 800, 800, 10, 80, 0.8, 0.1, 100, true, 100); // �ֳ��ɫ����
Linchong* lc = &linchong;  // ָ���ֳ��ָ��
Plot plot(lc);            // �������
Time t;                   // ʱ�����
Filestore files;          // �ļ��洢����
Shop1 shop1;              // �̵�1����
Shop2 shop2;              // �̵�2����
vector<Character*> enemies; // ���˽�ɫ�Ķ�̬����

// ��ʼ�����˽�ɫ
Character* smallen1 = new Character("����1", 40, 700, 700, 30, 90, 0.8, 0.05, 100, false);
Character* smallen2 = new Character("����2", 40, 700, 700, 30, 30, 0.8, 0.05, 100, false);
Character* bigen1 = new Character("��Ӫ", 40, 900, 900, 20, 40, 0.9, 0.1, 0, false);
Character* bigen2 = new Character("�", 40, 900, 1000, 30, 60, 0.85, 0.1, 0, false);
Character* bigen3 = new Character("½�ݺ�", 60, 1000, 1000, 40, 100, 0.85, 0.15, 0, false);

// ��ʼ������
Weapon weapon1("��", 20, 30, 10, 0.1, "ն��");
Weapon weapon2("��", 20, 34, 8, 0.11, "ն��");
Weapon weapon3("��", 20, 32, 10, 0.12, "���");
Weapon weapon4("ì", 20, 30, 11, 0.14, "��ͨ");
Weapon weapon5("��ǹ", 20, 28, 12, 0.15, "��ͨ");
Weapon dajian("��", 50, 40, 5, 0.1, "ն��");
Weapon tiegun("����", 50, 35, 10, 0.15, "���");
Weapon cijian("�̽�", 50, 30, 15, 0.2, "��ͨ");

// Ĭ������
Weapon weapon_default("�ֳ�Ļ�ǹ", 20, 30, 10, 0.1, "��ͨ");
Weapon lcwe[3]; // �ֳ����������

// ��ʼ������
Armor armor1("Ƥ��", 20, 25, 100, "ն��");
Armor armor2("���Ӽ�", 20, 30, 100, "��ͨ");
Armor armor3("���", 20, 35, 120, "���");
Armor armor_default("�ֳ�Ĳ���", 15, 20, 100, "ն��");

Armor bujia("����", 50, 25, 100, "��ͨ");
Armor tiejia("����", 100, 30, 120, "���");
Armor linjia("�ۼ�", 200, 35, 150, "ն��");

Armor lcar[3]; // �ֳ�Ļ�������

// ��ʼ����������
offensiveSkill skill_1("�������������˫ն", "�������6�Σ��Լ������½�", false, true, true, 0.7, "ն��", 6, selfDefenseBoost, 0.8, 3);
offensiveSkill skill_2("ǹ������", "���幥��5�Σ��Լ������½�", false, true, true, 0.8, "��ͨ", 5, selfAttackBoost, 0.8, 3);
offensiveSkill skill_3("�Ƿ�����", "�޶�ȫ�幥��������Լ�����", true, true, true, 3.4, "���", 1, selfDamage, 0.2, 0);
offensiveSkill skill_4("����֮��", "ȫ�幥��3��", true, true, true, 0.7, "ն��", 3, none, 0, 0);
offensiveSkill skill_5("������", "���鵥�����", false, true, false, 2.2, "���", 1, giveDefenseWeaken, 0.8, 3);
offensiveSkill skill_6("��ɨǧ��", "ȫ�幥��2��", true, true, true, 1.2, "��ͨ", 2, none, 0, 0);
offensiveSkill lcofsk[6]; // �ֳ�Ľ�����������

// ��ʼ��֧Ԯ����
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
supportSkill lcsusk[11]; // �ֳ��֧Ԯ��������

int main() {
    // ����ս��ϵͳ����
    int flag;

    // ���ű�������
    PlaySound(TEXT("309764634.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    // ���ֳ����Ĭ�ϵ����������׺ͼ���
    lc->addWeapon(&weapon_default);
    lc->addArmor(&armor_default);
    lc->addOffensiveSkill(&skill_4, false);
    lc->addOffensiveSkill(&skill_5, false);
    lc->addOffensiveSkill(&skill_6, false);

    // ��ʼ���û�����
    ui.ready();
    flag = ui.showstart(); // ��ʾ��ʼ���沢��ȡ�û�ѡ��

    // �����û�ѡ��ִ����Ӧ����
    if (flag == 2) {
        cout << "���ڼ���" << endl;
        // ������Ϸ�浵
        ready_save();
        we_read();
        ar_read();
        os_read();
        su_read();
        lc->loadFromFile("linchong.txt", lc);
        t = plot.loadTimeFromFile("time1.txt");
    }
    else if (flag == 3) {
        cout << "�����˳�" << endl;
        exit(1); // �˳�����
    }
    // ��������ϷʱΪ�ֳ�����Ĭ�����������׺���ʽ

   // ���о����ƽ���ֱ�� plottime ���� 10
    while (t.plottime <= 10)
    {
        switch (t.plottime)
        {
        case 1:
            // ��ӡ��ʾ��ǰ����Ҫ�͵�һĻ����
            plot.PrintPrompt(); // �� ctrl ����
            plot.PrintPrologue(); // ǰ����Ҫ
            plot.PrintScene(t.plottime); // ��һĻ
            change1(); // ִ��״̬�ı亯��
            break;

        case 2:
            // ��ӡ�ڶ�Ļ����
            plot.PrintScene(t.plottime); // �ڶ�Ļ
            change1(); // ִ��״̬�ı亯��
            break;

        case 3:
            if (t.day == 0)
            {
                // ��ӡ����Ļ����
                plot.PrintScene(t.plottime); // ����Ļ
            }
            runDevelopmentSystem(); // ��������ϵͳ
            change1(); // ִ��״̬�ı亯��
            break;

        case 4:
            // ��ӡ����Ļ����
            plot.PrintScene(t.plottime); // ����Ļ
            change1(); // ִ��״̬�ı亯��
            break;

        case 5:
            // ��ӡ����Ļ����
            plot.PrintScene(t.plottime); // ����Ļ
            change1(); // ִ��״̬�ı亯��
            break;

        case 6:
            // ��ӡ����Ļ��������ʾ��ͼ�����ı�ص�
            plot.PrintScene(t.plottime); // ����Ļ
            map1.showmap(lc->getPlace()); // ��ʾ��ͼ
            lc->changePlace(t.plottime); // �ı�ص�
            change1(); // ִ��״̬�ı亯��
            break;

        case 7:
            // ��ӡ����Ļ����������ս��ǰ׼�������ý�ɫ HP
            plot.PrintScene(t.plottime); // ����Ļ
            pre_battle2(enemies, lc, smallen1, smallen2); // ս��ǰ׼��
            plot.PrintScene11(); // ��ӡս������
            lc->setHP(lc->getMaxHP()); // ���� HP
            change1(); // ִ��״̬�ı亯��
            break;

        case 8:
            // ��ӡ�ڰ�Ļ����
            plot.PrintScene(t.plottime); // �ڰ�Ļ
            change1(); // ִ��״̬�ı亯��
            break;

        case 9:
            // ��ӡ�ھ�Ļ����������ս��ǰ׼��
            plot.PrintScene(t.plottime); // �ھ�Ļ
            pre_battle1(enemies, lc, bigen1, bigen2, bigen3); // ս��ǰ׼��
            change1(); // ִ��״̬�ı亯��
            break;

        case 10:
            // ��ӡ��ʮĻ���������������ƽ�
            plot.PrintScene(t.plottime); // ��ʮĻ
            ++t.plottime; // ���� plottime
            break;

        default:
            break;
        }
    }

    // ��Ϸ�������
    cout << "��Ϸ����" << endl;

    return 0;
}

// ��������ϵͳ
void runDevelopmentSystem()
{
    while (t.day <= 8) // �޸�Ϊ day <= 8��ȷ�� 8 �������ϵͳ
    {
        SetConsoleColor(7); // ���ÿ���̨��ɫ
        cout << "������ʮһ��";

        // ���� day ��ӡ��Ӧ�������ʽ
        switch (t.day)
        {
        case 1:
            cout << "���� (���������ʽ:" << skill_1.getName() << ")" << endl << endl;
            break;
        case 2:
            cout << "���� (���������ʽ:" << skill_2.getName() << " " << skill_8.getName() << ")" << endl << endl;
            break;
        case 3:
            cout << "���� (���������ʽ:" << skill_3.getName() << " " << skill_10.getName() << ")" << endl << endl;
            break;
        case 4:
            cout << "���� (���������ʽ:" << skill_13.getName() << " " << skill_15.getName() << ")" << endl << endl;
            break;
        case 5:
            cout << "ʮ�� (���������ʽ:" << skill_7.getName() << " " << skill_16.getName() << ")" << endl << endl;
            break;
        case 6:
            cout << "ʮһ (���������ʽ:" << skill_11.getName() << " " << skill_17.getName() << ")" << endl << endl;
            break;
        case 7:
            cout << "ʮ�� (���������ʽ:" << skill_9.getName() << " " << skill_14.getName() << ")" << endl << endl;
            break;
        case 8:
            cout << "ʮ�� (���������ʽ:" << skill_12.getName() << ")" << endl << endl;
            break;
        default:
            break;
        }

        // ��ʾ��ͼ�͸ı�ص�
        map1.showmap(lc->getPlace()); // ��ʾ��ͼ
        lc->changePlace(t.plottime); // �ı�ص�

        // ���ݵص�ִ����Ӧ����
        switch (lc->getPlace()) // 1��Ƶ꣬2��ݣ�3Ӫ��4���ϳ�5�о���6��ͷ��7����
        {
        case 1:
            shopset(linchong); // �̵�����
            ++t.day; // ���� day
            break;

        case 2:
            if (plot.handleTraining()) // �������ѵ��
            {
                switch (t.day)
                {
                case 1:
                    lc->addOffensiveSkill(&skill_1, true); // ��ӽ�������
                    break;
                case 2:
                    lc->addOffensiveSkill(&skill_2, true);
                    lc->addSupportSkill(&skill_8, true); // ���֧Ԯ����
                    break;
                case 3:
                    lc->addOffensiveSkill(&skill_3, true);
                    lc->addSupportSkill(&skill_10, true);
                    break;
                case 4:
                    lc->addSupportSkill(&skill_13, true);
                    lc->addSupportSkill(&skill_15, true);
                    break;
                case 5:
                    lc->addSupportSkill(&skill_7, true);
                    lc->addSupportSkill(&skill_16, true);
                    break;
                case 6:
                    lc->addSupportSkill(&skill_11, true);
                    lc->addSupportSkill(&skill_17, true);
                    break;
                case 7:
                    lc->addSupportSkill(&skill_9, true);
                    lc->addSupportSkill(&skill_14, true);
                    break;
                case 8:
                    lc->addSupportSkill(&skill_12, true); // ���֧Ԯ����
                    break;
                default:
                    break;
                }
            }
            ++t.day; // ���� day
            break;

        case 3:
            if (plot.handleBarracks() == 1) // �������Ӫ��
            {
                change2(); // ִ��״̬�ı亯��
            }
            break;

        case 6:
            plot.handleDock(); // ������ͷ
            ++t.day; // ���� day
            break;

        default:
            break;
        }
    }
}

// ׼��ս�� 1�����õ��˽�ɫ����װ�������ܣ�����ʼս��
void pre_battle1(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2, Character* character3)
{
    // ��յ����б�����������˽�ɫ
    enemies.clear();
    enemies.push_back(character1);
    enemies.push_back(character2);
    enemies.push_back(character3);

    // ���õ�һ�����˵����������׺ͼ���
    character1->addWeapon(&weapon1); // ���ն������
    character1->addArmor(&armor2); // ��ӹ�ͨ����
    character1->addOffensiveSkill(&skill_1, false); // ��ӽ������� 1
    character1->addOffensiveSkill(&skill_4, false); // ��ӽ������� 4
    character1->addSupportSkill(&skill_11, false); // ���֧Ԯ���� 11
    character1->addSupportSkill(&skill_8, false); // ���֧Ԯ���� 8

    // ���õڶ������˵����������׺ͼ���
    character2->addWeapon(&weapon5); // ��ӹ�ͨ����
    character2->addArmor(&armor3); // ��Ӵ������
    character2->addOffensiveSkill(&skill_6, false); // ��ӽ������� 6
    character2->addOffensiveSkill(&skill_2, false); // ��ӽ������� 2
    character2->addSupportSkill(&skill_10, false); // ���֧Ԯ���� 10
    character2->addSupportSkill(&skill_17, false); // ���֧Ԯ���� 17

    // ���õ��������˵����������׺ͼ���
    character3->addWeapon(&weapon3); // ��Ӵ������
    character3->addArmor(&armor1); // ���ն������
    character3->addOffensiveSkill(&skill_3, false); // ��ӽ������� 3
    character3->addOffensiveSkill(&skill_5, false); // ��ӽ������� 5
    character3->addSupportSkill(&skill_9, false); // ���֧Ԯ���� 9
    character3->addSupportSkill(&skill_7, false); // ���֧Ԯ���� 7

    // ����ս�����󲢿�ʼս��
    Battle battle_1;
    battle_1.startBattle(lc, &enemies);

    // ɾ�����˽�ɫ���ͷ��ڴ�
    delete character1;
    delete character2;
    delete character3;
}

// ׼��ս�� 2�����õ��˽�ɫ����װ�������ܣ�����ʼս��
void pre_battle2(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2)
{
    // ����������˽�ɫ
    enemies.push_back(character1);
    enemies.push_back(character2);

    // ���õ�һ�����˵����������׺ͼ���
    character1->addWeapon(&weapon1); // �������
    character1->addArmor(&armor3); // ��ӿ���
    character1->addOffensiveSkill(&skill_4, false); // ��ӽ������� 4
    character1->addSupportSkill(&skill_8, false); // ���֧Ԯ���� 8
    character1->addSupportSkill(&skill_12, false); // ���֧Ԯ���� 12

    // ���õڶ������˵����������׺ͼ���
    character2->addWeapon(&weapon5); // �������
    character2->addArmor(&armor1); // ��ӿ���
    character2->addOffensiveSkill(&skill_6, false); // ��ӽ������� 6
    character2->addSupportSkill(&skill_10, false); // ���֧Ԯ���� 10

    // ����ս�����󲢿�ʼս��
    Battle battle_1;
    battle_1.startBattle(lc, &enemies);

    // ɾ�����˽�ɫ���ͷ��ڴ�
    delete character1;
    delete character2;
}

// ״̬�ı亯�� 1������״̬�ı䲢���ܵݹ��������
void change1()
{
    // ��ȡ״̬�仯�Ľ��
    int f = plot.Printchange(t.plottime);
    int f_func = 0;

    if (f)
    {
        // ����״̬�仯�Ľ��ִ��״̬�ı亯�� 2
        f_func = change2();

        // ���״̬�ı亯�� 2 ���� 4����ݹ���� change1
        if (f_func == 4)
        {
            change1(); // �ݹ����
        }
    }
    else
    {
        return; // ���û��״̬�仯���򷵻�
    }
}

// ׼��������Ϸ����
void ready_save()
{
    // ��������
    lcwe[0] = dajian;
    lcwe[1] = tiegun;
    lcwe[2] = cijian;

    // ���ÿ���
    lcar[0] = bujia;
    lcar[1] = tiejia;
    lcar[2] = linjia;

    // ���ý�������
    lcofsk[0] = skill_1;
    lcofsk[1] = skill_2;
    lcofsk[2] = skill_3;

    // ����֧Ԯ����
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

// ״̬�ı亯�� 2�������û���ѡ��ִ�в�ͬ�Ĳ���
int change2()
{
    // ��ʾ�û�����˵�����ȡ�û�ѡ��
    int f = ui.showmenu();
    int f_func = 0;

    // ����û�ѡ���� 1����ʾ����
    if (f == 1)
    {
        ui.shuxing(lc); // ��ʾ��ɫ����
        change2(); // �ݹ���ã�������ʾ�˵�
    }

    // ����û�ѡ���� 2����ʾ����
    if (f == 2)
    {
        linchong.printWeapons(); // ��ӡ�����б�
        linchong.printArmors(); // ��ӡ�����б�
        change2(); // �ݹ���ã�������ʾ�˵�
    }

    // ����û�ѡ���� 3���浵
    if (f == 3)
    {
        // ������ɫ�Ŀ��ײ����±���Ŀ���״̬
        for (const auto& armor : *linchong.getArmors())
        {
            if (armor->getName() == "����") {
                bujia.be_get(); // ���²���״̬
            }
            if (armor->getName() == "����") {
                tiejia.be_get(); // ��������״̬
            }
            if (armor->getName() == "�ۼ�") {
                linjia.be_get(); // �����ۼ�״̬
            }
        }

        // ������ɫ�����������±��������״̬
        for (const auto& weapon : *linchong.getWeapons())
        {
            if (weapon->getName() == "����") {
                tiegun.be_get(); // ��������״̬
            }
            if (weapon->getName() == "�̽�") {
                cijian.be_get(); // ���´̽�״̬
            }
            if (weapon->getName() == "��") {
                dajian.be_get(); // ���´�״̬
            }
        }

        // ִ�б������
        ready_save(); // ׼����������
        we_save(); // ������������
        ar_save(); // �����������
        os_save(lcofsk); // ���������������
        su_save(lcsusk); // ����֧Ԯ��������
        lc->saveToFile("linchong.txt"); // �����ɫ���ݵ��ļ�
        plot.saveTimeToFile("time1.txt", t); // ����ʱ�����ݵ��ļ�

        change2(); // �ݹ���ã�������ʾ�˵�
    }

    // ����û�ѡ���� 4�������û�ѡ��
    if (f == 4)
        return f;
}

// �����������ݵ��ļ�
void we_save()
{
    std::ofstream outfile("weapon.txt", std::ios::out | std::ios::binary);

    // ����ļ��Ƿ�ɹ���
    if (!outfile) {
        std::cerr << "�޷����ļ���" << std::endl;
        return;
    }

    // �����������ڱ���������״̬
    int x[3];

    // ��ÿ��������״̬д������
    for (int i = 0; i < 3; i++)
    {
        x[i] = lcwe[i].get_ifget(); // ��ȡ������״̬
    }

    // ����������д���ļ�
    outfile.write(reinterpret_cast<char*>(x), 3 * sizeof(int));

    // �ر��ļ�
    outfile.close();

    std::cout << "�����ѱ��浽�ļ���" << std::endl;
}

// ���ļ���ȡ��������
void we_read()
{
    int size = 3;

    // ʹ��vector���洢��ȡ������
    std::vector<int> readArray(size);

    // ���ļ����ڶ�ȡ
    std::ifstream infile("weapon.txt", std::ios::in | std::ios::binary);

    // ����ļ��Ƿ�ɹ���
    if (!infile) {
        std::cerr << "�޷����ļ���" << std::endl;
        return;
    }

    // ��ȡ���ݵ�vector
    infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

    // �ر��ļ�
    infile.close();

    // ���ݶ�ȡ��״̬��������
    for (int i = 0; i < size; i++)
    {
        if (readArray[i])
        {
            lc->addWeapon(&lcwe[i]); // ��������ӵ���ɫ
            lcwe[i].be_get(); // ��������״̬
        }
    }
}

// ����������ݵ��ļ�
void ar_save()
{
    std::ofstream outfile("Armor.txt", std::ios::out | std::ios::binary);

    // ����ļ��Ƿ�ɹ���
    if (!outfile) {
        std::cerr << "�޷����ļ���" << std::endl;
        return;
    }

    // �����������ڱ�����׵�״̬
    int x[3];

    // ��ÿ�����׵�״̬д������
    for (int i = 0; i < 3; i++)
    {
        x[i] = lcar[i].get_ifget(); // ��ȡ���׵�״̬
    }

    // ����������д���ļ�
    outfile.write(reinterpret_cast<char*>(x), 3 * sizeof(int));

    // �ر��ļ�
    outfile.close();
    std::cout << "�����ѱ��浽�ļ���" << std::endl;
}

// ���ļ���ȡ��������
void ar_read()
{
    int size = 3;

    // ʹ��vector���洢��ȡ������
    std::vector<int> readArray(size);

    // ���ļ����ڶ�ȡ
    std::ifstream infile("Armor.txt", std::ios::in | std::ios::binary);

    // ����ļ��Ƿ�ɹ���
    if (!infile) {
        std::cerr << "�޷����ļ���" << std::endl;
        return;
    }

    // ��ȡ���ݵ�vector
    infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

    // �ر��ļ�
    infile.close();

    // ���ݶ�ȡ��״̬���¿���
    for (int i = 0; i < size; i++)
    {
        if (readArray[i])
            lc->addArmor(&lcar[i]); // ��������ӵ���ɫ
    }
}

// ��������������ݵ��ļ�
void os_save(offensiveSkill c[6])
{
    std::ofstream outfile("offensiveSkill.txt", std::ios::out | std::ios::binary);

    // ����ļ��Ƿ�ɹ���
    if (!outfile) {
        std::cerr << "�޷����ļ���" << std::endl;
        return;
    }

    // �����������ڱ���������ܵ�״̬
    int x[6];

    // ��ÿ���������ܵ�״̬д������
    for (int i = 0; i < 6; i++)
    {
        x[i] = c[i].get_ifget(); // ��ȡ�������ܵ�״̬
    }

    // ����������д���ļ�
    outfile.write(reinterpret_cast<char*>(x), 6 * sizeof(int));

    // �ر��ļ�
    outfile.close();
    std::cout << "���������ѱ��浽�ļ���" << std::endl;
}

// ���ļ���ȡ������������
void os_read()
{
    int size = 6;

    // ʹ��vector���洢��ȡ������
    std::vector<int> readArray(size);

    // ���ļ����ڶ�ȡ
    std::ifstream infile("offensiveSkill.txt", std::ios::in | std::ios::binary);

    // ����ļ��Ƿ�ɹ���
    if (!infile) {
        std::cerr << "�޷����ļ���" << std::endl;
        return;
    }

    // ��ȡ���ݵ�vector
    infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

    // �ر��ļ�
    infile.close();

    // ���ݶ�ȡ��״̬���½�������
    for (int i = 0; i < size; i++)
    {
        if (readArray[i])
            lc->addOffensiveSkill(&lcofsk[i], true); // ������������ӵ���ɫ
    }
}

// ��������������ݵ��ļ�
void su_save(supportSkill d[10])
{
    std::ofstream outfile("supportSkill.txt", std::ios::out | std::ios::binary);

    // ����ļ��Ƿ�ɹ���
    if (!outfile) {
        std::cerr << "�޷����ļ���" << std::endl;
        return;
    }

    // �����������ڱ���������ܵ�״̬
    int x[10];

    // ��ÿ���������ܵ�״̬д������
    for (int i = 0; i < 10; i++)
    {
        x[i] = d[i].get_ifget(); // ��ȡ�������ܵ�״̬
    }

    // ����������д���ļ�
    outfile.write(reinterpret_cast<char*>(x), 10 * sizeof(int));

    // �ر��ļ�
    outfile.close();
    std::cout << "���������ѱ��浽�ļ���" << std::endl;
}

// ���ļ���ȡ������������
void su_read()
{
    int size = 10;

    // ʹ��vector���洢��ȡ������
    std::vector<int> readArray(size);

    // ���ļ����ڶ�ȡ
    std::ifstream infile("supportSkill.txt", std::ios::in | std::ios::binary);

    // ����ļ��Ƿ�ɹ���
    if (!infile) {
        std::cerr << "�޷����ļ���" << std::endl;
        return;
    }

    // ��ȡ���ݵ�vector
    infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

    // �ر��ļ�
    infile.close();

    // ���ݶ�ȡ��״̬���·�������
    for (int i = 0; i < size; i++)
    {
        if (readArray[i])
            lc->addSupportSkill(&lcsusk[i], true); // ������������ӵ���ɫ
    }
}
// �����̵꣬�������û��Ĺ�������
void shopset(Linchong& linchong) {

    // ���̵�1���������
    shop1.addItem(make_unique<Weapon>(dajian)); // ��Ӵ�
    shop1.addItem(make_unique<Weapon>(tiegun)); // �������
    shop1.addItem(make_unique<Weapon>(cijian)); // ��Ӵ̽�

    // ���̵�2����ӷ���
    shop2.addItem(make_unique<Armor>(bujia)); // ��Ӳ���
    shop2.addItem(make_unique<Armor>(tiejia)); // �������
    shop2.addItem(make_unique<Armor>(linjia)); // ����ۼ�

    int n; // �û���ѡ��
    int id; // ��Ʒ�����

    // ��ʾ�̵껶ӭ��Ϣ
    plot.PrintWithDelay("��С��������һ�ߣ���һ�ƣ����������ʲô����\n", 30);

    // ��ʾ�̵����˵�
    cout << "0.�˳�          1.����           2.����" << endl;

    while (cin >> n) {
        // �����˳�ѡ��
        if (n == 0) {
            plot.PrintWithDelay("��С���������ϣ��������ߣ���\n", 30);
            break; // �˳�ѭ��
        }

        // ������������ѡ��
        if (n == 1) {
            shop1.listItems(); // �г��̵�1�е���������
            cout << "��ѡ����Ҫ������������,�˳�ѡ��0" << endl;

            while (cin >> id) {
                // �����˳�ѡ��
                if (id == 0) {
                    break; // �˳���������ѭ��
                }
                // ���Թ���ָ����ŵ���������Ŵ�1��ʼ��������Ҫ��1��
                if (shop1.buyItem(linchong, id - 1)) { // ���Թ�����Ʒ
                    shop1.listItems(); // �ٴ��г���Ʒ�Բ鿴�仯
                }
                cout << "��ѡ����Ҫ�����������ţ��˳�ѡ��0" << endl;
            }
        }

        // ��������ߵ�ѡ��
        if (n == 2) {
            shop2.listItems(); // �г��̵�2�е����з���
            cout << "��ѡ����Ҫ����ķ�����ţ��˳�ѡ��0" << endl;

            while (cin >> id) {
                // �����˳�ѡ��
                if (id == 0) {
                    break; // �˳����߹���ѭ��
                }
                // ���Թ���ָ����ŵķ��ߣ���Ŵ�1��ʼ��������Ҫ��1��
                if (shop2.buyItem(linchong, id - 1)) { // ���Թ�����Ʒ
                    shop2.listItems(); // �ٴ��г���Ʒ�Բ鿴�仯
                }
                cout << "��ѡ����Ҫ����ķ�����ţ��˳�ѡ��0" << endl;
            }
        }

        // ��ʾ�̵����˵�
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
