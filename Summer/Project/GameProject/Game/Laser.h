#pragma once
#include "../Base/Base.h"

class Laser : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	//攻撃番号
	int m_attack_no;
	int move_speed;
	int a;
	bool m_flip2;
public:
	Laser(const CVector2D& pos, bool flip, int type, int attack_no, float a, bool flip2);
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
	int Geta() {
		return a;
	}
};
