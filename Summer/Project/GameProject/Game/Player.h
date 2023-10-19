#pragma once
#include "../Base/Base.h"

class Player : public Base {
private:
	//状態
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
	//状態変数
	int m_state;
	CImage m_img;
	bool m_flip;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;
	//ヒットポイント
	int m_hp;
	//各状態での挙動
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