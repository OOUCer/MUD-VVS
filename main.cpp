// MUD设计.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include "battle.h"      // 包含战斗系统相关的头文件
#include "map11.h"       // 包含地图相关的头文件
#include "plot.h"        // 包含剧情相关的头文件
#include "UI.h"          // 包含用户界面相关的头文件
#include "Filestore.h"   // 包含文件存储相关的头文件
#include "shop.h"        // 包含商店相关的头文件
#include <windows.h>  
#include <mmsystem.h>  
#pragma comment(lib, "winmm.lib")  // 链接到 winmm.lib，用于播放音效

// 函数声明
void SetConsoleColor(int);
void shopset(Linchong& linchong);
void runDevelopmentSystem(); // 养成系统
void pre_battle1(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2, Character* character3);
void pre_battle2(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2); // 战斗系统准备
void change1(); // 幕与幕之间衔接
void ready_save(); // 准备保存游戏
int change2(); // 改变游戏状态

void we_save(); // 保存武器
void we_read(); // 读取武器
void ar_save(); // 保存护甲
void ar_read(); // 读取护甲
void os_save(offensiveSkill[6]); // 保存进攻技能
void os_read(); // 读取进攻技能
void su_save(supportSkill[11]); // 保存支援技能
void su_read(); // 读取支援技能

// 全局对象和变量初始化
UI ui;                      // 用户界面对象
Map map1;                   // 地图对象
Linchong linchong("林冲", 80, 800, 800, 10, 80, 0.8, 0.1, 100, true, 100); // 林冲角色对象
Linchong* lc = &linchong;  // 指向林冲的指针
Plot plot(lc);            // 剧情对象
Time t;                   // 时间对象
Filestore files;          // 文件存储对象
Shop1 shop1;              // 商店1对象
Shop2 shop2;              // 商店2对象
vector<Character*> enemies; // 敌人角色的动态数组

// 初始化敌人角色
Character* smallen1 = new Character("土匪1", 40, 700, 700, 30, 90, 0.8, 0.05, 100, false);
Character* smallen2 = new Character("土匪2", 40, 700, 700, 30, 30, 0.8, 0.05, 100, false);
Character* bigen1 = new Character("管营", 40, 900, 900, 20, 40, 0.9, 0.1, 0, false);
Character* bigen2 = new Character("差拨", 40, 900, 1000, 30, 60, 0.85, 0.1, 0, false);
Character* bigen3 = new Character("陆虞侯", 60, 1000, 1000, 40, 100, 0.85, 0.15, 0, false);

// 初始化武器
Weapon weapon1("剑", 20, 30, 10, 0.1, "斩击");
Weapon weapon2("刀", 20, 34, 8, 0.11, "斩击");
Weapon weapon3("棍", 20, 32, 10, 0.12, "打击");
Weapon weapon4("矛", 20, 30, 11, 0.14, "贯通");
Weapon weapon5("花枪", 20, 28, 12, 0.15, "贯通");
Weapon dajian("大剑", 50, 40, 5, 0.1, "斩击");
Weapon tiegun("铁棍", 50, 35, 10, 0.15, "打击");
Weapon cijian("刺剑", 50, 30, 15, 0.2, "贯通");

// 默认武器
Weapon weapon_default("林冲的花枪", 20, 30, 10, 0.1, "贯通");
Weapon lcwe[3]; // 林冲的武器数组

// 初始化护甲
Armor armor1("皮甲", 20, 25, 100, "斩击");
Armor armor2("锁子甲", 20, 30, 100, "贯通");
Armor armor3("板甲", 20, 35, 120, "打击");
Armor armor_default("林冲的布甲", 15, 20, 100, "斩击");

Armor bujia("布甲", 50, 25, 100, "贯通");
Armor tiejia("铁甲", 100, 30, 120, "打击");
Armor linjia("鳞甲", 200, 35, 150, "斩击");

