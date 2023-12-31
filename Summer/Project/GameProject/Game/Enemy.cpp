#include "Enemy.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include "Effect.h"
#include "Bullet.h"
#include "Laser.h"
#include "GameData.h"

int Enemy::m_cnt = 1;

Enemy::Enemy(const CVector2D& p, bool flip) :
	Base(eType_Enemy) {
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_img.ChangeAnimation(0);
	m_pos_old = m_pos = p;
	m_img.SetCenter(32, 32);
	//当たり判定用矩形設定
	m_rect = CRect(-32, -32, 32, 32);
	//体力の初期化
	m_hp = 1;
	//アタック番号の初期化
	m_attack_no = -1;
	//ダメージ番号の初期化
	m_damage_no = 1;
	m_flip = flip;
	m_state = eState_Idle;
}

void Enemy::StateIdle() {
	//移動量
	float move_speed = 2;
	//移動フラグ
	bool move_flag = false;

	Base* player = Base::FindObject(eType_Player);
	if (player) {
		//左移動
		if (player->m_pos.x < m_pos.x - 32) {
			//移動量を設定
			m_pos.x -= move_speed;
			//反転フラグ
			m_flip = true;
			move_flag = true;
		}
		//右移動
		if (player->m_pos.x > m_pos.x + 32) {
			//移動量を設定
			m_pos.x += move_speed;
			//反転フラグ
			m_flip = false;
			move_flag = true;
		}
		//上移動
		if (player->m_pos.y < m_pos.y - 32) {
			//移動量を設定
			m_pos.y -= move_speed;
		}
		//下移動
		if (player->m_pos.y > m_pos.y - 32) {
			//移動量を設定
			m_pos.y += move_speed;
		}
		if (player->m_pos.x > m_pos.x - 60 && player->m_pos.x < m_pos.x + 60 &&
			player->m_pos.y > m_pos.y - 55 && player->m_pos.y < m_pos.y + 55) {
			//攻撃状態へ移行
			m_state = eState_Attack;
			m_attack_no++;
		}
	}
	if (move_flag) {
		//走るアニメーション
		m_img.ChangeAnimation(eAnimRun);
	}
	else {
		//待機アニメーション
		m_img.ChangeAnimation(eAnimIdle);
	}
}

void Enemy::StateAttack() {
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-40, -0), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(40, -0), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	}
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Enemy::Update() {
	m_pos_old = m_pos;
	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
		//攻撃状態
	case eState_Attack:
		StateAttack();
		break;
	}
	m_img.UpdateAnimation();
}

void Enemy::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	//当たり判定矩形の表示
	//DrawRect();
	
}

void Enemy::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Player_Attack:
		if (Bullet* s = dynamic_cast<Bullet*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//同じ攻撃の連続ダメージ防止
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
				//同じ攻撃の連続ダメージ防止
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