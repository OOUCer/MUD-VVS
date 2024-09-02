#include "battle.h"
using namespace std;
Battle::Battle() : gen(rd()), dis(0.0, 1.0) {}
Battle::~Battle()
{
}
void Battle::startBattle(Linchong* player, vector<Character*>* enemies)
{
	showStartInformation(player, enemies);
	vector<pair<int, Character*>> sortedCharacters;
	sortBySpeed(&sortedCharacters, player, enemies);
	showSpeedLine(sortedCharacters);
	cout << "--------------------------------------------------------" << endl;
	int turn = 1;
	while (true)
	{
		cout << "回合" << turn << "开始！" << endl;

		// 清除上一回合的弱点命中状态,管理基础属性buff状态
		for (auto& it : sortedCharacters)
		{
			Character* theCharacter = it.second;
			manageWeaknessAndBuff(theCharacter);
		}
		for (auto& it : sortedCharacters)
		{
			Character* theCharacter = it.second;
			showAllStatus(theCharacter);
		}
		for (auto& it : sortedCharacters) // 战斗回合
		{
			cout << "现在轮到" << it.second->getName() << "行动" << endl;
			bool chargeFlag = false;
			it.second->setActionAvailability(true);
			manageComatoseStatus(it.second);
			if (it.second->getChargeStatus())
				chargeFlag = true;
			if (it.second->getAnticipateStatus())
			{
				it.second->setAnticipateStatus(false);
				cout << it.second->getName() << "停止了看破！" << endl;
			}
			if (!it.second->isPlayerControlled())
			{
				int actionCount = 0;
				while (it.second->getActionAvailability())
				{
					actionCount++;
					if (actionCount > 1)
						cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！" << endl;
					enemyTurn(it.second, player);
					if (evaluateBattleStatus(sortedCharacters))
						return;
				}
			}
			else
			{
				int actionCount = 0;
				while (it.second->getActionAvailability())
				{
					actionCount++;
					if (actionCount > 1)
						cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！" << endl;
					cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！" << endl;
					cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！" << endl;
					cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！" << endl;
					cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！" << endl;
					cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！" << endl;
					cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！" << endl;
					cout << it.second->getName() << "发动了本回合第" << actionCount << "次行动！" << endl;
					playerTurn(player, enemies);
					if (evaluateBattleStatus(sortedCharacters))
						return;
				}
			}
			if (chargeFlag)
				it.second->setChargeStatus(false);
		}
		turn++;
		cout << "--------------------------------------------------------" << endl;
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
bool Battle::evaluateBattleStatus(vector<pair<int, Character*>>& theCharacters)
{
	for (auto it = theCharacters.begin(); it != theCharacters.end();)
	{
		if (it->second->getHP() <= 0)
		{
			if (it->second->isPlayerControlled())
			{
				cout << "林冲被击败，战斗结束！" << endl;
				return true; // 玩家阵亡，退出战斗
			}
			else
			{
				cout << it->second->getName() << " 被击败了！" << endl;
				it = theCharacters.erase(it); // 移除阵亡的敌人
			}
		}
		else
			it++;
	}
	if (theCharacters.size() == 1 && theCharacters[0].second->isPlayerControlled())
	{
		// 所有敌人已被击败，玩家获胜
		cout << "林冲赢得了战斗胜利！" << endl;
		return true;
	}
	return false; // 继续战斗
}
void Battle::manageWeaknessAndBuff(Character* theCharacter)
{
	theCharacter->setWeaknessReceivedStatus(false);
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
				case selfDefenseBoost:effectName = "防御力"; break;
				case giveEvationWeaken:
				case selfEvationBoost:effectName = "闪避率"; break;
				case giveHitRateWeaken:
				case selfHitRateBoost:effectName = "命中率"; break;
				case giveAttackWeaken:
				case selfAttackBoost:effectName = "攻击力"; break;
				default: break;
				}
				itEffect = theCharacter->getEffectStatus()->erase(itEffect); // 移除效果
				cout << theCharacter->getName() << "的" << effectName << "恢复原状了！" << endl;
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
	normalAttack(player, enemy);
}
void Battle::playerTurn(Character* player, vector<Character*>* enemies)
{
	int choice;
	bool validChoice = false;
	//确保用户输入有效的选择  
	while (!validChoice) {
		cout << "选择行动：1.普通攻击 2.招式 3.切换武器 4.观察对手" << endl;
		cin >> choice;
		if (choice >= 1 && choice <= 4) {
			validChoice = true;
			switch (choice)
			{
			case 1: // 普通攻击  
			{
				cout << "选择攻击对象:" << endl;
				showEnemiesInformation(enemies);
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
				cout << "选择招式:" << endl;
				int skillIndex;
				showSkillInformationInBattle(player);
				cin >> skillIndex;
				if ((*player->getSkills())[skillIndex - 1]->getIsOffensive()
					&& (*player->getSkills())[skillIndex - 1]->getAttackType() != player->getFirstWeapon()->getAttackType())
				{
					cout << "武器不匹配，无法使用该招式" << endl;
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
				player->setActionAvailability(true);
				break;
			}
			case 4: // 观察对手  
			{
				// 实现观察对手的逻辑（如果有的话）  
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
		cout << target->getName() << "毫发无损！！" << endl << endl;
		return 0;
	}
	if (target->getAnticipateStatus())
	{
		damage *= 0.25;
		target->modifyHP(-damage);
		cout << target->getName() << "识破了！抵御了大部分伤害!";
		cout << target->getName() << "受到" << damage << "点伤害!" << endl << endl;
		return damage;
	}
	else
	{
		target->modifyHP(-damage);
		cout << target->getName() << "受到" << damage << "点伤害！" << endl << endl;
		return damage;
	}
}
void Battle::normalAttack(Character* target, Character* attacker)
{
	cout << attacker->getName() << "对" << target->getName() << "使用了普通攻击" << endl;
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
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0, 1.0);
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
		cout << "切换成功！" << endl;
		validChoice = true;
		string currentType = character->getFirstWeapon()->getAttackType();
		if (currentType != originalType)
			cout << "由于武器变更，攻击类型由" << originalType << "变为" << currentType << endl;
	}

}
void Battle::useSkill(Character* user, vector<Character*>* enemies, int skillIndex)
{
	user->setActionAvailability(false);
	Skill* theSkill = (*user->getSkills())[skillIndex];
	if (theSkill->getIsOffensive()) // 如果是进攻性技能
	{
		if (theSkill->getIsAOE()) // 如果是aoe伤害
		{
			cout << user->getName() << "使用了招式:" << theSkill->getName() << endl;
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
						cout << "对" << enemy->getName() << "第" << i << "次攻击:";
						totalDamage += singleDamagePerform(user, enemy, damage); // 单次伤害评估
					}
					cout << "总计造成" << totalDamage << "点伤害！" << endl;
				}
				effectPerform(user, enemy, theSkill);
			}
		}
		else
		{ // 如果是单体伤害
			cout << "选择攻击目标:" << endl;
			showEnemiesInformation(enemies);
			int targetIndex;
			cin >> targetIndex;
			cout << user->getName() << "对" << (*enemies)[targetIndex - 1]->getName() << "使用了招式:" << theSkill->getName() << endl;
			int damage = getDamage(user, (*enemies)[targetIndex - 1], theSkill->getDamageMultiplier());
			if (theSkill->getAttackFrequency() == 1)
				singleDamagePerform(user, (*enemies)[targetIndex - 1], damage);
			else
			{
				int totalDamage = 0;
				for (int i = 0; i < theSkill->getAttackFrequency(); i++)
				{
					cout << "对" << (*enemies)[targetIndex - 1]->getName() << "第" << i + 1 << "次攻击:" << endl;
					totalDamage += singleDamagePerform(user, (*enemies)[targetIndex - 1], damage); // 单次伤害评估
				}
				cout << "总计造成" << totalDamage << "点伤害！！！" << endl;
			}
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
				cout << user->getName() << "使用了招式:" << theSkill->getName() << endl;
				for (Character* enemy : *enemies)
					effectPerform(user, enemy, theSkill);
			}
			else
			{
				cout << "选择目标:" << endl;
				int targetIndex;
				cin >> targetIndex;
				cout << user->getName() << "对" << (*enemies)[targetIndex - 1]->getName() << "使用了招式:" << theSkill->getName() << endl;
				effectPerform(user, (*enemies)[targetIndex - 1], theSkill);
			}
		}

	}
}
int Battle::getDamage(Character* attacker, Character* target, float damageMultiplier)
{
	int damage = attacker->getAttack() - target->getDefense();
	damage *= damageMultiplier;
	if (attacker->getChargeStatus())
	{
		damage *= 2;
	}
	return damage;
}
int Battle::singleDamagePerform(Character* user, Character* enemy, int damage)
{
	if (checkHit(enemy->getEvasionRate(), user->getHitRate()))
	{
		if (isHittingWeakness(enemy->getFirstArmor()->getWeakness(), user->getFirstWeapon()->getAttackType()) && !enemy->getAnticipateStatus())
		{
			cout << "击中了弱点！";
			damage *= 1.5;
			if (!enemy->getWeaknessReceivedStatus())
			{
				cout << user->getName() << "获得额外行动的机会！";
				user->setActionAvailability(true);
				enemy->setWeaknessReceivedStatus(true);
			}
		}
		int returnDamage = takeDamage(enemy, damage);//返回值，用于计算总伤害
		return returnDamage;
	}
	else
	{
		cout << "未命中！" << endl;
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
			user->removeEffect(theSkill->getEffect());
			user->addEffect(theSkill->getEffect(), theSkill->getEffectIntensity(), theSkill->getDuration());
			describeEffect(user, enemy, theSkill);
		}
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
			cout << "但是失败了！" << endl;
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
	case giveAttackWeaken:
	case giveHitRateWeaken:
	case giveDefenseWeaken:
	case giveEvationWeaken:
	{
		enemy->removeEffect(theSkill->getEffect());
		enemy->addEffect(theSkill->getEffect(), theSkill->getEffectIntensity(), theSkill->getDuration());
		describeEffect(user, enemy, theSkill);
		break;
	}
	case giveComatose:
	{
		if (checkHit(0, theSkill->getEffectIntensity()))
		{
			enemy->setComatoseStatus(true, theSkill->getDuration());
			int gainHP = enemy->getMaxHP() * 0.75;
			enemy->modifyHP(gainHP);
			describeEffect(user, enemy, theSkill);
		}
	}
	default:
		break;
	}
}
bool Battle::checkAndOffset(Character* character, Skill* theSkill)//抵消相反效果
{
	bool offsetOccurred = false;
	skillEffectType theType = theSkill->getEffect();
	map<skillEffectType, pair<float, int>>* effectStatus = character->getEffectStatus();
	switch (theType)
	{
	case giveAttackWeaken:
	case selfAttackBoost:
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == selfAttackBoost || it->first == giveAttackWeaken) {
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					effectStatus->erase(it++);
					offsetOccurred = true;
					break;
				}
				++it; // 如果不删除，则移动到下一个元素  
			}
			else {
				++it; // 如果键不匹配，也移动到下一个元素  
			}
		}
		offsetOccurred = true;
		break;
	case giveDefenseWeaken:
	case selfDefenseBoost:
	{
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveDefenseWeaken || it->first == selfDefenseBoost) {
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					effectStatus->erase(it++);
					offsetOccurred = true;
					break;
				}
				++it; // 如果不删除，则移动到下一个元素  
			}
			else {
				++it; // 如果键不匹配，也移动到下一个元素  
			}
		}
		offsetOccurred = true;
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
					effectStatus->erase(it++);
					offsetOccurred = true;
					break;
				}
				++it; // 如果不删除，则移动到下一个元素  
			}
			else {
				++it; // 如果键不匹配，也移动到下一个元素  
			}
		}
		offsetOccurred = true;
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
					effectStatus->erase(it++);
					offsetOccurred = true;
					break;
				}
				++it; // 如果不删除，则移动到下一个元素  
			}
			else {
				++it; // 如果键不匹配，也移动到下一个元素  
			}
		}
		offsetOccurred = true;
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
			cout << theCharacter->getName() << "从昏迷中苏醒过来，可以行动了！" << endl;
		}
		else {
			cout << theCharacter->getName() << "昏迷中，无法行动！" << endl;
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
			cout << user->getName() << "防御力大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
		else
			cout << user->getName() << "防御力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
		break;
	}
	case selfEvationBoost:
	{
		cout << user->getName() << "闪避率大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
		break;
	}
	case selfHitRateBoost:
	{
		cout << user->getName() << "命中率大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
		break;
	}
	case selfAttackBoost:
	{
		if (theSkill->getEffectIntensity() >= 1)
			cout << user->getName() << "攻击力大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
		else
			cout << user->getName() << "攻击力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
		break;
	}
	case selfComatose:
	{
		cout << user->getName() << "开始睡觉,HP大量恢复了!" << endl;
		break;
	}
	case selfCharge:
	{
		cout << user->getName() << "正在蓄力，下回合伤害猛增！" << endl;
		break;
	}
	case selfAnticipate:
	{
		cout << user->getName() << "正看破敌方攻势！" << endl;
		break;
	}
	case giveAttackWeaken:
	{
		cout << enemy->getName() << "攻击力大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
		break;
	}
	case giveHitRateWeaken:
	{
		cout << enemy->getName() << "命中率大幅下降了，持续" << theSkill->getDuration() << "回合！" << endl;
		break;
	}
	case giveDefenseWeaken:
	{
		cout << enemy->getName() << "防御力大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
		break;
	}
	case giveEvationWeaken:
	{
		cout << enemy->getName() << "回避率大幅上升了，持续" << theSkill->getDuration() << "回合！" << endl;
		break;
	}
	case giveComatose:
	{
		cout << enemy->getName() << "昏迷了！持续" << theSkill->getDuration() << "回合！" << endl;
		break;
	}
	default:
		break;
	}
}
void Battle::showEnemiesInformation(vector<Character*>* enemies) {
	int i = 1;
	for (auto& it : *enemies)
	{
		cout << i << ":" << it->getName() << " ";
		i++;
	}
	cout << endl;
}
void Battle::showWeaponInformationInBattle(Character* user)
{
	vector<Weapon*>* weapons = user->getWeapons();
	if (weapons && !weapons->empty()) {
		for (size_t i = 1; i < weapons->size(); ++i) { // 从第二个元素开始遍历  
			cout << "序号:" << i << endl << "名称:" << (*weapons)[i]->getName() << endl;
			cout << "攻击力:" << (*weapons)[i]->getAttack() << endl;
			cout << "命中率加成:" << (*weapons)[i]->getHitRate() << endl;
			cout << "速度:" << (*weapons)[i]->getSpeed() << endl;
			cout << "攻击类型:" << (*weapons)[i]->getAttackType() << endl << endl;
		}
	}
}
void Battle::showSkillInformationInBattle(Character* user)
{
	vector<Skill*>* skills = user->getSkills();
	Weapon* theWeapon = user->getFirstWeapon();
	int i = 1;
	for (auto& it : *skills)
	{
		if (it->getIsOffensive())
		{
			cout << "招式序号:" << i << endl << "招式名称:" << it->getName() << endl;
			cout << "攻击类型:" << it->getAttackType();
			if (it->getAttackType() == theWeapon->getAttackType())
				cout << "（与武器匹配）" << endl;
			else
				cout << "（与武器不匹配）" << endl;
		}
		else
		{
			cout << "招式序号:" << i << endl << "招式名称:" << it->getName() << endl;

		}
		i++;
		cout << endl;
	}
}
void Battle::showSpeedLine(vector<pair<int, Character*>> sortedCharacters)
{
	int i = 1;
	int max = sortedCharacters.size();
	for (auto& it : sortedCharacters)
	{
		if (i == 1)
			cout << "最快出手者:" << it.second->getName() << endl;
		else if (i == max)
			cout << "最慢出手者:" << it.second->getName() << endl;
		else
			cout << "第" << i << "出手者:" << it.second->getName() << endl;
		i++;
	}
	cout << endl;
}
void Battle::showStartInformation(Linchong* player, vector<Character*>* enemies)
{
	cout << "战斗开始了！" << endl << endl;
	cout << "敌人共" << enemies->size() << "人:" << endl;
	showEnemiesInformation(enemies);
}
void Battle::showAllStatus(Character* character)
{
	map<skillEffectType, pair<float, int>>* theStatus = character->getEffectStatus();
	cout << character->getName() << "状态：";
	if (character->getChargeStatus()) cout << "已蓄力 ";
	if (character->getComatoseStatus()) cout << "昏迷不醒 ";
	if (character->getAnticipateStatus()) cout << "看破 ";
	for (auto& it : *theStatus)
	{
	}
	cout << endl;
}
