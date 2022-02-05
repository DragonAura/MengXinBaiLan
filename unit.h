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
	Unit(int,std::string);//此处int确定一个Unit的技能槽数量
	virtual ~Unit(){}
	void AddSkill(Skill_ID);//给定SkillID，给Unit添加技能
	void RemoveSkill(Skill_ID);//给定SkillID，删除Unit的技能
	void UseSkill(int);//每个技能被有其槽的位置，给定slot，使用对应的技能

protected:
	int health;
	int attack;
	std::string name;
	Unit_ID ID;
	std::vector<Skills*>SkillSlot;//使用vector来记录一个Unit的技能
	int EmptySlotNum;

};

class MonsterExample :public Unit
{

};