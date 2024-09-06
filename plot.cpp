#include "character.h" 
#include "plot.h"
#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <map>
#include <functional>
#include "map11.h"

using namespace std;


void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}// 颜色代码和对应颜色：0  黑色，1深蓝色，2 深绿色3，深青色，4  深红色， 5 深品红色， 6  深黄色 ，7浅灰色，8 暗灰色，9 蓝色， 10绿色， 11 青色，12 红色 ，13 品红色， 14 黄色，15  白色

void Plot::PrintWithDelay(const std::string& text, int delayMs) {
    for (char ch : text) {
        cout << ch;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delayMs));
        if (isCtrlPressed) {
            delayMs = acceleratedDelayMs;
        }
        else {
            delayMs = defaultDelayMs;
        }
    }
}

void Plot::KeyboardThread() {
    while (true) {
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
            isCtrlPressed = true;
        }
        else {
            isCtrlPressed = false;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Plot::PrintIntroduce(const std::string& backgroundSentence) {
    SetConsoleColor(7);
    PrintWithDelay(backgroundSentence, defaultDelayMs);
}

Plot::Plot(Character* charPtr) : character(charPtr), day(1) {
    // 启动线程监听Ctrl键状态
    keyboardThread = std::thread(&Plot::KeyboardThread, this);

    // 初始化 actionMap
    actionMap[1] = [this]() { handleTraining(); };
    actionMap[2] = [this]() { handleShop(); };
    actionMap[3] = [this]() { handleDock(); };
    actionMap[4] = [this]() { handleBarracks(); };
    // 初始化 sceneMap
    sceneMap[1] = [this]() { PrintScene1(); };
    sceneMap[2] = [this]() { PrintScene2(); };
    sceneMap[3] = [this]() { PrintScene3(); };
    sceneMap[4] = [this]() { PrintScene4(); };
    sceneMap[5] = [this]() { PrintScene5(); };
    sceneMap[6] = [this]() { PrintScene6(); };
    sceneMap[7] = [this]() { PrintScene7(); };
    sceneMap[8] = [this]() { PrintScene8(); };
    sceneMap[9] = [this]() { PrintScene9(); };
    sceneMap[10] = [this]() { PrintScene10(); };
}

Plot::~Plot() {
    // 确保线程结束前不干扰主线程
    if (keyboardThread.joinable()) {
        keyboardThread.detach();
    }
}

void Plot::PrintPrompt() {
    SetConsoleColor(1);
    PrintWithDelay("按下Ctrl键时加速显示\n", 30);
    SetConsoleColor(6);
}

void Plot::PrintPrologue() {
    SetConsoleColor(8);
    PrintWithDelay("前情提要：壬寅年,你因恶了高太尉，被发配沧州牢城后。由于柴大官人的关系，你得以在城中活动。\n", 30);
    SetConsoleColor(6);
}
int placeflag; //placeflag= 1 茶酒店 2 武馆 3 营房 4 草料场 5 市井 6 码头 7 古庙 
void Plot::PrintScene(int scene) {
    auto it = sceneMap.find(scene);
    if (it != sceneMap.end()) {
        it->second(); // 调用对应场景的处理函数
    }
    else {
        SetConsoleColor(12);
        PrintWithDelay("无效的场景编号。\n", 30);
    }
}

int Plot::Printchange(int t)//返回0，进入下一幕，返回1，进入菜单
{
    Sleep(1000);
    string input;
    int flag=0;
    std::cout << "1.下一幕             2.更多" << endl;
    cin>> input; 

    if (input=="1") {
        ++t;
        flag = 0;
    }
    else if(input=="2") {
        flag = 1;
    }

    return flag;
}

void Plot::PrintScene1() {
    placeflag = 4;
    SetConsoleColor(8);
    PrintWithDelay("第一幕：\n十一月初五，早晨，雪花纷飞，酒馆前的红灯笼散发着温暖的光芒\n", 30);
    placeflag = 1;
    SetConsoleColor(7);
    PrintWithDelay("李小二：", 30);
    SetConsoleColor(12);
    PrintWithDelay("“营前开了个茶酒店。因讨钱过来，遇见恩人。恩人不知为何事在这里？”\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("林冲指着脸上道：", 30);
    SetConsoleColor(12);
    PrintWithDelay("“我因恶了高太尉，生事陷害，受了一场官司，刺配到这里。不想今日到此遇见。”\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("李小二请林冲到家里面坐定，叫妻子出来拜了恩人。\n两口儿欢喜道：", 30);
    SetConsoleColor(12);
    PrintWithDelay("“夫妻二人正没个亲眷，今日得恩人到来，便是从天降下。”\n", 30);
    SetConsoleColor(10);
    PrintWithDelay("盘缠+100。\n", 30);
    if (character) {
        int gold = character->getGold();
        character->setGold(gold + 50);
    }
    SetConsoleColor(6);
    PrintWithDelay("【恭喜你解锁茶酒店：提供食宿和信息交流，有时有物品掉落】\n", 30);
}


void Plot::PrintScene2() {
    SetConsoleColor(8);
    PrintWithDelay("第二幕：\n十一月初六，中午，寒风刺骨，街道上的雪被踩得松软。\n", 30);
    placeflag = 1;
    SetConsoleColor(7);
    PrintWithDelay("林冲走入茶酒店。\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("李小二慌忙道：", 30);
    SetConsoleColor(12);
    PrintWithDelay("“却才有个东京来的人，在我这里请管营、差拨吃了半日酒。临了只见差拨应道：‘都在我两个身上，好歹要结果了他。’那两个把一包金银，都与管营、差拨。\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("林冲听了，大惊道：", 30);
    SetConsoleColor(12);
    PrintWithDelay("“这三十岁的正是陆虞候。那泼贱贼也敢来这里害我！休要撞着我，只教他骨肉为泥！”\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("李小二道：", 30);
    SetConsoleColor(12);
    PrintWithDelay("“只要提防他便了。恩人，这是这里的地图，还请收下。建议恩人去街上商店上买点防身用品。”\n", 30);
    SetConsoleColor(6);
    Map map2;
    map2.showmap(1);
    SetConsoleColor(7);
    PrintWithDelay("李小二道：", 30);
    PrintWithDelay("“这地图上标红色的，便是恩人目前所在的地方。恩人来小人的茶酒馆来可以休息回复体力，买点东西。去武馆可以提升武力，学习技能。去码头可以赚钱。”\n", 30);
    SetConsoleColor(6);
}

void Plot::PrintScene3() {
    SetConsoleColor(8);
    PrintWithDelay("第三幕:\n你走出茶酒店，走在雪地上。商店的木门敞开着，店内透出柔和的灯光。\n", 30);
    SetConsoleColor(7);
    placeflag = 5;
    PrintWithDelay("商店：", 30);
    SetConsoleColor(12);
    PrintWithDelay("“叫卖~~客官要买些什么？”\n", 30);
    PrintWithDelay("【恭喜你解锁市井：市井中有各种商店，可以购买各种物品，补给和装备。】\n", 30);
    // 选择部分
    // 开始八天的养成系统
    //runDevelopmentSystem();
}

void Plot::PrintScene4() {
    SetConsoleColor(8);
    PrintWithDelay("第四幕：\n十一月十五上午，管营将你带进点视厅，厅内空间宽敞，散发着清凉的气息。管营坐在宽大的木桌后。\n", 30);
    SetConsoleColor(7);
    PrintWithDelay("管营抬起头来，目光严肃：", 30);
    SetConsoleColor(12);
    PrintWithDelay("“此间东门外十五里，有座大军草场，有些常例钱取觅。如今，我抬举你去替那老军来守天王堂。”\n", 30);
    SetConsoleColor(6);
    PrintWithDelay("【恭喜你解锁草料场：负责存放草料，可以在这里获得物品。】\n", 30);
}

void Plot::PrintScene5() {
    placeflag = 4;
    SetConsoleColor(8); // 灰色
    PrintWithDelay("第五幕：\n你和差拨一同来到东门外。推开门时，木头发出轻微的吱呀声。屋内布满了草。\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("差拨走到老军面前，派他交割。老军吩咐林冲看管草堆后收拾行李，临了说道：\n", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“火盆、锅子、碗、碟，都借与你。”\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("老军指壁上挂的一个大葫芦说道：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“你若买酒吃时，只出草场，投东大路去三二里，便有市井。”\n", 30);
    placeflag = 5;
    SetConsoleColor(10); // 绿色
    PrintWithDelay("火盆+1，葫芦+1。\n", 30);
    SetConsoleColor(6);
}

void Plot::PrintScene6() {
    SetConsoleColor(8); // 灰色
    placeflag = 4;
    PrintWithDelay("第六幕：\n就坐下生些焰火起来，地炉里的火焰渐渐升起。仰面看那草屋时，四下被朔风吹撼，摇振得动。\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("林冲：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“要不那市井沽点酒？”\n", 30);
    placeflag = 5;
    SetConsoleColor(6);
}

void Plot::PrintScene7() {
    SetConsoleColor(8); // 灰色
    placeflag = 7;
    PrintWithDelay("第七幕：\n行不上半里多路，看见一所古庙。\n进入庙中，发现几名小偷正在里面，周围的烛光映照出他们阴险的面孔。\n你心里一紧，准备进入战斗。\n", 30);
    SetConsoleColor(6);
    PrintWithDelay("【恭喜你解锁古庙：避难场所，但也可能遇到危险从而引起战斗。】\n", 30);
    SetConsoleColor(7); // 白色
    placeflag = 5;
    PrintWithDelay("店家：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“天气寒冷，且酌三杯，权当接风。”", 30);
    SetConsoleColor(10); // 白色
    PrintWithDelay("店家切一盘熟牛肉，烫一壶热酒，请林冲吃。\n", 30);
    SetConsoleColor(10); // 绿色
    PrintWithDelay("购买酒恢复生命30点，牛肉恢复体力40点。\n", 30);
    SetConsoleColor(6);
}

void Plot::PrintScene8() {
    placeflag = 4;
    SetConsoleColor(8); // 灰色
    PrintWithDelay("第八幕：\n腊月初一，你回到草场，只见两间草厅已经被厚重的积雪压倒，雪花在空中纷飞，覆盖了一切。\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("林冲：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“去古庙对付一晚。”\n", 30);
    placeflag = 7;
    SetConsoleColor(6);
}

void Plot::PrintScene9() {
    SetConsoleColor(8); // 灰色
    PrintWithDelay("第九幕：\n腊月初二早晨，回到草场，火焰在草场上蔓延。\n你握紧手中的枪，准备开门扑灭火焰。就在此时，你听到前方传来急促的脚步声和低声对话。\n你听那三个人时，一个是差拨，一个是陆虞候，一个是富安。\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("林冲心中一阵惊慌，低声道：”", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“天可怜见林冲！若不是倒了草厅，我准定被这厮们烧死了！”\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("轻轻把石头掇开，挺着花枪,大喝一声：”\n", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“泼贼那里去！”\n", 30);
    SetConsoleColor(10); // 绿色
    PrintWithDelay("进入战斗。\n", 30);
    SetConsoleColor(6);
}

void Plot::PrintScene10() {
    SetConsoleColor(8); // 灰色
    PrintWithDelay("第十幕：\n凛凛严凝雾气昏，空中祥瑞降纷纷。须臾四野难分路，顷刻千山不见痕。\n银世界，玉乾坤，望中隐隐接昆仑。若还下到三更后，彷佛填平玉帝门。", 30);
    SetConsoleColor(6);
}




void Plot::handleTraining() {
    if (character) {
        int gold = character->getGold();
        int attack = character->getAttack();
        int currentHP = character->getHP();
        int maxHP = character->getMaxHP();

        // 检查体力是否足够
        if (currentHP < 20) {  // 假设训练需要至少20点体力
            SetConsoleColor(12);
            PrintWithDelay("你的体力不足，无法进行训练。\n", 30);
            SetConsoleColor(7);
            return;
        }

        // 进行训练相关的逻辑
        // 更新体力值
        character->modifyHP(-20);  // 训练消耗 20 点体力
        character->setGold(gold - 10);  // 训练花费 10 金

        SetConsoleColor(8);
        PrintWithDelay("武馆内练习的声音此起彼伏。\n", 30);
        SetConsoleColor(7);
        PrintWithDelay("馆主：", 30);
        SetConsoleColor(12);
        PrintWithDelay("“欢迎来到武馆！在这里，你可以通过训练获得强大的技能，提升你的战斗能力。我们的训练包括增加攻击力、防御力、以及一些特殊技能。”\n", 30);
        PrintWithDelay("“请注意，训练会消耗你的体力。如果你的体力不足，将无法继续训练。训练后的体力会恢复到最大体力的一部分。”\n\n", 30);
        SetConsoleColor(7);
        PrintWithDelay("你在馆内接受了强化训练，感觉自己的能力得到了显著提升。\n", 30);

        character->setAttack(attack + 10);
        character->setGold(gold - 10);
    }
    SetConsoleColor(6);
}



void Plot::handleShop() {
    int gold = character->getGold();
    SetConsoleColor(8); // 灰色
    PrintWithDelay("商店内灯火通明，架子上摆满了各种武器和补给品。\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("店主：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“欢迎光临，客官！您需要些什么？”\n", 30);
    SetConsoleColor(7); // 白色

}

void Plot::handleDock() {
    int gold = character->getGold();
    SetConsoleColor(8); // 灰色
    PrintWithDelay("在码头，你看到许多货物堆积在一起，工人们忙碌地搬运着。\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("码头工人：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“客官，有没有兴趣帮忙运货？帮忙的话可以赚些钱。”\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("你同意了，加入了运货的行列。\n", 30);
    SetConsoleColor(10); // 绿色
    PrintWithDelay("钱包+50\n", 30);
    character->setGold(gold + 50);
    SetConsoleColor(6);
}

void Plot::handleBarracks() {
    if (character) {
        bool running = true;
        while (running) {
            int currentHP = character->getHP(); // 获取当前HP
            int maxHP = character->getMaxHP(); // 获取最大HP
            int gold = character->getGold(); // 获取当前金币

            // 显示菜单
            SetConsoleColor(8); // 灰色
            PrintWithDelay("你回到营房，感到了一些疲惫，但也收获了不少。\n", 30);
            SetConsoleColor(7); // 白色
            PrintWithDelay("请选择你想要的操作：\n", 30);
            SetConsoleColor(10); // 绿色
            PrintWithDelay("1. 休息一下\n", 30);
            PrintWithDelay("2. 查看当前状态\n", 30);
            PrintWithDelay("3. 返回主菜单\n", 30);
            SetConsoleColor(6); // 黄色
            PrintWithDelay("请输入选项（1-3）：", 30);

            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                // 休息功能
                SetConsoleColor(8); // 灰色
                PrintWithDelay("你决定休息一下，为接下来的挑战做准备。\n", 30);
                SetConsoleColor(10); // 绿色
                PrintWithDelay("最大生命值+10。 生命值+50。（不超过最大生命值）\n", 30);
                character->setMaxHP(maxHP + 10);
                character->modifyHP(50);

                // 确保当前HP不超过最大HP
                if (character->getHP() > character->getMaxHP()) {
                    character->setHP(character->getMaxHP());
                }
                break;

            case 2:
                // 查看当前状态
                SetConsoleColor(8); // 灰色
                PrintWithDelay("当前状态如下：\n", 30);
                SetConsoleColor(7); // 白色
                PrintWithDelay("生命值：", 30);
                cout << character->getHP() << "/" << character->getMaxHP() << "\n";
                PrintWithDelay("金币：", 30);
                cout << character->getGold() << "\n";
                SetConsoleColor(6); // 黄色
                PrintWithDelay("按任意键返回菜单...", 30);
                cin.ignore(); // 等待用户输入
                cin.get();
                break;

            case 3:
                // 返回主菜单
                running = false;
                break;

            default:
                // 无效选项
                SetConsoleColor(12); // 红色
                PrintWithDelay("无效选项，请重新选择。\n", 30);
                SetConsoleColor(6); // 黄色
                break;
            }
        }
    }
}