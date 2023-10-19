#pragma once
#include "../Base/Base.h"

class Player : public Base {
private:
	//���
	enum {
		eState_Idle,
		eState_Attack,
		eState_Attack2_standby,
		eState_Attack2_Up,
		eState_Attack2_Right,
		eState_Attack2_Left,
		eState_Attack2_Down,
		eState_Down,
	};
	//��ԕϐ�
	int m_state;
	CImage m_img;
	bool m_flip;
	//�U���ԍ�
	int m_attack_no;
	//�_���[�W�ԍ�
	int m_damage_no;
	//�q�b�g�|�C���g
	int m_hp;
	//�e��Ԃł̋���
	void StateIdle();
	void StateAttack();
	void StateAttack2_standby();
	void StateAttack2_Up();
	void StateAttack2_Right();
	void StateAttack2_Left();
	void StateAttack2_Down();
	void StateDown();
public:
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};