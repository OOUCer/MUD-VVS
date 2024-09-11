#include"battle.h"

// Battle ��Ĺ��캯������ʼ�������������
Battle::Battle() : gen(rd()), dis(0.0, 1.0) {}

// ���ÿ���̨��ɫ����������Ϊ��ɫ����
void SetConsoleColor(int);// 1����ɫ 2��ɫ 3ǳ�� 4��ɫ 5��ɫ 6�Ȼ� 7��ɫ 8��ɫ 11���� 12ǳ�� 13�Ϻ� 14����

// ��ʼս����������Ҷ���͵����б�
void Battle::startBattle(Linchong* player, vector<Character*>* enemies) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));  // ��ʱ 1.5 �룬ģ��ս������
	system("cls");  // ����
	player->setSkillPoint(3);  // ��ʼ����Ҽ��ܵ���
	player->setAnticipateStatus(false);  // ��ʼ������״̬
	player->setChargeStatus(false);  // ��ʼ������״̬
	player->getEffectStatus()->clear();  // �����ҵ�Ч��״̬
	showStartInformation(player, enemies);  // ��ʾս����ʼ��Ϣ
	vector<pair<int, Character*>> sortedCharacters;  // ���ٶ�����Ľ�ɫ�б�
	sortBySpeed(&sortedCharacters, player, enemies);  // ����ɫ�ٶȽ�������
	showSpeedLine(sortedCharacters);  // ��ʾ�����Ľ�ɫ�ж�˳��
	cout << "--------------------------------------------------------��������������������������������������������������������������������������������" << endl;
	for (auto& it : sortedCharacters) {  // ����ÿ����ɫ�� HP Ϊ����� HP
		it.second->modifyHP(-it.second->getHP() + it.second->getMaxHP());
		prepareSkill(it.second);  // ׼����ɫ�ļ���
	}
	int turn = 1;  // �غϼ���
	manageSkillOrder(player);  // ������Ҽ��ܵ�˳��

	while (true)
	{
		if (turn > 1)
			system("cls");  // ������ǵ�һ���غϣ�����
		cout << "�غ���:" << turn << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// �����һ�غϵ�����״̬������������� buff ״̬
		for (auto& it : sortedCharacters) {
			Character* theCharacter = it.second;
			manageWeaknessAndBuff(theCharacter);  // �����ɫ������� buff ״̬
		}

		// �غ�ǰ��ʾ״̬
		for (auto& it : sortedCharacters) {
			Character* theCharacter = it.second;
			showAllStatus(theCharacter);  // ��ʾ����״̬
		}
		cout << "--------------------------------------------------------��������������������������������������������������������������������������������" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// ս���غϿ�ʼ
		for (auto& it : sortedCharacters) {
			if (it.first == 0)
				continue;  // �����������Ľ�ɫ
			cout << "�����ֵ�" << it.second->getName() << "�ж���" << endl;

			// ��ʱģ���ж��Ľ���
			if (it.second->isPlayerControlled())
				std::this_thread::sleep_for(std::chrono::milliseconds(400));
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(400));

			bool chargeFlag = false;  // ����Ƿ�������״̬

			it.second->setActionAvailability(true);  // ���ý�ɫ���ж�״̬Ϊ���ж�
			manageComatoseStatus(it.second);  // �������״̬
			if (it.second->getChargeStatus())
				chargeFlag = true;  // �����ɫ��������״̬�����ñ��Ϊ true

			if (it.second->getAnticipateStatus())  // �����ɫ���ڿ���״̬
			{
				it.second->setAnticipateStatus(false);  // ֹͣ����״̬
				cout << it.second->getName() << "ֹͣ�˿��ƣ�" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}

			// ����ҽ�ɫ�ж�
			if (!it.second->isPlayerControlled())
			{
				int actionCount = 0;  // �ж���������
				while (it.second->getActionAvailability())  // �����ɫ�����ж�
				{
					actionCount++;
					it.second->setActionCount(it.second->getActionCount() + 1);  // �����ж�����
					if (actionCount > 1)
						cout << it.second->getName() << "�����˱��غϵ�" << actionCount << "���ж���(�˺�+" << it.second->getActionCount() * 10 << "%!!!)" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					enemyTurn(it.second, player);  // �з���ɫ�Ļغϲ���
					if (evaluateBattleStatus(sortedCharacters, enemies, 1))
						return;  // ���ս���������˳�����
				}
			}
			else  // ��ҽ�ɫ�ж�
			{
				int actionCount = 0;
				while (it.second->getActionAvailability())
				{
					actionCount++;
					it.second->setActionCount(it.second->getActionCount() + 1);  // ������ҵ��ж�����
					if (player->getHitWeakness() && (player->getWeapons()->size() != 1))  // ����������������
					{
						cout << "���Զ����ж����Ƿ������л������Ҳ������ж�������(y/n)" << endl;
						while (getchar() != '\n');  // ������뻺����
						char answer = getchar();  // ��ȡ�������
						if (answer == 'y')
							weaponSwitch(player);  // �л�����
					}
					if (actionCount > 1)  // ����ǵڶ��λ������ж�
					{
						cout << it.second->getName() << "�����˱��غϵ�" << actionCount << "���ж���(�˺�+" << it.second->getActionCount() * 10 << "%!!!)" << endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(900));
						for (auto& i : *enemies)
						{
							Character* theCharacter = i;
							showAllStatus(theCharacter);  // ��ʾ���˵�״̬
						}
					}
					playerTurn(player, enemies);  // ��һغϲ���
					if (evaluateBattleStatus(sortedCharacters, enemies, 1))
						return;  // ���ս���������˳�����
				}
			}

			// �����ɫ��������״̬���غϽ�������������״̬
			if (chargeFlag)
				it.second->setChargeStatus(false);
		}

		turn++;  // ���ӻغϼ���
		cout << endl << "���غϵ��˽�������" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1400));
		if (evaluateBattleStatus(sortedCharacters, enemies, 0))
			return;  // ���ս���������˳�����
	}
}

