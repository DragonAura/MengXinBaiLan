#pragma once

enum Map_ID//记录所有的地图
{
	Map_MAP1
};

enum Object_ID//记录地图上可能出现的物体
{
	Object_GRASS,//默认状态下为Grass，表示无特殊规则，可正常行走
	Object_AIR
	
};

class Unit;//对Unit类做声明

class Explore//由Explore类派生出不同的Explore_Map（若有需要）
{
public:
//关于设置地图的两种函数重载
	void SetObject(int x1, int y1, int x2, int y2, Object_ID id);
	void SetObject(int x, int y, Object_ID id);

	void MapInit();

	Object_ID GetObject(int x, int y) { return Object[x][y]; }//提供外部获取地图内容的接口
	Map_ID GetID() { return MapID; }

protected:

	Map_ID MapID;
	Object_ID Object[MapXSize / BlockSize][MapYSize / BlockSize];//用来存储地图上所有位置的物体的具体内容

	std::vector<Unit*> Monsters;//用于记录一张地图上的怪物数量

};