Armor lcar[3]; // 林冲的护甲数组

// 初始化进攻技能
offensiveSkill skill_1("天上天下天地无双斩", "疯狂连击6次，自己防御下降", false, true, true, 0.7, "斩击", 6, selfDefenseBoost, 0.8, 3);
offensiveSkill skill_2("枪出如龙", "单体攻击5次，自己攻击下降", false, true, true, 0.8, "贯通", 5, selfAttackBoost, 0.8, 3);
offensiveSkill skill_3("登锋陷阵", "巨额全体攻击，损耗自己生命", true, true, true, 3.4, "打击", 1, selfDamage, 0.2, 0);
offensiveSkill skill_4("刀刃之云", "全体攻击3次", true, true, true, 0.7, "斩击", 3, none, 0, 0);
offensiveSkill skill_5("粉碎打击", "粉碎单体防御", false, true, false, 2.2, "打击", 1, giveDefenseWeaken, 0.8, 3);
offensiveSkill skill_6("横扫千军", "全体攻击2次", true, true, true, 1.2, "贯通", 2, none, 0, 0);
offensiveSkill lcofsk[6]; // 林冲的进攻技能数组

// 初始化支援技能
supportSkill skill_7("休养生息", "恢复体力，自身陷入昏迷状态", false, false, true, selfComatose, 1, 3);
supportSkill skill_8("以逸待劳", "下回合伤害猛增", false, false, true, selfCharge, 1, 1);
supportSkill skill_9("身经百战", "识破攻击，不被击中弱点", false, false, true, selfAnticipate, 1, 1);
supportSkill skill_10("蓄势待发", "自身攻击力上升", false, false, true, selfAttackBoost, 1.3, 3);
supportSkill skill_11("铜头铁臂", "自身防御上升", false, false, true, selfDefenseBoost, 1.3, 3);
supportSkill skill_12("炯炯有神", "自身命中率上升", false, false, true, selfHitRateBoost, 1.3, 3);
supportSkill skill_13("身轻如燕", "自身回避率上升", false, false, true, selfEvationBoost, 1.3, 3);
supportSkill skill_14("威吓", "敌人攻击力下降", true, false, false, giveAttackWeaken, 0.8, 3);
supportSkill skill_15("泼沙", "敌人命中率下降", true, false, false, giveHitRateWeaken, 0.8, 3);
supportSkill skill_16("纵兵劫掠", "可能时敌人昏迷", true, false, false, giveComatose, 0.75, 3);
supportSkill skill_17("破阵曲", "使敌人回避率下降", true, false, false, giveEvationWeaken, 0.7, 3);
supportSkill lcsusk[11]; // 林冲的支援技能数组

