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
		cout << "�غ�" << turn << "��ʼ��" << endl;
		
		// �����һ�غϵ���������״̬,�����������buff״̬
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

		for (auto& it : sortedCharacters) // ս���غ�
		{
			cout << "�����ֵ�" << it.second->getName() << "�ж�" << endl;
			bool chargeFlag = false;
			it.second->setActionAvailability(true);

			manageComatoseStatus(it.second);

			if (it.second->getChargeStatus())
				chargeFlag = true;

			if (it.second->getAnticipateStatus())
			{
				it.second->setAnticipateStatus(false);
				cout << it.second->getName() << "ֹͣ�˿��ƣ�" << endl;
			}

			if (!it.second->isPlayerControlled())
			{
				int actionCount = 0;
				while (it.second->getActionAvailability())
				{
					actionCount++;
					if (actionCount > 1)
						cout << it.second->getName() << "�����˱��غϵ�" << actionCount << "���ж���" << endl;
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
						cout << it.second->getName() << "�����˱��غϵ�" << actionCount << "���ж���" << endl;
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
				cout << "�ֳ屻���ܣ�ս��������" << endl;
				return true; // ����������˳�ս��
			}
			else
			{
				cout << it->second->getName() << " �������ˣ�" << endl;
				it = theCharacters.erase(it); // �Ƴ������ĵ���
			}
		}
		else
			it++;
	}

	if (theCharacters.size() == 1 && theCharacters[0].second->isPlayerControlled())
	{
		// ���е����ѱ����ܣ���һ�ʤ
		cout << "�ֳ�Ӯ����ս��ʤ����" << endl;
		return true;
	}

	return false; // ����ս��
}

