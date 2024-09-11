#include"battle.h"

// Battle 类的构造函数，初始化随机数生成器
Battle::Battle() : gen(rd()), dis(0.0, 1.0) {}

// 设置控制台颜色函数，参数为颜色代码
void SetConsoleColor(int);// 1深蓝色 2绿色 3浅蓝 4红色 5紫色 6橙黄 7白色 8灰色 11蓝绿 12浅红 13紫红 14明黄

// 开始战斗，传入玩家对象和敌人列表
void Battle::startBattle(Linchong* player, vector<Character*>* enemies) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));  // 延时 1.5 秒，模拟战斗加载
	system("cls");  // 清屏
	player->setSkillPoint(3);  // 初始化玩家技能点数
	player->setAnticipateStatus(false);  // 初始化看破状态
	player->setChargeStatus(false);  // 初始化蓄力状态
	player->getEffectStatus()->clear();  // 清空玩家的效果状态
	showStartInformation(player, enemies);  // 显示战斗初始信息
	vector<pair<int, Character*>> sortedCharacters;  // 按速度排序的角色列表
	sortBySpeed(&sortedCharacters, player, enemies);  // 按角色速度进行排序
	showSpeedLine(sortedCharacters);  // 显示排序后的角色行动顺序
	cout << "--------------------------------------------------------————————————————————————————————————————" << endl;
	for (auto& it : sortedCharacters) {  // 设置每个角色的 HP 为其最大 HP
		it.second->modifyHP(-it.second->getHP() + it.second->getMaxHP());
		prepareSkill(it.second);  // 准备角色的技能
	}
	int turn = 1;  // 回合计数
	manageSkillOrder(player);  // 管理玩家技能的顺序

	while (true)
	{
		if (turn > 1)
			system("cls");  // 如果不是第一个回合，清屏
		cout << "回合数:" << turn << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// 清除上一回合的弱点状态，管理基础属性 buff 状态
		for (auto& it : sortedCharacters) {
			Character* theCharacter = it.second;
			manageWeaknessAndBuff(theCharacter);  // 处理角色的弱点和 buff 状态
		}

		// 回合前显示状态
		for (auto& it : sortedCharacters) {
			Character* theCharacter = it.second;
			showAllStatus(theCharacter);  // 显示所有状态
		}
		cout << "--------------------------------------------------------————————————————————————————————————————" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// 战斗回合开始
		for (auto& it : sortedCharacters) {
			if (it.first == 0)
				continue;  // 跳过已阵亡的角色
			cout << "现在轮到" << it.second->getName() << "行动！" << endl;

			// 延时模拟行动的进行
			if (it.second->isPlayerControlled())
				std::this_thread::sleep_for(std::chrono::milliseconds(400));
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(400));

			bool chargeFlag = false;  // 标记是否处于蓄力状态

			it.second->setActionAvailability(true);  // 设置角色的行动状态为可行动
			manageComatoseStatus(it.second);  // 处理昏迷状态
			if (it.second->getChargeStatus())
				chargeFlag = true;  // 如果角色处于蓄力状态，设置标记为 true

			if (it.second->getAnticipateStatus())  // 如果角色处于看破状态
			{
				it.second->setAnticipateStatus(false);  // 停止看破状态
				cout << it.second->getName() << "停止了看破！" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}

			// 非玩家角色行动
			if (!it.second->isPlayerControlled())
			{
				int actionCount = 0;  // 行动次数计数
				while (it.second->getActionAvailability())  // 如果角色可以行动
				{
					actionCount++;
					it.second->setActionCount(it.second->getActionCount() + 1);  // 增加行动计数
					if (actionCount > 1)
						cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！(伤害+" << it.second->getActionCount() * 10 << "%!!!)" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					enemyTurn(it.second, player);  // 敌方角色的回合操作
					if (evaluateBattleStatus(sortedCharacters, enemies, 1))
						return;  // 如果战斗结束，退出函数
				}
			}
			else  // 玩家角色行动
			{
				int actionCount = 0;
				while (it.second->getActionAvailability())
				{
					actionCount++;
					it.second->setActionCount(it.second->getActionCount() + 1);  // 增加玩家的行动计数
					if (player->getHitWeakness() && (player->getWeapons()->size() != 1))  // 如果玩家命中了弱点
					{
						cout << "可以额外行动。是否立即切换武器且不消耗行动次数？(y/n)" << endl;
						while (getchar() != '\n');  // 清除输入缓冲区
						char answer = getchar();  // 获取玩家输入
						if (answer == 'y')
							weaponSwitch(player);  // 切换武器
					}
					if (actionCount > 1)  // 如果是第二次或更多次行动
					{
						cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！(伤害+" << it.second->getActionCount() * 10 << "%!!!)" << endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(900));
						for (auto& i : *enemies)
						{
							Character* theCharacter = i;
							showAllStatus(theCharacter);  // 显示敌人的状态
						}
					}
					playerTurn(player, enemies);  // 玩家回合操作
					if (evaluateBattleStatus(sortedCharacters, enemies, 1))
						return;  // 如果战斗结束，退出函数
				}
			}

			// 如果角色处于蓄力状态，回合结束后重置蓄力状态
			if (chargeFlag)
				it.second->setChargeStatus(false);
		}

		turn++;  // 增加回合计数
		cout << endl << "本回合到此结束！！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1400));
		if (evaluateBattleStatus(sortedCharacters, enemies, 0))
			return;  // 如果战斗结束，退出函数
	}
}

