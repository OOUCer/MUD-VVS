#include "battle.h"
//1深蓝色 2绿色 3浅蓝 4红色 5紫色 6橙黄 7白色 8灰色 11蓝绿 12浅红 13紫红 14明黄
using namespace std;
Battle::Battle() : gen(rd()), dis(0.0, 1.0) {}
void SetConsoleColor(int);

void Battle::startBattle(Linchong* player, vector<Character*>* enemies)
{
	player->setSkillPoint(3);
	manageSkillOrder(player);
	showStartInformation(player, enemies);
	vector<pair<int, Character*>> sortedCharacters;
	sortBySpeed(&sortedCharacters, player, enemies);

	showSpeedLine(sortedCharacters);
	cout << "--------------------------------------------------------————————————————————————————————————————" << endl;
	for (auto& it : sortedCharacters)//设置hp为最大HP
	{
		it.second->modifyHP(-it.second->getHP() + it.second->getMaxHP());
	}
	int turn = 1;
	while (true)
	{
		if (turn > 1)
			system("cls");
		cout << "回合数:" << turn << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// 清除上一回合的弱点状态,管理基础属性buff状态
		for (auto& it : sortedCharacters)
		{
			Character* theCharacter = it.second;
			manageWeaknessAndBuff(theCharacter);
		}

		for (auto& it : sortedCharacters)//回合前显示状态
		{
			Character* theCharacter = it.second;
			showAllStatus(theCharacter);
		}
		cout << "--------------------------------------------------------————————————————————————————————————————" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
		
		for (auto& it : sortedCharacters) // 战斗回合开始
		{
			if (it.first == 0)
				continue;
			cout << "现在轮到" << it.second->getName() << "行动！" << endl;

			if (it.second->isPlayerControlled())
				std::this_thread::sleep_for(std::chrono::milliseconds(400));
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(400));

			bool chargeFlag = false;

			it.second->setActionAvailability(true);
			manageComatoseStatus(it.second);
			if (it.second->getChargeStatus())
				chargeFlag = true;
			if (it.second->getAnticipateStatus())
			{
				it.second->setAnticipateStatus(false);
				cout << it.second->getName() << "停止了看破！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			if (!it.second->isPlayerControlled())
			{
				int actionCount = 0;
				while (it.second->getActionAvailability())
				{
					actionCount++;
					it.second->setActionCount(it.second->getActionCount() + 1);
					if (actionCount > 1)
						cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！(伤害+" << it.second->getActionCount() * 10 << "%!!!)" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
					enemyTurn(it.second, player);
					if (evaluateBattleStatus(sortedCharacters, enemies,1))
						return;
				}
			}
			else
			{
				int actionCount = 0;
				while (it.second->getActionAvailability())
				{
					actionCount++;
					it.second->setActionCount(it.second->getActionCount() + 1);
					if (player->getHitWeakness() && (player->getWeapons()->size() != 1))
					{
						cout << "可以额外行动。是否立即切换武器且不消耗行动次数？(y/n)" << endl;
						while (getchar() != '\n'); // 消耗掉直到换行符的所有字符  
						char answer = getchar(); // 现在读取用户的实际输入  
						if (answer == 'y')
							weaponSwitch(player);
					}
					if (actionCount > 1)
					{
						cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！(伤害+" << it.second->getActionCount() * 10 << "%!!!)" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(900));
						for (auto& i : *enemies)//回合前显示状态
						{
							Character* theCharacter = i;
							showAllStatus(theCharacter);
						}
					}
					playerTurn(player, enemies);
					if (evaluateBattleStatus(sortedCharacters, enemies,1))
						return;
				}
			}
			if (chargeFlag)
				it.second->setChargeStatus(false);
		}
		turn++;
		cout << endl << "本回合到此结束！！" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1400));
		if (evaluateBattleStatus(sortedCharacters, enemies,0))
			return;
	}
}

