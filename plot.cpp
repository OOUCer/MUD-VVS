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

/* 设置控制台颜色 */
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}// 颜色代码和对应颜色：0  黑色，1 深蓝色，2 深绿色，3 深青色，4 深红色，5 深品红色，6 深黄色，7 浅灰色，8 暗灰色，9 蓝色，10 绿色，11 青色，12 红色，13 品红色，14 黄色，15 白色

/* 按照指定的延迟逐字打印文本 */
void Plot::PrintWithDelay(const std::string& text, int delayMs) {
    for (char ch : text) {
        cout << ch;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delayMs));
        if (isCtrlPressed) {
            delayMs = acceleratedDelayMs;  // Ctrl键按下时加速
        }
        else {
            delayMs = defaultDelayMs;      // 否则使用默认延迟
        }
    }
}

/* 线程监听键盘，检测Ctrl键是否按下 */
void Plot::KeyboardThread() {
    while (true) {
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
            isCtrlPressed = true;
        }
        else {
            isCtrlPressed = false;
        }
        this_thread::sleep_for(chrono::milliseconds(100));  // 每100毫秒检查一次
    }
}

/* 打印场景介绍，设置为灰色 */
void Plot::PrintIntroduce(const std::string& backgroundSentence) {
    SetConsoleColor(7);
    PrintWithDelay(backgroundSentence, defaultDelayMs);
}

