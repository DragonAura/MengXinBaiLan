#include"total.h"

void standard(int& x, int& y)
{
	int temp = x;
	x = x < y ? x : y;
	y = temp > y ? temp : y;
}

Explore* MapGenerator(Map_ID id)
{
	Explore* map = nullptr;
	switch (id)
	{
	case Map_MAP1:
		map = new Explore(Map_MAP1);
		map->SetObject(1, 1, 40, 1, Object_WALL);
		map->SetObject(1, 1, 1, 40, Object_WALL);
		map->SetObject(40, 40, 40, 1, Object_WALL);
		map->SetObject(40, 40, 1, 40, Object_WALL);
		map->SetObject(20, 20, Object_WALL);
		map->AddEnemy(300, 300, Map_MAP1, Unit_Enemy_Demon, 10, 1, 20, 1, 0);
		break;
	}
	return map;
}

Explore::Explore(Map_ID id)
{
	MapID = id;
	for (int i = 0; i < MapXSize / BlockSize; i++)
		for (int j = 0; j < MapYSize / BlockSize; j++)
			Object[i][j] = Object_GRASS;
}

void Explore::AddEnemy(int x, int y, Map_ID map, Unit_ID id,int hp,int atk,int exp,int lvl,int skillnum)
{
	Unit* enemy = new Unit(hp, atk, exp, lvl, id, skillnum);
	enemy->ChangePosition(x, y, map);
	Enemies.push_back(enemy);
}

void Explore::KillEnemey(int x, int y)
{
	std::vector<Unit*>::iterator it;
	for (it = Enemies.begin(); it != Enemies.end(); it++)
		if ((*it)->GetX() == x && (*it)->GetY() == y)
		{
			Enemies.erase(it);
			break;
		}
}

void Explore::SetObject(int x1, int y1, int x2, int y2, Object_ID id)
{
	standard(x1, x2);
	standard(y1, y2);
	for (int i = x1-1; i < x2; i++)
		for (int j = y1-1; j < y2; j++)
			Object[i][j] = id;
}

void Explore::SetObject(int x, int y, Object_ID id)
{
	Object[x-1][y-1] = id;
}

//void Explore::MapInit()
//{
//	for (int i = 0; i < MapXSize / BlockSize; i++)
//		for (int j = 0; j < MapYSize / BlockSize; j++)
//			Object[i][j] = Object_GRASS;
//}