#pragma once

class Unit;

//要求每次在此处添加新技能后都在Unit.cpp中的SkillAdder中增加新的case！
enum Skill_ID//利用enum类型来枚举技能ID
{
	Skill_Example
};

class Skills
{

public:
	Skills(Skill_ID id, int level):skill_id(id),skill_level(level){}//构造技能的函数
	virtual ~Skills(){}
	virtual void InitSkill() = 0;//提供初始化接口
	virtual void UseSkill(const Unit&) = 0;//提供释放接口，技能的具体效果应当在UseSkill函数中完成

protected:
	Unit SelectedTarget;//选取所需释放技能的对象
	Skill_ID skill_id;
	int skill_level;

};

class SkillExample :public Skills
{
public:
	SkillExample(Skill_ID id, int level) :Skills(id, level) {}
	~SkillExample(){}
	void InitSkill();
	void UseSkill(const Unit&);

};