// 根据角色速度进行排序，速度高的角色优先行动
void Battle::sortBySpeed(vector<pair<int, Character*>>* sorted, Linchong* player, vector<Character*>* enemies) {
	sorted->push_back(make_pair(player->getSpeed(), player));  // 将玩家加入排序列表
	for (auto enemy : *enemies) {
		sorted->push_back(make_pair(enemy->getSpeed(), enemy));  // 将每个敌人加入排序列表
	}
	// 按速度从高到低排序
	sort(sorted->begin(), sorted->end(),
		[](const pair<int, Character*>& a, const pair<int, Character*>& b)
		{ return a.first > b.first; });
}

// 评估战斗状态，判断战斗是否结束
bool Battle::evaluateBattleStatus(vector<pair<int, Character*>>& theCharacters, vector<Character*>* enemies, int flag)
{
	// 遍历角色列表，检查角色是否阵亡
	for (auto it = theCharacters.begin(); it != theCharacters.end();) {
		if (it->second->getHP() <= 0) {  // 如果角色 HP 小于等于 0
			if (it->second->isPlayerControlled()) {  // 如果玩家阵亡
				cout << "林冲被击败，战斗结束！" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				it->second->setAnticipateStatus(false);  // 重置看破状态
				it->second->setChargeStatus(false);  // 重置蓄力状态
				it->second->getEffectStatus()->clear();  // 清空效果状态
				return true;  // 玩家阵亡，退出战斗
			}
			else {
				if (it->first != 0)
					cout << it->second->getName() << " 被击败了！" << endl; std::this_thread::sleep_for(std::chrono::milliseconds(500));
				it->first = 0;  // 将敌人的速度设置为 0，表示敌人阵亡
				it++;
				if (flag == 1)  // 如果战斗仍在继续
				{
					int leftEnemies = enemies->size();
					for (auto i : *enemies)
					{
						if (i->getHP() <= 0)  // 计算剩余敌人数目
							leftEnemies--;
					}
					if (leftEnemies == 0) {  // 如果所有敌人都被击败
						cout << "敌人全部被击败，林冲获得了胜利！" << endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(500));
						return true;  // 战斗胜利，退出
					}
				}
			}
		}
		else {
			it++;
		}
	}
	return false;  // 战斗未结束
}

