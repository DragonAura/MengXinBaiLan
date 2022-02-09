#pragma once

enum Skill_ID;

enum Map_ID;

enum Unit_ID//利用enum类型来枚举单位（怪物，玩家etc）ID
{
	Unit_Player,
	Unit_Monster_Example
};

Skills* SkillAdder(Skill_ID id);//通过该函数返回一个技能指针

//Unit类允许派生出新的Monster类，如果有相关需要的话
class Unit//出于各种原因，建议在定义Unit的时候采用定义指针、new的方式来在主程序中存储，否则需要取地址，可读性相对较差
{
	
public:

	Unit(){}
	Unit(int,char*);//构造函数中具体会初始化的数据待定，可能会需要很多
	virtual ~Unit(){}

//对外提供数值的函数
	Unit_ID GetID() { return ID; }
	int GetX() { return X; }
	int GetY() { return Y; }

//技能相关的函数
	int AddSkill(Skill_ID id);//给定SkillID，给Unit添加技能，返回值int起到判断是否成功增加的作用
	int RemoveSkill(Skill_ID id);//给定SkillID，删除Unit的技能
	int UseSkill(int slot);//每个技能被有其槽的位置，给定slot，使用对应的技能
	int AddOpponent(Unit* opponent);//释放技能之前要求先添加对象

//更改数据相关的函数接口
	void ChangeHp(int hp);//提供更改内部数据的接口，其中hp、atk可为负
	void ChangeAtk(int atk);
	void ChangeEXP(int exp);
	void ChangeLvl(int lvl);

//关于玩家移动的两种函数重载
	void ChangePosition(int x, int y, Map_ID map);//切换地图时或者初次定义时要求使用该函数，此时的xy为绝对位置
	void ChangePosition(int x, int y);//不切换地图在同一地图移动时应当使用该函数，此时的xy为相对位移

protected:
	int MaxHP;
	int health;//要求health至多为MaxHP
	int attack;//要求attack至少为1
	int skillpoint;//要求skillpoint至少为0，至多为200
	int experience;
	int level;
	char* name;
	Unit_ID ID;
	std::vector<Skills*>SkillSlot;//使用vector来记录一个Unit所具有的技能
	std::vector<Unit*>Opponent;//使用vector记录某次技能所锁定的对象
	int EmptySlotNum;
	int OpponentNum;
	int X, Y;//记录某Unit在当前地图的XY位置，应当以Pixel（即960x960）记录，而非Block记录
	Map_ID Map;//记录Unit当前所在的地图

};