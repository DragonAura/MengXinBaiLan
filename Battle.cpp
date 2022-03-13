#include"total.h"

void Battle::AddUnit(Unit* unit)
{
	switch (unit->GetID())
	{
	case Unit_Player:
		unit->BattleX = MapXSize / BlockSize / 2;
		unit->BattleY = MapYSize / BlockSize / 4 * 3;
		BattleUnit.push_back(unit);
		break;
	case Unit_Enemy_Demon:
	{
		Unit* new1 = new Unit;
		Unit* new2 = new Unit;
		*new1 = *unit, * new2 = *unit;
		new1->BattleX = MapXSize / BlockSize / 3;
		new1->BattleY = MapYSize / BlockSize / 4;
		new1->SetName("Demon1");
		new2->BattleX = MapXSize / BlockSize / 3 * 2;
		new2->BattleY = MapYSize / BlockSize / 4;
		new2->SetName("Demon2");
		BattleUnit.push_back(new1);
		BattleUnit.push_back(new2);
		break;
	}
	case Unit_Enemy_Slime:
	{
		Unit* new1 = new Unit;
		Unit* new2 = new Unit;
		Unit* new3 = new Unit;
		Unit* new4 = new Unit;
		*new1 = *unit, * new2 = *unit, * new3 = *unit, * new4 = *unit;
		new1->BattleX = MapXSize / BlockSize / 3;
		new1->BattleY = MapYSize / BlockSize / 6;
		new1->SetName("Slime1");
		new2->BattleX = MapXSize / BlockSize / 3 * 2;
		new2->BattleY = MapYSize / BlockSize / 6;
		new2->SetName("Slime2");
		new3->BattleX = MapXSize / BlockSize / 3;
		new3->BattleY = MapYSize / BlockSize / 3;
		new3->SetName("Slime3");
		new4->BattleX = MapXSize / BlockSize / 3 * 2;
		new4->BattleY = MapYSize / BlockSize / 3;
		new4->SetName("Slime4");
		BattleUnit.push_back(new1);
		BattleUnit.push_back(new2);
		BattleUnit.push_back(new3);
		BattleUnit.push_back(new4);
		break;
	}
	}
}

void Battle::InBattle()
{
	bl->DrawBattleMap();
	bl->DrawBattleUnit();
	bool test = true;
	while (test == true)
	{
		for (int i = 0; i < BattleUnit.size(); i++)//操作，具体函数待定
		{
			//bl->DrawBattleUnit();
			//if (testwin() == true)break;
			if (BattleUnit[i]->GetID() != Unit_Player)
			{
				AiControl(BattleUnit[i]);
				QString opponent;
				for (auto opp : BattleUnit[i]->LastOpponent)
					opponent = opponent + opp->GetName() + ", ";
				bl->AddInformation(BattleUnit[i]->GetName() + " Uses " + BattleUnit[i]->LastSkill->GetName() + " to " + opponent);
			}
			else
			{
				bl->ChangeControl();
				PlayerControl(BattleUnit[i]);
				QString opponent;
				for (auto opp : BattleUnit[i]->LastOpponent)
					opponent = opponent + opp->GetName() + ", ";
				bl->AddInformation(BattleUnit[i]->GetName() + " Uses " + BattleUnit[i]->LastSkill->GetName() + " to " + opponent);
				bl->ChangeControl();

			}
			if (testwin() == true)
			{
				test = false;
				break;
			}
			/*item->ChangeHp(-1);*/
			//for (auto opponent : BattleUnit)
			//	if (opponent->GetID() != item->GetID())
			//	{
			//		item->AddOpponent(opponent);
			//		break;
			//	}
			//item->UseSkill(0);
			bl->RefreshHp();
			bl->RefreshSp();
			bl->DrawBattleUnit();
			QEventLoop loop;//这一片段用于延迟一段时间，具体取决于下面第一个参数，单位为ms
			QTimer::singleShot(500, &loop, SLOT(quit()));
			loop.exec();
		}
	}
}

void Battle::AiControl(Unit* unit)//待细化，大体思路上会给不同的行动一个属性，从而判断怪物怎么行动比较好
{
	for (auto& opponent : BattleUnit)
		if (opponent->GetID() == Unit_Player)
		{
			unit->AddOpponent(opponent);
			break;
		}
	unit->UseSkill(0);
}

void Battle::PlayerControl(Unit* player)
{
	//for (auto& opponent : BattleUnit)
	//	if (opponent->GetID() != Unit_Player)
	//	{
	//		player->AddOpponent(opponent);
	//		break;
	//	}
	while (bl->UseSkill != true)
	{
		QEventLoop loop;
		QTimer::singleShot(50, &loop, SLOT(quit()));
		loop.exec();
	}
	//player->UseSkill(bl->GetSlot());
	bl->UseSkill = false;
	//bl->ResetSlot();
}

bool Battle::testwin()
{
	bool result = true;
	std::vector<Unit*>::iterator mark = BattleUnit.end();
	for (auto it = BattleUnit.begin(); it != BattleUnit.end(); it++)
	{
		if ((*it)->Alive() == false)
			mark = it;
		if ((*it)->GetID() == Unit_Player && (*it)->Alive() == false)
		{
			BattleUnit[0]->ChangeEXP(-INT_MAX);
			BattleUnit[0]->ResetPos(bl->GetMap());//死亡后将玩家送回初始位置
			bl->AddInformation("Player " + (*it)->GetName() + " dies and loses all of his exp. ");
			return true;
		}
		else if ((*it)->GetID() != Unit_Player && (*it)->Alive() == true)
			result = false;
	}
	if (mark != BattleUnit.end())
	{
		bl->AddInformation((*mark)->GetName() + " dies. ");
		BattleUnit[0]->ChangeEXP((*mark)->GetXP());
		delete (*mark);
		BattleUnit.erase(mark);
	}
	return result;
}