// 管理角色的弱点和增益效果
void Battle::manageWeaknessAndBuff(Character* theCharacter) {
	theCharacter->setWeaknessReceivedStatus(false);  // 重置弱点接受状态
	theCharacter->setHitWeakness(false);  // 重置命中弱点状态
	theCharacter->setActionCount(0);  // 重置行动次数

	// 检查角色是否有效果状态
	if (!theCharacter->getEffectStatus()->empty()) {
		// 遍历角色的效果状态列表
		for (auto itEffect = theCharacter->getEffectStatus()->begin(); itEffect != theCharacter->getEffectStatus()->end();) {
			itEffect->second.second--;  // 减少效果持续时间
			if (itEffect->second.second == 0) {
				string effectName = "无";
				// 根据效果类型确定效果名称
				switch (itEffect->first) {
				case giveDefenseWeaken:
				case selfDefenseBoost:effectName = "防御力"; break;
				case giveEvationWeaken:
				case selfEvationBoost:effectName = "闪避率"; break;
				case giveHitRateWeaken:
				case selfHitRateBoost:effectName = "命中率"; break;
				case giveAttackWeaken:
				case selfAttackBoost:effectName = "攻击力"; break;
				default: break;
				}
				// 效果持续时间结束后移除效果
				itEffect = theCharacter->getEffectStatus()->erase(itEffect);
				cout << theCharacter->getName() << "的" << effectName << "恢复原状了！" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			else {
				++itEffect;  // 如果效果仍然有效，继续下一个
			}
		}
	}
}

// 敌方回合逻辑
void Battle::enemyTurn(Character* enemy, Character* player) {
	// 如果敌人没有技能，执行普通攻击
	if (enemy->getSkills()->empty()) {
		normalAttack(player, enemy);
		return;
	}

	// 敌人可能使用技能或进行普通攻击
	uniform_int_distribution<> dis2(1, enemy->getSkills()->size());
	float randomValue = dis(gen);
	int index = dis2(gen);
	if (randomValue < 0.45)
		normalAttack(player, enemy);  // 45%几率普通攻击
	else
		userSkill_enemy(player, enemy, index - 1);  // 否则使用技能
}

// 玩家回合逻辑
void Battle::playerTurn(Character* player, vector<Character*>* enemies) {
	int choice;
	bool validChoice = false;
	float hpRate = static_cast<float>(player->getHP()) / player->getMaxHP();  // 计算玩家当前生命值百分比

	// 确保玩家输入的选择有效
	while (!validChoice) {
		// 显示玩家的状态信息
		cout << "<HP:" << static_cast<int>(100 * hpRate) << "%> "
			<< "<招式点数:" << player->getSkillPoint() << "> "
			<< "<攻击:" << player->getFirstWeapon()->getAttackType() << "> "
			<< "<弱点:" << player->getFirstArmor()->getWeakness() << ">" << endl
			<< "1.普通攻击 2.招式 3.切换武器 4.观察 " << endl << "选择行动:";

		if (!(cin >> choice)) {
			cin.clear();
#undef max
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "无效的输入，请输入一个数字。" << endl;
			continue;
		}

		// 检查玩家输入是否有效
		if (choice >= 1 && choice <= 4) {
			validChoice = true;
			switch (choice) {
			case 1: {  // 执行普通攻击
				showEnemiesInformation(enemies, player->getHitRate());  // 显示敌人信息
				cout << "选择攻击对象:";
				int targetIndex;
				cin >> targetIndex;
				if (targetIndex >= 1 && targetIndex <= enemies->size()) {
					normalAttack((*enemies)[targetIndex - 1], player);  // 普通攻击选定的敌人
				}
				else {
					cout << "无效的敌人索引，请重新输入。" << endl;
				}
				break;
			}
			case 2: {  // 使用招式
				if (player->getSkillPoint() == 0) {  // 检查招式点数是否足够
					validChoice = false;
					cout << player->getName() << "招式点数不足" << endl;
					break;
				}
				if (player->getSkills()->empty()) {  // 检查是否有可用技能
					validChoice = false;
					cout << player->getName() << "不会使用招式" << endl;
					break;
				}
				int skillIndex;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				showSkillInformationInBattle(player);  // 显示技能信息
				cout << "选择招式:";
				cin >> skillIndex;
				// 检查武器是否与技能兼容
				if ((*player->getSkills())[skillIndex - 1]->getIsOffensive() && (*player->getSkills())[skillIndex - 1]->getAttackType() != player->getFirstWeapon()->getAttackType()) {
					cout << "武器不匹配，无法使用该招式" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					validChoice = false;
					break;
				}
				useSkill(player, enemies, skillIndex - 1);  // 使用技能
				break;
			}
			case 3: {  // 切换武器
				if (player->getWeapons()->size() == 1) {  // 检查是否只有一把武器
					cout << player->getName() << "想切换武器，但只有一把武器。" << endl;
					validChoice = false;
					break;
				}
				weaponSwitch(player);  // 切换武器
				player->setActionAvailability(false);  // 设置玩家无法再进行其他行动
				break;
			}
			case 4: {  // 观察敌人状态
				player->setActionAvailability(false);

				cout << player->getName() << "瞪大眼睛，认真地观察场上状况！" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(900));  // 模拟观察时间
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

				// 显示所有敌人的状态
				for (auto& it : *enemies) {
					Character* theCharacter = it;
					showAllStatus(theCharacter);  // 显示敌人详细状态
					cout << "武器:" << theCharacter->getFirstWeapon()->getName() << "(" << theCharacter->getFirstWeapon()->getAttackType() << ")" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟观察延迟
					cout << "护具:" << theCharacter->getFirstArmor()->getName() << "(" << theCharacter->getFirstArmor()->getWeakness() << "是弱点)" << endl << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟观察延迟
				}

				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				cout << "输入1，停止观察:";
				char i;
				cin >> i;  // 玩家结束观察
				break;
			}
			}
		}
		else {
			cout << "无效的输入，请重新输入。" << endl;  // 提示玩家输入有效指令
		}
	}
}

// 处理伤害计算的逻辑
int Battle::takeDamage(Character* target, int damage) {
	if (damage < 0) {  // 如果伤害值为负，表示未造成伤害
		cout << target->getName() << "毫发无损！！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟无伤害时间
		return 0;
	}
	if (target->getAnticipateStatus()) {  // 检查目标是否开启了“预见”状态
		damage *= 0.25;  // 大幅减少伤害
		target->modifyHP(-damage);  // 扣除伤害
		cout << target->getName() << "识破了！抵御了大部分伤害!" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟预见伤害时间
		cout << target->getName() << "受到" << damage << "点伤害!" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟伤害反应时间
		return damage;
	}
	else {
		target->modifyHP(-damage);  // 正常扣除伤害
		cout << target->getName() << "受到" << damage << "点伤害！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟伤害反应时间
		return damage;
	}
}

