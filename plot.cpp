#include "plot.h"
#include <iostream>
#include <windows.h>
#include <chrono>
using namespace std;
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}//改变输出文字颜色
void Plot::PrintWithDelay(const std::string& text, int delayMs) {
    for (char ch : text) {
        cout << ch;
        cout.flush(); // 确保字符立即输出
        this_thread::sleep_for(chrono::milliseconds(delayMs));
        if (isCtrlPressed) {
            delayMs = acceleratedDelayMs; // Ctrl键按下时加速显示
        }
        else {
            delayMs = defaultDelayMs; // Ctrl键未按下时正常显示速度
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
    SetConsoleColor(7); // 白色
    PrintWithDelay(backgroundSentence, defaultDelayMs);
}
Plot::Plot() {
    // 启动线程监听Ctrl键状态
    keyboardThread = thread(&Plot::KeyboardThread, this);
}
Plot::~Plot() {
    // 确保线程结束前不干扰主线程
    if (keyboardThread.joinable()) {
        keyboardThread.detach();
    }
}
void Plot::PrintPrompt() {
    SetConsoleColor(1); // 蓝色
    PrintWithDelay("按下Cter键时加速显示\n", 30);
    SetConsoleColor(6);
}
void Plot::PrintPrologue() {
    SetConsoleColor(8); // 灰色
    PrintWithDelay("前情提要：你因恶了高太尉，被发配沧州牢城后。由于柴大官人的关系，你得以在城中活动。\n", 30);
    SetConsoleColor(6);
}
int placeflag;
//placeflag= 1 茶酒店    2 武馆  3 营房  4 草料场  5 市井  6 码头  7 古庙
void Plot::PrintScene(int& scene) {
    int now_day = 1;
    switch (scene) {
    case 1:
        placeflag = 4;
        SetConsoleColor(8); // 灰色
        PrintWithDelay("第一幕：\n你刚走出营房，周围的空气清冷而湿润，雪花纷飞，仿佛为大地铺上一层厚厚的银毯。草场被雪压得几乎瘫软，远处的山峦在雾霭中隐隐可见，整个世界被渲染成了冷酷的银色。你走在被雪覆盖的小路上，脚下发出“咯吱咯吱”的响声。忽然，看见前方有一座小茶酒店，酒馆前的红灯笼在寒风中摇曳生姿，散发出温暖的光芒。\n", 30);
        placeflag = 1;
        SetConsoleColor(7); // 白色
        PrintWithDelay("李小二：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“营前开了个茶酒店。因讨钱过来，遇见恩人。恩人不知为何事在这里？”\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("林冲指着脸上道：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“我因恶了高太尉，生事陷害，受了一场官司，刺配到这里。如今叫我管天王堂，未知久后如何。不想今日到此遇见。”\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("李小二就请林冲到家里面坐定，叫妻子出来拜了恩人。\n两口儿欢喜道：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“晚夫妻二人正没个亲眷，今日得恩人到来，便是从天降下。”\n", 30);
        SetConsoleColor(10); // 绿色
        PrintWithDelay("盘缠+100。棉袄+1。\n", 30);
        SetConsoleColor(6);
        break;
    case 2:
        SetConsoleColor(8); // 灰色
        PrintWithDelay("第二幕：\n冬日的寒风肆虐，街道上的雪被踩得松软，空气中弥漫着刺骨的寒冷。\n", 30);
        placeflag = 1;
        SetConsoleColor(7); // 白色
        PrintWithDelay("林冲走入茶酒店，说道：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“小二哥，连日好买卖。”\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("李小二慌忙道：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“恩人请坐。小人却待正要寻恩人，有些要紧话说。”\n", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“却才有个东京来的尴尬人，在我这里请管营、差拨吃了半日酒。差拨口里呐出‘高太尉’三个字来。临了只见差拨口里应道：‘都在我两个身上，好歹要结果了他。’那两个把一包金银，都与管营、差拨。又吃一回酒，各自散了。\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("林冲听了，大惊道：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“这三十岁的正是陆虞候。那泼贱贼也敢来这里害我！休要撞着我，只教他骨肉为泥！”\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("李小二道：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“只要提防他便了。建议恩人去街上商店上买点防身用品。”\n", 30);
        SetConsoleColor(6);
        break;
    case 3:
        SetConsoleColor(8); // 灰色
        PrintWithDelay("第三幕:\n你走出茶酒店，走在雪地上，脚下的积雪被压出一串串深深的足迹。街道上弥漫着冷风，街边的小商铺门前挂着红色的灯笼，照亮了寒冷的夜晚。商店的木门敞开着，店内透出柔和的灯光，昏黄的光芒在雪地上投下长长的影子。\n", 30);
        SetConsoleColor(7); // 白色
        placeflag = 5;
        PrintWithDelay("商店：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“叫卖~~客官要买些什么？”\n", 30);
        // 选择部分
        while (now_day != 9) {
            SetConsoleColor(1); // 蓝色
            cout << "现在是养成的第" << now_day++ << "天,";
            PrintWithDelay("请输入下面的标号：\n可选项：1.武馆（提升武力）\n2.商店（酒，牛肉，刀，枪，弓箭，鲁智深的禅杖，杨志的戒刀）\n3.码头（运货赚钱）\n4.营房（提升生命值）\n", 30);
            int choice;
            cin >> choice; // 假设使用 scanf 来读取用户的输入
            switch (choice) {
            case 1: // 武馆
                placeflag = 2;
                SetConsoleColor(8); // 灰色
                PrintWithDelay("武馆内练习的声音此起彼伏，馆主见到你，热情地招呼你。\n", 30);
                SetConsoleColor(7); // 白色
                PrintWithDelay("馆主：", 30);
                SetConsoleColor(12); // 红色
                PrintWithDelay("“欢迎来锻炼！今天的训练可以提升你的战斗能力。”\n", 30);
                SetConsoleColor(7); // 白色
                PrintWithDelay("你在馆内接受了强化训练，感觉自己的能力得到了显著提升。\n", 30);
                SetConsoleColor(10); // 绿色
                PrintWithDelay("武力+10。钱包-40。\n", 30);//attack+10,gold-40
                SetConsoleColor(6);
                break;
            case 2: // 商店
                placeflag = 5;
                SetConsoleColor(8); // 灰色
                PrintWithDelay("商店内灯火通明，架子上摆满了各种武器和补给品。店主热情地迎接你，介绍了店内的货品。\n", 30);
                SetConsoleColor(7); // 白色
                PrintWithDelay("店主：", 30);
                SetConsoleColor(12); // 红色
                PrintWithDelay("“欢迎光临，客官！我们有各式各样的武器和装备，您需要些什么？”\n", 30);
                SetConsoleColor(7); // 白色
                PrintWithDelay("你仔细挑选了一些武器和防具，准备应对可能的危险。\n", 30);
                SetConsoleColor(10); // 绿色
                PrintWithDelay("武器装备+1。钱包-50。\n", 30);//weapons+1,gold-50
                SetConsoleColor(6);
                break;
            case 3: // 码头
                placeflag = 6;
                SetConsoleColor(8); // 灰色
                PrintWithDelay("在码头，你看到许多货物堆积在一起，工人们忙碌地搬运着。\n", 30);
                SetConsoleColor(7); // 白色
                PrintWithDelay("码头工人：", 30);
                SetConsoleColor(12); // 红色
                PrintWithDelay("“客官，有没有兴趣帮忙运货？我们需要额外的劳动力，帮忙的话可以赚些钱。”\n", 30);
                SetConsoleColor(7); // 白色
                PrintWithDelay("你同意了，加入了运货的行列。整整一天，你忙碌地搬运货物，虽然很累，但看着自己的收入也感到很满意。\n", 30);
                SetConsoleColor(10); // 绿色
                PrintWithDelay("钱包+50\n", 30);//gold+50
                SetConsoleColor(6);
                break;
            case 4: // 营房
                placeflag = 3;
                SetConsoleColor(8); // 灰色
                PrintWithDelay("你回到营房，感到了一些疲惫，但也收获了不少。冬日的阳光透过营                         房的窗户洒进来，给你带来了一丝温暖。\n", 30);
                SetConsoleColor(7); // 白色          nb
                PrintWithDelay("你决定休息一下，为接下来的挑战做准备。\n", 30);
                SetConsoleColor(10); // 绿色
                PrintWithDelay("最大生命值+10。 生命值+50。（不超过最大生命值）\n", 30);//maxHP+10,HP+50(不超过maxHP)
                SetConsoleColor(6);
                break;
            default:
                SetConsoleColor(12); // 红色
                PrintWithDelay("无效的选择，请输入有效的标号。\n", 30);
                now_day--;
                SetConsoleColor(1);
                break;
            }
        }
    case 4:
        SetConsoleColor(8); // 灰色
        PrintWithDelay("第四幕：\n你走进点视厅，厅内空间宽敞，地面铺着青石板，散发着清凉的气息。墙上悬挂着几幅战图和战鼓，油灯下的光影在墙上摇曳，映出了一幅幅古老的战场景象。管营坐在宽大的木桌后，桌上摆放着几本厚重的账簿和笔墨，微弱的灯光下，纸页上的文字显得尤为清晰。\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("管营抬起头来，目光严肃：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“你来这里许多时，柴大官人面皮，不曾抬举得你。此间东门外十五里，有座大军草场，每月但是纳草纳料的，有些常例钱取觅。原是一个老军看管。如今，我抬举你去替那老军来守天王堂。你在那里寻几贯盘缠。你可和差拨便去那里交割。”\n", 30);
        SetConsoleColor(6);
        break;
    case 5:
        placeflag = 4;
        SetConsoleColor(8); // 灰色
        PrintWithDelay("第五幕：\n你和差拨一同来到东门外，黄土路两侧的墙壁上布满了裂纹，显得陈旧而粗糙。两扇沉重的木门上涂着一层陈旧的油漆，推开门时，木头发出轻微的吱呀声。屋内布满了草房，屋顶是用干草和木板搭成的，散发着一股浓烈的草香。\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("差拨走到老军面前，语气带着一丝正式：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“管营差这个林冲来替你回天王堂看守。你可即便交割。”\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("老军拿了钥匙，引着林冲，吩咐道：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“仓廒内自有官司封记。这几堆草，一堆堆都有数目。”\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("老军都点见了堆数，又引林冲到草厅上。老军收拾行李，临了说道：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“火盆、锅子、碗、碟，都借与你。”\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("老军指壁上挂一个大葫芦说道：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“你若买酒吃时，只出草场，投东大路去三二里，便有市井。”\n", 30);
        placeflag = 5;
        SetConsoleColor(10); // 绿色
        PrintWithDelay("火盆+1，葫芦+1。\n", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“叫卖~~客官要买些什么？”\n", 30);
        SetConsoleColor(6);
        break;
    case 6:
        SetConsoleColor(8); // 灰色
        placeflag = 4;
        PrintWithDelay("第六幕：\n就坐下生些焰火起来，地炉里的火焰渐渐升起，炉边堆着几块粗糙的柴炭，木柴发出噼啪的声响。屋边有一堆柴炭，拿几块来，生在地炉里。仰面看那草屋时，四下里崩坏了，又被朔风吹撼，摇振得动。\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("林冲：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“要不那市井沽点酒？”\n", 30);
        placeflag = 5;
        SetConsoleColor(6);
        break;
    case 7:
        SetConsoleColor(8); // 灰色
        placeflag = 7;
        PrintWithDelay("第七幕：\n行不上半里多路，看见一所古庙，庙宇的石砖墙壁斑驳不堪，几根青石柱子摇摇欲坠。\n又行了一回，望见一簇人家。你住脚看时，篱笆上挂着一把草帚，随风摇曳，露天里略显凄凉。\n你走向古庙，踏着雪地，脚下发出嘎吱嘎吱的声响。进入庙中，他发现几名小偷正在里面，周围的烛光摇曳不定，映照出他们阴险的面孔。\n你心里一紧，准备进入战斗。\n", 30);
        SetConsoleColor(7); // 白色
        placeflag = 5;
        PrintWithDelay("店家：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“天气寒冷，且酌三杯，权当接风。”店家切一盘熟牛肉，烫一壶热酒，请林冲吃。”\n", 30);
        SetConsoleColor(10); // 白色
        PrintWithDelay("体力+20，购买酒回复生命30点，牛肉回复体力40点。\n", 30);
        SetConsoleColor(6);
        break;
    case 8:
        placeflag = 4;
        SetConsoleColor(8); // 灰色
        PrintWithDelay("第八幕：\n你回到草场，只见两间草厅已经被厚重的积雪压倒，雪花在空中纷飞，覆盖了一切。\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("林冲：", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“去古庙对付一晚。”\n", 30);
        placeflag = 7;
        SetConsoleColor(6);
        break;
    case 9:
        SetConsoleColor(8); // 灰色
        PrintWithDelay("第九幕：\n  火焰在草场上蔓延，夜色中，火光映照出四周黑暗的轮廓，炽热的烟雾在空中盘旋，空气中弥漫着刺鼻的烧焦味。\n你握紧手中的枪，准备开门扑灭火焰。就在此时，你听到前方传来急促的脚步声和低声对话。\n你靠在庙门上，尽力阻挡门的推开。门缝透出微弱的光线，映出庙内朦胧的阴影。\n你听那三个人时，一个是差拨，一个是陆虞候，一个是富安。\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("林冲心中一阵惊慌，低声道：”", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“天可怜见林冲！若不是倒了草厅，我准定被这厮们烧死了！”\n", 30);
        SetConsoleColor(7); // 白色
        PrintWithDelay("轻轻把石头掇开，挺着花枪，一手拽开庙门，大喝一声：”\n", 30);
        SetConsoleColor(12); // 红色
        PrintWithDelay("“泼贼那里去！”\n", 30);
        SetConsoleColor(10); // 绿色
        PrintWithDelay("进入战斗。\n", 30);
        SetConsoleColor(6);
        break;
    case 10:
        SetConsoleColor(8); // 灰色
        PrintWithDelay("第十幕：\n凛凛严凝雾气昏，空中祥瑞降纷纷。须臾四野难分路，顷刻千山不见痕。\n银世界，玉乾坤，望中隐隐接昆仑。若还下到三更后，彷佛填平玉帝门。", 30);
        SetConsoleColor(6);
        break;
    }
}
/*
以下为main.cpp
#include <iostream>
#include "plot.h"
using namespace std;
int main() {
    Plot plot;
    plot.PrintPrompt();
    plot.PrintPrologue();
    for (int i = 1; i <= 10; ++i) {
        cout << "\n按Enter键继续到第 " << i << " 幕...";
        cin.get(); // 等待用户按下回车键
        // 打印当前幕
        plot.PrintScene(i);
        if (i > 9) {
            cout << "\n按Enter键退出...";
        }
    }
    return 0;
}
*/