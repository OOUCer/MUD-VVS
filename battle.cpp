#include "battle.h"

Battle::Battle() : gen(rd()), dis(0.0, 1.0) {}

void SetConsoleColor(int);//1����ɫ 2��ɫ 3ǳ�� 4��ɫ 5��ɫ 6�Ȼ� 7��ɫ 8��ɫ 11���� 12ǳ�� 13�Ϻ� 14����

void Battle::startBattle(Linchong* player, vector<Character*>* enemies){
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	system("cls");
	player->setSkillPoint(3);
	player->setAnticipateStatus(false);
	player->setChargeStatus(false);
	player->getEffectStatus()->clear();
	showStartInformation(player, enemies);
	vector<pair<int, Character*>> sortedCharacters;
	sortBySpeed(&sortedCharacters, player, enemies);
	showSpeedLine(sortedCharacters);
	cout << "--------------------------------------------------------��������������������������������������������������������������������������������" << endl;
	for (auto& it : sortedCharacters){//����hpΪ���HP
		it.second->modifyHP(-it.second->getHP() + it.second->getMaxHP());
		prepareSkill(it.second);
	}
	int turn = 1;
	manageSkillOrder(player);
	while (true)
	{
		if (turn > 1)
			system("cls");
		cout << "�غ���:" << turn << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// �����һ�غϵ�����״̬,�����������buff״̬
		for (auto& it : sortedCharacters){
			Character* theCharacter = it.second;
			manageWeaknessAndBuff(theCharacter);
		}
		//�غ�ǰ��ʾ״̬
		for (auto& it : sortedCharacters){
			Character* theCharacter = it.second;
			showAllStatus(theCharacter);
		}
		cout << "--------------------------------------------------------��������������������������������������������������������������������������������" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		// ս���غϿ�ʼ
		for (auto& it : sortedCharacters) {
			if (it.first == 0)
				continue;
			cout << "�����ֵ�" << it.second->getName() << "�ж���" << endl;

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
				cout << it.second->getName() << "ֹͣ�˿��ƣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			if (!it.second->isPlayerControlled())
			{
				int actionCount = 0;
				while (it.second->getActionAvailability())
				{
					actionCount++;
					it.second->setActionCount(it.second->getActionCount() + 1);
					if (actionCount > 1)
						cout << it.second->getName() << "�����˱��غϵ�" << actionCount << "���ж���(�˺�+" << it.second->getActionCount() * 10 << "%!!!)" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
					enemyTurn(it.second, player);
					if (evaluateBattleStatus(sortedCharacters, enemies, 1))
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
						cout << "���Զ����ж����Ƿ������л������Ҳ������ж�������(y/n)" << endl;
						while (getchar() != '\n'); // ���ĵ�ֱ�����з��������ַ�  
						char answer = getchar(); // ���ڶ�ȡ�û���ʵ������  
						if (answer == 'y')
							weaponSwitch(player);
					}
					if (actionCount > 1)
					{
						cout << it.second->getName() << "�����˱��غϵ�" << actionCount << "���ж���(�˺�+" << it.second->getActionCount() * 10 << "%!!!)" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(900));
						for (auto& i : *enemies)//�غ�ǰ��ʾ״̬
						{
							Character* theCharacter = i;
							showAllStatus(theCharacter);
						}
					}
					playerTurn(player, enemies);
					if (evaluateBattleStatus(sortedCharacters, enemies, 1))
						return;
				}
			}
			if (chargeFlag)
				it.second->setChargeStatus(false);
		}
		turn++;
		cout << endl << "���غϵ��˽�������" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1400));
		if (evaluateBattleStatus(sortedCharacters, enemies, 0))
			return;
	}
}

void Battle::sortBySpeed(vector<pair<int, Character*>>* sorted, Linchong* player, vector<Character*>* enemies){
	sorted->push_back(make_pair(player->getSpeed(), player));
	for (auto enemy : *enemies){
		sorted->push_back(make_pair(enemy->getSpeed(), enemy));
	}
	sort(sorted->begin(), sorted->end(),
		[](const pair<int, Character*>& a, const pair<int, Character*>& b)
		{ return a.first > b.first; });
}

