#include"total.h"

Skills* SkillAdder(Skill_ID id)//要求每次在Skills.h的enum里添加新技能后都在此处增加新的case！
{
	Skills* skill = nullptr;
	switch (id)
	{
	case Skill_Example:
		skill = new SkillExample(Skill_Example, 1);
		break;
	}
	return skill;
}

Unit::Unit(int slotnumber, std::string namestring)//Unit的构造函数，效果为将Unit的技能槽清空，
{
	SkillSlot.clear();
	SkillSlot.resize(slotnumber);
	for (auto& item : SkillSlot)
		item = nullptr;
	EmptySlotNum = slotnumber;
	name = namestring;
}

void Unit::AddSkill(Skill_ID id)
{

}

void Unit::RemoveSkill(Skill_ID id)
{

}

void Unit::UseSkill(int SlotofSkill)
{

}