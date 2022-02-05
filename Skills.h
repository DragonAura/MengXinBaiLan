﻿#pragma once

class Unit;

enum Skill_ID//利用enum类型来枚举技能ID
{
	Skill_Example
};

class Skills
{

public:
	Skills(Skill_ID id, int level):skill_id(id),skill_level(level){}//构造技能的函数
	~Skills(){}
	virtual void InitSkill() = 0;//提供初始化接口
	virtual void UseSkill() = 0;//提供释放接口

protected:
	virtual Unit SelectedTarget() = 0;//选取所需释放技能的对象
	Skill_ID skill_id;
	int skill_level;

};

class SkillExample :public Skills
{
public:
	SkillExample(Skill_ID id, int level) :Skills(id, level) {}
	~SkillExample() {}
	void InitSkill();
	void UseSkill();

protected:
	Unit SelectedTarget();
};