void Battle::sortBySpeed(vector<pair<int, Character*>>* sorted, Linchong* player, vector<Character*>* enemies)
{
	sorted->push_back(make_pair(player->getSpeed(), player));
	for (auto enemy : *enemies)
	{
		sorted->push_back(make_pair(enemy->getSpeed(), enemy));
	}

	sort(sorted->begin(), sorted->end(),
		[](const pair<int, Character*>& a, const pair<int, Character*>& b)
		{ return a.first > b.first; });
}

bool Battle::evaluateBattleStatus(vector<pair<int, Character*>>& theCharacters, vector<Character*>* enemies,int flag)
{
	for (auto it = theCharacters.begin(); it != theCharacters.end();) {
		if (it->second->getHP() <= 0) {
			if (it->second->isPlayerControlled()) {
				cout << "林冲被击败，战斗结束！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				return true; // 玩家阵亡，退出战斗
			}
			else {
				if(it->first != 0) 
					cout << it->second->getName() << " 被击败了！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				it->second->setActionAvailability(false);
				if (flag == 1) {
					it->first = 0;
					it++;
				}
				else
					it = theCharacters.erase(it);
				
			}
		}
		else
			it++;
	}
	for (auto it = enemies->begin(); it != enemies->end();) {
		Character* character = *it; // 解引用迭代器以获取 Character*  
		if (character->getHP() <= 0)
		{
			it = enemies->erase(it); // 移除阵亡的敌人  
		}
		else {
			it++; // 如果敌人未阵亡，则继续迭代  
		}
	}
	if (enemies->size() == 0) {
		// 所有敌人已被击败，玩家获胜
		cout << "林冲赢得了战斗胜利！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return true;
	}
	return false; // 继续战斗
}

void Battle::manageWeaknessAndBuff(Character* theCharacter) {
	theCharacter->setWeaknessReceivedStatus(false);
	theCharacter->setHitWeakness(false);
	theCharacter->setActionCount(0);
	if (!theCharacter->getEffectStatus()->empty())
	{
		for (auto itEffect = theCharacter->getEffectStatus()->begin(); itEffect != theCharacter->getEffectStatus()->end();)
		{
			itEffect->second.second--; // 减少效果持续时间
			if (itEffect->second.second == 0)
			{
				string effectName = "无";
				switch (itEffect->first)
				{
				case giveDefenseWeaken:
				case selfDefenseBoost:effectName = "防御力";break;
				case giveEvationWeaken:
				case selfEvationBoost:effectName = "闪避率";break;
				case giveHitRateWeaken:
				case selfHitRateBoost:effectName = "命中率";break;
				case giveAttackWeaken:
				case selfAttackBoost:effectName = "攻击力";break;
				default: break;
				}
				itEffect = theCharacter->getEffectStatus()->erase(itEffect); // 移除效果
				cout << theCharacter->getName() << "的" << effectName << "恢复原状了！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));

			}
			else
			{
				++itEffect; // 如果效果没有结束，则移动到下一个元素
			}
		}
	}
}

void Battle::enemyTurn(Character* enemy, Character* player)
{
	if (enemy->getSkills()->empty())
	{
		normalAttack(player, enemy);
		return;
	}
	uniform_int_distribution<> dis2(1, enemy->getSkills()->size());
	float randomValue = dis(gen);
	int index = dis2(gen);
	if (randomValue < 0.55)
		normalAttack(player, enemy);
	else
		userSkill_enemy(player, enemy, index - 1);
}

