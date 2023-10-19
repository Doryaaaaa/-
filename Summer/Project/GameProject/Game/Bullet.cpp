#include "Bullet.h"
#include "Player.h"
#include "GameData.h"

Bullet::Bullet(const CVector2D& pos, bool flip, int type, int attack_no,float a) :Base(type) {
	//�摜����
	m_img = COPY_RESOURCE("Bullet", CImage);
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(32, 32);
	//���S�ʒu�ݒ�
	m_img.SetCenter(16, 16);
	//�����蔻��p��`
	m_rect = CRect(-16, -16, 16, 16);
	//�U���ԍ�
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