#pragma once
#include "../Base/Base.h"

class Enemy : public Base {
private:
	enum {
		eState_Idle,
		eState_Attack,
	};
	int m_state;
	CImage m_img;
	bool m_flip;
	//体力
	int m_hp;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;
	bool m_is_ground;
	void StateIdle();
	void StateAttack();
public:
	Enemy(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	static int m_cnt;
	int Getm_cnt() {
		return m_cnt;
	}
};