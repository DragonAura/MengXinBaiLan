#pragma once

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
	virtual void UseSkill(Unit* opponent, Unit* user, int number) = 0;//提供释放接口，技能的具体效果应当在UseSkill函数中完成
	Skill_ID GetSkillID();
	int GetSP() { return SkillPoint; }
	QString GetName() { return name; }
	int MaxOpp() { return MaxOpponent; }

protected:
	Unit SelectedTarget;//选取所需释放技能的对象
	Skill_ID skill_id;
	int skill_level;
	const int MaxOpponent;
	int SkillPoint;//记录释放技能需要的技能点数，如果是类似于攻击之类回复技能点数的手段，则SkillPoint应为负
	QString name;

};


class SkillAttack :public Skills
{
public:
	SkillAttack(int lvl = 1, int max = 1) :Skills(Skill_Attack, lvl, max) { SkillPoint = -10; name = "Attack"; }
	~SkillAttack() {}
	void UseSkill(Unit* opponent, Unit* user, int number);
};