#include"total.h"

Skills* SkillAdder(Skill_ID id)//要求每次在Skills.h的enum里添加新技能后都在此处增加新的case
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

Unit::Unit(int slotnumber, char* namestring)//Unit的构造函数，效果为将Unit的技能槽清空，
{
	SkillSlot.clear();
	SkillSlot.resize(slotnumber);
	experience = 0;
	level = 1;
	for (auto& item : SkillSlot)
		item = nullptr;
	EmptySlotNum = slotnumber;
	name = namestring;
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

int Unit::UseSkill(int SlotofSkill, Unit& opponent)
{
	if (SkillSlot[SlotofSkill] == nullptr) return ERROR;
	SkillSlot[SlotofSkill]->UseSkill(opponent);
}