int main() {
    // 测试战斗系统部分
    int flag;

    // 播放背景音乐
    PlaySound(TEXT("309764634.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    // 给林冲添加默认的武器、护甲和技能
    lc->addWeapon(&weapon_default);
    lc->addArmor(&armor_default);
    lc->addOffensiveSkill(&skill_4, false);
    lc->addOffensiveSkill(&skill_5, false);
    lc->addOffensiveSkill(&skill_6, false);

    // 初始化用户界面
    ui.ready();
    flag = ui.showstart(); // 显示开始界面并获取用户选择

    // 根据用户选择执行相应操作
    if (flag == 2) {
        cout << "正在加载" << endl;
        // 加载游戏存档
        ready_save();
        we_read();
        ar_read();
        os_read();
        su_read();
        lc->loadFromFile("linchong.txt", lc);
        t = plot.loadTimeFromFile("time1.txt");
    }
    else if (flag == 3) {
        cout << "正在退出" << endl;
        exit(1); // 退出程序
    }
    // 开启新游戏时为林冲设置默认武器、护甲和招式

   // 进行剧情推进，直到 plottime 大于 10
    while (t.plottime <= 10)
    {
        switch (t.plottime)
        {
        case 1:
            // 打印提示、前情提要和第一幕场景
            plot.PrintPrompt(); // 按 ctrl 加速
            plot.PrintPrologue(); // 前情提要
            plot.PrintScene(t.plottime); // 第一幕
            change1(); // 执行状态改变函数
            break;

        case 2:
            // 打印第二幕场景
            plot.PrintScene(t.plottime); // 第二幕
            change1(); // 执行状态改变函数
            break;

        case 3:
            if (t.day == 0)
            {
                // 打印第三幕场景
                plot.PrintScene(t.plottime); // 第三幕
            }
            runDevelopmentSystem(); // 运行养成系统
            change1(); // 执行状态改变函数
            break;

        case 4:
            // 打印第四幕场景
            plot.PrintScene(t.plottime); // 第四幕
            change1(); // 执行状态改变函数
            break;

        case 5:
            // 打印第五幕场景
            plot.PrintScene(t.plottime); // 第五幕
            change1(); // 执行状态改变函数
            break;

        case 6:
            // 打印第六幕场景，显示地图，并改变地点
            plot.PrintScene(t.plottime); // 第六幕
            map1.showmap(lc->getPlace()); // 显示地图
            lc->changePlace(t.plottime); // 改变地点
            change1(); // 执行状态改变函数
            break;

        case 7:
            // 打印第七幕场景，进行战斗前准备，重置角色 HP
            plot.PrintScene(t.plottime); // 第七幕
            pre_battle2(enemies, lc, smallen1, smallen2); // 战斗前准备
            plot.PrintScene11(); // 打印战斗场景
            lc->setHP(lc->getMaxHP()); // 重置 HP
            change1(); // 执行状态改变函数
            break;

        case 8:
            // 打印第八幕场景
            plot.PrintScene(t.plottime); // 第八幕
            change1(); // 执行状态改变函数
            break;

        case 9:
            // 打印第九幕场景，进行战斗前准备
            plot.PrintScene(t.plottime); // 第九幕
            pre_battle1(enemies, lc, bigen1, bigen2, bigen3); // 战斗前准备
            change1(); // 执行状态改变函数
            break;

        case 10:
            // 打印第十幕场景，结束剧情推进
            plot.PrintScene(t.plottime); // 第十幕
            ++t.plottime; // 增加 plottime
            break;

        default:
            break;
        }
    }

    // 游戏结束输出
    cout << "游戏结束" << endl;

    return 0;
}

// 运行养成系统
void runDevelopmentSystem()
{
    while (t.day <= 8) // 修改为 day <= 8，确保 8 天的养成系统
    {
        SetConsoleColor(7); // 设置控制台颜色
        cout << "现在是十一月";

        // 根据 day 打印相应的武馆招式
        switch (t.day)
        {
        case 1:
            cout << "初六 (今日武馆招式:" << skill_1.getName() << ")" << endl << endl;
            break;
        case 2:
            cout << "初七 (今日武馆招式:" << skill_2.getName() << " " << skill_8.getName() << ")" << endl << endl;
            break;
        case 3:
            cout << "初八 (今日武馆招式:" << skill_3.getName() << " " << skill_10.getName() << ")" << endl << endl;
            break;
        case 4:
            cout << "初九 (今日武馆招式:" << skill_13.getName() << " " << skill_15.getName() << ")" << endl << endl;
            break;
        case 5:
            cout << "十日 (今日武馆招式:" << skill_7.getName() << " " << skill_16.getName() << ")" << endl << endl;
            break;
        case 6:
            cout << "十一 (今日武馆招式:" << skill_11.getName() << " " << skill_17.getName() << ")" << endl << endl;
            break;
        case 7:
            cout << "十二 (今日武馆招式:" << skill_9.getName() << " " << skill_14.getName() << ")" << endl << endl;
            break;
        case 8:
            cout << "十三 (今日武馆招式:" << skill_12.getName() << ")" << endl << endl;
            break;
        default:
            break;
        }

        // 显示地图和改变地点
        map1.showmap(lc->getPlace()); // 显示地图
        lc->changePlace(t.plottime); // 改变地点

        // 根据地点执行相应操作
        switch (lc->getPlace()) // 1茶酒店，2武馆，3营房4草料场5市井，6码头，7古庙
        {
        case 1:
            shopset(linchong); // 商店设置
            ++t.day; // 增加 day
            break;

        case 2:
            if (plot.handleTraining()) // 如果处理训练
            {
                switch (t.day)
                {
                case 1:
                    lc->addOffensiveSkill(&skill_1, true); // 添加进攻技能
                    break;
                case 2:
                    lc->addOffensiveSkill(&skill_2, true);
                    lc->addSupportSkill(&skill_8, true); // 添加支援技能
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
                    lc->addSupportSkill(&skill_12, true); // 添加支援技能
                    break;
                default:
                    break;
                }
            }
            ++t.day; // 增加 day
            break;

        case 3:
            if (plot.handleBarracks() == 1) // 如果处理营房
            {
                change2(); // 执行状态改变函数
            }
            break;

        case 6:
            plot.handleDock(); // 处理码头
            ++t.day; // 增加 day
            break;

        default:
            break;
        }
    }
}

// 准备战斗 1：设置敌人角色及其装备、技能，并开始战斗
void pre_battle1(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2, Character* character3)
{
    // 清空敌人列表并添加三个敌人角色
    enemies.clear();
    enemies.push_back(character1);
    enemies.push_back(character2);
    enemies.push_back(character3);

    // 配置第一个敌人的武器、盔甲和技能
    character1->addWeapon(&weapon1); // 添加斩击武器
    character1->addArmor(&armor2); // 添加贯通盔甲
    character1->addOffensiveSkill(&skill_1, false); // 添加进攻技能 1
    character1->addOffensiveSkill(&skill_4, false); // 添加进攻技能 4
    character1->addSupportSkill(&skill_11, false); // 添加支援技能 11
    character1->addSupportSkill(&skill_8, false); // 添加支援技能 8

    // 配置第二个敌人的武器、盔甲和技能
    character2->addWeapon(&weapon5); // 添加贯通武器
    character2->addArmor(&armor3); // 添加打击盔甲
    character2->addOffensiveSkill(&skill_6, false); // 添加进攻技能 6
    character2->addOffensiveSkill(&skill_2, false); // 添加进攻技能 2
    character2->addSupportSkill(&skill_10, false); // 添加支援技能 10
    character2->addSupportSkill(&skill_17, false); // 添加支援技能 17

    // 配置第三个敌人的武器、盔甲和技能
    character3->addWeapon(&weapon3); // 添加打击武器
    character3->addArmor(&armor1); // 添加斩击盔甲
    character3->addOffensiveSkill(&skill_3, false); // 添加进攻技能 3
    character3->addOffensiveSkill(&skill_5, false); // 添加进攻技能 5
    character3->addSupportSkill(&skill_9, false); // 添加支援技能 9
    character3->addSupportSkill(&skill_7, false); // 添加支援技能 7

    // 创建战斗对象并开始战斗
    Battle battle_1;
    battle_1.startBattle(lc, &enemies);

    // 删除敌人角色以释放内存
    delete character1;
    delete character2;
    delete character3;
}

// 准备战斗 2：设置敌人角色及其装备、技能，并开始战斗
void pre_battle2(vector<Character*>& enemies, Linchong* lc, Character* character1, Character* character2)
{
    // 添加两个敌人角色
    enemies.push_back(character1);
    enemies.push_back(character2);

    // 配置第一个敌人的武器、盔甲和技能
    character1->addWeapon(&weapon1); // 添加武器
    character1->addArmor(&armor3); // 添加盔甲
    character1->addOffensiveSkill(&skill_4, false); // 添加进攻技能 4
    character1->addSupportSkill(&skill_8, false); // 添加支援技能 8
    character1->addSupportSkill(&skill_12, false); // 添加支援技能 12

    // 配置第二个敌人的武器、盔甲和技能
    character2->addWeapon(&weapon5); // 添加武器
    character2->addArmor(&armor1); // 添加盔甲
    character2->addOffensiveSkill(&skill_6, false); // 添加进攻技能 6
    character2->addSupportSkill(&skill_10, false); // 添加支援技能 10

    // 创建战斗对象并开始战斗
    Battle battle_1;
    battle_1.startBattle(lc, &enemies);

    // 删除敌人角色以释放内存
    delete character1;
    delete character2;
}

// 状态改变函数 1：处理状态改变并可能递归调用自身
void change1()
{
    // 获取状态变化的结果
    int f = plot.Printchange(t.plottime);
    int f_func = 0;

    if (f)
    {
        // 根据状态变化的结果执行状态改变函数 2
        f_func = change2();

        // 如果状态改变函数 2 返回 4，则递归调用 change1
        if (f_func == 4)
        {
            change1(); // 递归调用
        }
    }
    else
    {
        return; // 如果没有状态变化，则返回
    }
}

// 准备保存游戏数据
void ready_save()
{
    // 设置武器
    lcwe[0] = dajian;
    lcwe[1] = tiegun;
    lcwe[2] = cijian;

    // 设置盔甲
    lcar[0] = bujia;
    lcar[1] = tiejia;
    lcar[2] = linjia;

    // 设置进攻技能
    lcofsk[0] = skill_1;
    lcofsk[1] = skill_2;
    lcofsk[2] = skill_3;

    // 设置支援技能
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

// 状态改变函数 2：根据用户的选择执行不同的操作
int change2()
{
    // 显示用户界面菜单并获取用户选择
    int f = ui.showmenu();
    int f_func = 0;

    // 如果用户选择了 1：显示属性
    if (f == 1)
    {
        ui.shuxing(lc); // 显示角色属性
        change2(); // 递归调用，继续显示菜单
    }

    // 如果用户选择了 2：显示背包
    if (f == 2)
    {
        linchong.printWeapons(); // 打印武器列表
        linchong.printArmors(); // 打印盔甲列表
        change2(); // 递归调用，继续显示菜单
    }

    // 如果用户选择了 3：存档
    if (f == 3)
    {
        // 遍历角色的盔甲并更新保存的盔甲状态
        for (const auto& armor : *linchong.getArmors())
        {
            if (armor->getName() == "布甲") {
                bujia.be_get(); // 更新布甲状态
            }
            if (armor->getName() == "铁甲") {
                tiejia.be_get(); // 更新铁甲状态
            }
            if (armor->getName() == "鳞甲") {
                linjia.be_get(); // 更新鳞甲状态
            }
        }

        // 遍历角色的武器并更新保存的武器状态
        for (const auto& weapon : *linchong.getWeapons())
        {
            if (weapon->getName() == "铁棍") {
                tiegun.be_get(); // 更新铁棍状态
            }
            if (weapon->getName() == "刺剑") {
                cijian.be_get(); // 更新刺剑状态
            }
            if (weapon->getName() == "大剑") {
                dajian.be_get(); // 更新大剑状态
            }
        }

        // 执行保存操作
        ready_save(); // 准备保存数据
        we_save(); // 保存武器数据
        ar_save(); // 保存盔甲数据
        os_save(lcofsk); // 保存进攻技能数据
        su_save(lcsusk); // 保存支援技能数据
        lc->saveToFile("linchong.txt"); // 保存角色数据到文件
        plot.saveTimeToFile("time1.txt", t); // 保存时间数据到文件

        change2(); // 递归调用，继续显示菜单
    }

    // 如果用户选择了 4：返回用户选择
    if (f == 4)
        return f;
}

// 保存武器数据到文件
void we_save()
{
    std::ofstream outfile("weapon.txt", std::ios::out | std::ios::binary);

    // 检查文件是否成功打开
    if (!outfile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    // 创建数组用于保存武器的状态
    int x[3];

    // 将每个武器的状态写入数组
    for (int i = 0; i < 3; i++)
    {
        x[i] = lcwe[i].get_ifget(); // 获取武器的状态
    }

    // 将数组数据写入文件
    outfile.write(reinterpret_cast<char*>(x), 3 * sizeof(int));

    // 关闭文件
    outfile.close();

    std::cout << "武器已保存到文件。" << std::endl;
}

// 从文件读取武器数据
void we_read()
{
    int size = 3;

    // 使用vector来存储读取的数据
    std::vector<int> readArray(size);

    // 打开文件用于读取
    std::ifstream infile("weapon.txt", std::ios::in | std::ios::binary);

    // 检查文件是否成功打开
    if (!infile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    // 读取数据到vector
    infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

    // 关闭文件
    infile.close();

    // 根据读取的状态更新武器
    for (int i = 0; i < size; i++)
    {
        if (readArray[i])
        {
            lc->addWeapon(&lcwe[i]); // 将武器添加到角色
            lcwe[i].be_get(); // 更新武器状态
        }
    }
}

// 保存盔甲数据到文件
void ar_save()
{
    std::ofstream outfile("Armor.txt", std::ios::out | std::ios::binary);

    // 检查文件是否成功打开
    if (!outfile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    // 创建数组用于保存盔甲的状态
    int x[3];

    // 将每个盔甲的状态写入数组
    for (int i = 0; i < 3; i++)
    {
        x[i] = lcar[i].get_ifget(); // 获取盔甲的状态
    }

    // 将数组数据写入文件
    outfile.write(reinterpret_cast<char*>(x), 3 * sizeof(int));

    // 关闭文件
    outfile.close();
    std::cout << "护甲已保存到文件。" << std::endl;
}

// 从文件读取盔甲数据
void ar_read()
{
    int size = 3;

    // 使用vector来存储读取的数据
    std::vector<int> readArray(size);

    // 打开文件用于读取
    std::ifstream infile("Armor.txt", std::ios::in | std::ios::binary);

    // 检查文件是否成功打开
    if (!infile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    // 读取数据到vector
    infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

    // 关闭文件
    infile.close();

    // 根据读取的状态更新盔甲
    for (int i = 0; i < size; i++)
    {
        if (readArray[i])
            lc->addArmor(&lcar[i]); // 将盔甲添加到角色
    }
}

// 保存进攻技能数据到文件
void os_save(offensiveSkill c[6])
{
    std::ofstream outfile("offensiveSkill.txt", std::ios::out | std::ios::binary);

    // 检查文件是否成功打开
    if (!outfile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    // 创建数组用于保存进攻技能的状态
    int x[6];

    // 将每个进攻技能的状态写入数组
    for (int i = 0; i < 6; i++)
    {
        x[i] = c[i].get_ifget(); // 获取进攻技能的状态
    }

    // 将数组数据写入文件
    outfile.write(reinterpret_cast<char*>(x), 6 * sizeof(int));

    // 关闭文件
    outfile.close();
    std::cout << "攻击技能已保存到文件。" << std::endl;
}

// 从文件读取进攻技能数据
void os_read()
{
    int size = 6;

    // 使用vector来存储读取的数据
    std::vector<int> readArray(size);

    // 打开文件用于读取
    std::ifstream infile("offensiveSkill.txt", std::ios::in | std::ios::binary);

    // 检查文件是否成功打开
    if (!infile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    // 读取数据到vector
    infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

    // 关闭文件
    infile.close();

    // 根据读取的状态更新进攻技能
    for (int i = 0; i < size; i++)
    {
        if (readArray[i])
            lc->addOffensiveSkill(&lcofsk[i], true); // 将进攻技能添加到角色
    }
}

// 保存防御技能数据到文件
void su_save(supportSkill d[10])
{
    std::ofstream outfile("supportSkill.txt", std::ios::out | std::ios::binary);

    // 检查文件是否成功打开
    if (!outfile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    // 创建数组用于保存防御技能的状态
    int x[10];

    // 将每个防御技能的状态写入数组
    for (int i = 0; i < 10; i++)
    {
        x[i] = d[i].get_ifget(); // 获取防御技能的状态
    }

    // 将数组数据写入文件
    outfile.write(reinterpret_cast<char*>(x), 10 * sizeof(int));

    // 关闭文件
    outfile.close();
    std::cout << "防御技能已保存到文件。" << std::endl;
}

// 从文件读取防御技能数据
void su_read()
{
    int size = 10;

    // 使用vector来存储读取的数据
    std::vector<int> readArray(size);

    // 打开文件用于读取
    std::ifstream infile("supportSkill.txt", std::ios::in | std::ios::binary);

    // 检查文件是否成功打开
    if (!infile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    // 读取数据到vector
    infile.read(reinterpret_cast<char*>(readArray.data()), size * sizeof(int));

    // 关闭文件
    infile.close();

    // 根据读取的状态更新防御技能
    for (int i = 0; i < size; i++)
    {
        if (readArray[i])
            lc->addSupportSkill(&lcsusk[i], true); // 将防御技能添加到角色
    }
}
// 设置商店，并处理用户的购买请求
void shopset(Linchong& linchong) {

    // 向商店1中添加武器
    shop1.addItem(make_unique<Weapon>(dajian)); // 添加大剑
    shop1.addItem(make_unique<Weapon>(tiegun)); // 添加铁棍
    shop1.addItem(make_unique<Weapon>(cijian)); // 添加刺剑

    // 向商店2中添加防具
    shop2.addItem(make_unique<Armor>(bujia)); // 添加布甲
    shop2.addItem(make_unique<Armor>(tiejia)); // 添加铁甲
    shop2.addItem(make_unique<Armor>(linjia)); // 添加鳞甲

    int n; // 用户的选择
    int id; // 物品的序号

    // 显示商店欢迎信息
    plot.PrintWithDelay("李小二：“走一走，瞧一瞧！恩人您买点什么？”\n", 30);

    // 显示商店主菜单
    cout << "0.退出          1.武器           2.防具" << endl;

    while (cin >> n) {
        // 处理退出选项
        if (n == 0) {
            plot.PrintWithDelay("李小二：“好嘞！恩人慢走！”\n", 30);
            break; // 退出循环
        }

        // 处理购买武器的选项
        if (n == 1) {
            shop1.listItems(); // 列出商店1中的所有武器
            cout << "请选择你要购买的武器序号,退出选择0" << endl;

            while (cin >> id) {
                // 处理退出选项
                if (id == 0) {
                    break; // 退出武器购买循环
                }
                // 尝试购买指定序号的武器（序号从1开始，所以需要减1）
                if (shop1.buyItem(linchong, id - 1)) { // 尝试购买物品
                    shop1.listItems(); // 再次列出物品以查看变化
                }
                cout << "请选择你要购买的武器序号，退出选择0" << endl;
            }
        }

        // 处理购买防具的选项
        if (n == 2) {
            shop2.listItems(); // 列出商店2中的所有防具
            cout << "请选择你要购买的防具序号，退出选择0" << endl;

            while (cin >> id) {
                // 处理退出选项
                if (id == 0) {
                    break; // 退出防具购买循环
                }
                // 尝试购买指定序号的防具（序号从1开始，所以需要减1）
                if (shop2.buyItem(linchong, id - 1)) { // 尝试购买物品
                    shop2.listItems(); // 再次列出物品以查看变化
                }
                cout << "请选择你要购买的防具序号，退出选择0" << endl;
            }
        }

        // 显示商店主菜单
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
