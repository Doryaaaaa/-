#include "Player.h"
#include "AnimData.h"
#include "Bullet.h"
#include "Slash.h"
#include "Slash_Big.h"
#include "Effect.h"
#include "Laser.h"

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//画像複製
	m_img = COPY_RESOURCE("Player", CImage);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old = m_pos = p;
	//中心位置設定
	m_img.SetCenter(32, 32);
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;
	//当たり判定用矩形
	m_rect = CRect(-32, -32, 32, 32);
	//ヒットポイント
	m_hp = 10;
}

void Player::StateIdle() {
	//移動量
	const float move_speed = 6;
	//移動フラグ
	bool move_flag = false;
	//左移動
	if (HOLD(CInput::eLeft)) {
		//移動量を設定
		m_pos.x += -move_speed;
		//反転フラグ
		m_flip = true;
		move_flag = true;
	}
	//右移動
	if (HOLD(CInput::eRight)) {
		//移動量を設定
		m_pos.x += move_speed;
		//反転フラグ
		m_flip = false;
		move_flag = true;
	}
	//上移動
	if (HOLD(CInput::eUp)) {
		//移動量を設定
		m_pos.y += -move_speed;
		move_flag = true;
	}
	//下移動
	if (HOLD(CInput::eDown)) {
		//移動量を設定
		m_pos.y += move_speed;
		move_flag = true;
	}
	//攻撃
	if (PUSH(CInput::eButton1)) {
		//攻撃状態へ移行
		m_state = eState_Attack;
		m_attack_no++;
	}
	if (PUSH(CInput::eButton2)) {
		//攻撃2待機状態
		m_state = eState_Attack2_standby;
	}
	//地面にいるなら
	else
	{
		//移動中なら
		if (move_flag) {
			//走るアニメーション
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			//待機アニメーション
			m_img.ChangeAnimation(eAnimIdle);
		}
	}
}

void Player::StateAttack() {
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack01, false);
	//移動量
	const float move_speed = 1;
	//移動フラグ
	bool move_flag = false;
	//左移動
	if (HOLD(CInput::eLeft)) {
		//移動量を設定
		m_pos.x += -move_speed;
		//反転フラグ
		m_flip = true;
		move_flag = true;
	}
	//右移動
	if (HOLD(CInput::eRight)) {
		//移動量を設定
		m_pos.x += move_speed;
		//反転フラグ
		m_flip = false;
		move_flag = true;
	}
	//上移動
	if (HOLD(CInput::eUp)) {
		//移動量を設定
		m_pos.y += -move_speed;
		move_flag = true;
	}
	//下移動
	if (HOLD(CInput::eDown)) {
		//移動量を設定
		m_pos.y += move_speed;
		move_flag = true;
	}
	//0番目のパターン
	if (m_img.GetIndex() == 0) {
		//上方向の弾
	    Base::Add(new Bullet(m_pos + CVector2D(0, -64), m_flip, eType_Player_Attack, m_attack_no,DtoR(180)));
		//右方向の弾
		Base::Add(new Bullet(m_pos + CVector2D(64, 0), m_flip, eType_Player_Attack, m_attack_no, DtoR(90)));
		//左方向の弾
		Base::Add(new Bullet(m_pos + CVector2D(-64, 0), m_flip, eType_Player_Attack, m_attack_no, DtoR(270)));
		//下方向の玉
		Base::Add(new Bullet(m_pos + CVector2D(0, 64), m_flip, eType_Player_Attack, m_attack_no, DtoR(0)));
		//右上方向の弾
		Base::Add(new Bullet(m_pos + CVector2D(32, -32), m_flip, eType_Player_Attack, m_attack_no, DtoR(130)));
		//右下方向の弾
		Base::Add(new Bullet(m_pos + CVector2D(32, 32), m_flip, eType_Player_Attack, m_attack_no, DtoR(50)));
		//左上方向の弾
		Base::Add(new Bullet(m_pos + CVector2D(-32, -32), m_flip, eType_Player_Attack, m_attack_no, DtoR(220)));
		//左下方向の弾
		Base::Add(new Bullet(m_pos + CVector2D(-32, 32), m_flip, eType_Player_Attack, m_attack_no, DtoR(310)));
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) { 
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_standby() {
	//攻撃待機アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack02, true);
	//上を押したら
	if (PUSH(CInput::eUp)) {
		m_state = eState_Attack2_Up;
		m_attack_no++;
	}
	//右を押したら
	else if (PUSH(CInput::eRight)) {
		m_state = eState_Attack2_Right;
		m_attack_no++;
	}
	//左を押したら
	else if (PUSH(CInput::eLeft)) {
		m_state = eState_Attack2_Left;
		m_attack_no++;
	}
	//下を押したら
	else if (PUSH(CInput::eDown)) {
		m_state = eState_Attack2_Down;
		m_attack_no++;
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_Up(){
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack02End, false);
	//0番目のパターン
	if (m_img.GetIndex() == 0) {
		Base::Add(new Laser(m_pos + CVector2D(0, -640), true, eType_Player_Attack, m_attack_no, DtoR(180),false));
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_Right() {
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack02End, false);
	//0番目のパターン
	if (m_img.GetIndex() == 0) {
		Base::Add(new Laser(m_pos + CVector2D(640, 0), true, eType_Player_Attack, m_attack_no, DtoR(90),false));
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_Left() {
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack02End, false);
	//0番目のパターン
	if (m_img.GetIndex() == 0) {
		Base::Add(new Laser(m_pos + CVector2D(-640, 0), true, eType_Player_Attack, m_attack_no, DtoR(-90),false));
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

void Player::StateAttack2_Down() {
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack02End, false);
	//0番目のパターン
	if (m_img.GetIndex() == 0) {
		Base::Add(new Laser(m_pos + CVector2D(0, 620), true, eType_Player_Attack, m_attack_no, DtoR(0),true));
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
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
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
		//攻撃状態
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
		//ダウン状態
	case eState_Down:
		StateDown();
		break;
	}
	//アニメーション更新
	m_img.UpdateAnimation();
}

void Player::Draw() {
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
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