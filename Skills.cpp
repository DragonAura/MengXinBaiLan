﻿#include"total.h"

Skill_ID Skills::GetSkillID()
{
	return skill_id;
}

int SkillExample::UseSkill(Unit* opponent, int opponentnumber)
{
	if (opponentnumber > MaxOpponent)return ERROR;//要求写出的任何Skills都应在第一句加上这一条
	opponent->ChangeHp(-1);//示例技能的效果为对所选中的对象造成一点伤害
	return NORMAL;
}

int SkillAttack::UseSkill(Unit* opponent, int opponentnumber)
{
	if (opponentnumber > MaxOpponent)return ERROR;
	srand((unsigned)time(NULL));
	int damage_basic = 3 + skill_level * 2;
	int damage_rand = 1 + damage_basic * 0.2;
	int damage = damage_basic - damage_rand + (rand() % (2 * damage_rand + 1));//随机数算法，可以取到[damage_basic-damage_rand , damage_basic+damage_rand]的随机数
	opponent->ChangeHp(-damage);
	return NORMAL;
}