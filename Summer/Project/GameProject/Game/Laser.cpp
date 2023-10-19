#include "Laser.h"
#include "Player.h"
#include "GameData.h"

Laser::Laser(const CVector2D& pos, bool flip, int type, int attack_no, float a, bool flip2) :Base(type) {
	//�摜����
	m_img = COPY_RESOURCE("Laser", CImage);
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(32, 1200);
	//���S�ʒu�ݒ�
	m_img.SetCenter(16, 600);
	//�����蔻��p��`
	if (abs(a) == DtoR(90)) {
		m_rect = CRect(-600, -16, 600, 16);
	}
	else {
		m_rect = CRect(-16, -600, 16, 600);
	}
	//�Đ��A�j���[�V�����ݒ�i�񃋁[�v�j
	m_img.ChangeAnimation(0, false);
	//�U���ԍ�
	m_attack_no = attack_no;
	//m_vec = CVector2D(sin(a), cos(a));
	m_flip2 = flip;
	m_img.SetAng(a);
}

void Laser::Update() {
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�A�j���[�V�����I���`�F�b�N
	if (m_img.CheckAnimationEnd()) {
		//�G�t�F�N�g���폜
		SetKill();
	}
}

void Laser::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipV(m_flip2);
	m_img.Draw();
	//DrawRect();
}