// ���ݽ�ɫ�ٶȽ��������ٶȸߵĽ�ɫ�����ж�
void Battle::sortBySpeed(vector<pair<int, Character*>>* sorted, Linchong* player, vector<Character*>* enemies) {
	sorted->push_back(make_pair(player->getSpeed(), player));  // ����Ҽ��������б�
	for (auto enemy : *enemies) {
		sorted->push_back(make_pair(enemy->getSpeed(), enemy));  // ��ÿ�����˼��������б�
	}
	// ���ٶȴӸߵ�������
	sort(sorted->begin(), sorted->end(),
		[](const pair<int, Character*>& a, const pair<int, Character*>& b)
		{ return a.first > b.first; });
}

// ����ս��״̬���ж�ս���Ƿ����
bool Battle::evaluateBattleStatus(vector<pair<int, Character*>>& theCharacters, vector<Character*>* enemies, int flag)
{
	// ������ɫ�б�����ɫ�Ƿ�����
	for (auto it = theCharacters.begin(); it != theCharacters.end();) {
		if (it->second->getHP() <= 0) {  // �����ɫ HP С�ڵ��� 0
			if (it->second->isPlayerControlled()) {  // ����������
				cout << "�ֳ屻���ܣ�ս��������" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				it->second->setAnticipateStatus(false);  // ���ÿ���״̬
				it->second->setChargeStatus(false);  // ��������״̬
				it->second->getEffectStatus()->clear();  // ���Ч��״̬
				return true;  // ����������˳�ս��
			}
			else {
				if (it->first != 0)
					cout << it->second->getName() << " �������ˣ�" << endl; std::this_thread::sleep_for(std::chrono::milliseconds(500));
				it->first = 0;  // �����˵��ٶ�����Ϊ 0����ʾ��������
				it++;
				if (flag == 1)  // ���ս�����ڼ���
				{
					int leftEnemies = enemies->size();
					for (auto i : *enemies)
					{
						if (i->getHP() <= 0)  // ����ʣ�������Ŀ
							leftEnemies--;
					}
					if (leftEnemies == 0) {  // ������е��˶�������
						cout << "����ȫ�������ܣ��ֳ�����ʤ����" << endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(500));
						return true;  // ս��ʤ�����˳�
					}
				}
			}
		}
		else {
			it++;
		}
	}
	return false;  // ս��δ����
}