// 执行普通攻击
void Battle::normalAttack(Character* target, Character* attacker) {
	cout << attacker->getName() << "对" << target->getName() << "使用了普通攻击" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟攻击延迟
	attacker->setActionAvailability(false);  // 设置攻击者无法进行其他行动
	int damage = getDamage(attacker, target, 1.0);  // 计算伤害值
	singleDamagePerform(attacker, target, damage);  // 执行单次伤害评估
}

// 检查攻击是否命中弱点
bool Battle::isHittingWeakness(string theWeakness, string attackType) {
	return (theWeakness == attackType);  // 如果攻击类型与目标弱点匹配，则命中弱点
}

// 检查攻击是否命中
bool Battle::checkHit(float evasionRate, float hitRate) {
	float randomValue = dis(gen);  // 生成随机数用于命中判定
	return randomValue <= hitRate * (1 - evasionRate);  // 根据命中率和闪避率计算是否命中
}

// 切换武器
void Battle::weaponSwitch(Character* character) {
	bool validChoice = false;
	vector<Weapon*>* weapons = character->getWeapons();  // 获取角色的武器列表
	string originalType = character->getFirstWeapon()->getAttackType();  // 获取当前武器的攻击类型
	showWeaponInformationInBattle(character);  // 显示角色的武器信息

	while (!validChoice) {
		cout << "选择要替换的武器的序号:" << endl;
		int index;
		cin >> index;  // 输入要替换的武器索引

		// 检查输入的索引是否合法
		if (index <= 0 || index > weapons->size() - 1) {
			cout << "无效的索引！" << endl;
			continue;
		}

		// 交换武器
		swap(*character->getFirstWeapon(), *((*weapons)[index]));
		cout << "切换成功！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟切换武器延迟
		validChoice = true;

		// 检查武器切换后攻击类型是否发生变化
		string currentType = character->getFirstWeapon()->getAttackType();
		if (currentType != originalType) {
			cout << "由于武器变更，攻击类型由" << originalType << "变为" << currentType << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟提示延迟
		}
	}
}

