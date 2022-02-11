#pragma once

enum Map_ID//记录所有的地图
{
	Map_MAP1
};

enum Object_ID//记录地图上可能出现的物体
{
	Object_GRASS,//默认状态下为Grass，表示无特殊规则，可正常行走
	Object_AIR,
	Object_WALL
	
};

class Unit;//对Unit类做声明

Explore* MapGenerator(Map_ID id);

void standard(int& x, int& y);//将输入的参数变为标准的前小后大

class Explore//由Explore类派生出不同的Explore_Map（若有需要）
{
public:

	Explore(Map_ID id);
	~Explore() {}
//关于设置地图的两种函数重载
	void SetObject(int x1, int y1, int x2, int y2, Object_ID id);//x,y的范围为1-40
	void SetObject(int x, int y, Object_ID id);

//设置敌人的函数
	void AddEnemy(int x, int y, Map_ID map, Unit_ID id, int hp, int atk, int exp, int lvl, int skillnum);
	
//提供外部获取地图内容的接口
	Object_ID GetObject(int x, int y) { return Object[x][y]; }
	std::vector<Unit*> GetEnemies() { return Enemies; }
	Map_ID GetID() { return MapID; }

protected:

	Map_ID MapID;
	Object_ID Object[MapXSize / BlockSize][MapYSize / BlockSize];//用来存储地图上所有位置的物体的具体内容

	std::vector<Unit*> Enemies;//用于记录一张地图上有什么怪物

};