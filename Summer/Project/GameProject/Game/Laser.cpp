#include "Laser.h"
#include "Player.h"
#include "GameData.h"

Laser::Laser(const CVector2D& pos, bool flip, int type, int attack_no, float a, bool flip2) :Base(type) {
	//画像複製
	m_img = COPY_RESOURCE("Laser", CImage);
	//座標設定
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(32, 1200);
	//中心位置設定
	m_img.SetCenter(16, 600);
	//当たり判定用矩形
	if (abs(a) == DtoR(90)) {
		m_rect = CRect(-600, -16, 600, 16);
	}
	else {
		m_rect = CRect(-16, -600, 16, 600);
	}
	//再生アニメーション設定（非ループ）
	m_img.ChangeAnimation(0, false);
	//攻撃番号
	m_attack_no = attack_no;
	//m_vec = CVector2D(sin(a), cos(a));
	m_flip2 = flip;
	m_img.SetAng(a);
}

void Laser::Update() {
	//アニメーション更新
	m_img.UpdateAnimation();
	//アニメーション終了チェック
	if (m_img.CheckAnimationEnd()) {
		//エフェクトを削除
		SetKill();
	}
}

void Laser::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipV(m_flip2);
	m_img.Draw();
	//DrawRect();
}