// �����ɫ�����������Ч��
void Battle::manageWeaknessAndBuff(Character* theCharacter) {
	theCharacter->setWeaknessReceivedStatus(false);  // �����������״̬
	theCharacter->setHitWeakness(false);  // ������������״̬
	theCharacter->setActionCount(0);  // �����ж�����

	// ����ɫ�Ƿ���Ч��״̬
	if (!theCharacter->getEffectStatus()->empty()) {
		// ������ɫ��Ч��״̬�б�
		for (auto itEffect = theCharacter->getEffectStatus()->begin(); itEffect != theCharacter->getEffectStatus()->end();) {
			itEffect->second.second--;  // ����Ч������ʱ��
			if (itEffect->second.second == 0) {
				string effectName = "��";
				// ����Ч������ȷ��Ч������
				switch (itEffect->first) {
				case giveDefenseWeaken:
				case selfDefenseBoost:effectName = "������"; break;
				case giveEvationWeaken:
				case selfEvationBoost:effectName = "������"; break;
				case giveHitRateWeaken:
				case selfHitRateBoost:effectName = "������"; break;
				case giveAttackWeaken:
				case selfAttackBoost:effectName = "������"; break;
				default: break;
				}
				// Ч������ʱ��������Ƴ�Ч��
				itEffect = theCharacter->getEffectStatus()->erase(itEffect);
				cout << theCharacter->getName() << "��" << effectName << "�ָ�ԭ״�ˣ�" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			else {
				++itEffect;  // ���Ч����Ȼ��Ч��������һ��
			}
		}
	}
}

// �з��غ��߼�
void Battle::enemyTurn(Character* enemy, Character* player) {
	// �������û�м��ܣ�ִ����ͨ����
	if (enemy->getSkills()->empty()) {
		normalAttack(player, enemy);
		return;
	}

	// ���˿���ʹ�ü��ܻ������ͨ����
	uniform_int_distribution<> dis2(1, enemy->getSkills()->size());
	float randomValue = dis(gen);
	int index = dis2(gen);
	if (randomValue < 0.45)
		normalAttack(player, enemy);  // 45%������ͨ����
	else
		userSkill_enemy(player, enemy, index - 1);  // ����ʹ�ü���
}

// ��һغ��߼�
void Battle::playerTurn(Character* player, vector<Character*>* enemies) {
	int choice;
	bool validChoice = false;
	float hpRate = static_cast<float>(player->getHP()) / player->getMaxHP();  // ������ҵ�ǰ����ֵ�ٷֱ�

	// ȷ����������ѡ����Ч
	while (!validChoice) {
		// ��ʾ��ҵ�״̬��Ϣ
		cout << "<HP:" << static_cast<int>(100 * hpRate) << "%> "
			<< "<��ʽ����:" << player->getSkillPoint() << "> "
			<< "<����:" << player->getFirstWeapon()->getAttackType() << "> "
			<< "<����:" << player->getFirstArmor()->getWeakness() << ">" << endl
			<< "1.��ͨ���� 2.��ʽ 3.�л����� 4.�۲� " << endl << "ѡ���ж�:";

		if (!(cin >> choice)) {
			cin.clear();
#undef max
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "��Ч�����룬������һ�����֡�" << endl;
			continue;
		}

		// �����������Ƿ���Ч
		if (choice >= 1 && choice <= 4) {
			validChoice = true;
			switch (choice) {
			case 1: {  // ִ����ͨ����
				showEnemiesInformation(enemies, player->getHitRate());  // ��ʾ������Ϣ
				cout << "ѡ�񹥻�����:";
				int targetIndex;
				cin >> targetIndex;
				if (targetIndex >= 1 && targetIndex <= enemies->size()) {
					normalAttack((*enemies)[targetIndex - 1], player);  // ��ͨ����ѡ���ĵ���
				}
				else {
					cout << "��Ч�ĵ������������������롣" << endl;
				}
				break;
			}
			case 2: {  // ʹ����ʽ
				if (player->getSkillPoint() == 0) {  // �����ʽ�����Ƿ��㹻
					validChoice = false;
					cout << player->getName() << "��ʽ��������" << endl;
					break;
				}
				if (player->getSkills()->empty()) {  // ����Ƿ��п��ü���
					validChoice = false;
					cout << player->getName() << "����ʹ����ʽ" << endl;
					break;
				}
				int skillIndex;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				showSkillInformationInBattle(player);  // ��ʾ������Ϣ
				cout << "ѡ����ʽ:";
				cin >> skillIndex;
				// ��������Ƿ��뼼�ܼ���
				if ((*player->getSkills())[skillIndex - 1]->getIsOffensive() && (*player->getSkills())[skillIndex - 1]->getAttackType() != player->getFirstWeapon()->getAttackType()) {
					cout << "������ƥ�䣬�޷�ʹ�ø���ʽ" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					validChoice = false;
					break;
				}
				useSkill(player, enemies, skillIndex - 1);  // ʹ�ü���
				break;
			}
			case 3: {  // �л�����
				if (player->getWeapons()->size() == 1) {  // ����Ƿ�ֻ��һ������
					cout << player->getName() << "���л���������ֻ��һ��������" << endl;
					validChoice = false;
					break;
				}
				weaponSwitch(player);  // �л�����
				player->setActionAvailability(false);  // ��������޷��ٽ��������ж�
				break;
			}
			case 4: {  // �۲����״̬
				player->setActionAvailability(false);

				cout << player->getName() << "�ɴ��۾�������ع۲쳡��״����" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(900));  // ģ��۲�ʱ��
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

				// ��ʾ���е��˵�״̬
				for (auto& it : *enemies) {
					Character* theCharacter = it;
					showAllStatus(theCharacter);  // ��ʾ������ϸ״̬
					cout << "����:" << theCharacter->getFirstWeapon()->getName() << "(" << theCharacter->getFirstWeapon()->getAttackType() << ")" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ��۲��ӳ�
					cout << "����:" << theCharacter->getFirstArmor()->getName() << "(" << theCharacter->getFirstArmor()->getWeakness() << "������)" << endl << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ��۲��ӳ�
				}

				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				cout << "����1��ֹͣ�۲�:";
				char i;
				cin >> i;  // ��ҽ����۲�
				break;
			}
			}
		}
		else {
			cout << "��Ч�����룬���������롣" << endl;  // ��ʾ���������Чָ��
		}
	}
}