bool Battle::evaluateBattleStatus(vector<pair<int, Character*>>& theCharacters, vector<Character*>* enemies, int flag)
{
	for (auto it = theCharacters.begin(); it != theCharacters.end();) {
		if (it->second->getHP() <= 0) {
			if (it->second->isPlayerControlled()) {
				cout << "�ֳ屻���ܣ�ս��������" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				it->second->setAnticipateStatus(false);
				it->second->setChargeStatus(false);
				it->second->getEffectStatus()->clear();
				return true; // ����������˳�ս��
			}
			else {
				if (it->first != 0)
					cout << it->second->getName() << " �������ˣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
		Character* character = *it; // �����õ������Ի�ȡ Character*  
		if (character->getHP() <= 0)
		{
			it = enemies->erase(it); // �Ƴ������ĵ���  
		}
		else {
			it++; // �������δ���������������  
		}
	}
	if (enemies->size() == 0) {
		// ���е����ѱ����ܣ���һ�ʤ
		cout << "�ֳ�Ӯ����ս��ʤ����" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return true;
	}
	return false; // ����ս��
}

void Battle::manageWeaknessAndBuff(Character* theCharacter) {
	theCharacter->setWeaknessReceivedStatus(false);
	theCharacter->setHitWeakness(false);
	theCharacter->setActionCount(0);
	if (!theCharacter->getEffectStatus()->empty()){
		for (auto itEffect = theCharacter->getEffectStatus()->begin(); itEffect != theCharacter->getEffectStatus()->end();){
			itEffect->second.second--; // ����Ч������ʱ��
			if (itEffect->second.second == 0){
				string effectName = "��";
				switch (itEffect->first){
				case giveDefenseWeaken:
				case selfDefenseBoost:effectName = "������";break;
				case giveEvationWeaken:
				case selfEvationBoost:effectName = "������";break;
				case giveHitRateWeaken:
				case selfHitRateBoost:effectName = "������";break;
				case giveAttackWeaken:
				case selfAttackBoost:effectName = "������";break;
				default: break;
				}
				itEffect = theCharacter->getEffectStatus()->erase(itEffect); // �Ƴ�Ч��
				cout << theCharacter->getName() << "��" << effectName << "�ָ�ԭ״�ˣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			else{
				++itEffect; // ���Ч��û�н��������ƶ�����һ��Ԫ��
			}
		}
	}
}

void Battle::enemyTurn(Character* enemy, Character* player){
	if (enemy->getSkills()->empty()){
		normalAttack(player, enemy);
		return;
	}
	uniform_int_distribution<> dis2(1, enemy->getSkills()->size());
	float randomValue = dis(gen);
	int index = dis2(gen);
	if (randomValue < 0.45)
		normalAttack(player, enemy);
	else
		userSkill_enemy(player, enemy, index - 1);
}

void Battle::playerTurn(Character* player, vector<Character*>* enemies){
	int choice;
	bool validChoice = false;
	float hpRate = static_cast<float>(player->getHP()) / player->getMaxHP();
	//ȷ���û�������Ч��ѡ��  
	while (!validChoice) {
		cout << "<HP:" << static_cast<int>(100 * hpRate) << "%> " << "<��ʽ����:" << player->getSkillPoint()
			<< "> " << "<����:" << player->getFirstWeapon()->getAttackType()
			<< "> <" << "����:" << player->getFirstArmor()->getWeakness() << ">" << endl << "1.��ͨ���� 2.��ʽ 3.�л����� 4.�۲� " << endl << "ѡ���ж�:";
		if (!(cin >> choice)) {
			cin.clear();
#undef max
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "��Ч�����룬������һ�����֡�" << endl;
			continue;
		}
		if (choice >= 1 && choice <= 4) {
			validChoice = true;
			switch (choice){
			case 1:  {// ��ͨ����
				showEnemiesInformation(enemies, player->getHitRate());
				cout << "ѡ�񹥻�����:";
				int targetIndex;
				cin >> targetIndex;
				if (targetIndex >= 1 && targetIndex <= enemies->size()) {
					normalAttack((*enemies)[targetIndex - 1], player);
				}
				else {
					cout << "��Ч�ĵ������������������롣" << endl;
				}
				break;
			}
			case 2:  {// ��ʽ
				if (player->getSkillPoint() == 0){
					validChoice = false;
					cout << player->getName() << "��ʽ��������" << endl;
					break;
				}
				if (player->getSkills()->empty()){
					validChoice = false;
					cout << player->getName() << "����ʹ����ʽ" << endl;
					break;
				}
				int skillIndex;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				showSkillInformationInBattle(player);
				cout << "ѡ����ʽ:";
				cin >> skillIndex;
				if ((*player->getSkills())[skillIndex - 1]->getIsOffensive()&& (*player->getSkills())[skillIndex - 1]->getAttackType() != player->getFirstWeapon()->getAttackType()){
					cout << "������ƥ�䣬�޷�ʹ�ø���ʽ" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
					validChoice = false;
					break;
				}
				useSkill(player, enemies, skillIndex - 1);
				break;
			}
			case 3:  {// �л�����
				if (player->getWeapons()->size() == 1){
					cout << player->getName() << "���л���������ֻ��һ��������" << endl;
					validChoice = false;
					break;
				}
				weaponSwitch(player);
				player->setActionAvailability(false);
				break;
			}
			case 4:  {// �۲����
				player->setActionAvailability(false);
				cout << player->getName() << "�ɴ��۾�������ع۲쳡��״����" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(900));
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				for (auto& it : *enemies){//�غ�ǰ��ʾ״̬
					Character* theCharacter = it;
					showAllStatus(theCharacter);
					cout << "����:" << theCharacter->getFirstWeapon()->getName() << "(" << theCharacter->getFirstWeapon()->getAttackType() << ")" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
					cout << "����:" << theCharacter->getFirstArmor()->getName() << "(" << theCharacter->getFirstArmor()->getWeakness() << "������)" << endl << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << "����1��ֹͣ�۲�:";
				char i;cin >> i;
				break;
			}
			}
		}
		else {
			cout << "��Ч�����룬���������롣" << endl;
		}
	}
}

int Battle::takeDamage(Character* target, int damage){
	if (damage < 0){
		cout << target->getName() << "�������𣡣�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return 0;
	}
	if (target->getAnticipateStatus()){
		damage *= 0.25;
		target->modifyHP(-damage);
		cout << target->getName() << "ʶ���ˣ������˴󲿷��˺�!";std::this_thread::sleep_for(std::chrono::milliseconds(500));
		cout << target->getName() << "�ܵ�" << damage << "���˺�!" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return damage;
	}
	else{
		target->modifyHP(-damage);
		cout << target->getName() << "�ܵ�" << damage << "���˺���" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return damage;
	}
}

void Battle::normalAttack(Character* target, Character* attacker){
	cout << attacker->getName() << "��" << target->getName() << "ʹ������ͨ����" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
	attacker->setActionAvailability(false);
	int damage = getDamage(attacker, target, 1.0);
	singleDamagePerform(attacker, target, damage); // �����˺�����
}

bool Battle::isHittingWeakness(string theWeakness, string attackType){
	return (theWeakness == attackType);
}

bool Battle::checkHit(float evasionRate, float hitRate){
	float randomValue = dis(gen);
	return randomValue <= hitRate * (1 - evasionRate);
}

void Battle::weaponSwitch(Character* character){
	bool validChoice = false;
	vector<Weapon*>* weapons = character->getWeapons();
	string originalType = character->getFirstWeapon()->getAttackType();
	showWeaponInformationInBattle(character);
	while (!validChoice){
		cout << "ѡ��Ҫ�滻�����������:" << endl;
		int index;
		cin >> index;
		if (index <= 0 || index > weapons->size() - 1) {
			cout << "��Ч��������" << endl;
			continue;
		}
		swap(*character->getFirstWeapon(), *((*weapons)[index]));
		cout << "�л��ɹ���" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		validChoice = true;
		string currentType = character->getFirstWeapon()->getAttackType();
		if (currentType != originalType){
			cout << "�����������������������" << originalType << "��Ϊ" << currentType << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}


void Battle::useSkill(Character* user, vector<Character*>* enemies, int skillIndex){
	user->setActionAvailability(false);
	user->setSkillPoint(user->getSkillPoint() - 1);
	Skill* theSkill = (*user->getSkills())[skillIndex];
	if (theSkill->getIsOffensive()) {// ����ǽ����Լ���
		bool ishit = false;
		if (theSkill->getIsAOE()) {
			cout << user->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			for (Character* enemy : *enemies){
				int damage = getDamage(user, enemy, theSkill->getDamageMultiplier());
				if (theSkill->getAttackFrequency() == 1){
					cout << "��" << enemy->getName() << "�Ĺ���:";
					singleDamagePerform(user, enemy, damage);
				}
				else{
					int totalDamage = 0;
					for (int i = 0; i < theSkill->getAttackFrequency(); i++)
					{
						cout << "��" << enemy->getName() << "��" << i + 1 << "�ι���:" << endl;
						totalDamage += singleDamagePerform(user, enemy, damage); // �����˺�����
					}
					cout << "�ܼ����" << totalDamage << "���˺���" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
				if (!theSkill->getIsSelf())
					effectPerform(user, enemy, theSkill);
			}
			if (theSkill->getIsSelf()) effectPerform(user, 0, theSkill);
		}
		else{ //����
			showEnemiesInformation(enemies, user->getHitRate());
			cout << "ѡ�񹥻�Ŀ��:";
			int targetIndex;
			cin >> targetIndex;
			cout << user->getName() << "��" << (*enemies)[targetIndex - 1]->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			int damage = getDamage(user, (*enemies)[targetIndex - 1], theSkill->getDamageMultiplier());
			if (theSkill->getAttackFrequency() == 1)
				ishit = singleDamagePerform(user, (*enemies)[targetIndex - 1], damage);
			else{
				int totalDamage = 0;
				for (int i = 0; i < theSkill->getAttackFrequency(); i++){
					cout << "��" << (*enemies)[targetIndex - 1]->getName() << "��" << i + 1 << "�ι���:" << endl;
					totalDamage += singleDamagePerform(user, (*enemies)[targetIndex - 1], damage); // �����˺�����
				}
				cout << "�ܼ����" << totalDamage << "���˺�������" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				if (totalDamage > 0) ishit = 1;
			}
			if (ishit)
				effectPerform(user, (*enemies)[targetIndex - 1], theSkill);
		}
	}
	else {// ����Ǹ�������
		if (theSkill->getIsSelf()){
			effectPerform(user, 0, theSkill);
		}
		else{
			if (theSkill->getIsAOE()){
				cout << user->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				for (Character* enemy : *enemies)
					effectPerform(user, enemy, theSkill);
			}
			else{
				cout << "ѡ��Ŀ��:";
				showEnemiesInformation(enemies, 1);
				int targetIndex;
				cin >> targetIndex;
				cout << user->getName() << "��" << (*enemies)[targetIndex - 1]->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
				effectPerform(user, (*enemies)[targetIndex - 1], theSkill);
			}
		}

	}
}

void Battle::userSkill_enemy(Character* player, Character* enemy, int skillIndex)
{
	enemy->setActionAvailability(false);
	Skill* theSkill = (*enemy->getSkills())[skillIndex];
	if (theSkill->getIsOffensive()) // ����ǽ����Լ���
	{
		bool ishit = false;
		cout << enemy->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		int damage = getDamage(enemy, player, theSkill->getDamageMultiplier());
		if (theSkill->getAttackFrequency() == 1)
			ishit = singleDamagePerform(enemy, player, damage);
		else
		{
			int totalDamage = 0;
			for (int i = 0; i < theSkill->getAttackFrequency(); i++){
				cout << "��" << player->getName() << "��" << i + 1 << "�ι���:" << endl;
				totalDamage += singleDamagePerform(enemy, player, damage); // �����˺�����
			}
			cout << "�ܼ����" << totalDamage << "���˺���" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		if (ishit) effectPerform(enemy, player, theSkill);
	}
	else {
		if (theSkill->getIsSelf()) {
			cout << enemy->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			effectPerform(enemy, 0, theSkill);
		}
		else {
			cout << enemy->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			effectPerform(enemy, player, theSkill);
		}
	}
}

int Battle::getDamage(Character* attacker, Character* target, float damageMultiplier)
{
	int damage = attacker->getAttack() - target->getDefense();
	damage *= damageMultiplier;
	if (attacker->getChargeStatus()) damage *= 2;
	if (attacker->getActionCount() > 1) damage *= attacker->getActionCount() * 0.1 + 1;
	return damage;
}

int Battle::singleDamagePerform(Character* user, Character* enemy, int damage)
{
	if (checkHit(enemy->getEvasionRate(), user->getHitRate())){
		if (isHittingWeakness(enemy->getFirstArmor()->getWeakness(), user->getFirstWeapon()->getAttackType()) && !enemy->getAnticipateStatus()){
			cout << "�������㣡";std::this_thread::sleep_for(std::chrono::milliseconds(500));
			damage *= 1.5;
			if (!enemy->getWeaknessReceivedStatus()){
				if (user->isPlayerControlled()){
					cout << user->getName() << "��ö����ж�����ʽ��!";std::this_thread::sleep_for(std::chrono::milliseconds(500));
					user->setSkillPoint(user->getSkillPoint() + 2);
					user->setActionAvailability(true);
					user->setHitWeakness(true);
					enemy->setWeaknessReceivedStatus(true);
				}
				else{
					cout << "���Զ����ж���" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
					user->setActionAvailability(true);
					user->setHitWeakness(true);
					enemy->setWeaknessReceivedStatus(true);
				}
			}
		}
		int returnDamage = takeDamage(enemy, damage);//����ֵ�����ڼ������˺�
		return returnDamage;
	}
	else{
		cout << "δ����" << enemy->getName() << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return 0;
	}
}

void Battle::effectPerform(Character* user, Character* enemy, Skill* theSkill){
	switch (theSkill->getEffect()){
	case selfDefenseBoost:
	case selfEvationBoost:
	case selfHitRateBoost:
	case selfAttackBoost:{
		if (!checkAndOffset(user, theSkill)){
			user->addEffect(theSkill->getEffect(), theSkill->getEffectIntensity(), theSkill->getDuration());
			describeEffect(user, enemy, theSkill);
		}
		else
			describeEffect(user, enemy, theSkill);
		break;
	}
	case selfComatose:{
		if (checkHit(0, theSkill->getEffectIntensity())){
			user->setComatoseStatus(true, theSkill->getDuration());
			int gainHP = user->getMaxHP() * 0.75;
			user->modifyHP(gainHP);
			describeEffect(user, enemy, theSkill);

		}
		else{
			cout << "����ʧ���ˣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;
	}
	case selfCharge:{
		user->setChargeStatus(true);
		describeEffect(user, enemy, theSkill);
		break;
	}
	case selfAnticipate:{
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
	case giveEvationWeaken:{
		if (!checkAndOffset(enemy, theSkill))
		{
			enemy->addEffect(theSkill->getEffect(), theSkill->getEffectIntensity(), theSkill->getDuration());
			describeEffect(user, enemy, theSkill);
		}
		else
			describeEffect(user, enemy, theSkill);
		break;
	}
	case giveComatose:{
		if (checkHit(0, theSkill->getEffectIntensity()))
		{
			enemy->setComatoseStatus(true, theSkill->getDuration());
			describeEffect(user, enemy, theSkill);
		}
		else
			cout << enemy->getName() << "û���ܵ�Ӱ�죡" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	case none:
	default:break;
	}
}

bool Battle::checkAndOffset(Character* character, Skill* theSkill){
	bool offsetOccurred = false;//Ĭ��δ����
	skillEffectType theType = theSkill->getEffect();
	map<skillEffectType, pair<float, int>>* effectStatus = character->getEffectStatus();
	if (effectStatus->empty())
		return false;
	switch (theType){
	case giveAttackWeaken:
	case selfAttackBoost:
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == selfAttackBoost || it->first == giveAttackWeaken){
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0) {
					offsetOccurred = true;//��������  
				}
				effectStatus->erase(it++);
			}
			else {
				++it; // �������ƥ�䣬Ҳ�ƶ�����һ��Ԫ��  
			}
		}
		break;
	case giveDefenseWeaken:
	case selfDefenseBoost:{
		for (auto it = effectStatus->begin(); it != effectStatus->end(); ){
			if (it->first == giveDefenseWeaken || it->first == selfDefenseBoost){
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0){//�������
					offsetOccurred = true;
				}
				effectStatus->erase(it++);
				break;
			}
			else {
				++it; // �������ƥ�䣬Ҳ�ƶ�����һ��Ԫ��  
			}
		}
		break;
	}
	case giveEvationWeaken:
	case selfEvationBoost:{
		for (auto it = effectStatus->begin(); it != effectStatus->end(); ){
			if (it->first == giveEvationWeaken || it->first == selfEvationBoost) {
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0){
					offsetOccurred = true;
				}
				effectStatus->erase(it++);
				break;
			}
			else {
				++it; // �������ƥ�䣬Ҳ�ƶ�����һ��Ԫ��  
			}
		}
		break;
	}
	case selfHitRateBoost:
	case giveHitRateWeaken:{
		for (auto it = effectStatus->begin(); it != effectStatus->end(); ){
			if (it->first == giveHitRateWeaken || it->first == selfHitRateBoost) {
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0){
					offsetOccurred = true;
				}
				effectStatus->erase(it++);
			}
			else {
				++it; // �������ƥ�䣬Ҳ�ƶ�����һ��Ԫ��  
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
	if (theCharacter->getComatoseStatus()){
		int currentDuration = theCharacter->getComatoseDuration();
		theCharacter->setComatoseStatus(true, currentDuration - 1);
		if (theCharacter->getComatoseDuration() == 0){
			theCharacter->setComatoseStatus(false, 0);
			cout << theCharacter->getName() << "�ӻ��������ѹ����������ж��ˣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else {
			cout << theCharacter->getName() << "�����У��޷��ж���" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
			theCharacter->setActionAvailability(false);
		}
	}
}

void Battle::describeEffect(Character* user, Character* enemy, Skill* theSkill)
{
	switch (theSkill->getEffect()){
	case selfDefenseBoost:{
		if (theSkill->getEffectIntensity() >= 1){
			cout << user->getName() << "��������������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else{
			cout << user->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;
	}
	case selfEvationBoost:{
		cout << user->getName() << "�����ʴ�������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfHitRateBoost:{
		cout << user->getName() << "�����ʴ�������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfAttackBoost:{
		if (theSkill->getEffectIntensity() >= 1)
		{
			cout << user->getName() << "��������������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
			cout << user->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfComatose:{
		cout << user->getName() << "��ʼ˯��,HP�����ָ���!" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfCharge:{
		cout << user->getName() << "�����������»غ��˺�������" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfAnticipate:{
		cout << user->getName() << "�����Ƶз����ƣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case selfDamage: {
		cout << user->getName() << "���������HP,";break;std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	case giveAttackWeaken:{
		cout << enemy->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case giveHitRateWeaken:{
		cout << enemy->getName() << "�����ʴ���½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case giveDefenseWeaken:{
		cout << enemy->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case giveEvationWeaken:{
		cout << enemy->getName() << "�ر��ʴ���½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	case giveComatose:{
		cout << enemy->getName() << "�����ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	default:
		break;
	}
}

void Battle::showEnemiesInformation(vector<Character*>* enemies, float hitRate) {
	int i = 1;
	float trueHitRate;
	for (auto& it : *enemies){
		trueHitRate = (1 - it->getEvasionRate()) * hitRate;
		cout << i << ":" << it->getName();
		cout << setprecision(3) << "(������:" << trueHitRate * 100 << "%)" << endl;;
		i++;
	}
}

void Battle::showWeaponInformationInBattle(Character* user){
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	vector<Weapon*>* weapons = user->getWeapons();
	if (weapons && !weapons->empty()) {
		for (size_t i = 1; i < weapons->size(); ++i) { // �ӵڶ���Ԫ�ؿ�ʼ����  
			cout << "#" << i << " " << (*weapons)[i]->getName();
			cout << " [" << (*weapons)[i]->getAttackType() << "]";
			cout << " [������+" << (*weapons)[i]->getAttack() << "]";
			cout << " [������+" << 100 * (*weapons)[i]->getHitRate() << "%]" << endl;
		}
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void Battle::showSkillInformationInBattle(Character* user){
	vector<Skill*>* skills = user->getSkills();
	Weapon* theWeapon = user->getFirstWeapon();
	int i = 1;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	for (auto& it : *skills){
		if (it->getIsOffensive()){
			cout << "#" << i << " " << it->getName();
			cout << "��" << it->getDescription();
			cout << "����" << it->getAttackType();

			if (it->getAttackType() == theWeapon->getAttackType())
				cout << "(ƥ��)��" << endl;
			else
				cout << "(��ͻ)��" << endl;
		}
		else{
			cout << "#" << i << " " << it->getName();
			cout << "��" << it->getDescription() << "��" << endl;
		}
		i++;
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void Battle::showSpeedLine(vector<pair<int, Character*>> sortedCharacters){
	int i = 1;
	int max = sortedCharacters.size();
	cout << "����˳��:";std::this_thread::sleep_for(std::chrono::milliseconds(500));
	for (auto& it : sortedCharacters){
		cout << it.second->getName() << " ";
		i++;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << endl;
}

void Battle::showStartInformation(Linchong* player, vector<Character*>* enemies){
	cout << "ս����ʼ��" << endl;std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << "���˹�" << enemies->size() << "��:";std::this_thread::sleep_for(std::chrono::milliseconds(500));
	int i = 1;
	for (auto& it : *enemies){
		cout << "" << it->getName() << " ";
		i++;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << endl;
}

void Battle::showAllStatus(Character* character){
	map<skillEffectType, pair<float, int>>* theStatus = character->getEffectStatus();
	bool haveStatus = false;
	float hpRate = static_cast<float>(character->getHP()) / character->getMaxHP();
	cout << setprecision(2) << character->getName() << "HPʣ��" << character->getHP()<<"("<< static_cast<int>(100 * hpRate) << "%)  ����״̬��";
	if (character->getChargeStatus()) {
		cout << "������ ";
		haveStatus = true;
	}
	if (character->getComatoseStatus()) {
		cout << "���Բ��� ";
		haveStatus = true;
	}
	if (character->getAnticipateStatus()) {
		cout << "���� ";
		haveStatus = true;
	}
	if (theStatus->empty()){
		if (!haveStatus) cout << "��";
		cout << endl;
	}
	else {
		for (auto& it : *theStatus){
			switch (it.first){
			case selfDefenseBoost:{
				if ((it.second.first) >= 1)
					cout << "����������(" << it.second.second << ") ";
				else
					cout << "�������½�(" << it.second.second << ") ";
				break;
			}
			case selfEvationBoost:{
				cout << "����������(" << it.second.second << ") ";
				break;
			}
			case selfHitRateBoost:{
				cout << "������������(" << it.second.second << ") ";
				break;
			}
			case selfAttackBoost: {
				if (it.second.first >= 1)
					cout << "����������(" << it.second.second << ") ";
				else
					cout << "�������½�(" << it.second.second << ") ";
				break;
			}
			case giveAttackWeaken:{
				cout << "�������½�(" << it.second.second << ") ";
				break;
			}
			case giveHitRateWeaken:{
				cout << "�������½�(" << it.second.second << ") ";
				break;
			}
			case giveDefenseWeaken:{
				cout << "�������½�(" << it.second.second << ") ";
				break;
			}
			case giveEvationWeaken:{
				cout << "�ر����½�(" << it.second.second << ") ";
				break;
			}
			default: break;
			}
		}
		cout << endl;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Battle::manageSkillOrder(Character* character){
	vector<Skill*>* skills = character->getSkills();
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getIsOffensive();
		}
	);
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "���";
		}
	);
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "��ͨ";
		}
	);
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "ն��";
		}
	);
}

void Battle::prepareSkill(Character* character){
	character->getSkills()->clear();
	vector<Skill*>* skills = character->getSkills();
	vector<offensiveSkill*>* oskills = character->getoSkills();
	vector<supportSkill *>* sskills = character->getsSkills();
	if(!sskills->empty())
		for (auto& it : *sskills) {
		skills->push_back(it);
		}
	if(!oskills->empty())
		for (auto& it : *oskills) {
			skills->push_back(it);
		}
}


