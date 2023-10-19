#include "Enemy_Rare.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash_Big.h"
#include "Effect.h"
#include "Bullet.h"
#include "Laser.h"
#include "GameData.h"

Enemy_Rare::Enemy_Rare(const CVector2D& p, bool flip) :
	Base(eType_Enemy) {
	m_img = COPY_RESOURCE("Enemy_Rare", CImage);
	m_img.SetSize(192, 192);
	m_img.ChangeAnimation(0);
	m_pos_old = m_pos = p;
	m_img.SetCenter(96, 96);
	//�����蔻��p��`�ݒ�
	m_rect = CRect(-96, -96, 96, 96);
	//�̗͂̏�����
	m_hp = 10;
	//�A�^�b�N�ԍ��̏�����
	m_attack_no = -1;
	//�_���[�W�ԍ��̏�����
	m_damage_no = 1;
	m_flip = flip;
	m_state = eState_Idle;
	m_cnt = 0;
}

void Enemy_Rare::StateIdle() {
	//�ړ���
	float move_speed = 1;
	//�ړ��t���O
	bool move_flag = false;

	Base* player = Base::FindObject(eType_Player);
	if (player) {
		//���ړ�
		if (player->m_pos.x < m_pos.x - 32) {
			//�ړ��ʂ�ݒ�
			m_pos.x -= move_speed;
			//���]�t���O
			m_flip = true;
			move_flag = true;
		}
		//�E�ړ�
		if (player->m_pos.x > m_pos.x + 32) {
			//�ړ��ʂ�ݒ�
			m_pos.x += move_speed;
			//���]�t���O
			m_flip = false;
			move_flag = true;
		}
		//��ړ�
		if (player->m_pos.y < m_pos.y - 32) {
			//�ړ��ʂ�ݒ�
			m_pos.y -= move_speed;
		}
		//���ړ�
		if (player->m_pos.y > m_pos.y - 32) {
			//�ړ��ʂ�ݒ�
			m_pos.y += move_speed;
		}
		if (player->m_pos.x > m_pos.x - 90 && player->m_pos.x < m_pos.x + 90 &&
			player->m_pos.y > m_pos.y - 90 && player->m_pos.y < m_pos.y + 90 ) {
			//�U����Ԃֈڍs
			m_state = eState_Attack;
			m_attack_no++;
		}
	}
	if (move_flag) {
		//����A�j���[�V����
		m_img.ChangeAnimation(eAnimRun);
	}
	else {
		//�ҋ@�A�j���[�V����
		m_img.ChangeAnimation(eAnimIdle);
	}
}

void Enemy_Rare::StateAttack() {
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash_Big(m_pos + CVector2D(-100, 0), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash_Big(m_pos + CVector2D(100, 0), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	}
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Enemy_Rare::Update() {
	m_pos_old = m_pos;
	switch (m_state) {
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;
		//�U�����
	case eState_Attack:
		StateAttack();
		break;
	}
	m_img.UpdateAnimation();
}

void Enemy_Rare::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	//�����蔻���`�̕\��
	//DrawRect();

}

void Enemy_Rare::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Player_Attack:
		if (Bullet* s = dynamic_cast<Bullet*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//�����U���̘A���_���[�W�h�~
				m_damage_no = s->GetAttackNo();
				m_hp -= 1;
				if (m_hp <= 0) {
					m_kill = true;
					m_cnt += 100;
					GameData::s_score += 100;
				}
			}
		}
		if (Laser* s = dynamic_cast<Laser*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//�����U���̘A���_���[�W�h�~
				m_damage_no = s->GetAttackNo();
				m_hp -= 1;
				if (m_hp <= 0) {
					m_kill = true;
					m_cnt += 100;
					GameData::s_score += 100;
				}
			}
		}
		break;
	}
}