// �����˺�������߼�
int Battle::takeDamage(Character* target, int damage) {
	if (damage < 0) {  // ����˺�ֵΪ������ʾδ����˺�
		cout << target->getName() << "�������𣡣�" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ�����˺�ʱ��
		return 0;
	}
	if (target->getAnticipateStatus()) {  // ���Ŀ���Ƿ����ˡ�Ԥ����״̬
		damage *= 0.25;  // ��������˺�
		target->modifyHP(-damage);  // �۳��˺�
		cout << target->getName() << "ʶ���ˣ������˴󲿷��˺�!" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ��Ԥ���˺�ʱ��
		cout << target->getName() << "�ܵ�" << damage << "���˺�!" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ���˺���Ӧʱ��
		return damage;
	}
	else {
		target->modifyHP(-damage);  // �����۳��˺�
		cout << target->getName() << "�ܵ�" << damage << "���˺���" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ���˺���Ӧʱ��
		return damage;
	}
}

// ִ����ͨ����
void Battle::normalAttack(Character* target, Character* attacker) {
	cout << attacker->getName() << "��" << target->getName() << "ʹ������ͨ����" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ�⹥���ӳ�
	attacker->setActionAvailability(false);  // ���ù������޷����������ж�
	int damage = getDamage(attacker, target, 1.0);  // �����˺�ֵ
	singleDamagePerform(attacker, target, damage);  // ִ�е����˺�����
}

// ��鹥���Ƿ���������
bool Battle::isHittingWeakness(string theWeakness, string attackType) {
	return (theWeakness == attackType);  // �������������Ŀ������ƥ�䣬����������
}

// ��鹥���Ƿ�����
bool Battle::checkHit(float evasionRate, float hitRate) {
	float randomValue = dis(gen);  // ������������������ж�
	return randomValue <= hitRate * (1 - evasionRate);  // ���������ʺ������ʼ����Ƿ�����
}

// �л�����
void Battle::weaponSwitch(Character* character) {
	bool validChoice = false;
	vector<Weapon*>* weapons = character->getWeapons();  // ��ȡ��ɫ�������б�
	string originalType = character->getFirstWeapon()->getAttackType();  // ��ȡ��ǰ�����Ĺ�������
	showWeaponInformationInBattle(character);  // ��ʾ��ɫ��������Ϣ

	while (!validChoice) {
		cout << "ѡ��Ҫ�滻�����������:" << endl;
		int index;
		cin >> index;  // ����Ҫ�滻����������

		// �������������Ƿ�Ϸ�
		if (index <= 0 || index > weapons->size() - 1) {
			cout << "��Ч��������" << endl;
			continue;
		}

		// ��������
		swap(*character->getFirstWeapon(), *((*weapons)[index]));
		cout << "�л��ɹ���" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ���л������ӳ�
		validChoice = true;

		// ��������л��󹥻������Ƿ����仯
		string currentType = character->getFirstWeapon()->getAttackType();
		if (currentType != originalType) {
			cout << "�����������������������" << originalType << "��Ϊ" << currentType << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ����ʾ�ӳ�
		}
	}
}

