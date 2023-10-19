#pragma once
#include "../Base/Base.h"

class Enemy_Rare : public Base {
private:
	enum {
		eState_Idle,
		eState_Attack,
	};
	int m_state;
	CImage m_img;
	bool m_flip;
	//‘Ì—Í
	int m_hp;
	//UŒ‚”Ô†
	int m_attack_no;
	//ƒ_ƒ[ƒW”Ô†
	int m_damage_no;
	bool m_is_ground;
	void StateIdle();
	void StateAttack();
public:
	Enemy_Rare(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	int m_cnt;
	int Getm_cnt() {
		return m_cnt;
	}
};
