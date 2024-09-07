// MUD设计.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
#pragma comment(lib, "winmm.lib")  // 链接到winmm.lib
struct Time
{
    int plottime = 1;
    int day = 1;
};


void SetConsoleColor(int);
void shopset(Linchong &linchong);
void runDevelopmentSystem();//养成系统
void pre_battle1(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2,Character* character3);
void pre_battle2(vector<Character*>&enemies, Linchong* lc, Character* character1, Character* character2);//战斗系统准备
void change1();//幕与幕之间衔接
int change2();

    UI ui;
    Map map1;
    Linchong linchong("林冲", 80, 800, 800, 10, 80, 0.8, 0.1, 100, true, 100);
    Linchong* lc = &linchong;
    Plot plot(lc);
    Time t;
    Filestore files;
    Shop1 shop1;
    Shop2 shop2;
    vector<Character*> enemies;
    Character* smallen1 = new Character("土匪1", 10, 100, 100, 10, 10, 0.8, 0.01, 100, false);
    Character* smallen2 = new Character("土匪2", 10, 100, 100, 10, 10, 0.8, 0.01, 100, false);
    Character* bigen1 = new Character("管营", 40, 200, 200, 30, 20, 0.8, 0.01, 0, false);
    Character* bigen2 = new Character("差拨", 40, 200, 200, 30, 20, 0.8, 0.01, 0, false);
    Character* bigen3 = new Character("陆虞侯", 80, 500, 500, 50, 20, 0.8, 0.01, 0, false);

    Weapon weapon1("剑", 20, 30, 10, 0.1, "斩击");
    Weapon weapon2("刀", 20, 30, 10, 0.1, "斩击");
    Weapon weapon3("棍", 20, 30, 10, 0.1, "打击");
    Weapon weapon4("矛", 20, 30, 10, 0.1, "贯通");
    Weapon weapon5("花枪", 20, 30, 10, 0.1, "贯通");
    Weapon weapon_default("林冲的花枪", 20, 30, 10, 0.1, "贯通");

    Armor armor1("防具1", 20, 30, 100, "斩击");
    Armor armor2("防具2", 20, 30, 100, "贯通");
    Armor armor3("防具3", 20, 30, 100, "打击");
    Armor armor_default("林冲的布甲", 20, 30, 100, "斩击");

    offensiveSkill skill_1("刀光剑影", "疯狂连击6次，自己防御下降", false, true, true, 0.7, "斩击", 6, selfDefenseBoost, 0.8, 3);
    offensiveSkill skill_2("枪出如龙", "单体攻击5次，自己攻击下降", false, true, true, 0.8, "贯通", 5, selfAttackBoost, 0.8, 3);
    offensiveSkill skill_3("登锋陷阵", "巨额全体攻击，损耗自己生命", true, true, true, 3.4, "打击", 1, selfDamage, 0.2, 0);
    //offensiveSkill skill_4("光刃暴雨", "全体攻击3次", true, true, true, 0.7, "斩击", 3, none, 0, 0);
    //offensiveSkill skill_5("粉碎打击", "粉碎单体防御", false, true, false, 2.2, "打击", 1, giveDefenseWeaken, 0.8, 3);
    offensiveSkill skill_6("横扫千军", "全体攻击2次", true, true, true, 1.2, "贯通", 2, none, 0, 0);

    supportSkill skill_7("休养生息", "恢复体力，自身陷入昏迷状态", false, false, true, selfComatose, 1, 3);
    supportSkill skill_8("以逸待劳", "下回合伤害猛增", false, false, true, selfCharge, 1, 1);
    supportSkill skill_9("身经百战", "识破攻击，不被击中弱点", false, false, true, selfAnticipate, 1, 1);
    supportSkill skill_10("蓄势待发", "自身攻击力上升", false, false, true, selfAttackBoost, 1.3, 3);
    supportSkill skill_11("铜头铁臂", "自身防御上升", false, false, true, selfDefenseBoost, 1.3, 3);
    supportSkill skill_12("炯炯有神", "自身命中率上升", false, false, true, selfHitRateBoost, 1.3, 3);
    supportSkill skill_13("身轻如燕", "自身回避率上升", false, false, true, selfEvationBoost, 1.3, 3);
    //supportSkill skill_14("威吓", "敌人攻击力下降", true, false, false, giveAttackWeaken, 0.8, 3);
    //supportSkill skill_15("泼沙", "敌人命中率下降", true, false, false, giveHitRateWeaken, 0.8, 3);
    supportSkill skill_16("纵兵劫掠", "可能时敌人昏迷", true, false, false, giveComatose, 0.75, 3);
    supportSkill skill_17("破阵曲", "使敌人回避率下降", true, false, false, giveEvationWeaken, 0.7, 3);



