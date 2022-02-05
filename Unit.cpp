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