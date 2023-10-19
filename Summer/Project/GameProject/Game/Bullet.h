#pragma once
#include "../Base/Base.h"

class Bullet : public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;
	//�U���ԍ�
	int m_attack_no;
	int move_speed;
	int a;
public:
	Bullet(const CVector2D& pos, bool flip, int type, int attack_no,float a);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
	int Geta() {
		return a;
	}
};
