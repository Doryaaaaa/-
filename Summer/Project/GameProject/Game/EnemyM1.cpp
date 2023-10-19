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
		//X����12�`1800�̊ԂŃ����_��
		Base::Add(new Enemy(CVector2D(Utility::Rand(12.0f, 1800.0f), 0),false));
		//���̏o������
		m_cnt = Utility::Rand(50, 70);
	}
}