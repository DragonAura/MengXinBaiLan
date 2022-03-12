#include"total.h"

Skills* SkillAdder(Skill_ID id)//要求每次在Skills.h的enum里添加新技能后都在此处增加新的case
{
	Skills* skill = nullptr;
	switch (id)
	{
	case Skill_Attack:
		skill = new SkillAttack(1, 1);
	}
	return skill;
}

Unit::Unit(int hp, int atk, int exp, int lvl, Unit_ID id, int slotnumber,int sizex,int sizey)//Unit的构造函数，效果为将Unit初始化；位置没有专门初始化，需要在构造之后手动设置
{
	Opponent.clear();
	OpponentNum = 0;
	MaxHP = hp;
	health = hp;
	attack = atk;
	MaxEXP = exp;
	experience = 0;
	level = lvl;
	skillpoint = 100;
	ID = id;
	name = " ";
	SizeX = sizex;
	SizeY = sizey;
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
	if (experience < 0)experience = 0;
}

bool Unit::LevelUp()
{
	if (experience >= MaxEXP)
	{
		experience -= MaxEXP;
		MaxEXP += 20;
		attack += 1;
		MaxHP += 20;
		health = MaxHP;
		return true;
	}
	else return false;
}

void Unit::ChangePosition(int x, int y, Map_ID map)
{
	X = x, Y = y, Map = map;
}

void Unit::ChangePosition(int x, int y)
{
	X += x, Y += y;
}

bool Unit::AddSkill(Skill_ID id)
{
	if (EmptySlotNum == 0) return false;//检测是否还有剩余的技能槽
	Skills* newSkill = SkillAdder(id);
	if (newSkill == nullptr) return false;//检测输入id的合法性
	SkillSlot.push_back(newSkill);
	return true;
}

bool Unit::RemoveSkill(Skill_ID id)
{
	if (id == Skill_Attack)return false;
	std::vector<Unit*>::iterator mark = Opponent.end()+1;
	for (auto it = Opponent.begin(); it != Opponent.end(); it++)
		if ((*it)->GetID() == id)
		{
			mark = it;
			break;
		}
	if (mark != Opponent.end() + 1)
		Opponent.erase(mark);
	return true;
}

bool Unit::AddOpponent(Unit* newopponent)
{
	if (OpponentNum >= 5) return false;
	Opponent.push_back(newopponent);
	OpponentNum++;
	return true;
}

bool Unit::RemoveOpponent(Unit* opponent)
{
	bool test = false;
	auto mark = Opponent.end();
	for (auto it = Opponent.begin(); it != Opponent.end(); it++)
	{
		if ((*it)->GetName() == opponent->GetName())
		{
			mark = it;
			test = true;
			break;
		}
	}
	if (test == true)
	{
		Opponent.erase(mark);
		OpponentNum--;
	}
	return test;
}

bool Unit::testOpp(int slot)
{
	return SkillSlot[slot]->MaxOpp() > OpponentNum ? true : false;
}

bool Unit::UseSkill(int SlotofSkill)
{
	if (SlotofSkill > SkillSlot.size()) return false;//检测选中的技能槽是否有技能
	if (skillpoint < SkillSlot[SlotofSkill]->GetSP())return false;//检测选中的技能是否有足够的SP释放
	LastSkill = SkillSlot[SlotofSkill];
	LastOpponent = Opponent;
	for (auto& item : Opponent)
		SkillSlot[SlotofSkill]->UseSkill(item, this, OpponentNum);
	OpponentNum = 0;
	Opponent.clear();
	skillpoint -= SkillSlot[SlotofSkill]->GetSP();
	return true;
}