// ʹ�ü���
void Battle::useSkill(Character* user, vector<Character*>* enemies, int skillIndex) {
	user->setActionAvailability(false);  // �����û��޷����������ж�
	user->setSkillPoint(user->getSkillPoint() - 1);  // ����һ����ʽ����
	Skill* theSkill = (*user->getSkills())[skillIndex];  // ��ȡʹ�õļ���

	if (theSkill->getIsOffensive()) {  // ����ǽ����Լ���
		bool ishit = false;

		// ����Ƿ�Χ��������
		if (theSkill->getIsAOE()) {
			cout << user->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ�⼼��ʹ���ӳ�

			// �����е��˽��й���
			for (Character* enemy : *enemies) {
				int damage = getDamage(user, enemy, theSkill->getDamageMultiplier());  // �����˺�
				if (theSkill->getAttackFrequency() == 1) {
					cout << "��" << enemy->getName() << "�Ĺ���:";
					singleDamagePerform(user, enemy, damage);  // ִ�е����˺�
				}
				else {
					int totalDamage = 0;

					// ��ι���
					for (int i = 0; i < theSkill->getAttackFrequency(); i++) {
						cout << "��" << enemy->getName() << "��" << i + 1 << "�ι���:" << endl;
						totalDamage += singleDamagePerform(user, enemy, damage);  // ���ִ���˺�
					}
					cout << "�ܼ����" << totalDamage << "���˺���" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ�⹥�������ӳ�
				}

				// ������ܲ������Ҽ��ܣ�ִ��Ч��
				if (!theSkill->getIsSelf())
					effectPerform(user, enemy, theSkill);
			}

			// ��������Ҽ��ܣ�ִ��Ч��
			if (theSkill->getIsSelf())
				effectPerform(user, 0, theSkill);

		}
		else {  // ���幥��
			showEnemiesInformation(enemies, user->getHitRate());  // ��ʾ������Ϣ
			cout << "ѡ�񹥻�Ŀ��:";
			int targetIndex;
			cin >> targetIndex;  // ѡ�񹥻�Ŀ��
			cout << user->getName() << "��" << (*enemies)[targetIndex - 1]->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ�⼼��ʹ���ӳ�

			int damage = getDamage(user, (*enemies)[targetIndex - 1], theSkill->getDamageMultiplier());  // �����˺�
			if (theSkill->getAttackFrequency() == 1)
				ishit = singleDamagePerform(user, (*enemies)[targetIndex - 1], damage);  // ִ�е����˺�
			else {
				int totalDamage = 0;

				// ��ι���
				for (int i = 0; i < theSkill->getAttackFrequency(); i++) {
					cout << "��" << (*enemies)[targetIndex - 1]->getName() << "��" << i + 1 << "�ι���:" << endl;
					totalDamage += singleDamagePerform(user, (*enemies)[targetIndex - 1], damage);  // ���ִ���˺�
				}
				cout << "�ܼ����" << totalDamage << "���˺�������" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ�⹥�������ӳ�

				// ������˺�����0����ʾ��������
				if (totalDamage > 0)
					ishit = true;
			}

			// ����������У�ִ�м���Ч��
			if (ishit)
				effectPerform(user, (*enemies)[targetIndex - 1], theSkill);
		}
	}
	else {  // ����Ǹ�������
		if (theSkill->getIsSelf()) {
			effectPerform(user, 0, theSkill);  // ���Ҽ���Ч��ִ��
		}
		else {
			if (theSkill->getIsAOE()) {
				cout << user->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ�⼼��ʹ���ӳ�

				// �����е���ִ��Ч��
				for (Character* enemy : *enemies)
					effectPerform(user, enemy, theSkill);
			}
			else {
				cout << "ѡ��Ŀ��:";
				showEnemiesInformation(enemies, 1);  // ��ʾ������Ϣ
				int targetIndex;
				cin >> targetIndex;  // ѡ��������Ŀ��
				cout << user->getName() << "��" << (*enemies)[targetIndex - 1]->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));  // ģ�⼼��ʹ���ӳ�
				effectPerform(user, (*enemies)[targetIndex - 1], theSkill);  // ִ��Ч��
			}
		}
	}
}
// ִ�е��˵ļ��ܹ���
void Battle::userSkill_enemy(Character* player, Character* enemy, int skillIndex)
{
	// ���õ��˼���ʹ��״̬Ϊ������
	enemy->setActionAvailability(false);

	// ��ȡ������ʹ�õļ���
	Skill* theSkill = (*enemy->getSkills())[skillIndex];

	// ��������ǽ����Լ���
	if (theSkill->getIsOffensive())
	{
		bool ishit = false;
		cout << enemy->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// �����˺�
		int damage = getDamage(enemy, player, theSkill->getDamageMultiplier());

		// ���ݹ���Ƶ�ʾ����˺�ִ�з�ʽ
		if (theSkill->getAttackFrequency() == 1)
			ishit = singleDamagePerform(enemy, player, damage);
		else
		{
			int totalDamage = 0;
			for (int i = 0; i < theSkill->getAttackFrequency(); i++)
			{
				cout << "��" << player->getName() << "��" << i + 1 << "�ι���:" << endl;
				totalDamage += singleDamagePerform(enemy, player, damage); // �����˺�����
			}
			cout << "�ܼ����" << totalDamage << "���˺���" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		// ����������У�ִ�м���Ч��
		if (ishit) effectPerform(enemy, player, theSkill);
	}
	else
	{
		// ��������Ƿǽ����Լ���
		if (theSkill->getIsSelf())
		{
			cout << enemy->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			effectPerform(enemy, 0, theSkill); // ִ��������Ч��
		}
		else
		{
			cout << enemy->getName() << "ʹ������ʽ:" << theSkill->getName() << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			effectPerform(enemy, player, theSkill); // ִ�жԵ��˼���Ч��
		}
	}
}

// ���㹥����ɵ��˺�
int Battle::getDamage(Character* attacker, Character* target, float damageMultiplier)
{
	// ��������˺�
	int damage = attacker->getAttack() - target->getDefense();
	damage *= damageMultiplier; // Ӧ���˺�����

	// ��������ߴ��ڳ���״̬���˺�����
	if (attacker->getChargeStatus()) damage *= 2;

	// ���ݹ����ߵ��ж����������˺�
	if (attacker->getActionCount() > 1)
		damage *= attacker->getActionCount() * 0.1 + 1;

	return damage;
}

// ִ�е����˺�����
int Battle::singleDamagePerform(Character* user, Character* enemy, int damage)
{
	// ����Ƿ�����
	if (checkHit(enemy->getEvasionRate(), user->getHitRate()))
	{
		// ����Ƿ����е��˵�����
		if (isHittingWeakness(enemy->getFirstArmor()->getWeakness(), user->getFirstWeapon()->getAttackType()) && !enemy->getAnticipateStatus())
		{
			cout << "�������㣡";
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			damage *= 1.5; // �����˺�

			// �������δ�����յ��������˺�
			if (!enemy->getWeaknessReceivedStatus())
			{
				// ����û�����ҿ��ƣ����������ж��ͼ��ܵ�
				if (user->isPlayerControlled())
				{
					cout << user->getName() << "��ö����ж�����ʽ��!";
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					user->setSkillPoint(user->getSkillPoint() + 2);
					user->setActionAvailability(true);
					user->setHitWeakness(true);
					enemy->setWeaknessReceivedStatus(true);
				}
				else
				{
					cout << "���Զ����ж���" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					user->setActionAvailability(true);
					user->setHitWeakness(true);
					enemy->setWeaknessReceivedStatus(true);
				}
			}
		}

		// ���㲢�����˺�
		int returnDamage = takeDamage(enemy, damage);
		return returnDamage;
	}
	else
	{
		cout << "δ����" << enemy->getName() << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		return 0;
	}
}

// ִ�м���Ч��
void Battle::effectPerform(Character* user, Character* enemy, Skill* theSkill)
{
	// ���ݼ���Ч������ִ�в�ͬ��Ч��
	switch (theSkill->getEffect())
	{
	case selfDefenseBoost:
	case selfEvationBoost:
	case selfHitRateBoost:
	case selfAttackBoost:
	{
		if (!checkAndOffset(user, theSkill))
		{
			// ����Ч�����û�
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
			// ʹ�û����ڻ���״̬�����ָ�һ��HP
			user->setComatoseStatus(true, theSkill->getDuration());
			int gainHP = user->getMaxHP() * 0.75;
			user->modifyHP(gainHP);
			describeEffect(user, enemy, theSkill);
		}
		else
		{
			cout << "����ʧ���ˣ�" << endl;
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
			// ����Ч��������
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
			// ʹ���˴��ڻ���״̬
			enemy->setComatoseStatus(true, theSkill->getDuration());
			describeEffect(user, enemy, theSkill);
		}
		else
		{
			cout << enemy->getName() << "û���ܵ�Ӱ�죡" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;
	}

	case none:
	default:
		break;
	}
}

// ��鼼�ܶԽ�ɫ��Ч���Ƿ�ᱻ����Ч������
// ����������������� true�����򷵻� false
bool Battle::checkAndOffset(Character* character, Skill* theSkill)
{
	bool offsetOccurred = false; // Ĭ��δ��������
	skillEffectType theType = theSkill->getEffect();
	map<skillEffectType, pair<float, int>>* effectStatus = character->getEffectStatus();

	// ���û������Ч�������޷���������
	if (effectStatus->empty())
		return false;

	switch (theType)
	{
	case giveAttackWeaken:
	case selfAttackBoost:
		// ��鲢�Ƴ��빥��������/����Ч����ͻ��Ч��
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == selfAttackBoost || it->first == giveAttackWeaken)
			{
				// �����Ч���Ƿ��ܵ�������Ч��
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true; // �����˵���
				}
				effectStatus->erase(it++); // �Ƴ�Ч��
			}
			else
			{
				++it; // �ƶ�����һ��Ч��
			}
		}
		break;

	case giveDefenseWeaken:
	case selfDefenseBoost:
		// ��鲢�Ƴ������������/����Ч����ͻ��Ч��
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveDefenseWeaken || it->first == selfDefenseBoost)
			{
				// �����Ч���Ƿ��ܵ�������Ч��
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true; // �����˵���
				}
				effectStatus->erase(it++); // �Ƴ�Ч��
				break; // �ҵ�ƥ��Ч����ֱ���˳�
			}
			else
			{
				++it; // �ƶ�����һ��Ч��
			}
		}
		break;

	case giveEvationWeaken:
	case selfEvationBoost:
		// ��鲢�Ƴ�������������/����Ч����ͻ��Ч��
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveEvationWeaken || it->first == selfEvationBoost)
			{
				// �����Ч���Ƿ��ܵ�������Ч��
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true; // �����˵���
				}
				effectStatus->erase(it++); // �Ƴ�Ч��
				break; // �ҵ�ƥ��Ч����ֱ���˳�
			}
			else
			{
				++it; // �ƶ�����һ��Ч��
			}
		}
		break;

	case selfHitRateBoost:
	case giveHitRateWeaken:
		// ��鲢�Ƴ�������������/����Ч����ͻ��Ч��
		for (auto it = effectStatus->begin(); it != effectStatus->end(); )
		{
			if (it->first == giveHitRateWeaken || it->first == selfHitRateBoost)
			{
				// �����Ч���Ƿ��ܵ�������Ч��
				if (((theSkill->getEffectIntensity() - 1) * (it->second.first - 1)) < 0)
				{
					offsetOccurred = true; // �����˵���
				}
				effectStatus->erase(it++); // �Ƴ�Ч��
			}
			else
			{
				++it; // �ƶ�����һ��Ч��
			}
		}
		break;

	default:
		break;
	}

	return offsetOccurred; // �����Ƿ����˵���
}