/* 构造函数，初始化情节并启动键盘监听线程 */
Plot::Plot(Character* charPtr) : character(charPtr), day(1) {
    // 启动线程监听Ctrl键状态
    keyboardThread = std::thread(&Plot::KeyboardThread, this);

    // 初始化actionMap
    actionMap[1] = [this]() { handleTraining(); };
    actionMap[2] = [this]() { handleShop(); };
    actionMap[3] = [this]() { handleDock(); };
    actionMap[4] = [this]() { handleBarracks(); };

    // 初始化sceneMap，映射场景ID到具体的场景打印函数
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

/* 析构函数，确保键盘线程安全退出 */
Plot::~Plot() {
    // 确保线程结束前不干扰主线程
    if (keyboardThread.joinable()) {
        keyboardThread.detach();
    }
}

/* 打印提示信息，显示加速显示的提示 */
void Plot::PrintPrompt() {
    SetConsoleColor(1);
    PrintWithDelay("按下Ctrl键时加速显示\n", 30);
    SetConsoleColor(6);
}

/* 打印游戏序幕，设置为暗灰色 */
void Plot::PrintPrologue() {
    SetConsoleColor(8);
    PrintWithDelay("前情提要：壬寅年,你因恶了高太尉，被陆虞侯和高太尉联手陷害，发配沧州牢城。后由于柴大官人的关系，你得以在城中活动。\n", 30);
    SetConsoleColor(6);
}

int placeflag; // placeflag表示场景标志：1 茶酒店，2 武馆，3 营房，4 草料场，5 市井，6 码头，7 古庙

/* 打印指定场景 */
void Plot::PrintScene(int scene) {
    auto it = sceneMap.find(scene);
    if (it != sceneMap.end()) {
        it->second();  // 调用对应场景的处理函数
    }
    else {
        SetConsoleColor(12);
        PrintWithDelay("无效的场景编号。\n", 30);
    }
}

/* 打印选择菜单并返回选择结果 */
int Plot::Printchange(int& t) // 返回0，进入下一幕，返回1，进入菜单
{
    Sleep(500);  // 延迟500ms
    string input;
    int flag = 0;

    std::cout << "1.下一幕             2.更多" << endl;
    cin >> input;

    if (input == "1") {
        ++t;
        flag = 0;  // 选择下一幕
    }
    else if (input == "2") {
        flag = 1;  // 选择更多选项
    }

    return flag;
}

/* 打印第一幕的场景 */
void Plot::PrintScene1() {
    placeflag = 4;  // 设置场景为草料场
    SetConsoleColor(8);
    PrintWithDelay("第一幕：\n十一月初五，早晨，雪花纷飞，酒馆前的红灯笼散发着温暖的光芒\n", 30);

    placeflag = 1;  // 设置场景为茶酒店
    SetConsoleColor(7);
    PrintWithDelay("李小二：", 30);

    SetConsoleColor(12);
    PrintWithDelay("“营前开了个茶酒店。因讨钱过来，遇见恩人。恩人不知为何事在这里？”\n", 30);

    SetConsoleColor(7);
    PrintWithDelay("你指着脸上道：", 30);

    SetConsoleColor(12);
    PrintWithDelay("“我因恶了高太尉，生事陷害，受了一场官司，刺配到这里。不想今日到此遇见。”\n", 30);

    SetConsoleColor(7);
    PrintWithDelay("李小二请你到家里面坐定，叫妻子出来拜了恩人。\n两口儿欢喜道：", 30);

    SetConsoleColor(12);
    PrintWithDelay("“夫妻二人正没个亲眷，今日得恩人到来，便是从天降下。这些盘缠恩人且收下，聊表心意”\n", 30);

    SetConsoleColor(10);
    PrintWithDelay("盘缠+100。\n", 30);

    // 增加角色的金币数量
    if (character) {
        int gold = character->getGold();
        character->setGold(gold + 100);
    }

    /*SetConsoleColor(6);
    PrintWithDelay("【恭喜你解锁茶酒店：提供食宿和信息交流，有时有物品掉落】\n", 30);*/
    SetConsoleColor(15);
}


void Plot::PrintScene2() {
    // 设置控制台颜色为灰色
    SetConsoleColor(8);
    // 打印第二幕的场景描述，并延迟显示
    PrintWithDelay("第二幕：\n十一月初六，中午，寒风刺骨，街道上的雪被踩得松软。\n", 30);
    placeflag = 1;  // 设置场景标记为1
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    PrintWithDelay("你走入茶酒店。\n", 30);
    // 打印李小二的对话
    SetConsoleColor(7);
    PrintWithDelay("李小二慌忙道：", 30);
    SetConsoleColor(12); // 设置控制台颜色为红色
    PrintWithDelay("“却才有个东京来的人，在我这里请管营、差拨吃了半日酒。临了只见差拨应道：‘都在我两个身上，好歹要结果了他。’那两个把一包金银，都与管营、差拨。\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    PrintWithDelay("你听了，大惊道：", 30);
    SetConsoleColor(12); // 设置控制台颜色为红色
    PrintWithDelay("“这三十岁的正是陆虞候。那泼贱贼也敢来这里害我！休要撞着我，只教他骨肉为泥！”\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    PrintWithDelay("李小二道：", 30);
    SetConsoleColor(12); // 设置控制台颜色为红色
    PrintWithDelay("“只要提防他便了。恩人，这是这里的地图，还请收下。”\n", 30);
    // 设置控制台颜色为青色
    SetConsoleColor(6);
    Map map2;
    cout << endl;
    cout << endl;
    cout << endl;
    Sleep(1000); // 暂停1秒
    cout << endl;
    cout << "输入“ENTER”打开地图" << endl;
    getchar(); // 等待用户输入
    cin.get();
    map2.showmap(1); // 显示地图
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    PrintWithDelay("李小二道：", 30);
    SetConsoleColor(12); // 设置控制台颜色为红色
    PrintWithDelay("“这地图上标红色的，便是恩人目前所在的地方。”\n“恩人来小人的茶酒馆来可以休息回复体力，买点东西。去武馆可以提升武力，学习技能。去码头可以赚钱。”\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
}

void Plot::PrintScene3() {
    // 设置控制台颜色为灰色
    SetConsoleColor(8);
    // 打印第三幕的场景描述，并延迟显示
    PrintWithDelay("第三幕:\n你正与李小二交谈时，一位鹤发童颜的老者走了进来，手中拿一算命的招牌。\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    PrintWithDelay("是否花费20盘缠算一下命？\n", 30);
    cout << "1.是          2.否" << endl;
    int flag;
    cin >> flag; // 获取用户输入
    if (flag == 1) {
        // 如果用户选择“是”，则显示算命结果
        PrintWithDelay("老者摸了摸手骨，又看了看面像，大惊到：\n", 30);
        SetConsoleColor(12); // 设置控制台颜色为红色
        PrintWithDelay("这位小兄弟，你八天后,也便是十一月十四，会有血光之灾，到时向东而行，其灾必解。”\n", 30);
        SetConsoleColor(10); // 设置控制台颜色为绿色
        cout << "盘缠 - 20" << endl;
        // 恢复控制台颜色为白色
        SetConsoleColor(7);
        if (character) {
            int gold = character->getGold(); // 获取当前金币数量
            character->setGold(gold - 20); // 减少20金币
        }
    }
    else {
        // 如果用户选择“否”，则仍然显示算命结果
        SetConsoleColor(7);
        PrintWithDelay("你没理会那位老者，但他却一把将其拉过，摸了摸手骨，又看了看面像，大惊到：\n", 30);
        SetConsoleColor(12); // 设置控制台颜色为红色
        PrintWithDelay("这位小兄弟，你八天后,也便是十一月十四，会有血光之灾，到时向东而行，其灾必解。”\n", 30);
        // 恢复控制台颜色为白色
        SetConsoleColor(7);
        // 备用代码：为将来可能的扩展准备
        // PrintWithDelay("你没理会那位老者，但他却一把将其拉过，摸了摸手骨，又看了看面像，大惊到：“这位小兄弟，你八天后，也便是十一月十四，会有血光之灾，到时向东而行，其灾必解。”\n", 30);
    }
    // 打印离开茶酒店的描述
    PrintWithDelay("你拜谢老者，却不必再提。只见你与李小二又交谈两句后，便离开了茶酒店\n", 30);
    // 备用代码：为将来可能的扩展准备
    /*placeflag = 5;
    PrintWithDelay("商店：", 30);
    SetConsoleColor(12);
    PrintWithDelay("“叫卖~~客官要买些什么？”\n", 30);
    PrintWithDelay("【恭喜你解锁市井：市井中有各种商店，可以购买各种物品，补给和装备。】\n", 30);*/
    // 选择部分
    // 开始八天的养成系统
    //runDevelopmentSystem();
}

void Plot::PrintScene4() {
    // 设置控制台颜色为灰色
    SetConsoleColor(8);
    // 打印第四幕的场景描述，并延迟显示
    PrintWithDelay("第四幕：\n十一月十五上午，管营将你带进点视厅，厅内空间宽敞，散发着清凉的气息。管营坐在宽大的木桌后。\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    PrintWithDelay("管营抬起头来，目光严肃：", 30);
    SetConsoleColor(12); // 设置控制台颜色为红色
    PrintWithDelay("“此间东门外十五里，有座大军草场，有些常例钱取觅。如今，我抬举你去替那老军来守天王堂。”\n", 30);
    // 备用代码：为将来可能的扩展准备
    /*SetConsoleColor(6);
    PrintWithDelay("【恭喜你解锁草料场：负责存放草料，可以在这里获得物品。】\n", 30);*/
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
}

void Plot::PrintScene5() {
    placeflag = 4; // 设置场景标记为4
    // 设置控制台颜色为灰色
    SetConsoleColor(8);
    // 打印第五幕的场景描述，并延迟显示
    PrintWithDelay("第五幕：\n你和差拨一同来到东门外。推开门时，木头发出轻微的吱呀声。屋内布满了草。\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    PrintWithDelay("差拨走到老军面前，派他交割。老军吩咐你看管草堆后收拾行李，临了说道：\n", 30);
    SetConsoleColor(12); // 设置控制台颜色为红色
    PrintWithDelay("“火盆、锅子、碗、碟，都借与你。”\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    PrintWithDelay("老军指壁上挂的一个大葫芦说道：", 30);
    SetConsoleColor(12); // 设置控制台颜色为红色
    PrintWithDelay("“你若买酒吃时，只出草场，投东大路去三二里，便有市井。”\n", 30);
    placeflag = 5; // 设置场景标记为5
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    // 备用代码：为将来可能的扩展准备
    //PrintWithDelay("火盆+1，葫芦+1。\n", 30);
    //SetConsoleColor(6);
}

void Plot::PrintScene6() {
    // 设置控制台颜色为灰色
    SetConsoleColor(8);
    placeflag = 4; // 设置场景标记为4
    // 打印第六幕的场景描述，并延迟显示
    PrintWithDelay("第六幕：\n你就坐下生些焰火起来，地炉里的火焰渐渐升起。仰面看那草屋时，四下被朔风吹撼，摇振得动。\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    PrintWithDelay("你：", 30);
    SetConsoleColor(12); // 设置控制台颜色为红色
    PrintWithDelay("“要不那市井沽点酒？”\n", 30);
    // 备用代码：为将来可能的扩展准备
    //placeflag = 5;
    //SetConsoleColor(7);
}

void Plot::PrintScene7() {
    // 设置控制台颜色为灰色
    SetConsoleColor(8);
    placeflag = 7; // 设置场景标记为7
    // 打印第七幕的场景描述，并延迟显示
    PrintWithDelay("第七幕：\n行不上半里多路，看见一所古庙。\n进入庙中，发现几名土匪正在里面，周围的烛光映照出他们阴险的面孔。\n你心里一紧，准备进入战斗。\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
    // 备用代码：为将来可能的扩展准备
    //PrintWithDelay("【恭喜你解锁古庙：避难场所，但也可能遇到危险从而引起战斗。】\n", 30);
    //SetConsoleColor(7); // 白色
    //placeflag = 5;
    //PrintWithDelay("店家：", 30);
    //SetConsoleColor(12); // 红色
    //PrintWithDelay("“天气寒冷，且酌三杯，权当接风。”", 30);
    //SetConsoleColor(10); // 白色
    //PrintWithDelay("店家切一盘熟牛肉，烫一壶热酒，请你吃。\n", 30);
    //SetConsoleColor(10); // 绿色
    //PrintWithDelay("状态回满\n", 30);
    //SetConsoleColor(6);
}


void Plot::PrintScene11() {
    SetConsoleColor(7); // 白色
    placeflag = 5; // 设置场景标记为5
    // 打印店家的对话
    PrintWithDelay("店家：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“天气寒冷，且酌三杯，权当接风。”", 30);
    SetConsoleColor(10); // 白色
    // 打印提供的食物和饮品
    PrintWithDelay("店家切一盘熟牛肉，烫一壶热酒，请你吃。\n", 30);
    SetConsoleColor(10); // 绿色
    // 打印状态恢复提示
    PrintWithDelay("状态回满\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
}

void Plot::PrintScene8() {
    placeflag = 4; // 设置场景标记为4
    SetConsoleColor(8); // 灰色
    // 打印第八幕的场景描述
    PrintWithDelay("第八幕：\n你回到草场，只见两间草厅已经被厚重的积雪压倒，雪花在空中纷飞，覆盖了一切。\n", 30);
    SetConsoleColor(7); // 白色
    // 打印角色的对话
    PrintWithDelay("你：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“去古庙对付一晚。”\n", 30);
    placeflag = 7; // 设置场景标记为7
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
}

void Plot::PrintScene9() {
    SetConsoleColor(8); // 灰色
    // 打印第九幕的场景描述
    PrintWithDelay("第九幕：\n正在休息时，忽然你望见草料场起火了\n你收拾行李，准备开门扑灭火焰。就在此时，你听到前方传来急促的脚步声和低声对话。\n你听那三个人时，一个是差拨，一个是陆虞候，一个是富安。\n", 30);
    SetConsoleColor(7); // 白色
    // 打印角色的对话
    PrintWithDelay("你心中一阵惊慌，低声道：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“天可怜见你！若不是倒了草厅，我准定被这厮们烧死了！”\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("轻轻把石头掇开，挺着花枪, 大喝一声：", 30);
    SetConsoleColor(12); // 红色
    PrintWithDelay("“泼贼那里去！”\n", 30);
    SetConsoleColor(10); // 绿色
    // 打印进入战斗的提示
    PrintWithDelay("进入战斗。\n", 30);
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
}

void Plot::PrintScene10() {
    system("cls"); // 清屏
    SetConsoleColor(7); // 白色
    // 打印诗句的格式
    for (int i = 0; i < 29; i++)
        cout << " ";
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("凛凛严凝雾气昏，空中祥瑞降纷纷。", 500);
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("须臾四野难分路，顷刻千山不见痕。", 500);
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("银世界，玉乾坤，望中隐隐接昆仑。", 500);
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;

    for (int i = 0; i < 36; i++)
        cout << " ";
    PrintWithDelay("若还下到三更后，彷佛填平玉帝门。", 500);
    for (int i = 0; i < 36; i++)
        cout << " ";
    cout << endl;
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
}

int Plot::handleTraining() {
    if (character) {
        int gold = character->getGold(); // 获取金币数量
        int attack = character->getAttack(); // 获取攻击力
        int currentHP = character->getHP(); // 获取当前体力
        int maxHP = character->getMaxHP(); // 获取最大体力

        // 训练前的检查（目前被注释掉）
        // if (currentHP < 20) { // 假设训练需要至少20点体力
        //     SetConsoleColor(12);
        //     PrintWithDelay("你的体力不足，无法进行训练。\n", 30);
        //     SetConsoleColor(7);
        //     return;
        // }

        // 进行训练相关的逻辑（目前被注释掉）
        // character->modifyHP(-20);  // 训练消耗20点体力
        // character->setGold(gold - 10);  // 训练花费10金币

        SetConsoleColor(8); // 灰色
        PrintWithDelay("武馆内练习的声音此起彼伏。\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("馆主：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“欢迎来到武馆！在这里，你可以通过训练提升攻击力，获得技能，提升战斗能力。”\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("是否花费10盘缠进行训练\n", 30);
        SetConsoleColor(10); // 绿色
        cout << "1.是           2.否" << endl;
        SetConsoleColor(7); // 白色
        int flag;
        cin >> flag; // 获取用户选择
        while (flag != 1 && flag != 2) {
            cout << "输入错误，请重新输入" << endl;
            SetConsoleColor(10); // 绿色
            cout << "1.是              2.否" << endl;
            SetConsoleColor(7); // 白色
            cin >> flag; // 重新获取用户选择
        }
        if (flag == 1) {
            if (gold < 10) {
                PrintWithDelay("盘缠不足，请去码头赚钱后再来\n", 30);
                return 0; // 返回0表示未能进行训练
            }
            else {
                PrintWithDelay("你在馆内接受了强化训练，感觉自己的能力得到了显著提升。\n", 30);
                return 1; // 返回1表示训练成功
            }
        }
        else if (flag == 2) {
            PrintWithDelay("你离开了武馆。\n", 30);
            return 0; // 返回0表示未进行训练
        }
    }
    // 恢复控制台颜色为白色
    SetConsoleColor(7);
}


void Plot::handleShop() {
    int gold = character->getGold(); // 获取当前金币

    SetConsoleColor(8); // 灰色
    // 打印商店内的描述
    PrintWithDelay("商店内灯火通明，架子上摆满了各种武器和补给品。\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("店主：", 30);
    SetConsoleColor(12); // 红色
    // 打印店主的对话
    PrintWithDelay("“欢迎光临，客官！您需要些什么？”\n", 30);
    SetConsoleColor(7); // 恢复为白色
}

void Plot::handleDock() {
    int gold = character->getGold(); // 获取当前金币

    SetConsoleColor(8); // 灰色
    // 打印码头的描述
    PrintWithDelay("在码头，你看到许多货物堆积在一起，工人们忙碌地搬运着。\n", 30);
    SetConsoleColor(7); // 白色
    PrintWithDelay("码头工人：", 30);
    SetConsoleColor(12); // 红色
    // 打印码头工人的对话
    PrintWithDelay("“客官，有没有兴趣帮忙运货？帮忙的话可以赚些钱。”\n", 30);
    SetConsoleColor(10); // 绿色
    // 打印选项
    cout << "1.是              2.否" << endl;
    SetConsoleColor(7); // 恢复为白色
    int f = 0;
    cin >> f; // 获取用户输入
    while (f != 1 && f != 2) {
        // 输入错误提示
        cout << "输入错误，请重新输入" << endl;
        SetConsoleColor(10); // 绿色
        cout << "1.是              2.否" << endl;
        SetConsoleColor(7); // 恢复为白色
        cin >> f; // 重新获取用户输入
    }
    if (f == 1) {
        // 用户同意帮助
        PrintWithDelay("你同意了，加入了运货的行列。\n", 30);
        SetConsoleColor(10); // 绿色
        PrintWithDelay("钱包+50\n", 30);
        character->setGold(gold + 50); // 增加金币
        SetConsoleColor(7); // 恢复为白色
    }
    else if (f == 2) {
        // 用户选择离开
        PrintWithDelay("你离开了码头。\n", 30);
        return;
    }
}

int Plot::handleBarracks() {
    if (character) {
        bool running = true;
        while (running) {
            int currentHP = character->getHP(); // 获取当前HP
            int maxHP = character->getMaxHP(); // 获取最大HP
            int gold = character->getGold(); // 获取当前金币

            SetConsoleColor(8); // 灰色
            // 打印营房的描述
            PrintWithDelay("你回到营房，感到了一些疲惫，但也收获了不少。\n", 30);
            SetConsoleColor(7); // 白色
            PrintWithDelay("请选择你想要的操作：\n", 30);
            SetConsoleColor(10); // 绿色
            // 打印操作选项
            PrintWithDelay("1. 查看菜单", 30);
            cout << "        ";
            PrintWithDelay("2. 离开\n", 30);
            SetConsoleColor(7); // 恢复为白色

            int choice;
            cin >> choice; // 获取用户选择
            return choice; // 返回用户选择的操作
        }
    }
    return 0; // 返回0表示没有选择任何操作
}

void Plot::saveTimeToFile(const string& filename, const Time& time) {
    ofstream outFile(filename); // 打开文件进行写操作
    if (outFile.is_open()) {
        // 将时间数据写入文件
        outFile << time.plottime << "\n";
        outFile << time.day << "\n";
    }
    outFile.close(); // 关闭文件
    cout << "进度已储存" << endl; // 打印保存成功提示
}

Time Plot::loadTimeFromFile(const string& filename) {
    ifstream inFile(filename); // 打开文件进行读操作
    Time time;
    if (inFile.is_open()) {
        // 从文件中读取时间数据
        inFile >> time.plottime;
        inFile >> time.day;
    }
    inFile.close(); // 关闭文件
    return time; // 返回读取的时间数据
}
