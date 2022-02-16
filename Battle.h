#pragma once

#include"DEFINE.h"

class Unit;//对Unit类做声明
class Skills;//对Skills类做声明
class BaiLan;

class Battle
{
public:
	Battle(Unit* unit1, Unit* unit2, BaiLan* bailan) { AddUnit(unit1); AddUnit(unit2); bl = bailan; }
	~Battle(){}
	void AddUnit(Unit* unit);//增加时要求提前对每一种不同的Unit_ID的enum进行相关的布局
	bool testwin();//用于测试战斗是否结束
	void InBattle();//用于描述战斗过程，玩家胜利返回true，反之则返回false
	void AiControl(Unit* unit);
	void PlayerControl(Unit* player);

private:
	Object_ID BattleMap[MapXSize / BlockSize][MapYSize / BlockSize];
	std::vector<Unit*>BattleUnit;
	BaiLan* bl;
};