// �����ɫ�Ļ���״̬
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
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
		{
			cout << theCharacter->getName() << "�����У��޷��ж���" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			theCharacter->setActionAvailability(false); // ���ý�ɫΪ�����ж�
		}
	}
}

// ��������Ч��
void Battle::describeEffect(Character* user, Character* enemy, Skill* theSkill)
{
	switch (theSkill->getEffect())
	{
	case selfDefenseBoost:
		if (theSkill->getEffectIntensity() >= 1)
		{
			cout << user->getName() << "��������������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
		{
			cout << user->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;

	case selfEvationBoost:
		cout << user->getName() << "�����ʴ�������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfHitRateBoost:
		cout << user->getName() << "�����ʴ�������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfAttackBoost:
		if (theSkill->getEffectIntensity() >= 1)
		{
			cout << user->getName() << "��������������ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else
		{
			cout << user->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		break;

	case selfComatose:
		cout << user->getName() << "��ʼ˯��,HP�����ָ���!" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfCharge:
		cout << user->getName() << "�����������»غ��˺�������" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfAnticipate:
		cout << user->getName() << "�����Ƶз����ƣ�" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case selfDamage:
		cout << user->getName() << "���������HP,";
		break;

	case giveAttackWeaken:
		cout << enemy->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case giveHitRateWeaken:
		cout << enemy->getName() << "�����ʴ���½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case giveDefenseWeaken:
		cout << enemy->getName() << "����������½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case giveEvationWeaken:
		cout << enemy->getName() << "�ر��ʴ���½��ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	case giveComatose:
		cout << enemy->getName() << "�����ˣ�����" << theSkill->getDuration() << "�غϣ�" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;

	default:
		break;
	}
}

// ��ʾ���˵���Ϣ���������˵����ֺ�������
void Battle::showEnemiesInformation(vector<Character*>* enemies, float hitRate) {
	int i = 1; // ���ڱ�ŵ���
	float trueHitRate; // �������ʵ������

	// �������е���
	for (auto& it : *enemies) {
		// ������ʵ�����ʣ����ǵ��˵�������
		trueHitRate = (1 - it->getEvasionRate()) * hitRate;

		// ������˵ı�š����ֺͼ������������
		cout << i << ":" << it->getName();
		cout << setprecision(3) << "(������:" << trueHitRate * 100 << "%)" << endl;
		i++; // ���ӵ��˵ı��
	}
}

// ��ʾ�û���������Ϣ���������������ơ��������͡���������������
void Battle::showWeaponInformationInBattle(Character* user) {
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	// ��ȡ�û��������б�
	vector<Weapon*>* weapons = user->getWeapons();

	// ��������б�Ϊ�գ�����ʾÿ����������Ϣ
	if (weapons && !weapons->empty()) {
		for (size_t i = 1; i < weapons->size(); ++i) { // �ӵڶ���������ʼ�����������һ����Ĭ��������
			cout << "#" << i << " " << (*weapons)[i]->getName(); // �����������
			cout << " [" << (*weapons)[i]->getAttackType() << "]"; // �����������
			cout << " [������+" << (*weapons)[i]->getAttack() << "]"; // ���������
			cout << " [������+" << 100 * (*weapons)[i]->getHitRate() << "%]" << endl; // ���������
		}
	}

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

// ��ʾ�û��ļ�����Ϣ���������ܵ����ơ��������������ͺ��뵱ǰ������ƥ�����
void Battle::showSkillInformationInBattle(Character* user) {
	vector<Skill*>* skills = user->getSkills(); // ��ȡ�û��ļ����б�
	Weapon* theWeapon = user->getFirstWeapon(); // ��ȡ�û��ĵ�һ������
	int i = 1; // ���ڱ�ż���

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	// �������м���
	for (auto& it : *skills) {
		if (it->getIsOffensive()) { // ��������ǽ����Ե�
			cout << "#" << i << " " << it->getName(); // �����������
			cout << "��" << it->getDescription(); // �����������
			cout << "����" << it->getAttackType(); // ������ܹ�������

			// ��鼼�ܵĹ��������Ƿ��������Ĺ�������ƥ��
			if (it->getAttackType() == theWeapon->getAttackType())
				cout << "(ƥ��)��" << endl; // ���ƥ�䣬���"ƥ��"
			else
				cout << "(��ͻ)��" << endl; // �����ƥ�䣬���"��ͻ"
		}
		else { // ��������Ǹ����Ե�
			cout << "#" << i << " " << it->getName(); // �����������
			cout << "��" << it->getDescription() << "��" << endl; // �����������
		}
		i++; // ���Ӽ��ܱ��
	}

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

// ��ʾ��ɫ�ĳ���˳��
void Battle::showSpeedLine(vector<pair<int, Character*>> sortedCharacters) {
	int i = 1;
	int max = sortedCharacters.size(); // ��ȡ��ɫ����

	cout << "����˳��:"; std::this_thread::sleep_for(std::chrono::milliseconds(500)); // ��ͣ0.5��

	// ���ÿ����ɫ������
	for (auto& it : sortedCharacters) {
		cout << it.second->getName() << " ";
		i++;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // ��ͣ0.5��
	cout << endl;
}

// ��ʾս����ʼ����Ϣ���������˵������͵��˵�����
void Battle::showStartInformation(Linchong* player, vector<Character*>* enemies) {
	cout << "ս����ʼ��" << endl; std::this_thread::sleep_for(std::chrono::milliseconds(500)); // ��ͣ0.5��
	cout << "���˹�" << enemies->size() << "��:"; std::this_thread::sleep_for(std::chrono::milliseconds(500)); // ��ͣ0.5��

	int i = 1;

	// ���ÿ�����˵�����
	for (auto& it : *enemies) {
		cout << "" << it->getName() << " ";
		i++;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // ��ͣ0.5��
	cout << endl;
}

// ��ʾ��ɫ������״̬������HP������״̬��Ч��
void Battle::showAllStatus(Character* character) {
	map<skillEffectType, pair<float, int>>* theStatus = character->getEffectStatus(); // ��ȡ��ɫ��Ч��״̬
	bool haveStatus = false; // ����Ƿ�������״̬
	float hpRate = static_cast<float>(character->getHP()) / character->getMaxHP(); // ����HP����

	cout << setprecision(2) << character->getName() << "HPʣ��" << character->getHP() << "(" << static_cast<int>(100 * hpRate) << "%)  ����״̬��";

	// ��鲢�����ɫ������״̬
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

	if (theStatus->empty()) {
		if (!haveStatus) cout << "��"; // ���û��״̬�����"��"
		cout << endl;
	}
	else {
		// �������������Ч��״̬
		for (auto& it : *theStatus) {
			switch (it.first) {
			case selfDefenseBoost:
				if ((it.second.first) >= 1)
					cout << "����������(" << it.second.second << ") ";
				else
					cout << "�������½�(" << it.second.second << ") ";
				break;
			case selfEvationBoost:
				cout << "����������(" << it.second.second << ") ";
				break;
			case selfHitRateBoost:
				cout << "������������(" << it.second.second << ") ";
				break;
			case selfAttackBoost:
				if (it.second.first >= 1)
					cout << "����������(" << it.second.second << ") ";
				else
					cout << "�������½�(" << it.second.second << ") ";
				break;
			case giveAttackWeaken:
				cout << "�������½�(" << it.second.second << ") ";
				break;
			case giveHitRateWeaken:
				cout << "�������½�(" << it.second.second << ") ";
				break;
			case giveDefenseWeaken:
				cout << "�������½�(" << it.second.second << ") ";
				break;
			case giveEvationWeaken:
				cout << "�ر����½�(" << it.second.second << ") ";
				break;
			default:
				break;
			}
		}
		cout << endl;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // ��ͣ0.5��
}

// ���ռ��ܵĹ������ͶԼ��ܽ�������
void Battle::manageSkillOrder(Character* character) {
	vector<Skill*>* skills = character->getSkills(); // ��ȡ��ɫ�ļ����б�

	// �ȶ��������������Լ��ܷ���ǰ��
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getIsOffensive();
		}
	);

	// �ȶ�����������������Ϊ"���"�ļ��ܷ���ǰ��
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "���";
		}
	);

	// �ȶ�����������������Ϊ"��ͨ"�ļ��ܷ���ǰ��
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "��ͨ";
		}
	);

	// �ȶ�����������������Ϊ"ն��"�ļ��ܷ���ǰ��
	stable_partition(skills->begin(), skills->end(),
		[](Skill* skill) {
			return skill->getAttackType() == "ն��";
		}
	);
}

// ׼����ɫ�ļ��ܣ����������ܺͽ���������ӵ������б���
void Battle::prepareSkill(Character* character) {
	// ��ս�ɫ�ļ����б�
	character->getSkills()->clear();

	vector<Skill*>* skills = character->getSkills(); // ��ȡ��ɫ�ļ����б�
	vector<offensiveSkill*>* oskills = character->getoSkills(); // ��ȡ��ɫ�Ľ��������б�
	vector<supportSkill*>* sskills = character->getsSkills(); // ��ȡ��ɫ�ĸ��������б�

	// ������������б�Ϊ�գ������и���������ӵ������б���
	if (!sskills->empty())
		for (auto& it : *sskills) {
			skills->push_back(it);
		}

	// ������������б�Ϊ�գ������н���������ӵ������б���
	if (!oskills->empty())
		for (auto& it : *oskills) {
			skills->push_back(it);
		}
}



