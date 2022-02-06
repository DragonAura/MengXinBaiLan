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

Unit::Unit(int slotnumber, char* namestring)//Unit的构造函数，效果为将Unit的技能槽清空，
{
	SkillSlot.clear();
	SkillSlot.resize(slotnumber);
	Opponent.clear();
	Opponent.resize(5);
	OpponentNum = 0;
	experience = 0;
	level = 1;
	for (auto& item : SkillSlot)
		item = nullptr;
	for (auto& item : Opponent)
		item = nullptr;
	EmptySlotNum = slotnumber;
	name = namestring;
}

void Unit::ChangeHp(int hp)
{
	health += hp;
	if (health < 0)health = 0;
	if (health > 100)health = 100;
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

int Unit::AddSkill(Skill_ID id)
{
	if (EmptySlotNum == 0) return ERROR;//防止出现未知错误
	Skills* newSkill = SkillAdder(id);
	if (newSkill == nullptr) return ERROR;//检测输入id的合法性
	for (auto& item : SkillSlot)
		if (item == nullptr)
		{
			item = newSkill;
			break;
		}
	return NORMAL;
}

void Unit::RemoveSkill(Skill_ID id)
{
	for(auto& item:SkillSlot)
		if (item != nullptr && item->GetSkillID() == id)
		{
			delete item;
			item = nullptr;
			EmptySlotNum++;
			break;
		}
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
	if (SkillSlot[SlotofSkill] == nullptr) return ERROR;
	for (int i = 0; i < OpponentNum; i++)
		SkillSlot[SlotofSkill]->UseSkill(Opponent[i], OpponentNum);
	OpponentNum = 0;
	Opponent.clear();
	for (auto& item : Opponent)
		item = nullptr;
	return NORMAL;
}