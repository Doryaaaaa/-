#include "Player.h"
#include "AnimData.h"
#include "Bullet.h"
#include "Slash.h"
#include "Slash_Big.h"
#include "Effect.h"
#include "Laser.h"

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//�摜����
	m_img = COPY_RESOURCE("Player", CImage);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	//���S�ʒu�ݒ�
	m_img.SetCenter(32, 32);
	//���]�t���O
	m_flip = flip;
	//�ʏ��Ԃ�
	m_state = eState_Idle;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
	m_damage_no = -1;
	//�����蔻��p��`
	m_rect = CRect(-32, -32, 32, 32);
	//�q�b�g�|�C���g
	m_hp = 10;
}

void Player::StateIdle() {
	//�ړ���
	const float move_speed = 6;
	//�ړ��t���O
	bool move_flag = false;
	//���ړ�
	if (HOLD(CInput::eLeft)) {
		//�ړ��ʂ�ݒ�
		m_pos.x += -move_speed;
		//���]�t���O
		m_flip = true;
		move_flag = true;
	}
	//�E�ړ�
	if (HOLD(CInput::eRight)) {
		//�ړ��ʂ�ݒ�
		m_pos.x += move_speed;
		//���]�t���O
		m_flip = false;
		move_flag = true;
	}
	//��ړ�
	if (HOLD(CInput::eUp)) {
		//�ړ��ʂ�ݒ�
		m_pos.y += -move_speed;
		move_flag = true;
	}
	//���ړ�
	if (HOLD(CInput::eDown)) {
		//�ړ��ʂ�ݒ�
		m_pos.y += move_speed;
		move_flag = true;
	}
	//�U��
	if (PUSH(CInput::eButton1)) {
		//�U����Ԃֈڍs
		m_state = eState_Attack;
		m_attack_no++;
	}
	if (PUSH(CInput::eButton2)) {
		//�U��2�ҋ@���
		m_state = eState_Attack2_standby;
	}
	//�n�ʂɂ���Ȃ�
	else
	{
		//�ړ����Ȃ�
		if (move_flag) {
			//����A�j���[�V����
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			//�ҋ@�A�j���[�V����
			m_img.ChangeAnimation(eAnimIdle);
		}
	}
}

void Player::StateAttack() {
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack01, false);
	//�ړ���
	const float move_speed = 1;
	//�ړ��t���O
	bool move_flag = false;
	//���ړ�
	if (HOLD(CInput::eLeft)) {
		//�ړ��ʂ�ݒ�
		m_pos.x += -move_speed;
		//���]�t���O
		m_flip = true;
		move_flag = true;
	}
	//�E�ړ�
	if (HOLD(CInput::eRight)) {
		//�ړ��ʂ�ݒ�
		m_pos.x += move_speed;
		//���]�t���O
		m_flip = false;
		move_flag = true;
	}
	//��ړ�
	if (HOLD(CInput::eUp)) {
		//�ړ��ʂ�ݒ�
		m_pos.y += -move_speed;
		move_flag = true;
	}
	//���ړ�
	if (HOLD(CInput::eDown)) {
		//�ړ��ʂ�ݒ�
		m_pos.y += move_speed;
		move_flag = true;
	}
	//0�Ԗڂ̃p�^�[��
	if (m_img.GetIndex() == 0) {
		//������̒e
	    Base::Add(new Bullet(m_pos + CVector2D(0, -64), m_flip, eType_Player_Attack, m_attack_no,DtoR(180)));
		//�E�����̒e
		Base::Add(new Bullet(m_pos + CVector2D(64, 0), m_flip, eType_Player_Attack, m_attack_no, DtoR(90)));
		//�������̒e
		Base::Add(new Bullet(m_pos + CVector2D(-64, 0), m_flip, eType_Player_Attack, m_attack_no, DtoR(270)));
		//�������̋�
		Base::Add(new Bullet(m_pos + CVector2D(0, 64), m_flip, eType_Player_Attack, m_attack_no, DtoR(0)));
		//�E������̒e
		Base::Add(new Bullet(m_pos + CVector2D(32, -32), m_flip, eType_Player_Attack, m_attack_no, DtoR(130)));
		//�E�������̒e
		Base::Add(new Bullet(m_pos + CVector2D(32, 32), m_flip, eType_Player_Attack, m_attack_no, DtoR(50)));
		//��������̒e
		Base::Add(new Bullet(m_pos + CVector2D(-32, -32), m_flip, eType_Player_Attack, m_attack_no, DtoR(220)));
		//���������̒e
		Base::Add(new Bullet(m_pos + CVector2D(-32, 32), m_flip, eType_Player_Attack, m_attack_no, DtoR(310)));
	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) { 
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_standby() {
	//�U���ҋ@�A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack02, true);
	//�����������
	if (PUSH(CInput::eUp)) {
		m_state = eState_Attack2_Up;
		m_attack_no++;
	}
	//�E����������
	else if (PUSH(CInput::eRight)) {
		m_state = eState_Attack2_Right;
		m_attack_no++;
	}
	//������������
	else if (PUSH(CInput::eLeft)) {
		m_state = eState_Attack2_Left;
		m_attack_no++;
	}
	//������������
	else if (PUSH(CInput::eDown)) {
		m_state = eState_Attack2_Down;
		m_attack_no++;
	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_Up(){
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack02End, false);
	//0�Ԗڂ̃p�^�[��
	if (m_img.GetIndex() == 0) {
		Base::Add(new Laser(m_pos + CVector2D(0, -640), true, eType_Player_Attack, m_attack_no, DtoR(180),false));
	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_Right() {
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack02End, false);
	//0�Ԗڂ̃p�^�[��
	if (m_img.GetIndex() == 0) {
		Base::Add(new Laser(m_pos + CVector2D(640, 0), true, eType_Player_Attack, m_attack_no, DtoR(90),false));
	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_Left() {
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack02End, false);
	//0�Ԗڂ̃p�^�[��
	if (m_img.GetIndex() == 0) {
		Base::Add(new Laser(m_pos + CVector2D(-640, 0), true, eType_Player_Attack, m_attack_no, DtoR(-90),false));
	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_Down() {
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack02End, false);
	//0�Ԗڂ̃p�^�[��
	if (m_img.GetIndex() == 0) {
		Base::Add(new Laser(m_pos + CVector2D(0, 620), true, eType_Player_Attack, m_attack_no, DtoR(0),true));
	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}

void Player::StateDown() {
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
	}
}


void Player::Update() {
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
	case eState_Attack2_standby:
		StateAttack2_standby();
		break;
	case eState_Attack2_Up:
		StateAttack2_Up();
		break;
	case eState_Attack2_Right:
		StateAttack2_Right();
		break;
	case eState_Attack2_Left:
		StateAttack2_Left();
		break;
	case eState_Attack2_Down:
		StateAttack2_Down();
		break;
		//�_�E�����
	case eState_Down:
		StateDown();
		break;
	}
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
}

void Player::Draw() {
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	//DrawRect();
}

void Player::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Enemy_Attack:
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				m_damage_no = s->GetAttackNo();
				m_hp -= 1;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
			}
		}
		else if(Slash_Big* s = dynamic_cast<Slash_Big*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				m_damage_no = s->GetAttackNo();
				m_hp -= 2;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
			}
		}
		break;
	}
}