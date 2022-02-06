﻿#pragma once

class Unit;

//要求每次在此处添加新技能后都在Unit.cpp中的SkillAdder中增加新的case！
enum Skill_ID//利用enum类型来枚举技能ID
{
	Skill_Attack,//Attack为基础技能
	Skill_Example
};

class Skills
{

public:
	Skills(Skill_ID id, int level = 1, int max = 1) :skill_id(id), skill_level(level), MaxOpponent(max) {}//构造技能的函数
	virtual ~Skills(){}
	virtual int UseSkill(Unit*, int) = 0;//提供释放接口，技能的具体效果应当在UseSkill函数中完成
	Skill_ID GetSkillID();

protected:
	Unit SelectedTarget;//选取所需释放技能的对象
	Skill_ID skill_id;
	int skill_level;
	const int MaxOpponent;

};

class SkillExample :public Skills//该技能为示范技能，后续所有技能应当按照该模板编写
{
public:
	SkillExample(int lvl, int max) :Skills(Skill_Example, lvl, max) {}
	~SkillExample() {}
	int UseSkill(Unit* opponent, int number);

};

class SkillAttack :public Skills
{
public:
	SkillAttack(int lvl = 1, int max = 1) :Skills(Skill_Attack, lvl, max) {}
	~SkillAttack() {}
	int UseSkill(Unit* opponent, int number);
};