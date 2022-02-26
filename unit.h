#pragma once

#include<QString>

class Battle;

enum Skill_ID;

enum Map_ID;

enum Unit_ID//利用enum类型来枚举单位（怪物，玩家etc）ID
{
	Unit_Player,
	Unit_Enemy_Demon,
	Unit_Enemy_Slime
};

Skills* SkillAdder(Skill_ID id);//通过该函数返回一个技能指针

//Unit类允许派生出新的Monster类，如果有相关需要的话
class Unit//出于各种原因，建议在定义Unit的时候采用定义指针、new的方式来在主程序中存储，否则需要取地址，可读性相对较差
{
	
public:

	Unit(){}
	Unit(int hp, int atk, int exp, int lvl, Unit_ID id, int slotnumber, int sizex=24, int sizey=48);
	virtual ~Unit(){}
	void SetName(QString name_) { name = name_; }

//对外提供数值的函数
	Unit_ID GetID() { return ID; }
	int GetX() { return X; }
	int GetY() { return Y; }
	int GetHP() { return health; }
	int GetATK() { return attack; }
	int GetXP() { return MaxEXP; }
	QString GetName() { return name; }
	bool Alive() { return health > 0 ? true : false; }

//技能相关的函数
	int AddSkill(Skill_ID id);//给定SkillID，给Unit添加技能，返回值int起到判断是否成功增加的作用
	int RemoveSkill(Skill_ID id);//给定SkillID，删除Unit的技能
	int UseSkill(int slot);//每个技能被有其槽的位置，给定slot，使用对应的技能
	int AddOpponent(Unit* opponent);//释放技能之前要求先添加对象

//更改数据相关的函数接口
	void ChangeHp(int hp);//提供更改内部数据的接口，其中hp、atk可为负
	void ChangeAtk(int atk);
	void ChangeEXP(int exp);

	bool LevelUp();//每次战斗之后都应当调用这个函数

//关于玩家移动的两种函数重载
	void ChangePosition(int x, int y, Map_ID map);//切换地图时或者初次定义时要求使用该函数，此时的xy为绝对位置
	void ChangePosition(int x, int y);//不切换地图在同一地图移动时应当使用该函数，此时的xy为相对位移

	int BattleX, BattleY;//记录某Unit在当前Battle地图的XY位置，应当以Block（24x24）记录
	int SizeX, SizeY;//记录某Unit的贴图大小，主要用于遇敌检测
	Skills* LastSkill;
	std::vector<Unit*>LastOpponent;

protected:
	int MaxHP;
	int health;//要求health至多为MaxHP
	int attack;//要求attack至少为1
	int skillpoint;//要求skillpoint至少为0，至多为200
	int experience;
	int MaxEXP;//指升级需要的经验，一般只用于玩家，初始化时所有Unit都会赋为100防止出现错误
	int level;
	QString name;
	Unit_ID ID;
	std::vector<Skills*>SkillSlot;//使用vector来记录一个Unit所具有的技能
	std::vector<Unit*>Opponent;//使用vector记录某次技能所锁定的对象
	int EmptySlotNum;
	int OpponentNum;
	int X, Y;//记录某Unit在当前Explore地图的XY位置，应当以Pixel（即960x960）记录，而非Block记录
	Map_ID Map;//记录Unit当前所在的地图
	

};