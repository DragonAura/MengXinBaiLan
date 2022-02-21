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
}

void Battle::InBattle()
{
	while (testwin() == false)
	{
		for (int i = 0; i < BattleUnit.size();i++)//操作，具体函数待定
		{
			if (testwin() == true)break;
			if (BattleUnit[i]->GetID() != Unit_Player)
			{
				AiControl(BattleUnit[i]);
				bl->ChangeUIEnemyHealth(BattleUnit[i]->GetHP());
				bl->ChangeUIEnemyName(BattleUnit[i]->GetName());
				QString opponent;
				for (auto opp : BattleUnit[i]->LastOpponent)
					opponent = opponent + opp->GetName() + ", ";
				bl->AddInformation(BattleUnit[i]->GetName() + " Uses " + BattleUnit[i]->LastSkill->GetName() + " to " + opponent);
			}
			else
			{
				bl->ChangeUIEnemyHealth(" ");
				bl->ChangeUIEnemyName(" ");
				PlayerControl(BattleUnit[i]);
				QString opponent;
				for (auto opp : BattleUnit[i]->LastOpponent)
					opponent = opponent + opp->GetName() + ", ";
				bl->AddInformation(BattleUnit[i]->GetName() + " Uses " + BattleUnit[i]->LastSkill->GetName() + " to " + opponent);
				
			}
			if (testwin() == true)break;
			/*item->ChangeHp(-1);*/
			//for (auto opponent : BattleUnit)
			//	if (opponent->GetID() != item->GetID())
			//	{
			//		item->AddOpponent(opponent);
			//		break;
			//	}
			//item->UseSkill(0);
			bl->ChangeUIPlayerHP(BattleUnit[0]->GetHP());
			QEventLoop loop;//这一片段用于延迟一段时间，具体取决于下面第一个参数，单位为ms
			QTimer::singleShot(1000, &loop, SLOT(quit()));
			loop.exec();
		}
	}
}

void Battle::AiControl(Unit* unit)//待细化
{
	for(auto& opponent:BattleUnit)
		if (opponent->GetID() == Unit_Player)
		{
			unit->AddOpponent(opponent);
			break;
		}
	unit->UseSkill(0);
}

void Battle::PlayerControl(Unit* player)
{
	for (auto& opponent : BattleUnit)
		if (opponent->GetID() != Unit_Player)
		{
			player->AddOpponent(opponent);
			break;
		}
	while (bl->GetSlot() == -1)
	{
		QEventLoop loop;
		QTimer::singleShot(100, &loop, SLOT(quit()));
		loop.exec();
	}
	player->UseSkill(bl->GetSlot());
	bl->ResetSlot();
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
			bl->AddInformation("Player " + (*it)->GetName() + " Dies");
			return true;
		}
		else if ((*it)->GetID() != Unit_Player && (*it)->Alive() == true)
				result = false;
	}
	if (mark != BattleUnit.end())
	{
		bl->AddInformation((*mark)->GetName() + " Dies");
		delete (*mark);
		BattleUnit.erase(mark);
	}
	return result;
}