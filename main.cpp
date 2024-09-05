// MUD设计.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
void change1();//幕与幕之间衔接
int change2();


UI ui;
Map map1;
Linchong linchong("林冲", 80, 1000, 800, 10, 80, 0.8, 0.1, 0, true, 0);
Linchong* lc = &linchong;
Plot plot(lc);
Time t;
Filestore files;
int main(){
    //测试战斗系统________________
    vector<Character*> enemies;
    Character* character1 = new Character("宋江", 40, 1000, 1000, 40, 40, 0.8, 0.1, 0, false);
    Character* character2 = new Character("鲁智深", 40, 2000, 1000, 40, 40, 0.8, 0.1, 0, false);
    enemies.push_back(character1);
    enemies.push_back(character2);

    Weapon weapon1("剑", 20, 30, 10, 0.1, "斩击");
    Weapon weapon2("刀", 20, 30, 10, 0.1, "斩击");
    Weapon weapon3("棍", 20, 30, 10, 0.1, "打击");
    Weapon weapon4("矛", 20, 30, 10, 0.1, "贯通");
    Weapon weapon5("枪", 20, 30, 10, 0.1, "贯通");

    Armor armor1("防具1", 20, 30, 100, "斩击");
    Armor armor2("防具2", 20, 30, 100, "贯通");
    Armor armor3("防具3", 20, 30, 100, "打击");

    offensiveSkill skill_1("天上天下天地无双斩", "疯狂连击6次，自己防御下降", false, true, true, 0.7, "斩击", 6, selfDefenseBoost, 0.8, 3);
    offensiveSkill skill_2("百鸟朝凤", "单体攻击5次，自己攻击下降", false, true, true, 0.8, "贯通", 5, selfAttackBoost, 0.8, 3);
    offensiveSkill skill_3("巨人之战", "巨额全体攻击，损耗自己生命", true, true, true, 3.4, "打击", 1, selfDamage, 0.2, 0);
    offensiveSkill skill_4("光刃暴雨", "全体攻击3次", true, true, true, 0.7, "斩击", 3, none, 0, 0);
    offensiveSkill skill_5("粉碎打击", "粉碎单体防御", false, true, false, 2.2, "打击", 1, giveDefenseWeaken, 0.8, 3);
    offensiveSkill skill_6("横扫千军", "全体攻击2次", true, true, true, 1.2, "贯通", 2, none, 0, 0);

    supportSkill skill_7("睡觉", "恢复体力，自身陷入昏迷状态", false, false, true, selfComatose, 1, 3);
    supportSkill skill_8("蓄力", "下回合伤害猛增", false, false, true, selfCharge, 1, 1);
    supportSkill skill_9("看破", "识破攻击，不被击中弱点", false, false, true, selfAnticipate, 1, 1);
    supportSkill skill_10("剑舞", "自身攻击力上升", false, false, true, selfAttackBoost, 1.3, 3);
    supportSkill skill_11("铁壁", "自身防御上升", false, false, true, selfDefenseBoost, 1.3, 3);
    supportSkill skill_12("鹰眼", "自身命中率上升", false, false, true, selfHitRateBoost, 1.3, 3);
    supportSkill skill_13("跳舞", "自身回避率上升", false, false, true, selfEvationBoost, 1.3, 3);
    supportSkill skill_14("威吓", "敌人攻击力下降", true, false, false, giveAttackWeaken, 0.8, 3);
    supportSkill skill_15("泼沙", "敌人命中率下降", true, false, false, giveHitRateWeaken, 0.8, 3);
    supportSkill skill_16("摇篮曲", "可能时敌人昏迷", true, false, false, giveComatose, 0.75, 3);
    supportSkill skill_17("清除浓雾", "使敌人回避率下降", true, false, false, giveEvationWeaken, 0.7, 3);

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


   // ui.ready();
    //ui.showstart();//开始界面
   // plot.PrintPrompt();//按ctrl加速
   // plot.PrintPrologue();//前情提要
    //plot.PrintScene(t.plottime);//第一幕


    change1();
    shopset(linchong);
    change1();
    plot.PrintScene(3);

    return 0;

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
    
     if (f == 1)//显示属性
     {
         ui.shuxing(lc);
         change2();
     }
     if (f == 2)//显示背包
     {

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
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
