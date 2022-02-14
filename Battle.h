#pragma once

#include"DEFINE.h"

class Unit;//对Unit类做声明
class Skills;//对Skills类做声明

class Battle
{
public:
	Battle(Unit* unit1, Unit* unit2) { AddUnit(unit1); AddUnit(unit2); }
	~Battle(){}
	void AddUnit(Unit* unit);//增加时要求提前对每一种不同的Unit_ID的enum进行相关的布局
	bool testwin();//用于测试战斗是否结束
	void InBattle();//用于描述战斗过程

private:
	Object_ID BattleMap[MapXSize / BlockSize][MapYSize / BlockSize];
	std::vector<Unit*>BattleUnit;
};