void Battle::manageWeaknessAndBuff(Character* theCharacter)
{
	theCharacter->setWeaknessReceivedStatus(false);
	if (!theCharacter->getEffectStatus()->empty())
	{
		for (auto itEffect = theCharacter->getEffectStatus()->begin(); itEffect != theCharacter->getEffectStatus()->end();)
		{
			itEffect->second.second--; // ����Ч������ʱ��
			if (itEffect->second.second == 0)
			{
				string effectName = "��";
				switch (itEffect->first)
				{
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
				cout << theCharacter->getName() << "��" << effectName << "�ָ�ԭ״�ˣ�" << endl;

			}
			else
			{
				++itEffect; // ���Ч��û�н��������ƶ�����һ��Ԫ��
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

	//ȷ���û�������Ч��ѡ��  
	while (!validChoice) {
		cout << "ѡ���ж���1.��ͨ���� 2.��ʽ 3.�л����� 4.�۲����" << endl;
		cin >> choice; 
		if (choice >= 1 && choice <= 4) {
			validChoice = true;   
			switch (choice)
			{
			case 1: // ��ͨ����  
			{
				cout << "ѡ�񹥻�����:" << endl;
				showEnemiesInformation(enemies);
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
			case 2: // ��ʽ  
			{
				cout << "ѡ����ʽ:" << endl;
				int skillIndex;
				showSkillInformationInBattle(player);
				cin >> skillIndex;
				if ((*player->getSkills())[skillIndex - 1]->getIsOffensive()
					&& (*player->getSkills())[skillIndex - 1]->getAttackType() != player->getFirstWeapon()->getAttackType())
				{
					cout << "������ƥ�䣬�޷�ʹ�ø���ʽ" << endl;
					validChoice = false;
					break;
				}

				useSkill(player, enemies, skillIndex - 1);
				break;
			}
			case 3: // �л�����  
			{
				if (player->getWeapons()->size() == 1)
				{
					cout << player->getName() << "���л���������ֻ��һ��������" << endl;
					validChoice = false;
					break;
				}
				weaponSwitch(player);
				player->setActionAvailability(true);
				break;
			}
			case 4: // �۲����  
			{
				// ʵ�ֹ۲���ֵ��߼�������еĻ���  
				break;
			}
			}
		}
		else {
			cout << "��Ч�����룬���������롣" << endl;
		}
	}
}

int Battle::takeDamage(Character* target, int damage)
{
	if (damage < 0)
	{
		cout << target->getName() << "�������𣡣�" << endl<<endl;
		return 0;
	}
	if (target->getAnticipateStatus())
	{
		damage *= 0.25;
		target->modifyHP(-damage);
		cout << target->getName() << "ʶ���ˣ������˴󲿷��˺�!" ;
		cout << target->getName() << "�ܵ�" << damage << "���˺�!" << endl<<endl;
		return damage;
	}
	else
	{
		target->modifyHP(-damage);
		cout << target->getName() << "�ܵ�" << damage << "���˺���" << endl<<endl;
		return damage;
	}
}

void Battle::normalAttack(Character* target, Character* attacker)
{
	cout << attacker->getName() << "��" << target->getName() << "ʹ������ͨ����" << endl;
	attacker->setActionAvailability(false);
	int damage = getDamage(attacker, target, 1.0);
	singleDamagePerform(attacker, target, damage); // �����˺�����
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
		cout << "ѡ��Ҫ�滻�����������:" << endl;
		int index;
		cin >> index;
		if (index <= 0 || index > weapons->size() - 1) {
			cout << "��Ч��������" << endl;
			continue;
		}
		swap(*character->getFirstWeapon(), *((*weapons)[index]));
		cout << "�л��ɹ���" << endl;
		validChoice = true;
		string currentType = character->getFirstWeapon()->getAttackType();
		if (currentType != originalType)
			cout << "�����������������������"<<originalType<<"��Ϊ" << currentType << endl;
	}
	
}

void Battle::useSkill(Character* user, vector<Character*>* enemies, int skillIndex)
{
	user->setActionAvailability(false);
	Skill* theSkill = (*user->getSkills())[skillIndex];
	if (theSkill->getIsOffensive()) // ����ǽ����Լ���
	{
		if (theSkill->getIsAOE()) // �����aoe�˺�
		{
			cout << user->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
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
						cout << "��" << enemy->getName() << "��" << i << "�ι���:" ;
						totalDamage+=singleDamagePerform(user, enemy, damage); // �����˺�����
					}
					cout << "�ܼ����" << totalDamage << "���˺���" << endl;
				}
				effectPerform(user, enemy, theSkill);
			}
		}
		else
		{ // ����ǵ����˺�
			cout << "ѡ�񹥻�Ŀ��:" << endl;
			showEnemiesInformation(enemies);
			int targetIndex;
			cin >> targetIndex;
			cout << user->getName() << "��" << (*enemies)[targetIndex-1]->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
			int damage = getDamage(user, (*enemies)[targetIndex-1], theSkill->getDamageMultiplier());
			if (theSkill->getAttackFrequency() == 1)
				singleDamagePerform(user, (*enemies)[targetIndex-1], damage);
			else
			{
				int totalDamage = 0;
				for (int i = 0; i < theSkill->getAttackFrequency(); i++)
				{
					cout << "��" << (*enemies)[targetIndex-1]->getName() << "��" << i+1 << "�ι���:" << endl;
					totalDamage+=singleDamagePerform(user, (*enemies)[targetIndex-1], damage); // �����˺�����
				}
				cout << "�ܼ����" << totalDamage << "���˺�������" << endl;
			}
			effectPerform(user, (*enemies)[targetIndex-1], theSkill);
		}
	}
	else // ����Ǹ�������
	{
		if (theSkill->getIsSelf())
		{
			effectPerform(user, 0, theSkill);
		}
		else 
		{
			if (theSkill->getIsAOE())
			{
				cout << user->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
				for (Character* enemy : *enemies)
					effectPerform(user, enemy, theSkill);
			}
			else
			{
				cout << "ѡ��Ŀ��:" << endl;
				int targetIndex;
				cin >> targetIndex;
				cout << user->getName() << "��" << (*enemies)[targetIndex - 1]->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
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
			cout << "���������㣡";
			damage *= 1.5;
			if (!enemy->getWeaknessReceivedStatus())
			{
				cout << user->getName() << "��ö����ж��Ļ��ᣡ";
				user->setActionAvailability(true);
				enemy->setWeaknessReceivedStatus(true);
			}
		}
		int returnDamage=takeDamage(enemy, damage);//����ֵ�����ڼ������˺�
		return returnDamage;
	}
	else
	{
		cout << "δ���У�" << endl;
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
		if (checkAndOffset(user, theSkill))
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
			cout << "����ʧ���ˣ�" << endl;
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
		if (checkAndOffset(enemy, theSkill))
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
			int gainHP = enemy->getMaxHP() * 0.75;
			enemy->modifyHP(gainHP);
			describeEffect(user, enemy, theSkill);
		}
	}

	default:
		break;
	}
}

