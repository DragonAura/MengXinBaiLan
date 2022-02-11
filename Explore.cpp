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