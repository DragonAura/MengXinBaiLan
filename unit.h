#pragma once

enum Unit_ID//利用enum类型来枚举单位（怪物，玩家etc）ID
{
	Player
};

class Unit
{

};

class Player :public Unit
{
private:
	char* name;

public:

};

class Monster:public Unit
{

};

class ExampleMonster :public Monster
{

};