bool Battle::checkAndOffset(Character* character, Skill* theSkill)//�����෴Ч��
{
	bool offsetOccurred=false;
	skillEffectType theType=theSkill->getEffect();
	map<skillEffectType, pair<float, int>>* effectStatus=character->getEffectStatus();
	switch (theType)
	{
	case giveAttackWeaken:
	case selfAttackBoost:
		for (auto it = effectStatus->begin(); it != effectStatus->end(); ) 
		{
			if (it->first == selfAttackBoost || it->first == giveAttackWeaken) { 
				if (((theSkill->getEffectIntensity()-1) * (it->second.first - 1)) < 0) //������
				{
					effectStatus->erase(it++);  
					offsetOccurred = true;
					break;   
				}
				++it; // �����ɾ�������ƶ�����һ��Ԫ��  
			}
			else {
				++it; // �������ƥ�䣬Ҳ�ƶ�����һ��Ԫ��  
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
				++it; // �����ɾ�������ƶ�����һ��Ԫ��  
			}
			else {
				++it; // �������ƥ�䣬Ҳ�ƶ�����һ��Ԫ��  
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
				++it; // �����ɾ�������ƶ�����һ��Ԫ��  
			}
			else {
				++it; // �������ƥ�䣬Ҳ�ƶ�����һ��Ԫ��  
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
				++it; // �����ɾ�������ƶ�����һ��Ԫ��  
			}
			else {
				++it; // �������ƥ�䣬Ҳ�ƶ�����һ��Ԫ��  
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
			cout << theCharacter->getName() << "�ӻ��������ѹ����������ж��ˣ�" << endl;
		}
		else {
			cout << theCharacter->getName() << "�����У��޷��ж���" << endl;

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
				cout << user->getName() << "��������������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			else
				cout << user->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			break;
		}
		case selfEvationBoost:
		{
			cout << user->getName() << "�����ʴ�������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			break;
		}
		case selfHitRateBoost:
		{
			cout << user->getName() << "�����ʴ�������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			break;
		}
		case selfAttackBoost:
		{
			if(theSkill->getEffectIntensity()>=1)
				cout << user->getName() << "��������������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			else
				cout << user->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			break;
		}
		case selfComatose:
		{
			cout << user->getName() << "��ʼ˯��,HP�����ָ���!" << endl;
			break;
		}
		case selfCharge:
		{
			cout << user->getName() << "�����������»غ��˺�������" << endl;
			break;
		}
		case selfAnticipate:
		{
			cout << user->getName() << "�����Ƶз����ƣ�" << endl;
			break;
		}
		case giveAttackWeaken:
		{
			cout << enemy->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			break;
		}
		case giveHitRateWeaken:
		{
			cout << enemy->getName() << "�����ʴ���½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			break;
		}
		case giveDefenseWeaken:
		{
			cout << enemy->getName() << "��������������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			break;
		}
		case giveEvationWeaken:
		{	
			cout << enemy->getName() << "�ر��ʴ�������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			break;
		}
		case giveComatose:
		{
			cout << enemy->getName() << "�����ˣ�����" << theSkill->getDuration()<<"�غϣ�"<<endl;
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
		for (size_t i = 1; i < weapons->size(); ++i) { // �ӵڶ���Ԫ�ؿ�ʼ����  
			cout <<"���:" << i  << endl << "����:" <<(*weapons)[i]->getName() << endl;
			cout << "������:" << (*weapons)[i]->getAttack() << endl;
			cout << "�����ʼӳ�:" << (*weapons)[i]->getHitRate() << endl;
			cout << "�ٶ�:" << (*weapons)[i]->getSpeed() << endl;
			cout << "��������:" << (*weapons)[i]->getAttackType() << endl<<endl;  
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
			cout << "��ʽ���:" << i << endl << "��ʽ����:" << it->getName() << endl;
			cout << "��������:" << it->getAttackType() ;
			if (it->getAttackType() == theWeapon->getAttackType())
				cout << "��������ƥ�䣩" << endl;
			else
				cout << "����������ƥ�䣩" << endl;

		}
		else
		{
			cout << "��ʽ���:" << i << endl << "��ʽ����:" << it->getName() << endl;
			
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
			cout << "��������:" << it.second->getName() << endl;
		else if (i == max)
			cout << "����������:" << it.second->getName() << endl;
		else
			cout << "��" << i << "������:" << it.second->getName() << endl;
		i++;
	}
	cout << endl;
}

void Battle::showStartInformation(Linchong* player, vector<Character*>* enemies)
{
	cout << "ս����ʼ�ˣ�" << endl<<endl;
	cout << "���˹�" << enemies->size() << "��:" << endl;
	showEnemiesInformation(enemies);
}

void Battle::showAllStatus(Character* character)
{
	map<skillEffectType, pair<float, int>>* theStatus=character->getEffectStatus();
	cout << character->getName() << "״̬��";
	if (character->getChargeStatus()) cout << "������ ";
	if (character->getComatoseStatus()) cout << "���Բ��� ";
	if (character->getAnticipateStatus()) cout << "���� ";
	if (theStatus->empty())
	{
		cout << endl;
		return;
	}
		

	for (auto& it : *theStatus)
	{
		switch (it.first)
		{
		case selfDefenseBoost:
		{
			if ((it.second.first) >= 1)
				cout << "����������(" << it.second.second << ") " << endl;
			else
				cout << "�������½�(" << it.second.second << ") " << endl;
			break;
		}
		case selfEvationBoost:
		{
			cout  << "����������(" << it.second.second << ") " << endl;
			break;
		}
		case selfHitRateBoost:
		{
			cout  << "������������(" << it.second.second << ") " << endl;
			break;
		}
		case selfAttackBoost:
		{
			if (it.second.first >= 1)
				cout  << "����������(" << it.second.second << ") " << endl;
			else
				cout  << "�������½�(" << it.second.second << ") " << endl;
			break;
		}

		case giveAttackWeaken:
		{
			cout  << "�������½�(" << it.second.second << ") ";
			break;
		}
		case giveHitRateWeaken:
		{
			cout  << "�������½�(" << it.second.second << ") " << endl;
			break;
		}
		case giveDefenseWeaken:
		{
			cout  << "�������½�(" << it.second.second << ") " << endl;
			break;
		}
		case giveEvationWeaken:
		{
			cout  << "�ر����½�(" << it.second.second << ") " << endl;
			break;
		}
		default: break;
		}
	}
	cout << endl;
}
