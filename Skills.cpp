#include"total.h"

Skill_ID Skills::GetSkillID()
{
	return skill_id;
}

int SkillExample::UseSkill(Unit* opponent, int opponentnumber)
{
	if (opponentnumber > MaxOpponent)return ERROR;//要求写出的任何Skills都应在第一句加上这一条
}
