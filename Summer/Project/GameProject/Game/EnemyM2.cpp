#include "EnemyM2.h"
#include "Enemy.h"

EnemyM2::EnemyM2() : Base(eType_EnemyM)
{
	m_cnt = 0;
}

void EnemyM2::Update()
{
	m_cnt--;
	if (m_cnt <= 0) {
		//XŽ²‚Í12`1800‚ÌŠÔ‚Åƒ‰ƒ“ƒ_ƒ€
		Base::Add(new Enemy(CVector2D(Utility::Rand(12.0f, 1800.0f),1000), false));
		//ŽŸ‚ÌoŒ»ŽžŠÔ
		m_cnt = Utility::Rand(50, 70);
	}
}