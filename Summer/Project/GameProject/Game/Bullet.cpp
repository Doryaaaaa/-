#include "Bullet.h"
#include "Player.h"
#include "GameData.h"

Bullet::Bullet(const CVector2D& pos, bool flip, int type, int attack_no,float a) :Base(type) {
	//画像複製
	m_img = COPY_RESOURCE("Bullet", CImage);
	//座標設定
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(32, 32);
	//中心位置設定
	m_img.SetCenter(16, 16);
	//当たり判定用矩形
	m_rect = CRect(-16, -16, 16, 16);
	//攻撃番号
	m_attack_no = attack_no;
	m_vec = CVector2D(sin(a), cos(a)) * 4;
}

void Bullet::Update() {
	m_pos += m_vec;

	if (m_pos.y > 950) {
		SetKill();
	}
	if (m_pos.x < 20) {
		SetKill();
	}
	if (m_pos.x > 1870) {
		SetKill();
	}
	if (m_pos.y < 0) {
		SetKill();
	}
}

void Bullet::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}

void Bullet::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Enemy:
		if(Base::CollisionRect(this, b)) {
			SetKill();
		}
		break;
	}
}