int main(){
    //测试战斗系统________________
    //pre_battle(enemies,  lc, character1,character2);
    int flag;
    //PlaySound(TEXT("309764634.wav"), NULL, SND_FILENAME | SND_ASYNC);
    PlaySound(TEXT("309764634.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    lc->addWeapon(&weapon_default);//林冲添加默认武器
    lc->addArmor(&armor_default);//林冲添加默认装备
    // 这里可以添加你的主程序代码  
    // 由于使用了SND_ASYNC，所以音乐会在后台播放  
    // 如果你想让程序等待直到用户关闭，可以使用以下代码  

    ui.ready();
    flag=ui.showstart();//开始界面
    if (flag == 2)
    {
        cout << "正在加载" << endl;
        files.loadGame(linchong);
    }
    else if (flag == 3)
    {
        cout << "正在退出" << endl;
        exit(1);
    }
    while(t.plottime<=10)
    {
        switch (t.plottime)
        {
        case 1:
            plot.PrintPrompt();//按ctrl加速
            plot.PrintPrologue();//前情提要
            plot.PrintScene(t.plottime);//第一幕
            change1();
            break;
        case 2:
            plot.PrintScene(t.plottime);//第二幕
            
            change1(); 
            break;
        case 3:
            plot.PrintScene(t.plottime);//3
            change1();
            runDevelopmentSystem();//养成
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
            pre_battle2(enemies, lc, smallen1, smallen2);
            plot.PrintScene11();
            change1(); 
            break;
        case 7:
            plot.PrintScene(t.plottime);//7
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
    cout << "游戏结束" << endl;
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;

}














void runDevelopmentSystem() {
    while (t.day <= 8) { // 修改为day <= 8，确保8天的养成系统
        SetConsoleColor(7);
        cout << "现在是十一月";
        switch (t.day)
        {
        case 1:cout << "初六" << endl; break;
        case 2:cout << "初七" << endl; break;
        case 3:cout << "初八" << endl; break;
        case 4:cout << "初九" << endl; break;
        case 5:cout << "十日" << endl; break;
        case 6:cout << "十一" << endl; break;
        case 7:cout << "十二" << endl; break;
        case 8:cout << "十三" << endl; break;
        default:
            break;
        }
        map1.showmap(lc->getPlace());
        lc->changePlace(t.plottime);
        switch (lc->getPlace())//1茶酒店，2武馆，3营房4草料场5市井，6码头，7古庙
        {
        case 1:
            shopset(linchong); ++t.day; break;
        case 2:
            if (plot.handleTraining())
            {
                switch (t.day)
                {
                case 1:
                    lc->addOffensiveSkill(&skill_1); break;
                case 2:
                    lc->addOffensiveSkill(&skill_2); lc->addSupportSkill(&skill_11); break;
                case 3:
                    lc->addOffensiveSkill(&skill_3); lc->addSupportSkill(&skill_12); break;
                case 4:
                    lc->addOffensiveSkill(&skill_6); lc->addSupportSkill(&skill_13); break;
                case 5:
                    lc->addSupportSkill(&skill_7); lc->addSupportSkill(&skill_16); break;
                case 6:
                    lc->addSupportSkill(&skill_8); lc->addSupportSkill(&skill_17); break;
                case 7:
                    lc->addSupportSkill(&skill_9); break;
                case 8:
                    lc->addSupportSkill(&skill_10); break;
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
        //plot.PrintWithDelay("请输入下面的标号：\n可选项：1.武馆（提升武力）\n2.商店（酒，牛肉，刀，枪，弓箭，鲁智深的禅杖，杨志的戒刀）\n3.码头（运货赚钱,钱可以用来购买商店中的武器和防具）\n4.营房（提升体力）\n", 30);
        
    }
}

void pre_battle1(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2, Character* character3)
{
    enemies.push_back(character1);
    enemies.push_back(character2);
    enemies.push_back(character3);

    character1->addWeapon(&weapon1);
    character1->addArmor(&armor1);
    character1->addOffensiveSkill(&skill_1);
    character1->addSupportSkill(&skill_8);

    character2->addWeapon(&weapon5);
    character2->addArmor(&armor2);
    character2->addOffensiveSkill(&skill_6);
    character2->addSupportSkill(&skill_10);

    character3->addWeapon(&weapon4);
    character3->addArmor(&armor3);
    character3->addOffensiveSkill(&skill_3);
    character3->addSupportSkill(&skill_9);
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
    
     if (f == 1)//显示属性
     {
         ui.shuxing(lc);
         change2();
     }
     if (f == 2)//显示背包
     {
         linchong.printWeapons();
         linchong.printArmors();
         change2();
     }
     if (f == 3)//存档
     {
         files.saveGame(linchong);
         change2();
     }
     if (f == 4)
        return f;
  }
 void shopset(Linchong& linchong) {

     Weapon dajian("大剑", 50, 300, 0, 0.4, "斩击");
     Weapon tiegun("铁棍", 50, 200, 5, 0.6, "打击");
     Weapon cijian("刺剑", 50, 110, 10, 1, "贯通");
     Armor bujia("布甲", 50, 50, 100, "贯通");
     Armor tiejia("铁甲", 100, 100, 200, "打击");
     Armor linjia("鳞甲", 200, 200, 400, "斩击");


     shop1.addItem(make_unique<Weapon>(dajian));
     shop1.addItem(make_unique<Weapon>(tiegun));
     shop1.addItem(make_unique<Weapon>(cijian));
     shop2.addItem(make_unique<Armor>(bujia));
     shop2.addItem(make_unique<Armor>(tiejia));
     shop2.addItem(make_unique<Armor>(linjia));

     int n;
     int id;
     plot.PrintWithDelay("李小二：“走一走，瞧一瞧！恩人您买点什么？”\n", 30);
     cout << "0.退出          1.武器           2.防具" << endl;
     while (cin >> n) {
         if (n == 0) {
             plot.PrintWithDelay("李小二：“好嘞！恩人慢走！”\n", 30);
             break;
         }
         if (n == 1) {
             shop1.listItems();
             cout << "请选择你要购买的武器序号,退出选择0" << endl;
             while (cin >> id) {
                 // 尝试购买物品  
                 if (id == 0) {
                     break;
                 }
                 if (shop1.buyItem(linchong, id - 1)) { // 尝试购买索引为0的物品（Sword）  
                     shop1.listItems(); // 再次列出物品以查看变化  
                 }
                 cout << "请选择你要购买的武器序号，退出选择0" << endl;
             }
         }
         if (n == 2) {
             shop2.listItems();
             cout << "请选择你要购买的防具序号，退出选择0" << endl;
             while (cin >> id) {
                 // 尝试购买物品  
                 if (id == 0) {
                     break;
                 }
                 if (shop2.buyItem(linchong, id - 1)) { // 尝试购买索引为0的物品（Sword）  
                     shop2.listItems(); // 再次列出物品以查看变化  
                 }
                 cout << "请选择你要购买的防具序号，退出选择0" << endl;
             }
         }
         cout << "0.退出          1.武器           2.防具" << endl;
     }

 }

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
