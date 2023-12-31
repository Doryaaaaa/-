#include "EnemyM1.h"
#include "Enemy.h"

EnemyM1::EnemyM1() : Base(eType_EnemyM)
{
	m_cnt = 0;
}

void EnemyM1::Update()
{
	m_cnt--;
	if (m_cnt <= 0) {
		//X軸は12〜1800の間でランダム
		Base::Add(new Enemy(CVector2D(Utility::Rand(12.0f, 1800.0f), 0),false));
		//次の出現時間
		m_cnt = Utility::Rand(50, 70);
	}
}