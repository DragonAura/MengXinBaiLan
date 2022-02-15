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
		new2->BattleX = MapXSize / BlockSize / 3 * 2;
		new2->BattleY = MapYSize / BlockSize / 4;
		BattleUnit.push_back(new1);
		BattleUnit.push_back(new2);
		break;
	}
}

void Battle::InBattle()
{
	while (testwin() == false)
	{
		for (auto& item : BattleUnit)//操作，具体函数待定
		{
			/*item->ChangeHp(-1);*/
			for (auto opponent : BattleUnit)
				if (opponent->GetID() != item->GetID())
				{
					item->AddOpponent(opponent);
					break;
				}
			item->UseSkill(0);
			bl->ChangeUIHP(BattleUnit[0]->GetHP());
			QEventLoop loop;
			QTimer::singleShot(100, &loop, SLOT(quit()));
			loop.exec();
			if (testwin() == true)break;
		}
	}
}

bool Battle::testwin()
{
	bool result = true;
	std::vector<Unit*>::iterator mark = BattleUnit.end();
	for (auto it = BattleUnit.begin(); it != BattleUnit.end(); it++)
	{
		if ((*it)->Alive() == false)
			mark = it;
		if ((*it)->GetID() == Unit_Player && (*it)->Alive() == false)return true;
		else
			if ((*it)->GetID() != Unit_Player && (*it)->Alive() == true)
			{
				result = false;
			}
	}
	if (mark != BattleUnit.end())
		BattleUnit.erase(mark);
	return result;
}