#pragma once

enum Skill_ID;

enum Unit_ID//利用enum类型来枚举单位（怪物，玩家etc）ID
{
	Player,
	Monster_Example
};

Skills* SkillAdder(Skill_ID);//通过该函数返回一个技能指针

class Unit
{
	
public:

	Unit() {}
	Unit(int,char*);//此处int确定一个Unit的技能槽数量
	virtual ~Unit(){}

//技能相关的函数
	int AddSkill(Skill_ID id);//给定SkillID，给Unit添加技能，返回值int起到判断是否成功增加的作用
	void RemoveSkill(Skill_ID id);//给定SkillID，删除Unit的技能
	int UseSkill(int slot);//每个技能被有其槽的位置，给定slot，使用对应的技能
	int AddOpponent(Unit* opponent);//释放技能之前要求先添加对象

//更改数据相关的函数接口
	void ChangeHp(int hp);//提供更改内部数据的接口，其中hp、atk可为负
	void ChangeAtk(int atk);
	void ChangeEXP(int exp);
	void ChangeLvl(int lvl);

protected:
	int health;//要求health至多为100
	int attack;//要求attack至少为1
	int experience;
	int level;
	char* name;
	Unit_ID ID;
	std::vector<Skills*>SkillSlot;//使用vector来记录一个Unit的技能
	std::vector<Unit*>Opponent;//使用vector记录某次技能所锁定的对象
	int EmptySlotNum;
	int OpponentNum;

};

class MonsterExample :public Unit
{

};