void Battle::playerTurn(Character* player, vector<Character*>* enemies)
{
	int choice;
	bool validChoice = false;
	float hpRate = static_cast<float>(player->getHP()) / player->getMaxHP();
	//确保用户输入有效的选择  
	while (!validChoice) {
		cout << "<HP:" << static_cast<int>(100 * hpRate) << "%> " << "<招式点数:" << player->getSkillPoint()
			<< "> " << "<攻击:" << player->getFirstWeapon()->getAttackType()
			<< "> <" << "弱点:" << player->getFirstArmor()->getWeakness() << ">" << endl << "1.普通攻击 2.招式 3.切换武器 4.观察 " << endl << "选择行动:";
		if (!(cin >> choice)) {
			cin.clear();
#undef max
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "无效的输入，请输入一个数字。" << endl;
			continue;
		}
		if (choice >= 1 && choice <= 4) {
			validChoice = true;
			switch (choice)
			{
			case 1: // 普通攻击  
			{
				showEnemiesInformation(enemies, player->getHitRate());
				cout << "选择攻击对象:";
				int targetIndex;
				cin >> targetIndex;
				if (targetIndex >= 1 && targetIndex <= enemies->size()) {
					normalAttack((*enemies)[targetIndex - 1], player);
				}
				else {
					cout << "无效的敌人索引，请重新输入。" << endl;
				}
				break;
			}
			case 2: // 招式  
			{
				if (player->getSkillPoint() == 0)
				{
					validChoice = false;
					cout << player->getName() << "招式点数不足" << endl;
					break;
				}
				if (player->getSkills()->empty())
				{
					validChoice = false;
					cout << player->getName() << "不会使用招式" << endl;
					break;
				}
				int skillIndex;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				showSkillInformationInBattle(player);
				cout << "选择招式:";
				cin >> skillIndex;
				if ((*player->getSkills())[skillIndex - 1]->getIsOffensive()
					&& (*player->getSkills())[skillIndex - 1]->getAttackType() != player->getFirstWeapon()->getAttackType())
				{
					cout << "武器不匹配，无法使用该招式" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
					validChoice = false;
					break;
				}

				useSkill(player, enemies, skillIndex - 1);
				break;
			}
			case 3: // 切换武器  
			{
				if (player->getWeapons()->size() == 1)
				{
					cout << player->getName() << "想切换武器，但只有一把武器。" << endl;
					validChoice = false;
					break;
				}
				weaponSwitch(player);
				player->setActionAvailability(false);
				break;
			}
			case 4: // 观察对手  
			{
				player->setActionAvailability(false);
				cout << player->getName() << "瞪大眼睛，认真地观察场上状况！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(900));
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				for (auto& it : *enemies)//回合前显示状态
				{
					Character* theCharacter = it;
					showAllStatus(theCharacter);
					cout << "武器:" << theCharacter->getFirstWeapon()->getName() << "(" << theCharacter->getFirstWeapon()->getAttackType() << ")" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
					cout << "护具:" << theCharacter->getFirstArmor()->getName() << "(" << theCharacter->getFirstArmor()->getWeakness() << "是弱点)" << endl << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << "输入1，停止观察:";
				char i;cin >> i;
				break;
			}
			}
		}
		else {
			cout << "无效的输入，请重新输入。" << endl;
		}
	}
}

int Battle::takeDamage(Character* target, int damage)
{
	if (damage < 0)
	{
		cout << target->getName() << "毫发无损！！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return 0;
	}
	if (target->getAnticipateStatus())
	{
		damage *= 0.25;
		target->modifyHP(-damage);
		cout << target->getName() << "识破了！抵御了大部分伤害!";std::this_thread::sleep_for(std::chrono::milliseconds(500));
		cout << target->getName() << "受到" << damage << "点伤害!" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return damage;
	}
	else
	{
		target->modifyHP(-damage);
		cout << target->getName() << "受到" << damage << "点伤害！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return damage;
	}
}

void Battle::normalAttack(Character* target, Character* attacker)
{
	cout << attacker->getName() << "对" << target->getName() << "使用了普通攻击" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
	attacker->setActionAvailability(false);
	int damage = getDamage(attacker, target, 1.0);
	singleDamagePerform(attacker, target, damage); // 单次伤害评估
}

bool Battle::isHittingWeakness(string theWeakness, string attackType)
{

	return (theWeakness == attackType);
}

bool Battle::checkHit(float evasionRate, float hitRate)
{
	float randomValue = dis(gen);
	return randomValue <= hitRate * (1 - evasionRate);
}

void Battle::weaponSwitch(Character* character)
{
	bool validChoice = false;
	vector<Weapon*>* weapons = character->getWeapons();
	string originalType = character->getFirstWeapon()->getAttackType();
	showWeaponInformationInBattle(character);
	while (!validChoice)
	{
		cout << "选择要替换的武器的序号:" << endl;
		int index;
		cin >> index;
		if (index <= 0 || index > weapons->size() - 1) {
			cout << "无效的索引！" << endl;
			continue;
		}
		swap(*character->getFirstWeapon(), *((*weapons)[index]));
		cout << "切换成功！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		validChoice = true;
		string currentType = character->getFirstWeapon()->getAttackType();
		if (currentType != originalType)
		{
			cout << "由于武器变更，攻击类型由" << originalType << "变为" << currentType << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}

}

void Battle::useSkill(Character* user, vector<Character*>* enemies, int skillIndex)
{
	user->setActionAvailability(false);
	user->setSkillPoint(user->getSkillPoint() - 1);
	Skill* theSkill = (*user->getSkills())[skillIndex];
	if (theSkill->getIsOffensive()) // 如果是进攻性技能
	{
		bool ishit=false;
		if (theSkill->getIsAOE()) // 如果是aoe伤害
		{
			cout << user->getName() << "使用了招式:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			for (Character* enemy : *enemies)
			{
				int damage = getDamage(user, enemy, theSkill->getDamageMultiplier());
				if (theSkill->getAttackFrequency() == 1)
					singleDamagePerform(user, enemy, damage);
				else
				{
					int totalDamage = 0;
					for (int i = 0; i < theSkill->getAttackFrequency(); i++)
					{
						cout << "对" << enemy->getName() << "第" << i + 1 << "次攻击:" << endl;
						totalDamage += singleDamagePerform(user, enemy, damage); // 单次伤害评估
					}
					cout << "总计造成" << totalDamage << "点伤害！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
				if (!theSkill->getIsSelf())
					effectPerform(user, enemy, theSkill);
			}
			if (theSkill->getIsSelf()) effectPerform(user, 0, theSkill);
		}
		else
		{ // 如果是单体伤害
			showEnemiesInformation(enemies, user->getHitRate());
			cout << "选择攻击目标:";
			int targetIndex;
			cin >> targetIndex;
			cout << user->getName() << "对" << (*enemies)[targetIndex - 1]->getName() << "使用了招式:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			int damage = getDamage(user, (*enemies)[targetIndex - 1], theSkill->getDamageMultiplier());
			if (theSkill->getAttackFrequency() == 1)
				ishit = singleDamagePerform(user, (*enemies)[targetIndex - 1], damage);
			else
			{
				int totalDamage = 0;
				for (int i = 0; i < theSkill->getAttackFrequency(); i++)
				{
					cout << "对" << (*enemies)[targetIndex - 1]->getName() << "第" << i + 1 << "次攻击:" << endl;
					totalDamage += singleDamagePerform(user, (*enemies)[targetIndex - 1], damage); // 单次伤害评估
				}
				cout << "总计造成" << totalDamage << "点伤害！！！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				if (totalDamage > 0) ishit = 1;
			}
			if (ishit)
				effectPerform(user, (*enemies)[targetIndex - 1], theSkill);
		}
	}
	else // 如果是辅助技能
	{
		if (theSkill->getIsSelf())
		{
			effectPerform(user, 0, theSkill);
		}
		else
		{
			if (theSkill->getIsAOE())
			{
				cout << user->getName() << "使用了招式:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				for (Character* enemy : *enemies)
					effectPerform(user, enemy, theSkill);
			}
			else
			{
				cout << "选择目标:";
				showEnemiesInformation(enemies, 1);
				int targetIndex;
				cin >> targetIndex;
				cout << user->getName() << "对" << (*enemies)[targetIndex - 1]->getName() << "使用了招式:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				effectPerform(user, (*enemies)[targetIndex - 1], theSkill);
			}
		}

	}
}

void Battle::userSkill_enemy(Character* player, Character* enemy, int skillIndex)
{
	enemy->setActionAvailability(false);
	Skill* theSkill = (*enemy->getSkills())[skillIndex];
	if (theSkill->getIsOffensive()) // 如果是进攻性技能
	{
		bool ishit = false;
		cout << enemy->getName() << "使用了招式:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		int damage = getDamage(enemy, player, theSkill->getDamageMultiplier());
		if (theSkill->getAttackFrequency() == 1)
			ishit=singleDamagePerform(enemy, player, damage);
		else
		{
			int totalDamage = 0;
			for (int i = 0; i < theSkill->getAttackFrequency(); i++)
			{
				cout << "对" << player->getName() << "第" << i + 1 << "次攻击:" << endl;
				totalDamage += singleDamagePerform(enemy, player, damage); // 单次伤害评估
			}
			cout << "总计造成" << totalDamage << "点伤害！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		if(ishit) 
			effectPerform(enemy, player, theSkill);
	}
	else // 如果是辅助技能
	{
		if (theSkill->getIsSelf()) {
			cout << enemy->getName() << "使用了招式:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			effectPerform(enemy, 0, theSkill);
		}
		else {
			cout << enemy->getName() << "使用了招式:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			effectPerform(enemy, player, theSkill);
		}
	}
}

int Battle::getDamage(Character* attacker, Character* target, float damageMultiplier)
{
	int damage = attacker->getAttack() - target->getDefense();
	damage *= damageMultiplier;
	if (attacker->getChargeStatus())
		damage *= 2;
	if (attacker->getActionCount() > 1)
		damage *= attacker->getActionCount() * 0.1 + 1;
	return damage;
}

int Battle::singleDamagePerform(Character* user, Character* enemy, int damage)
{
	if (checkHit(enemy->getEvasionRate(), user->getHitRate()))
	{
		if (isHittingWeakness(enemy->getFirstArmor()->getWeakness(), user->getFirstWeapon()->getAttackType()) && !enemy->getAnticipateStatus())
		{
			cout << "命中弱点！";std::this_thread::sleep_for(std::chrono::milliseconds(500));
			damage *= 1.5;
			if (!enemy->getWeaknessReceivedStatus())
			{

				if (user->isPlayerControlled())
				{
					cout << user->getName() << "获得额外行动与招式点!";std::this_thread::sleep_for(std::chrono::milliseconds(500));
					user->setSkillPoint(user->getSkillPoint() + 2);
					user->setActionAvailability(true);
					user->setHitWeakness(true);
					enemy->setWeaknessReceivedStatus(true);
				}
				else
				{
					cout << "可以额外行动！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
					user->setActionAvailability(true);
					user->setHitWeakness(true);
					enemy->setWeaknessReceivedStatus(true);
				}
			}
		}
		int returnDamage = takeDamage(enemy, damage);//返回值，用于计算总伤害
		return returnDamage;
	}
	else
	{
		cout << "未命中" << enemy->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return 0;
	}
}

void Battle::effectPerform(Character* user, Character* enemy, Skill* theSkill)
{
	switch (theSkill->getEffect())
	{

	case selfDefenseBoost:
	case selfEvationBoost:
	case selfHitRateBoost:
	case selfAttackBoost:
	{
		if (!checkAndOffset(user, theSkill))
		{
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
			user->setComatoseStatus(true, theSkill->getDuration());
			int gainHP = user->getMaxHP() * 0.75;
			user->modifyHP(gainHP);
			describeEffect(user, enemy, theSkill);

		}
		else
		{
			cout << "但是失败了！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
	case selfDamage: {
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
			enemy->setComatoseStatus(true, theSkill->getDuration());
			describeEffect(user, enemy, theSkill);
		}
		else
			cout << enemy->getName() << "没有受到影响！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	case none:
	default:
		break;
	}
}

bool Battle::checkAndOffset(Character* character, Skill* theSkill)//抵消相反效果
{
	bool offsetOccurred = false;//默认未抵消

	skillEffectType theType = theSkill->getEffect();
	map<skillEffectType, pair<float, int>>* effectStatus = character->getEffectStatus();
	if (effectStatus->empty())
		return false;
	switch (theType)
	{
	case giveAttackWeaken:
	case selfAttackBoost:
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == selfAttackBoost || it->first == giveAttackWeaken)
			{
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0) //如果相悖
				{
					offsetOccurred = true;//抵消出现  
				}
				effectStatus->erase(it++);
			}
			else {
				++it; // 如果键不匹配，也移动到下一个元素  
			}
		}
		break;
	case giveDefenseWeaken:
	case selfDefenseBoost:
	{
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveDefenseWeaken || it->first == selfDefenseBoost)
			{
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)//如抵消
				{
					offsetOccurred = true;
				}
				effectStatus->erase(it++);
				break;
			}
			else {
				++it; // 如果键不匹配，也移动到下一个元素  
			}
		}
		break;
	}
	case giveEvationWeaken:
	case selfEvationBoost:
	{
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveEvationWeaken || it->first == selfEvationBoost) {
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true;
				}
				effectStatus->erase(it++);
				break;
			}
			else {
				++it; // 如果键不匹配，也移动到下一个元素  
			}
		}
		break;
	}
	case selfHitRateBoost:
	case giveHitRateWeaken:
	{
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveHitRateWeaken || it->first == selfHitRateBoost) {
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true;
				}
				effectStatus->erase(it++);
			}
			else {
				++it; // 如果键不匹配，也移动到下一个元素  
			}
		}
		break;
	}
	default: break;
	}
	return offsetOccurred;
}

