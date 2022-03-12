#include"total.h"

Skill_ID Skills::GetSkillID()
{
	return skill_id;
}

bool SkillAttack::UseSkill(Unit* opponent, Unit* user, int opponentnumber)
{
	if (opponentnumber > MaxOpponent)return false;
	srand((unsigned)time(NULL));
	int damage_basic = user->GetATK() + skill_level * 2;
	int damage_rand = skill_level;
	int damage = damage_basic - damage_rand + (rand() % (2 * damage_rand + 1));//随机数算法，可以取到[damage_basic-damage_rand , damage_basic+damage_rand]的随机数
	opponent->ChangeHp(-damage);
	return true;
}