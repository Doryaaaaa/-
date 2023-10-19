#include "Enemy.h"
#include "Enemy_RareM.h"
#include "Enemy_Rare.h"
#include "GameData.h"

Enemy_RareM::Enemy_RareM() : Base(eType_EnemyM)
{
	flag = 0;
}

void Enemy_RareM::Update()
{
	if (GameData::s_score != 0) {
		if (GameData::s_score % 5000 == 0) {
			if (flag == 0) {
				Base::Add(new Enemy_Rare(CVector2D(0, Utility::Rand(12.0f, 1000.0f)), false));
				flag = 1;
			}
		}
		else {
			flag = 0;
		}
	}
}