#include"total.h"

Skills* SkillAdder(Skill_ID id)//要求每次在Skills.h的enum里添加新技能后都在此处增加新的case
{
	Skills* skill = nullptr;
	switch (id)
	{
	case Skill_Example:
		skill = new SkillExample(1, 1);
		break;
	case Skill_Attack:
		skill = new SkillAttack(1, 1);
	}
	return skill;
}

Unit::Unit(int hp, int atk, int exp, int lvl, Unit_ID id, int slotnumber)//Unit的构造函数，效果为将Unit初始化；位置没有专门初始化，需要在构造之后手动设置
{
	Opponent.clear();
	Opponent.resize(5);
	OpponentNum = 0;
	MaxHP = hp;
	health = hp;
	attack = atk;
	experience = exp;
	level = lvl;
	skillpoint = 100;
	ID = id;
	name = " ";
	for (auto& item : Opponent)
		item = nullptr;
	EmptySlotNum = slotnumber;
	AddSkill(Skill_Attack);
}

void Unit::ChangeHp(int hp)
{
	health += hp;
	if (health < 0)health = 0;
	if (health > MaxHP)health = MaxHP;
}

void Unit::ChangeAtk(int atk)
{
	attack += atk;
	if (attack < 1)attack = 1;
}

void Unit::ChangeEXP(int exp)
{
	experience += exp;
}

void Unit::ChangeLvl(int lvl)
{
	level += lvl;
}

void Unit::ChangePosition(int x, int y, Map_ID map)
{
	X = x, Y = y, Map = map;
}

void Unit::ChangePosition(int x, int y)
{
	X += x, Y += y;
}

int Unit::AddSkill(Skill_ID id)
{
	if (EmptySlotNum == 0) return ERROR;//检测是否还有剩余的技能槽
	Skills* newSkill = SkillAdder(id);
	if (newSkill == nullptr) return ERROR;//检测输入id的合法性
	SkillSlot.push_back(newSkill);
	return NORMAL;
}

int Unit::RemoveSkill(Skill_ID id)
{
	if (id == Skill_Attack)return ERROR;
	for(auto& item:SkillSlot)
		if (item != nullptr && item->GetSkillID() == id)
		{
			delete item;
			item = nullptr;
			EmptySlotNum++;
			break;
		}
	return NORMAL;
}

int Unit::AddOpponent(Unit* newopponent)
{
	if (OpponentNum >= 5) return ERROR;
	Opponent[OpponentNum] = newopponent;
	OpponentNum++;
	return NORMAL;
}

int Unit::UseSkill(int SlotofSkill)
{
	if (SkillSlot[SlotofSkill] == nullptr) return ERROR;//检测选中的技能槽是否有技能
	if (skillpoint < SkillSlot[SlotofSkill]->GetSP())return ERROR;//检测选中的技能是否有足够的SP释放
	for (int i = 0; i < OpponentNum; i++)
		SkillSlot[SlotofSkill]->UseSkill(Opponent[i], this, OpponentNum);
	OpponentNum = 0;
	Opponent.clear();
	Opponent.resize(5);
	skillpoint -= SkillSlot[SlotofSkill]->GetSP();
	return NORMAL;
}