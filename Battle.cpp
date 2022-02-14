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
		for (auto item : BattleUnit)//操作，具体函数待定
			;
	}
}

bool Battle::testwin()
{
	bool result = true;
	for (auto item : BattleUnit)
		if (item->GetID() == Unit_Player && item->GetHP() <= 0)return true;
		else
			if (item->GetID() != Unit_Player && item->GetHP() > 0)
			{
				result = false;
			}
	return result;
}