// 使用技能
void Battle::useSkill(Character* user, vector<Character*>* enemies, int skillIndex) {
	user->setActionAvailability(false);  // 设置用户无法进行其他行动
	user->setSkillPoint(user->getSkillPoint() - 1);  // 消耗一个招式点数
	Skill* theSkill = (*user->getSkills())[skillIndex];  // 获取使用的技能

	if (theSkill->getIsOffensive()) {  // 如果是进攻性技能
		bool ishit = false;

		// 如果是范围攻击技能
		if (theSkill->getIsAOE()) {
			cout << user->getName() << "使用了招式:" << theSkill->getName() << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟技能使用延迟

			// 对所有敌人进行攻击
			for (Character* enemy : *enemies) {
				int damage = getDamage(user, enemy, theSkill->getDamageMultiplier());  // 计算伤害
				if (theSkill->getAttackFrequency() == 1) {
					cout << "对" << enemy->getName() << "的攻击:";
					singleDamagePerform(user, enemy, damage);  // 执行单次伤害
				}
				else {
					int totalDamage = 0;

					// 多次攻击
					for (int i = 0; i < theSkill->getAttackFrequency(); i++) {
						cout << "对" << enemy->getName() << "第" << i + 1 << "次攻击:" << endl;
						totalDamage += singleDamagePerform(user, enemy, damage);  // 逐次执行伤害
					}
					cout << "总计造成" << totalDamage << "点伤害！" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟攻击结束延迟
				}

				// 如果技能不是自我技能，执行效果
				if (!theSkill->getIsSelf())
					effectPerform(user, enemy, theSkill);
			}

			// 如果是自我技能，执行效果
			if (theSkill->getIsSelf())
				effectPerform(user, 0, theSkill);

		}
		else {  // 单体攻击
			showEnemiesInformation(enemies, user->getHitRate());  // 显示敌人信息
			cout << "选择攻击目标:";
			int targetIndex;
			cin >> targetIndex;  // 选择攻击目标
			cout << user->getName() << "对" << (*enemies)[targetIndex - 1]->getName() << "使用了招式:" << theSkill->getName() << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟技能使用延迟

			int damage = getDamage(user, (*enemies)[targetIndex - 1], theSkill->getDamageMultiplier());  // 计算伤害
			if (theSkill->getAttackFrequency() == 1)
				ishit = singleDamagePerform(user, (*enemies)[targetIndex - 1], damage);  // 执行单次伤害
			else {
				int totalDamage = 0;

				// 多次攻击
				for (int i = 0; i < theSkill->getAttackFrequency(); i++) {
					cout << "对" << (*enemies)[targetIndex - 1]->getName() << "第" << i + 1 << "次攻击:" << endl;
					totalDamage += singleDamagePerform(user, (*enemies)[targetIndex - 1], damage);  // 逐次执行伤害
				}
				cout << "总计造成" << totalDamage << "点伤害！！！" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟攻击结束延迟

				// 如果总伤害大于0，表示攻击命中
				if (totalDamage > 0)
					ishit = true;
			}

			// 如果攻击命中，执行技能效果
			if (ishit)
				effectPerform(user, (*enemies)[targetIndex - 1], theSkill);
		}
	}
	else {  // 如果是辅助技能
		if (theSkill->getIsSelf()) {
			effectPerform(user, 0, theSkill);  // 自我技能效果执行
		}
		else {
			if (theSkill->getIsAOE()) {
				cout << user->getName() << "使用了招式:" << theSkill->getName() << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟技能使用延迟

				// 对所有敌人执行效果
				for (Character* enemy : *enemies)
					effectPerform(user, enemy, theSkill);
			}
			else {
				cout << "选择目标:";
				showEnemiesInformation(enemies, 1);  // 显示敌人信息
				int targetIndex;
				cin >> targetIndex;  // 选择辅助技能目标
				cout << user->getName() << "对" << (*enemies)[targetIndex - 1]->getName() << "使用了招式:" << theSkill->getName() << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 模拟技能使用延迟
				effectPerform(user, (*enemies)[targetIndex - 1], theSkill);  // 执行效果
			}
		}
	}
}
// 执行敌人的技能攻击
void Battle::userSkill_enemy(Character* player, Character* enemy, int skillIndex)
{
	// 设置敌人技能使用状态为不可用
	enemy->setActionAvailability(false);

	// 获取敌人所使用的技能
	Skill* theSkill = (*enemy->getSkills())[skillIndex];

	// 如果技能是进攻性技能
	if (theSkill->getIsOffensive())
	{
		bool ishit = false;
		cout << enemy->getName() << "使用了招式:" << theSkill->getName() << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// 计算伤害
		int damage = getDamage(enemy, player, theSkill->getDamageMultiplier());

		// 根据攻击频率决定伤害执行方式
		if (theSkill->getAttackFrequency() == 1)
			ishit = singleDamagePerform(enemy, player, damage);
		else
		{
			int totalDamage = 0;
			for (int i = 0; i < theSkill->getAttackFrequency(); i++)
			{
				cout << "对" << player->getName() << "第" << i + 1 << "次攻击:" << endl;
				totalDamage += singleDamagePerform(enemy, player, damage); // 单次伤害评估
			}
			cout << "总计造成" << totalDamage << "点伤害！" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		// 如果攻击命中，执行技能效果
		if (ishit) effectPerform(enemy, player, theSkill);
	}
	else
	{
		// 如果技能是非进攻性技能
		if (theSkill->getIsSelf())
		{
			cout << enemy->getName() << "使用了招式:" << theSkill->getName() << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			effectPerform(enemy, 0, theSkill); // 执行自身技能效果
		}
		else
		{
			cout << enemy->getName() << "使用了招式:" << theSkill->getName() << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			effectPerform(enemy, player, theSkill); // 执行对敌人技能效果
		}
	}
}

// 计算攻击造成的伤害
int Battle::getDamage(Character* attacker, Character* target, float damageMultiplier)
{
	// 计算基础伤害
	int damage = attacker->getAttack() - target->getDefense();
	damage *= damageMultiplier; // 应用伤害倍数

	// 如果攻击者处于充能状态，伤害翻倍
	if (attacker->getChargeStatus()) damage *= 2;

	// 根据攻击者的行动次数调整伤害
	if (attacker->getActionCount() > 1)
		damage *= attacker->getActionCount() * 0.1 + 1;

	return damage;
}

// 执行单次伤害攻击
int Battle::singleDamagePerform(Character* user, Character* enemy, int damage)
{
	// 检查是否命中
	if (checkHit(enemy->getEvasionRate(), user->getHitRate()))
	{
		// 检查是否命中敌人的弱点
		if (isHittingWeakness(enemy->getFirstArmor()->getWeakness(), user->getFirstWeapon()->getAttackType()) && !enemy->getAnticipateStatus())
		{
			cout << "命中弱点！";
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			damage *= 1.5; // 增加伤害

			// 如果敌人未曾接收到过弱点伤害
			if (!enemy->getWeaknessReceivedStatus())
			{
				// 如果用户是玩家控制，奖励额外行动和技能点
				if (user->isPlayerControlled())
				{
					cout << user->getName() << "获得额外行动与招式点!";
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					user->setSkillPoint(user->getSkillPoint() + 2);
					user->setActionAvailability(true);
					user->setHitWeakness(true);
					enemy->setWeaknessReceivedStatus(true);
				}
				else
				{
					cout << "可以额外行动！" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					user->setActionAvailability(true);
					user->setHitWeakness(true);
					enemy->setWeaknessReceivedStatus(true);
				}
			}
		}

		// 计算并返回伤害
		int returnDamage = takeDamage(enemy, damage);
		return returnDamage;
	}
	else
	{
		cout << "未命中" << enemy->getName() << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return 0;
	}
}

// 执行技能效果
void Battle::effectPerform(Character* user, Character* enemy, Skill* theSkill)
{
	// 根据技能效果类型执行不同的效果
	switch (theSkill->getEffect())
	{
	case selfDefenseBoost:
	case selfEvationBoost:
	case selfHitRateBoost:
	case selfAttackBoost:
	{
		if (!checkAndOffset(user, theSkill))
		{
			// 增加效果到用户
			user->addEffect(theSkill->getEffect(), theSkill->getEffectIntensity(), theSkill->getDuration());
			describeEffect(user, enemy, theSkill);
		}
		else
			describeEffect(user, enemy, theSkill);
		break;
	}

	case selfComatose:
	{
		if (checkHit(0, theSkill->getEffectIntensity()))
		{
			// 使用户处于昏迷状态，并恢复一定HP
			user->setComatoseStatus(true, theSkill->getDuration());
			int gainHP = user->getMaxHP() * 0.75;
			user->modifyHP(gainHP);
			describeEffect(user, enemy, theSkill);
		}
		else
		{
			cout << "但是失败了！" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;
	}

	case selfCharge:
	{
		user->setChargeStatus(true);
		describeEffect(user, enemy, theSkill);
		break;
	}

	case selfAnticipate:
	{
		user->setAnticipateStatus(true);
		describeEffect(user, enemy, theSkill);
		break;
	}

	case selfDamage:
	{
		int damage = user->getMaxHP() * theSkill->getEffectIntensity();
		describeEffect(user, enemy, theSkill);
		takeDamage(user, damage);
		break;
	}

	case giveAttackWeaken:
	case giveHitRateWeaken:
	case giveDefenseWeaken:
	case giveEvationWeaken:
	{
		if (!checkAndOffset(enemy, theSkill))
		{
			// 增加效果到敌人
			enemy->addEffect(theSkill->getEffect(), theSkill->getEffectIntensity(), theSkill->getDuration());
			describeEffect(user, enemy, theSkill);
		}
		else
			describeEffect(user, enemy, theSkill);
		break;
	}

	case giveComatose:
	{
		if (checkHit(0, theSkill->getEffectIntensity()))
		{
			// 使敌人处于昏迷状态
			enemy->setComatoseStatus(true, theSkill->getDuration());
			describeEffect(user, enemy, theSkill);
		}
		else
		{
			cout << enemy->getName() << "没有受到影响！" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;
	}

	case none:
	default:
		break;
	}
}

// 检查技能对角色的效果是否会被现有效果抵消
// 如果发生抵消，返回 true；否则返回 false
bool Battle::checkAndOffset(Character* character, Skill* theSkill)
{
	bool offsetOccurred = false; // 默认未发生抵消
	skillEffectType theType = theSkill->getEffect();
	map<skillEffectType, pair<float, int>>* effectStatus = character->getEffectStatus();

	// 如果没有现有效果，则无法发生抵消
	if (effectStatus->empty())
		return false;

	switch (theType)
	{
	case giveAttackWeaken:
	case selfAttackBoost:
		// 检查并移除与攻击力增加/减少效果冲突的效果
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == selfAttackBoost || it->first == giveAttackWeaken)
			{
				// 检查新效果是否能抵消现有效果
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true; // 发生了抵消
				}
				effectStatus->erase(it++); // 移除效果
			}
			else
			{
				++it; // 移动到下一个效果
			}
		}
		break;

	case giveDefenseWeaken:
	case selfDefenseBoost:
		// 检查并移除与防御力增加/减少效果冲突的效果
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveDefenseWeaken || it->first == selfDefenseBoost)
			{
				// 检查新效果是否能抵消现有效果
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true; // 发生了抵消
				}
				effectStatus->erase(it++); // 移除效果
				break; // 找到匹配效果后直接退出
			}
			else
			{
				++it; // 移动到下一个效果
			}
		}
		break;

	case giveEvationWeaken:
	case selfEvationBoost:
		// 检查并移除与闪避率增加/减少效果冲突的效果
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveEvationWeaken || it->first == selfEvationBoost)
			{
				// 检查新效果是否能抵消现有效果
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true; // 发生了抵消
				}
				effectStatus->erase(it++); // 移除效果
				break; // 找到匹配效果后直接退出
			}
			else
			{
				++it; // 移动到下一个效果
			}
		}
		break;

	case selfHitRateBoost:
	case giveHitRateWeaken:
		// 检查并移除与命中率增加/减少效果冲突的效果
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveHitRateWeaken || it->first == selfHitRateBoost)
			{
				// 检查新效果是否能抵消现有效果
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true; // 发生了抵消
				}
				effectStatus->erase(it++); // 移除效果
			}
			else
			{
				++it; // 移动到下一个效果
			}
		}
		break;

	default:
		break;
	}

	return offsetOccurred; // 返回是否发生了抵消
}

