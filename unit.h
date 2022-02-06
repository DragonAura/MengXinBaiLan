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
	friend class Skills;//方便技能对Unit的health和attack进行调整修改

public:
	Unit() {}
	Unit(int,char*);//此处int确定一个Unit的技能槽数量
	virtual ~Unit(){}
	int AddSkill(Skill_ID);//给定SkillID，给Unit添加技能，返回值int起到判断是否成功增加的作用
	void RemoveSkill(Skill_ID);//给定SkillID，删除Unit的技能
	int UseSkill(int,Unit&);//每个技能被有其槽的位置，给定slot，使用对应的技能

protected:
	int health;
	int attack;
	int experience;
	int level;
	char* name;
	Unit_ID ID;
	std::vector<Skills*>SkillSlot;//使用vector来记录一个Unit的技能
	int EmptySlotNum;

};

class MonsterExample :public Unit
{

};