void Battle::manageComatoseStatus(Character* theCharacter)
{


	if (theCharacter->getComatoseStatus())
	{
		int currentDuration = theCharacter->getComatoseDuration();
		theCharacter->setComatoseStatus(true, currentDuration - 1);
		if (theCharacter->getComatoseDuration() == 0)
		{
			theCharacter->setComatoseStatus(false, 0);
			cout << theCharacter->getName() << "从昏迷中苏醒过来，可以行动了！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else {
			cout << theCharacter->getName() << "昏迷中，无法行动！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));

			theCharacter->setActionAvailability(false);
		}
	}


}

void Battle::describeEffect(Character* user, Character* enemy, Skill* theSkill)
{
	switch (theSkill->getEffect())
	{

	case selfDefenseBoost:
	{
		if (theSkill->getEffectIntensity() >= 1)
		{
			cout << user->getName() << "防御力大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
		{
			cout << user->getName() << "防御力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;
	}
	case selfEvationBoost:
	{
		cout << user->getName() << "闪避率大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfHitRateBoost:
	{
		cout << user->getName() << "命中率大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfAttackBoost:
	{
		if (theSkill->getEffectIntensity() >= 1)
		{
			cout << user->getName() << "攻击力大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
			cout << user->getName() << "攻击力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfComatose:
	{
		cout << user->getName() << "开始睡觉,HP大量恢复了!" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfCharge:
	{
		cout << user->getName() << "正在蓄力，下回合伤害猛增！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfAnticipate:
	{
		cout << user->getName() << "正看破敌方攻势！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfDamage: {
		cout << user->getName() << "损耗了自身HP,";break;std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	case giveAttackWeaken:
	{
		cout << enemy->getName() << "攻击力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case giveHitRateWeaken:
	{
		cout << enemy->getName() << "命中率大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case giveDefenseWeaken:
	{
		cout << enemy->getName() << "防御力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case giveEvationWeaken:
	{
		cout << enemy->getName() << "回避率大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case giveComatose:
	{
		cout << enemy->getName() << "昏迷了！持续" << theSkill->getDuration() << "回合！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}

	default:
		break;
	}
}

void Battle::showEnemiesInformation(vector<Character*>* enemies, float hitRate) {
	int i = 1;
	float trueHitRate;
	for (auto& it : *enemies)
	{
		trueHitRate = (1 - it->getEvasionRate()) * hitRate;
		cout << i << ":" << it->getName();
		cout << setprecision(3) << "(命中率:" << trueHitRate * 100 << "%)" << endl;;
		i++;
	}
}

void Battle::showWeaponInformationInBattle(Character* user)
{
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	vector<Weapon*>* weapons = user->getWeapons();
	if (weapons && !weapons->empty()) {
		for (size_t i = 1; i < weapons->size(); ++i) { // 从第二个元素开始遍历  
			cout << "#" << i << " " << (*weapons)[i]->getName();
			cout << " [" << (*weapons)[i]->getAttackType() << "]";
			cout << " [攻击力+" << (*weapons)[i]->getAttack() << "]";
			cout << " [命中率+" << 100 * (*weapons)[i]->getHitRate() << "%]" << endl;
		}
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

}

void Battle::showSkillInformationInBattle(Character* user)
{
	vector<Skill*>* skills = user->getSkills();
	Weapon* theWeapon = user->getFirstWeapon();
	int i = 1;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	for (auto& it : *skills)
	{
		if (it->getIsOffensive())
		{
			cout << "#" << i << " " << it->getName();
			cout << "【" << it->getDescription();
			cout << "】【" << it->getAttackType();

			if (it->getAttackType() == theWeapon->getAttackType())
				cout << "(匹配)】" << endl;
			else
				cout << "(冲突)】" << endl;


		}
		else
		{
			cout << "#" << i << " " << it->getName();
			cout << "【" << it->getDescription() << "】" << endl;

		}
		i++;
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void Battle::showSpeedLine(vector<pair<int, Character*>> sortedCharacters)
{
	int i = 1;
	int max = sortedCharacters.size();
	cout << "出手顺序:";std::this_thread::sleep_for(std::chrono::milliseconds(500));
	for (auto& it : sortedCharacters)
	{
		cout << it.second->getName() << " ";
		i++;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << endl;
}

void Battle::showStartInformation(Linchong* player, vector<Character*>* enemies)
{
	cout << "战斗开始！" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << "敌人共" << enemies->size() << "人:";std::this_thread::sleep_for(std::chrono::milliseconds(500));

	int i = 1;
	for (auto& it : *enemies)
	{
		cout << "" << it->getName() << " ";
		i++;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << endl;
}

void Battle::showAllStatus(Character* character)
{
	map<skillEffectType, pair<float, int>>* theStatus = character->getEffectStatus();
	bool haveStatus = false;
	float hpRate = static_cast<float>(character->getHP()) / character->getMaxHP();
	cout << setprecision(2) << character->getName() << "HP剩余" << static_cast<int>(100 * hpRate) << "%  特殊状态：";
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
	if (theStatus->empty())
	{
		if (!haveStatus) cout << "无";
		cout << endl;
	}
	else {
		for (auto& it : *theStatus)
		{
			switch (it.first)
			{
			case selfDefenseBoost:
			{
				if ((it.second.first) >= 1)
					cout << "防御力上升(" << it.second.second << ") ";
				else
					cout << "防御力下降(" << it.second.second << ") ";
				break;
			}
			case selfEvationBoost:
			{
				cout << "闪避率上升(" << it.second.second << ") ";
				break;
			}
			case selfHitRateBoost:
			{
				cout << "命中率上升了(" << it.second.second << ") ";
				break;
			}
			case selfAttackBoost:
			{
				if (it.second.first >= 1)
					cout << "攻击力上升(" << it.second.second << ") ";
				else
					cout << "攻击力下降(" << it.second.second << ") ";
				break;
			}

			case giveAttackWeaken:
			{
				cout << "攻击力下降(" << it.second.second << ") ";
				break;
			}
			case giveHitRateWeaken:
			{
				cout << "命中率下降(" << it.second.second << ") ";
				break;
			}
			case giveDefenseWeaken:
			{
				cout << "防御力下降(" << it.second.second << ") ";
				break;
			}
			case giveEvationWeaken:
			{
				cout << "回避率下降(" << it.second.second << ") ";
				break;
			}
			default: break;
			}
		}
		cout << endl;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Battle::manageSkillOrder(Character* character)
{
	vector<Skill*>* skills = character->getSkills();
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getIsOffensive();
		}
	);
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "打击";
		}
	);
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "贯通";
		}
	);
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "斩击";
		}
	);
}