// 管理角色的昏迷状态
void Battle::manageComatoseStatus(Character* theCharacter)
{
	if (theCharacter->getComatoseStatus())
	{
		int currentDuration = theCharacter->getComatoseDuration();
		theCharacter->setComatoseStatus(true, currentDuration - 1);

		if (theCharacter->getComatoseDuration() == 0)
		{
			theCharacter->setComatoseStatus(false, 0);
			cout << theCharacter->getName() << "从昏迷中苏醒过来，可以行动了！" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
		{
			cout << theCharacter->getName() << "昏迷中，无法行动！" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			theCharacter->setActionAvailability(false); // 设置角色为不可行动
		}
	}
}

// 描述技能效果
void Battle::describeEffect(Character* user, Character* enemy, Skill* theSkill)
{
	switch (theSkill->getEffect())
	{
	case selfDefenseBoost:
		if (theSkill->getEffectIntensity() >= 1)
		{
			cout << user->getName() << "防御力大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
		{
			cout << user->getName() << "防御力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;

	case selfEvationBoost:
		cout << user->getName() << "闪避率大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfHitRateBoost:
		cout << user->getName() << "命中率大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfAttackBoost:
		if (theSkill->getEffectIntensity() >= 1)
		{
			cout << user->getName() << "攻击力大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
		{
			cout << user->getName() << "攻击力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;

	case selfComatose:
		cout << user->getName() << "开始睡觉,HP大量恢复了!" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfCharge:
		cout << user->getName() << "正在蓄力，下回合伤害猛增！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfAnticipate:
		cout << user->getName() << "正看破敌方攻势！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfDamage:
		cout << user->getName() << "损耗了自身HP,";
		break;

	case giveAttackWeaken:
		cout << enemy->getName() << "攻击力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case giveHitRateWeaken:
		cout << enemy->getName() << "命中率大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case giveDefenseWeaken:
		cout << enemy->getName() << "防御力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case giveEvationWeaken:
		cout << enemy->getName() << "回避率大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case giveComatose:
		cout << enemy->getName() << "昏迷了！持续" << theSkill->getDuration() << "回合！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	default:
		break;
	}
}

// 显示敌人的信息，包括敌人的名字和命中率
void Battle::showEnemiesInformation(vector<Character*>* enemies, float hitRate) {
	int i = 1; // 用于编号敌人
	float trueHitRate; // 计算的真实命中率

	// 遍历所有敌人
	for (auto& it : *enemies) {
		// 计算真实命中率：考虑敌人的闪避率
		trueHitRate = (1 - it->getEvasionRate()) * hitRate;

		// 输出敌人的编号、名字和计算出的命中率
		cout << i << ":" << it->getName();
		cout << setprecision(3) << "(命中率:" << trueHitRate * 100 << "%)" << endl;
		i++; // 增加敌人的编号
	}
}

// 显示用户的武器信息，包括武器的名称、攻击类型、攻击力和命中率
void Battle::showWeaponInformationInBattle(Character* user) {
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	// 获取用户的武器列表
	vector<Weapon*>* weapons = user->getWeapons();

	// 如果武器列表不为空，则显示每把武器的信息
	if (weapons && !weapons->empty()) {
		for (size_t i = 1; i < weapons->size(); ++i) { // 从第二个武器开始遍历（假设第一个是默认武器）
			cout << "#" << i << " " << (*weapons)[i]->getName(); // 输出武器名称
			cout << " [" << (*weapons)[i]->getAttackType() << "]"; // 输出攻击类型
			cout << " [攻击力+" << (*weapons)[i]->getAttack() << "]"; // 输出攻击力
			cout << " [命中率+" << 100 * (*weapons)[i]->getHitRate() << "%]" << endl; // 输出命中率
		}
	}

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

// 显示用户的技能信息，包括技能的名称、描述、攻击类型和与当前武器的匹配情况
void Battle::showSkillInformationInBattle(Character* user) {
	vector<Skill*>* skills = user->getSkills(); // 获取用户的技能列表
	Weapon* theWeapon = user->getFirstWeapon(); // 获取用户的第一把武器
	int i = 1; // 用于编号技能

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	// 遍历所有技能
	for (auto& it : *skills) {
		if (it->getIsOffensive()) { // 如果技能是进攻性的
			cout << "#" << i << " " << it->getName(); // 输出技能名称
			cout << "【" << it->getDescription(); // 输出技能描述
			cout << "】【" << it->getAttackType(); // 输出技能攻击类型

			// 检查技能的攻击类型是否与武器的攻击类型匹配
			if (it->getAttackType() == theWeapon->getAttackType())
				cout << "(匹配)】" << endl; // 如果匹配，输出"匹配"
			else
				cout << "(冲突)】" << endl; // 如果不匹配，输出"冲突"
		}
		else { // 如果技能是辅助性的
			cout << "#" << i << " " << it->getName(); // 输出技能名称
			cout << "【" << it->getDescription() << "】" << endl; // 输出技能描述
		}
		i++; // 增加技能编号
	}

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

// 显示角色的出手顺序
void Battle::showSpeedLine(vector<pair<int, Character*>> sortedCharacters) {
	int i = 1;
	int max = sortedCharacters.size(); // 获取角色总数

	cout << "出手顺序:"; std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 暂停0.5秒

	// 输出每个角色的名字
	for (auto& it : sortedCharacters) {
		cout << it.second->getName() << " ";
		i++;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 暂停0.5秒
	cout << endl;
}

// 显示战斗开始的信息，包括敌人的数量和敌人的名字
void Battle::showStartInformation(Linchong* player, vector<Character*>* enemies) {
	cout << "战斗开始！" << endl; std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 暂停0.5秒
	cout << "敌人共" << enemies->size() << "人:"; std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 暂停0.5秒

	int i = 1;

	// 输出每个敌人的名字
	for (auto& it : *enemies) {
		cout << "" << it->getName() << " ";
		i++;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 暂停0.5秒
	cout << endl;
}

// 显示角色的所有状态，包括HP、特殊状态和效果
void Battle::showAllStatus(Character* character) {
	map<skillEffectType, pair<float, int>>* theStatus = character->getEffectStatus(); // 获取角色的效果状态
	bool haveStatus = false; // 标记是否有特殊状态
	float hpRate = static_cast<float>(character->getHP()) / character->getMaxHP(); // 计算HP比例

	cout << setprecision(2) << character->getName() << "HP剩余" << character->getHP() << "(" << static_cast<int>(100 * hpRate) << "%)  特殊状态：";

	// 检查并输出角色的特殊状态
	if (character->getChargeStatus()) {
		cout << "已蓄力 ";
		haveStatus = true;
	}
	if (character->getComatoseStatus()) {
		cout << "昏迷不醒 ";
		haveStatus = true;
	}
	if (character->getAnticipateStatus()) {
		cout << "看破 ";
		haveStatus = true;
	}

	if (theStatus->empty()) {
		if (!haveStatus) cout << "无"; // 如果没有状态，输出"无"
		cout << endl;
	}
	else {
		// 遍历并输出所有效果状态
		for (auto& it : *theStatus) {
			switch (it.first) {
			case selfDefenseBoost:
				if ((it.second.first) >= 1)
					cout << "防御力上升(" << it.second.second << ") ";
				else
					cout << "防御力下降(" << it.second.second << ") ";
				break;
			case selfEvationBoost:
				cout << "闪避率上升(" << it.second.second << ") ";
				break;
			case selfHitRateBoost:
				cout << "命中率上升了(" << it.second.second << ") ";
				break;
			case selfAttackBoost:
				if (it.second.first >= 1)
					cout << "攻击力上升(" << it.second.second << ") ";
				else
					cout << "攻击力下降(" << it.second.second << ") ";
				break;
			case giveAttackWeaken:
				cout << "攻击力下降(" << it.second.second << ") ";
				break;
			case giveHitRateWeaken:
				cout << "命中率下降(" << it.second.second << ") ";
				break;
			case giveDefenseWeaken:
				cout << "防御力下降(" << it.second.second << ") ";
				break;
			case giveEvationWeaken:
				cout << "回避率下降(" << it.second.second << ") ";
				break;
			default:
				break;
			}
		}
		cout << endl;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 暂停0.5秒
}

// 按照技能的攻击类型对技能进行排序
void Battle::manageSkillOrder(Character* character) {
	vector<Skill*>* skills = character->getSkills(); // 获取角色的技能列表

	// 稳定分区，将进攻性技能放在前面
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getIsOffensive();
		}
	);

	// 稳定分区，将攻击类型为"打击"的技能放在前面
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "打击";
		}
	);

	// 稳定分区，将攻击类型为"贯通"的技能放在前面
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "贯通";
		}
	);

	// 稳定分区，将攻击类型为"斩击"的技能放在前面
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "斩击";
		}
	);
}

// 准备角色的技能，将辅助技能和进攻技能添加到技能列表中
void Battle::prepareSkill(Character* character) {
	// 清空角色的技能列表
	character->getSkills()->clear();

	vector<Skill*>* skills = character->getSkills(); // 获取角色的技能列表
	vector<offensiveSkill*>* oskills = character->getoSkills(); // 获取角色的进攻技能列表
	vector<supportSkill*>* sskills = character->getsSkills(); // 获取角色的辅助技能列表

	// 如果辅助技能列表不为空，将所有辅助技能添加到技能列表中
	if (!sskills->empty())
		for (auto& it : *sskills) {
			skills->push_back(it);
		}

	// 如果进攻技能列表不为空，将所有进攻技能添加到技能列表中
	if (!oskills->empty())
		for (auto& it : *oskills) {
			skills->push_back(it);
		}
}



