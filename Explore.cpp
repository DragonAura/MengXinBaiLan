#include"total.h"

void Explore::SetObject(int x1, int y1, int x2, int y2, Object_ID id)
{
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
			Object[i][j] = id;
}

void Explore::SetObject(int x, int y, Object_ID id)
{
	Object[x][y] = id;
}

void Explore::MapInit()
{
	for (int i = 0; i < MapXSize / BlockSize; i++)
		for (int j = 0; j < MapYSize / BlockSize; j++)
			Object[i][j] = Object_GRASS;
}